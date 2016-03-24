;-------------------------------------
; Inteface Basica con Windows
;-------------------------------------
hInstance = $100000
format PE64 GUI 5.0 at hInstance
entry start

XRES equ 640
YRES equ 480
STYLE  = WS_VISIBLE or WS_CAPTION or WS_SYSMENU
STYLEX = WS_EX_APPWINDOW

include 'include/win64w.inc'

section '' code readable executable

start:
	label .0 qword at ebp-8*20 ; rcx / xmm0L
	label .1 qword at ebp-8*19 ; rdx / xmm1L
	label .2 qword at ebp-8*18 ; r8  / xmm2L
	label .3 qword at ebp-8*17 ; r9  / xmm3L
	label .4 qword at ebp-8*16
	label .5 qword at ebp-8*15
	label .6 qword at ebp-8*14
	label .7 qword at ebp-8*13
	label .8 qword at ebp-8*12
	label .9 qword at ebp-8*11
	label .A qword at ebp-8*10
	label .B qword at ebp-8*9
	label .C qword at ebp-8*8
	label .D qword at ebp-8*7
	label .E qword at ebp-8*6
	label .F qword at ebp-8*5
	label .G qword at ebp-8*4
	label .H qword at ebp-8*3
	label .I qword at ebp-8*2
	label .J qword at ebp-8*1

	push rsi rdi
	enter 8*20,0

	xor rdi,rdi
	xor rcx,rcx
	mov edx,IDC_ARROW
	call [LoadCursor]

	mov ecx,class ; #32#
	mov [rcx+WNDCLASSEX.hCursor],rax ; HCURSOR:HANDLE:PVOID
	call [RegisterClassEx]

	; RECT structure (0,0,MAX_X,MAX_Y)
	mov [.4],rdi
	mov dword [.5],XRES
	mov dword [.5+4],YRES
	; find actual width and height needed for desired client area
	lea rcx,[.4]
	mov edx,STYLE
	mov r8,rdi ; FALSE
	mov r9d,STYLEX
	call [AdjustWindowRectEx]

	movq xmm0,[.5]
	psubd xmm0,dqword [.4]
	punpckldq xmm0,xmm7
	mov ecx,STYLEX
	mov edx,CLASSNAME ; #32#
	mov r8,rdx
	mov r9d,STYLE
	mov rax,CW_USEDEFAULT
	mov [.4],rax
	mov [.5],rax
	movdqa dqword [.6],xmm0 ; qword width, qword height
	movdqa dqword [.8],xmm7
	mov [.A],hInstance
	mov [.B],rdi
	call [CreateWindowEx]
	mov	[hWnd],rax

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

;---------- INICIO
restart:
	mov esi,Dpila
	xor eax,eax
	call inicio
	jmp SYSEND
;----- CODE -----
include 'cod.asm'
;----- CODE -----

; OS inteface
; stack............
; [esi+4] [esi] eax       ( [esi+4] [esi] eax --
;===============================================

align 16
SYSUPDATE: ; ( -- )
	push rax rbx rdx rcx
	invoke	PeekMessage,msg,0,0,0,PM_NOREMOVE
	or	rax,rax
	jz	.noEvent
	invoke	GetMessage,msg,0,0,0
	or	rax,rax
	jz	.endApp
	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
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


;===============================================
align 16
SYSREDRAW: ; ( -- )
       invoke SetDIBitsToDevice,[hDC],0,0,XRES,YRES,0,0,0,YRES,SYSFRAME,bmi,0
       ret

;===============================================
align 16
SYSCLS: 	; ( -- )
	mov rax,[SYSPAPER]
	mov rcx,rax
	shl rcx,32
	or rax,rcx
	lea rdi,[SYSFRAME]
	mov rcx,(XRES*YRES)/2
	rep stosq
	ret

;===============================================
SYSMSEC: ;  ( -- msec )
	lea rsi,[rsi-8]
	mov [rsi], rax
	invoke GetTickCount
	ret

;===============================================
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
SYSDATE: ;  ( -- y m d )
	lea rsi,[rsi-24]
	mov [esi+16],rax
	invoke GetLocalTime,SysTime
	movzx rax,[SysTime.wYear]
	mov [esi+8],rax
	movzx rax,[SysTime.wMonth]
	mov [esi],rax
	movzx rax, [SysTime.wDay]
	ret


;===============================================
SYSLOAD: ; ( 'from "filename" -- 'to )
	mov rcx,[rsp+8]; paso la dirección donde se encuentra la ruta del archivo
	invoke CreateFile,rcx,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING+FILE_FLAG_SEQUENTIAL_SCAN,0

	mov [hdir],rax
	or rax,rax

	jz @loadend
	mov rax,[rsp+16]
	mov [afile],rax
@loadagain:
	invoke ReadFile,[hdir],[afile],$ffffff,cntr,0 ; hasta 16MB
	cmp rax, 0
	jne	@loadend
	invoke CloseHandle,[hdir]
	mov rax,[afile]
	add rax,[cntr]
@loadend:

	ret

;===============================================
SYSSAVE: ; ( 'from cnt "filename" -- )
	 mov rax, [rsp+8]
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

;##########################################################################
;;proc WindowProc hwnd,wmsg,wparam,lparam
win_proc: ; hWnd,uMsg,wParam,lParam = rcx,rdx,r8,r9
	cmp	edx,WM_MOUSEMOVE
	je	wmmousemove
	cmp	edx,WM_LBUTTONUP
	je	wmmouseev
	cmp	edx,WM_MBUTTONUP
	je	wmmouseev
	cmp	edx,WM_RBUTTONUP
	je	wmmouseev
	cmp	edx,WM_LBUTTONDOWN
	je	wmmouseev
	cmp	edx,WM_MBUTTONDOWN
	je	wmmouseev
	cmp	edx,WM_RBUTTONDOWN
	je	wmmouseev
	cmp	edx,WM_KEYUP
	je	wmkeyup
	cmp	edx,WM_KEYDOWN
	je	wmkeydown
	cmp	edx,WM_DESTROY
	je	xit
	invoke	DefWindowProc,rcx,rdx,r8,r9
	ret

  wmmousemove:
	mov [SYSXYM],r9
	xor rax,rax
	ret
  wmmouseev:
	mov [SYSBM],r8
	xor rax,rax
	ret
  wmkeyup:
	mov eax,r8d
	shr eax,32
	and eax,$7f
	or eax,$80
	mov [SYSKEY],rax
	xor rax,rax
	ret
  wmkeydown:			; cmp [wparam],VK_ESCAPE ; je wmdestroy
	mov eax,r9d
	shr eax,32
	and eax,$7f
	mov [SYSKEY],rax
	xor rax,rax
	ret
  xit:
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
	msg	MSG

	hWnd	dq ?
	hDC	dq ?

	rec	RECT
	bmi	BITMAPINFOHEADER
	SysTime SYSTEMTIME
	class	WNDCLASSEX sizeof.WNDCLASSEX,0,win_proc,0,0,hInstance,0,0,0,0,CLASSNAME,0
	CLASSNAME TCHAR 'FASM64',0

align 16
	include 'dat.asm'

align 16
	hdir		dq 0
	afile		dq 0
	cntr		dq 0

	SYSXYM	dq 0
	SYSBM	dq 0
	SYSPAPER dq 0
	SYSKEY	dq 0

align 16
	Dpila	rq 1024 ; Pila Auxiliar

align 16 ; CUADRO DE VIDEO (FrameBuffer)
	 SYSFRAME  rd XRES*YRES

