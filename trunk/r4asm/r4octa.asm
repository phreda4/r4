; OctaOS 
;LANG FASM
include '\\RD\FASM.INC'

XRES equ 640
YRES equ 480
VMODO equ $4112
;mov esi,tmp_path
;call cdfile
;mov [current_dir],ebx
pcall gui.new.t3,XRES,YRES,title
call getmxy1
pcall wait_ms1,40
;---- Inicio R4
mov [NIVEL0],esp
call SYSUPDATE
mov esi,pila
xor eax,eax
jmp inicio

title:   db 12,'Fasm example'
msg1:
db " Vesa/Mouse Error",13
db " Press any key to exit. ",13,0
;.................compilado.....................
include 'cod.asm'
;.................compilado.....................

;===============================================
SYSEND:
mov esp,[NIVEL0]               ; nivel de llamada 0
ret                            ; Return control to OctaOS

;===============================================
SYSUPDATE:
pusha
mov [SYSEVENT],0
call getd
jnc .keyb
call getmxy2
jnc .mouse
pcall wait_ms2,40
jnc .tick
call get_redraw
jnc .redraw
call del_msg
popa
ret
     .redraw:
call SYSREDRAW
popa
ret
     .tick:
inc [last_tick]
popa
ret
     .keyb:
;jmp SYSEND
cmp eax,keyb.esc
je SYSEND
and eax,7fh
mov [SYSKEY],eax
mov eax,[SYSKEYM+eax*4]
mov [SYSEVENT],eax
popa
ret
     .mouse:
mov [SYSBM],ebx
shl edx,16
or eax,16
mov [SYSXYM],eax
mov eax,[SYSMM]
test ebx,ebx
jz .l1
mov eax,[SYSMS]
    .l1:
mov [SYSEVENT],eax
popa
ret

;===============================================
SYSRUN:; ( "nombre" -- )
ret

;===============================================
SYSREDRAW:; BuffToScreen32:
pusha
mov al,bmp32_write
call setvideofuncion
mov dword[bmp],SYSFRAME
mov eax,0
mov ebx,0
mov ecx,XRES
mov edx,YRES
call rectangulo
popa
ret

;===============================================
SYSIFILL:; ( v cnt src -- )
push edi
mov edi,eax
mov ecx,[esi]
mov eax,[esi+4]
cld
rep stosd
mov eax,[esi+8]
lea esi,[esi+12]
pop edi
ret

;===============================================
SYSMSEC: ret

;===============================================
SYSTIME: int 1
lea esi,[esi-12]
mov [esi+8],eax
cli
mov   al,4                                      ; RTC  04h
out   70h,al
in    al,71h                            ; read hour
call Bcd2Bin
mov [esi+4],eax; NOS-1
mov   al,2                                      ; RTC  02h
out   70h,al
in    al,71h                            ; read minute
call Bcd2Bin
mov [esi],eax; NOS
xor   al,al                                     ; RTC  00h
out   70h,al
in    al,71h                            ; read second
call Bcd2Bin
sti
ret

;===============================================
SYSDATE: int 1
lea esi,[esi-12]
mov [esi+8],eax
cli
   xor eax,eax
mov   al,9                                      ; RTC 09h
out   70h,al
in    al,71h                                    ; read year
call Bcd2Bin
mov [esi+4],eax; NOS-1
mov   al,8                                      ; RTC 08h
out   70h,al
in    al,71h                                    ; read month
call Bcd2Bin
mov [esi],eax  ; NOS
mov   al,7                                      ; RTC 07h
out   70h,al
in    al,71h                                    ; read day
call Bcd2Bin   ;TOS
   sti
   ret

Bcd2Bin:; ebx trash
xor eax,eax
mov   bl,0x0a
mov   bh,al
shr   al,4
mul   bl
and   bh,0x0f
add   al,bh
ret

;===============================================
SYSDIR:; ( "path" -- )
ret
pusha
mov ebx,[current_dir]
lea esi,[eax+1]
xor eax,eax
call cdfile
jc SYSEND
mov [current_dir],ebx
popa
ret

copy_path:
pusha
mov edi,tmp_path+1
mov ecx,33
     .l1:
lodsb
stosb
cmp al,20h
jc .l2
loop .l1
jmp SYSEND;path too long
     .l2:
popa
ret

tmp_path: db '\\D0\WINDOWS\OCTA\PRUEBAS\CODIGO  '
current_dir dd 0
;===============================================
SYSFILE:; ( nro -- "name" )
ret

;===============================================
SYSLOAD:; ( 'from "filename" -- 'to )
ret
int 1
pusha   ;eax->file name
mov esi,eax
call copy_path
mov ebx,[current_dir]
mov eax,80h
mov esi,tmp_path
call open
test eax,eax
jz SYSEND
or ecx,-1
call read ;edi=bufer
call close
popa
ret

;===============================================
SYSSAVE:; ( 'from cnt "filename" -- )
;|WriteCommand       rd 1
; 43.Writes a file to floppy,
;ESI points to name of file to make,
;EDI = place to load file from,
;EAX = size of file to load in bytes,
;set's CF to 1 on error, error code in AH,
;sucsess EBX = number of sectors loaded, ECX = file size in bytes.
ret

align 4

last_tick dd 0

 NIVEL0        dd 0   ; pila de codigo

 SYSEVENT      dd 0
 SYSXYM        dd 0
 SYSBM         dd 0
 SYSKEY        dd 0
 SYSMS         dd 0
 SYSMM         dd 0
 SYSME         dd 0

 SYSBPP        dd 32
 SYSW          dd XRES
 SYSH          dd YRES
 SYSVSIZE      dd XRES*YRES

include 'dat.asm'

align 4

 SYSKEYM       rd 256
 ppila         rd 1024
 pila          rd 1024
 SYSFRAME      rd XRES*YRES
 FREE_MEM      rd 1024*4; 4M(32bits) 16MB


