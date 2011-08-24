;-------------------------------------
; Inteface Basica con Windows
;-------------------------------------
format PE GUI 4.0
entry start

XRES equ 640
YRES equ 480
;XRES equ 800 ;YRES equ 600
;XRES equ 1024 ;YRES equ 768
;XRES equ 1280 ;YRES equ 800

include 'include\win32a.inc'

section '.code' code readable executable

start:
	invoke	GetModuleHandle,0
	mov	[hinstance],eax
	invoke	LoadIcon,0,IDI_APPLICATION
	mov	[wc.hIcon],eax
	mov	[wc.style],0
	mov	[wc.lpfnWndProc],WindowProc
	mov	[wc.cbClsExtra],0
	mov	[wc.cbWndExtra],0
	mov	eax,[hinstance]
	mov	[wc.hInstance],eax
	mov	[wc.hbrBackground],0
	mov	dword [wc.lpszMenuName],0
	mov	dword [wc.lpszClassName],_class
	invoke	RegisterClass,wc
	mov [dwExStyle],WS_EX_APPWINDOW
	mov [dwStyle],WS_VISIBLE+WS_CAPTION+WS_SYSMENU
	invoke ShowCursor,0
	xor eax,eax
	mov [rec.left],eax
	mov [rec.top],eax
	mov [rec.right],XRES
	mov [rec.bottom],YRES
	invoke AdjustWindowRect,rec,[dwStyle],0
	mov eax,[rec.left]
	sub [rec.right],eax
	mov eax,[rec.top]
	sub [rec.bottom],eax
	xor eax,eax
	mov [rec.left],eax
	mov [rec.top],eax
	invoke	CreateWindowEx,[dwExStyle],_class,_title,[dwStyle],0,0,[rec.right],[rec.bottom],0,0,[hinstance],0
	mov	[hwnd],eax
	invoke GetDC,[hwnd]
	mov [hDC],eax
	mov [bmi.biSize],sizeof.BITMAPINFOHEADER
	mov [bmi.biWidth],XRES
	mov [bmi.biHeight],-YRES
	mov [bmi.biPlanes],1
	mov [bmi.biBitCount],32
	mov [bmi.biCompression],BI_RGB
	invoke ShowWindow,[hwnd],SW_NORMAL
	invoke UpdateWindow,[hwnd]

;---------- INICIO
restart:
	mov esi,Dpila	; inicio de pila
	xor eax,eax	; tope de pila
;        call test1
	call test2
	jmp SYSEND

;--- ejemplo 1 llena la pantalla
test1:
	xor ebx,ebx
loopi:
;        inc edx
	mov [SYSFRAME+ebx*4],edx
	add ebx,1
	cmp ebx,640*480
	jl loopi
	add edx,1
	call SYSREDRAW
	call SYSUPDATE
	cmp [SYSKEY],1
	jne test1

	ret
;---ejemplo 2 uso de mouse
test2:
	call SYSCLS
loop2:
	mov eax, [SYSXYM]
	mov ebx,eax
	shr eax,16
	and ebx,$ffff
	imul eax,XRES
	add eax,ebx
	mov [SYSFRAME+eax*4],$ffffff

	call SYSREDRAW
	call SYSUPDATE
	cmp [SYSKEY],1
	jne loop2
	ret

; OS inteface
; stack............
; [esi+4] [esi] eax       ( [esi+4] [esi] eax --
;===============================================
align 16
SYSUPDATE: ; ( -- )
	push eax ebx edx ecx
	invoke	PeekMessage,msg,0,0,0,PM_NOREMOVE
	or	eax,eax
	jz	.noEvent
	invoke	GetMessage,msg,0,0,0
	or	eax,eax
	jz	.endApp
	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
.noEvent:
	pop ecx edx ebx eax
	ret
.endApp:
	pop ecx edx ebx eax
;===============================================
align 16
SYSEND: ; ( -- )
	invoke ReleaseDC,[hwnd],[hDC]
	invoke DestroyWindow,[hwnd]
	invoke ExitProcess,0
	ret
;===============================================
align 16
SYSREDRAW: ; ( -- )
	pusha
	invoke SetDIBitsToDevice,[hDC],0,0,XRES,YRES,0,0,0,YRES,SYSFRAME,bmi,0
	popa
	ret
;===============================================
align 16
SYSCLS: 	; ( -- )
	pusha
	mov eax,[SYSPAPER]
	lea edi,[SYSFRAME]
	mov ecx,XRES*YRES
	rep stosd
	popa
	ret
;===============================================
SYSMSEC: ;  ( -- msec )
	lea esi,[esi-4]
	mov [esi], eax
	invoke GetTickCount
	ret
;===============================================
SYSTIME: ;  ( -- s m h )
	lea esi,[esi-12]
	mov [esi+8],eax
	invoke GetLocalTime,SysTime
	movzx eax,word [SysTime.wHour]
	mov [esi+4],eax
	movzx eax,word [SysTime.wMinute]
	mov [esi],eax
	movzx eax,word [SysTime.wSecond]
	ret
;===============================================
SYSDATE: ;  ( -- y m d )
	lea esi,[esi-12]
	mov [esi+8],eax
	invoke GetLocalTime,SysTime
	movzx eax,word [SysTime.wYear]
	mov [esi+4],eax
	movzx eax,word [SysTime.wMonth]
	mov [esi],eax
	movzx eax,word [SysTime.wDay]
	ret
;===============================================
SYSLOAD: ; ( 'from "filename" -- 'to )
	invoke CreateFile,eax,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING+FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	mov eax,[esi]
	jz @loadend
	mov [afile],eax
@loadagain:
	invoke ReadFile,[hdir],[afile],$ffffff,cntr,0 ; hasta 16MB
;       or      eax,eax
;       jnz     @loadend
	invoke CloseHandle,[hdir]
	mov eax,[afile]
	add eax,[cntr]
@loadend:
	lea esi,[esi+4]
	ret
;===============================================
SYSSAVE: ; ( 'from cnt "filename" -- )
	invoke CreateFile,eax,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_NO_BUFFERING+FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	jz .saveend
	mov edx,[esi+4]
	mov ecx,[esi]
	invoke WriteFile,[hdir],edx,ecx,cntr,0
	cmp [cntr],ecx
	je .saveend
	or eax,eax
	jz .saveend
	invoke CloseHandle,[hdir]
.saveend:
	lea esi,[esi+8]
	lodsd
	ret
;--------------------------------------
proc WindowProc hwnd,wmsg,wparam,lparam
	mov	eax,[wmsg]
	cmp	eax,WM_MOUSEMOVE
	je	wmmousemove
	cmp	eax,WM_LBUTTONUP
	je	wmmouseev
	cmp	eax,WM_MBUTTONUP
	je	wmmouseev
	cmp	eax,WM_RBUTTONUP
	je	wmmouseev
	cmp	eax,WM_LBUTTONDOWN
	je	wmmouseev
	cmp	eax,WM_MBUTTONDOWN
	je	wmmouseev
	cmp	eax,WM_RBUTTONDOWN
	je	wmmouseev
	cmp	eax,WM_KEYUP
	je	wmkeyup
	cmp	eax,WM_KEYDOWN
	je	wmkeydown
  defwindowproc:
	invoke	DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
	ret
  wmmousemove:
	mov eax,[lparam]
	mov [SYSXYM],eax
	xor eax,eax
	ret
  wmmouseev:
	mov eax,[wparam]
	mov [SYSBM],eax
	xor eax,eax
	ret
  wmkeyup:
	mov eax,[lparam]
	shr eax,16
	and eax,$7f
	or eax,$80
	mov [SYSKEY],eax
	xor eax,eax
	ret
  wmkeydown:			; cmp [wparam],VK_ESCAPE ; je wmdestroy
	mov eax,[lparam]
	shr eax,16
	and eax,$7f
	mov [SYSKEY],eax
	xor eax,eax
	ret
endp
;----------------------------------------------
section '.idata' import data readable

library kernel,'KERNEL32.DLL', user,'USER32.DLL', gdi,'GDI32.DLL'
import kernel,\
	 GetModuleHandle,'GetModuleHandleA', CreateFile,'CreateFileA',\
	 ReadFile,'ReadFile',  WriteFile,'WriteFile',\
	 CloseHandle,'CloseHandle', GetTickCount,'GetTickCount',\
	 ExitProcess,'ExitProcess', GetLocalTime,'GetLocalTime',\
	 SetCurrentDirectory,'SetCurrentDirectoryA', FindFirstFile,'FindFirstFileA',\
	 FindNextFile,'FindNextFileA',	FindClose,'FindClose'

import user,\
	 RegisterClass,'RegisterClassA', CreateWindowEx,'CreateWindowExA',\
	 DestroyWindow,'DestroyWindow', DefWindowProc,'DefWindowProcA',\
	 GetMessage,'GetMessageA', PeekMessage,'PeekMessageA',\
	 TranslateMessage,'TranslateMessage', DispatchMessage,'DispatchMessageA',\
	 LoadCursor,'LoadCursorA', LoadIcon,'LoadIconA',\
	 SetCursor,'SetCursor', MessageBox,'MessageBoxA',\
	 PostQuitMessage,'PostQuitMessage', WaitMessage,'WaitMessage'	 ,\
	 ShowWindow,'ShowWindow', UpdateWindow,'UpdateWindow',\
	 ChangeDisplaySettings,'ChangeDisplaySettingsA', GetDC,'GetDC',\
	 ReleaseDC,'ReleaseDC', AdjustWindowRect,'AdjustWindowRect',\
	 ShowCursor,'ShowCursor'

import gdi,\
	SetDIBitsToDevice,'SetDIBitsToDevice'

section '.data' data readable writeable

	hinstance	dd 0
	hwnd		dd 0
	wc		WNDCLASS ;EX?
	msg		MSG
	hDC		dd 0
	dwExStyle	dd 0
	dwStyle 	dd 0
	rec		RECT
	bmi		BITMAPINFOHEADER
	SysTime 	SYSTEMTIME
	hdir		dd 0
	afile		dd 0
	cntr		dd 0
	_title		db 'asm',0
	_class		db 'asm',0
align 4
	SYSXYM	dd 0
	SYSBM	dd 0
	SYSKEY	dd 0
	SYSPAPER dd 0
	Dpila	rd 1024 ; Pila Auxiliar
align 16 ; CUADRO DE VIDEO (FrameBuffer)
	SYSFRAME	rd XRES*YRES
