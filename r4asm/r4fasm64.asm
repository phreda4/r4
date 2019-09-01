;-------------------------------------
; win64 Interface
; PHREDA
;-------------------------------------
hInstance = $100000
format PE64 GUI 5.0 at hInstance
entry start

XRES equ 1024
YRES equ 600
STYLE  = WS_VISIBLE or WS_CAPTION or WS_SYSMENU
STYLEX = WS_EX_APPWINDOW

include 'include/win64w.inc'

section '' code readable executable

start:
        push rsi rdi
        enter 8*20,0
        xor rdi,rdi
        xor rcx,rcx

        invoke LoadCursor,0,IDC_ARROW
        invoke RegisterClassEx,class
        invoke ShowCursor,0

        ; RECT structure (0,0,MAX_X,MAX_Y)
        mov [ebp-8*16],rdi
        mov dword [ebp-8*15],XRES
        mov dword [ebp-8*15+4],YRES
        ; find actual width and height needed for desired client area
        lea rcx,[ebp-8*16]
        mov edx,STYLE
        mov r8,rdi ; FALSE
        mov r9d,STYLEX
        call [AdjustWindowRectEx]

        movq xmm0,[ebp-8*15]
        psubd xmm0,dqword [ebp-8*16]
        punpckldq xmm0,xmm7
        mov ecx,STYLEX
        mov edx,CLASSNAME ; #32#
        mov r8,rdx
        mov r9d,STYLE
        mov rax,CW_USEDEFAULT
        mov [ebp-8*16],rax
        mov [ebp-8*15],rax
        movdqa dqword [ebp-8*14],xmm0 ; qword width, qword height
        movdqa dqword [ebp-8*12],xmm7
        mov dword [ebp-8*10],hInstance
        mov [ebp-8*9],rdi
        call [CreateWindowEx]
        mov [hWnd],rax

        invoke GetDC,[hWnd]
        mov [hDC],rax
        mov [bmi.biSize],sizeof.BITMAPINFOHEADER
        mov [bmi.biWidth],XRES
        mov [bmi.biHeight],-YRES
        mov [bmi.biPlanes],1
        mov [bmi.biBitCount],32
        mov [bmi.biCompression],BI_RGB

        invoke ShowWindow,[hWnd],SW_NORMAL
        invoke UpdateWindow,[hWnd]

;       invoke VirtualAlloc,0,MAXMEM,MEM_COMMIT+MEM_RESERVE,PAGE_READWRITE ;
        or rax,rax
;       jz SYSEND
        mov [FREE_MEM],rax

;---------- INICIO
restart:
        mov rbp,DSTACK
        xor rax,rax
        call inicio
        jmp SYSEND
;----- CODE -----
include 'code64.asm'
;----- CODE -----

; OS inteface
; stack............
; [rbp+8] [rbp] rax       ( [rbp+8] [rbp] rax --
;===============================================

;===============================================
align 16
SYSREDRAW: ; ( -- )
        invoke SetDIBitsToDevice,[hDC],0,0,XRES,YRES,0,0,0,YRES,SYSFRAME,bmi,0
        ret

;===============================================
align 16
SYSMSEC: ;  ( -- msec )
        lea rsi,[rsi-8]
        mov [rsi], rax
        invoke GetTickCount
        ret

;===============================================
align 16
SYSTIME: ;  ( -- s m h )
        lea rsi,[rsi-24]
        mov [rsi+16],rax
        invoke GetLocalTime,SysTime
        movzx rax,[SysTime.wHour]
        mov [rsi+8],rax
        movzx rax,[SysTime.wMinute]
        mov [rsi],rax
        movzx rax, [SysTime.wSecond]
        ret

;===============================================
align 16
SYSDATE: ;  ( -- y m d )
        lea rsi,[rsi-24]
        mov [rbp+16],rax
        invoke GetLocalTime,SysTime
        movzx rax,[SysTime.wYear]
        mov [rbp+8],rax
        movzx rax,[SysTime.wMonth]
        mov [rbp],rax
        movzx rax, [SysTime.wDay]
        ret


;===============================================
align 16
SYSLOAD: ; ( 'from "filename" -- 'to )
        mov rcx,[rsp+8]; paso la dirección donde se encuentra la ruta del archivo
        invoke CreateFile,rcx,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING+FILE_FLAG_SEQUENTIAL_SCAN,0
        mov [hdir],rax
        or rax,rax
        jz .loadend
        mov rax,[rsp+16]
        mov [afile],rax
        invoke ReadFile,[hdir],[afile],$ffffff,cntr,0 ; hasta 16MB
        cmp rax, 0
        jne     .loadend
        invoke CloseHandle,[hdir]
        mov rax,[afile]
        add rax,[cntr]
.loadend:
        ret

;===============================================
align 16
SYSSAVE: ; ( 'from cnt "filename" -- )
        mov rax,[rsp+8]
        invoke CreateFile,rax,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,0
        mov [hdir],rax
        or rax,rax
        jz .saveend
        mov rdx,[rsp+24]
        mov rcx,[rsp+16]
        invoke WriteFile,[hdir],rdx,rcx,cntr,0
        cmp [cntr],rcx
        je .saveend
        or rax,rax
        jz .saveend
        invoke CloseHandle,[hdir]
.saveend:
        ret

;===============================================
align 16
SYSAPPEND: ; ( 'from cnt "filename" -- )
        mov rax,[rsp+8] ;FILE_APPEND_DATA=4
        invoke CreateFile,eax,4,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,0
        mov [hdir],rax
        or rax,rax
        jz .append
        mov rdx,[rsp+24]
        mov rcx,[rsp+16]
        invoke WriteFile,[hdir],rdx,rcx,cntr,0
        cmp [cntr],rcx
        je .append
        or rax,rax
        jz .append
        invoke CloseHandle,[hdir]
.append:
        ret

;##########################################################################
align 16
SYSUPDATE: ; ( -- )
        push rax rbx rdx rcx
        invoke  PeekMessage,msg,0,0,0,PM_NOREMOVE
        or      rax,rax
        jz      .noEvent
        invoke  GetMessage,msg,0,0,0
        or      rax,rax
        jz      .endApp
        invoke  TranslateMessage,msg
        invoke  DispatchMessage,msg
.noEvent:
        pop rcx rdx rbx rax
        ret
.endApp:
        pop rcx rdx rbx rax
;===============================================
align 16
SYSEND: ; ( -- )
        invoke ReleaseDC,[hWnd],[hDC]
        invoke DestroyWindow,[hWnd]
        invoke ExitProcess,0
        leave
        pop rdi rsi
        ret

;##########################################################################
;;proc WindowProc hwnd,wmsg,wparam,lparam
align 16
win_proc: ; hWnd,uMsg,wParam,lParam = rcx,rdx,r8,r9
        cmp     edx,WM_MOUSEMOVE
        je      .wmmousemove
        cmp     edx,WM_LBUTTONUP
        je      .wmmouseev
        cmp     edx,WM_MBUTTONUP
        je      .wmmouseev
        cmp     edx,WM_RBUTTONUP
        je      .wmmouseev
        cmp     edx,WM_LBUTTONDOWN
        je      .wmmouseev
        cmp     edx,WM_MBUTTONDOWN
        je      .wmmouseev
        cmp     edx,WM_RBUTTONDOWN
        je      .wmmouseev
        cmp     edx,WM_KEYUP
        je      .wmkeyup
        cmp     edx,WM_KEYDOWN
        je      .wmkeydown
        cmp     edx,WM_DESTROY
        je      .exit
        invoke  DefWindowProc,rcx,rdx,r8,r9
        ret
.wmmousemove:
        mov [SYSXYM],r9
        xor rax,rax
        ret
.wmmouseev:
        mov [SYSBM],r8
        xor rax,rax
        ret
.wmkeyup:
        mov eax,r8d
        shr eax,32
        and eax,$ff
        or eax,$100
        mov [SYSKEY],rax
        xor rax,rax
        ret
.wmkeydown:
        mov eax,r9d
        shr eax,32
        and eax,$ff
        mov [SYSKEY],rax
        xor rax,rax
        ret
.exit:
        enter 32,0 ; shadow space required
        xor ecx,ecx
        call [PostQuitMessage]
        xor eax,eax ; handled
        leave
        retn

;-------------------------------------------------------------------
;##########################################################################
section '' import readable writeable

  library kernel32,'KERNEL32',user32,'USER32',gdi32,'GDI32'

  include 'include\api\kernel32.inc'
  include 'include\api\user32.inc'
  include 'include\api\gdi32.inc'

section '.data' data readable writeable

align 16
        msg     MSG
        hWnd    dq ?
        hDC     dq ?
        rec     RECT
        bmi     BITMAPINFOHEADER
        SysTime SYSTEMTIME
        class   WNDCLASSEX sizeof.WNDCLASSEX,0,win_proc,0,0,hInstance,0,0,0,0,CLASSNAME,0
        CLASSNAME TCHAR 'r3d',0

align 16
        include 'data64.asm'

align 16
        hdir            dq ?
        afile           dq ?
        cntr            dq ?
        SYSXYM          dq ?
        SYSBM           dq ?
        SYSKEY          dq ?
        FREE_MEM        dq ?

align 16 ; CUADRO DE VIDEO (FrameBuffer)
        DSTACK    rq 256
        SYSFRAME  rd XRES*YRES