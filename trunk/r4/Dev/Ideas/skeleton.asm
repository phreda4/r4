format binary
use64
;-------------------------------------------------------------------------------
; DESC:     SDL defines.
;-------------------------------------------------------------------------------
SDL_INIT_VIDEO = 0x00000020
SDL_NOFRAME = 0x00000020
SDL_HWSURFACE = 0x00000001
SDL_FULLSCREEN = 0x80000000
SDL_KEYDOWN = 2
SDL_KEYUP = 3
SDLK_ESCAPE	= 27
;-------------------------------------------------------------------------------
; DESC:     Load libc function.
;-------------------------------------------------------------------------------
macro       LDLIBCF     name* {
            xor         edi,edi
            mov         rsi,g_str.#name
            call        [dlsym]
            mov         [name],rax
}
;-------------------------------------------------------------------------------
; DESC:     Load SDL function.
;-------------------------------------------------------------------------------
macro       LDSDLF      name* {
            mov         rdi,[g_libsdl]
            mov         rsi,g_str.#name
            call        [dlsym]
            mov         [name],rax
}
;-------------------------------------------------------------------------------
; DESC:     ELF header.
;-------------------------------------------------------------------------------
            org         0x400000
            db          0x7f,'ELF',2,1,1,0,0,0,0,0,0,0,0,0
            dw          2                                       ; File type - executable
            dw          62                                      ; Machine - AMD64/EM64T
            dd          1                                       ; File format version
            dq          Start                                   ; Process entry address
            dq          64                                      ; Program header table file offset
            dq          0                                       ; Section header table file offset
            dd          0                                       ; Processor-specific flags
            dw          64                                      ; Size of this header
            dw          56                                      ; Size of program header
            dw          3                                       ; Number of program headers
            dw          64                                      ; Size of section header
            dw          0                                       ; Number of section headers
            dw          0                                       ; Section header string table index
            dd          3                                       ; PT_INTERP
            dd          4                                       ; Flags - R
            dq          ELF_interp-0x400000                     ; Offset
            dq          ELF_interp,ELF_interp                   ; VirtAddr,PhysAddr
            dq          ELF_interp.SIZE,ELF_interp.SIZE         ; FileSiz,MemSiz
            dq          1                                       ; Align
            dd          2                                       ; PT_DYNAMIC
            dd          4                                       ; Flags - R
            dq          ELF_dynamic-0x400000                    ; Offset
            dq          ELF_dynamic,ELF_dynamic                 ; VirtAddr,PhysAddr
            dq          ELF_dynamic.SIZE,ELF_dynamic.SIZE       ; FileSiz,MemSiz
            dq          8                                       ; Align
            dd          1                                       ; PT_LOAD
            dd          7                                       ; Flags - RWE
            dq          0                                       ; Offset
            dq          0x400000,0x400000                       ; VirtAddr,PhysAddr
            dq          ELF_SIZE,ELF_SIZE                       ; FileSiz,MemSiz
            dq          0x100000                                ; Align
;-------------------------------------------------------------------------------
; NAME:     ComputeColor
; IN:       xmm0.xyzw   normalized x coordinate (replicated)
; IN:       xmm1.xyzw   normalized y coordinate (replicated)
; OUT:      xmm0.xyz    pixel color
;-------------------------------------------------------------------------------
ComputeColor:
            sub         rsp,8
            mov         ecx,100
.Repeat:
            sqrtps      xmm0,xmm0
            sub         ecx,1
            jnz         .Repeat
            movaps      xmm0,dqword [g_1_0]
            add         rsp,8
            ret
;-------------------------------------------------------------------------------
; NAME:     Start
; DESC:     Program entry point.
;-------------------------------------------------------------------------------
Start:
            event       equ rbp-32
            x           equ rbp-36
            y           equ rbp-40
            screen      equ rbp-48
            mov         rbp,rsp
            sub         rsp,128
            ; load SDL 1.2 library
            mov         rdi,g_str.libsdl
            mov         esi,1                                   ; RTLD_LAZY = 1
            call        [dlopen]
            mov         [g_libsdl],rax
            ; load SDL functions
            LDSDLF      SDL_Init
            LDSDLF      SDL_Quit
            LDSDLF      SDL_SetVideoMode
            LDSDLF      SDL_PollEvent
            LDSDLF      SDL_LockSurface
            LDSDLF      SDL_UnlockSurface
            LDSDLF      SDL_UpdateRect
            ; init SDL
            mov         edi,SDL_INIT_VIDEO
            call        [SDL_Init]
            mov         edi,IMG_WIDTH
            mov         esi,IMG_HEIGHT
            mov         edx,32
            mov         ecx,SDL_HWSURFACE+SDL_NOFRAME;+SDL_FULLSCREEN
            call        [SDL_SetVideoMode]
            mov         [screen],rax
            mov         rdi,rax
            call        [SDL_LockSurface]
            ; mov screen->pixels pointer to rbx
            mov         rbx,[screen]
            mov         rbx,[rbx+32]
            ; begin loops
            mov         dword [y],0
.LoopY:
            mov         dword [x],0
.LoopX:
            ; compute normalized x coordinate [-1.0 , 1.0]
            cvtsi2ss    xmm0,[x]
            divss       xmm0,[g_img_width]
            shufps      xmm0,xmm0,0x00
            subps       xmm0,dqword [g_0_5]
            addps       xmm0,xmm0
            ; compute normalized y coordinate [-1.0 , 1.0]
            cvtsi2ss    xmm1,[y]
            divss       xmm1,[g_img_height]
            shufps      xmm1,xmm1,0x00
            subps       xmm1,dqword [g_0_5]
            addps       xmm1,xmm1
            ; compute and write pixel color to the buffer
            call        ComputeColor
            ; clamp to [0.0 , 1.0]
            maxps       xmm0,dqword [g_0_0]
            minps       xmm0,dqword [g_1_0]
            ; convert from [0.0 , 1.0] to [0 , 255]
            mulps       xmm0,dqword [g_255_0]
            cvttps2dq   xmm0,xmm0
            pshufb      xmm0,dqword [g_img_conv_mask]
            ; set alpha to 0xff
            movd        eax,xmm0
            or          eax,0xff000000
            mov         [rbx],eax
            ; advance pixel pointer
            add         rbx,4
            ; continue .LoopX
            inc         dword [x]
            cmp         dword [x],IMG_WIDTH
            jne         .LoopX
            ; continue .LoopY
            inc         dword [y]
            cmp         dword [y],IMG_HEIGHT
            jne         .LoopY
            ; unlock screen surface
            mov         rdi,[screen]
            call        [SDL_UnlockSurface]
.MainLoop:
            ; process window events
.EventLoop:
            lea         rdi,[event]
            call        [SDL_PollEvent]
            test        eax,eax
            jz          .EventLoopEnd
            cmp         byte [event+0],SDL_KEYDOWN
            je          .Keydown
            cmp         byte [event+0],SDL_KEYUP
            je          .Keyup
            jmp         .EventLoop
.Keydown:
            cmp         dword [event+8],SDLK_ESCAPE
            je          .MainLoopEnd
            jmp         .EventLoop
.Keyup:
            ; process event
            jmp         .EventLoop
.EventLoopEnd:
            ; draw and update
            mov         rdi,[screen]
            xor         esi,esi
            xor         edx,edx
            xor         ecx,ecx
            xor         r8d,r8d
            call        [SDL_UpdateRect]
            jmp         .MainLoop
.MainLoopEnd:
            call        [SDL_Quit]
            ; terminate process
            mov         eax,60
            xor         edi,edi
            syscall

IMG_WIDTH=1440
IMG_HEIGHT=900
align 4
g_img_width  dd         1440.0
g_img_height dd         900.0

align 16
g_img_conv_mask db      8,4,0,12,12 dup 0x80
g_0_0       dd          4 dup 0.0
g_0_5       dd          4 dup 0.5
g_1_0       dd          4 dup 1.0
g_255_0     dd          4 dup 255.0

align 8
g_libsdl    dq          0
; libc functions
dlopen      dq          0
dlsym       dq          0
; SDL functions
SDL_Init    dq          0
SDL_Quit    dq          0
SDL_SetVideoMode\
            dq          0
SDL_PollEvent\
            dq          0
SDL_LockSurface\
            dq          0
SDL_UnlockSurface\
            dq          0
SDL_UpdateRect\
            dq          0

align 1
g_str:
.libsdl     db          'libSDL-1.2.so.0',0
.SDL_Init   db          'SDL_Init',0 
.SDL_Quit   db          'SDL_Quit',0
.SDL_SetVideoMode\
            db          'SDL_SetVideoMode',0
.SDL_PollEvent\
            db          'SDL_PollEvent',0
.SDL_LockSurface\
            db          'SDL_LockSurface',0
.SDL_UnlockSurface\
            db          'SDL_UnlockSurface',0
.SDL_UpdateRect\
            db          'SDL_UpdateRect',0

align 8
ELF_dynamic:
            dq          1,ELF_strtab.libdl-ELF_strtab           ; DT_NEEDED
            dq          5,ELF_strtab                            ; DT_STRTAB
            dq          6,ELF_symtab                            ; DT_SYMTAB
            dq          10,ELF_strtab.SIZE                      ; DT_STRSZ
            dq          11,24                                   ; DT_SYMENT
            dq          7,ELF_rela                              ; DT_RELA
            dq          8,ELF_rela.SIZE                         ; DT_RELASZ
            dq          9,24                                    ; DT_RELAENT
            dq          0,0                                     ; terminator
.SIZE=$-ELF_dynamic

ELF_strtab:
            db          0
.libdl      db          'libdl.so.2',0
.dlopen     db          'dlopen',0
.dlsym      db          'dlsym',0
.SIZE=$-ELF_strtab

align 4
ELF_symtab:
            dd          ELF_strtab.dlopen-ELF_strtab
            db          (1 shl 4)+2,0
            dw          0
            dq          0,0
            dd          ELF_strtab.dlsym-ELF_strtab
            db          (1 shl 4)+2,0
            dw          0
            dq          0,0
.SIZE=$-ELF_symtab

align 8
ELF_rela:
            dq          dlopen,(0 shl 32)+1,0
            dq          dlsym,(1 shl 32)+1,0
.SIZE=$-ELF_rela

ELF_interp  db          '/lib/ld-linux-x86-64.so.2',0
.SIZE=$-ELF_interp

ELF_SIZE=$-$$
