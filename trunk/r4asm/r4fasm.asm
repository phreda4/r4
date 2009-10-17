;-------------------------------------
; Inteface Windows :R4 - PHReda 2009/10
;-------------------------------------
format PE GUI 4.0
entry start

;XRES equ 640
;YRES equ 480
;XRES equ 800
;YRES equ 600
XRES equ 1024
YRES equ 768
;XRES equ 1280
;YRES equ 800

include 'include\win32a.inc'

section '.data' data readable writeable

	_title	db ':r4',0
	_class	db ':r4',0
	_error	db 'err',0
	_dir 	db '*',0
	mapex 	db    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
			db	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
			db	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47
			db	 48, 49, 50, 51, 52, 69, 70, 71, 56, 73, 74, 75, 76, 77, 78, 79
			db	 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
			db	 96, 97, 98, 99, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
			db	 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111
			db	112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127
align 4
	hinstance	dd 0
	hwnd		dd 0
	wc			WNDCLASS ;EX?
	msg			MSG
	hDC			dd 0
	dwExStyle	dd 0
	dwStyle 	dd 0
	rec			RECT
	bmi			BITMAPINFOHEADER
;	bmiq		dd 0,0,0,0 ;RGBQUAD

;	screenSettings  DEVMODE ;no esta??

	SysTime		SYSTEMTIME
	Sfinddata	FINDDATA

	active		dd 0
	hdir		dd 0
	sfile 		dd 0
	afile 		dd 0
	cntr		dd 0

align 4

  SYSEVENT	dd 0

  SYSXYM	dd 0
  SYSBM 	dd 0
  SYSKEY	dd 0

  SYSiKEY	dd 0
  SYSiPEN	dd 0

  SYSW		dd XRES
  SYSH		dd YRES

  SYSCDIR	dd 0

include 'dat.asm'

  SYSNDIR	rd 8192
  SYSIDIR	rd 1024

align 4
  Dpila 	rd 1024

align 8
	SYSFRAME	rd XRES*YRES
align 8
	SYSEFRAME	rd XRES*YRES
align 8
	FREE_MEM	rd 1024*16 ; 16M(32bits) 64MB(8bits)

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
	mov [dwStyle],WS_VISIBLE+WS_CAPTION+WS_CLIPSIBLINGS+WS_CLIPCHILDREN+WS_SYSMENU+WS_MINIMIZEBOX
	invoke ShowCursor,0
	mov [rec.left],0
	mov [rec.top],0
	mov [rec.right],XRES
	mov [rec.bottom],YRES
	invoke AdjustWindowRect,rec,[dwStyle],0

	;hWnd=CreateWindowEx( dwExStyle,wc.lpszClassName, wc.lpszClassName,dwStyle,
    ; (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
    ; rec.right-rec.left, rec.bottom-rec.top,0,0,wc.hInstance,0);

;	invoke GetSystemMetrics,SM_CXSCREEN
;	mov [WSCR],eax
;	invoke GetSystemMetrics,SM_CYSCREEN
;	mov [HSCR],eax

	invoke	CreateWindowEx,[dwExStyle],_class,_title,[dwStyle],0,0,XRES,YRES,0,0,[hinstance],0
;	invoke	CreateWindowEx,[dwExStyle],_class,_title,[dwStyle],0,0,0,0,0,0,[hinstance],0
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
	mov esi,Dpila
	xor eax,eax
	jmp inicio
;.................compilado.....................
include 'cod.asm'
;.................compilado.....................
	jmp SYSEND

; OS inteface
; stack............
; [esi+4] [esi] eax       ( [esi+4] [esi] eax --
;===============================================
SYSUPDATE: ; ( -- )
	push eax ebx
	invoke	PeekMessage,msg,0,0,0,PM_NOREMOVE
	or	eax,eax
	jz	@noevent
	invoke	GetMessage,msg,0,0,0
	or	eax,eax
	jz	@isyse
	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
	pop ebx eax
	mov ecx,[SYSEVENT]
	or ecx,ecx
	jnz @dispara
	ret
@dispara:
	mov [SYSEVENT],0
	jmp ecx
@isyse:
	pop ebx eax
;===============================================
SYSEND: ; ( -- )
	invoke ReleaseDC,[hwnd],[hDC]
	invoke DestroyWindow,[hwnd]
	invoke ExitProcess,0
	ret
@noevent:
	pop ebx eax
	ret

;===============================================
SYSRUN: ; ( "nombre" -- )

	lodsd
	ret

;===============================================
SYSREDRAW: ; ( -- )
	pusha
	invoke StretchDIBits,[hDC],0,0,XRES,YRES,0,0,XRES,YRES,SYSFRAME,bmi,0,SRCCOPY
;StretchDIBits(hDC,0,0,gr_ancho,gr_alto,0,0,gr_ancho,gr_alto,gr_buffer,&bmi,DIB_RGB_COLORS,SRCCOPY);
	popa
	ret

;===============================================
SYSIFILL: ; ( v cnt src -- )
	pusha
	mov edi,eax
	mov ecx,[esi]
	mov eax,[esi+4]
;       cld
loopf:
	mov [edi],eax
	add edi,4
	loop loopf

	;rep stosd
	;pop edi
	popa
	lea esi,[esi+8]
	lodsd
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
SYSDIR: ; ( "path" -- )
	push eax ebx esi edi
	invoke SetCurrentDirectory,eax
	or eax,eax
	jz @dirfin
	mov edi,SYSNDIR
	mov ebx,0
	invoke FindFirstFile,_dir,Sfinddata
	mov [hdir],eax
	cmp eax,INVALID_HANDLE_VALUE
	je @dirfin
@dirotro:
	mov eax,[Sfinddata.dwFileAttributes]
	cmp eax,FILE_ATTRIBUTE_DIRECTORY
	je @noguarda
	mov [SYSIDIR+4*ebx],edi
	inc ebx
	mov eax,Sfinddata.cFileName
@dircp:
	mov cl,byte [eax]
	mov byte [edi],cl
	inc edi
	inc eax
	or cl,cl
	jnz @dircp
@noguarda:
	invoke FindNextFile,[hdir],Sfinddata
	or eax,eax
	jnz @dirotro
@dirfin:
	mov [SYSCDIR],ebx
	invoke FindClose,[hdir]
	pop edi esi ebx eax
	lodsd
	ret

;===============================================
SYSFILE: ; ( nro -- "name" )
	cmp eax,[SYSCDIR]
	jnl @nof
	mov eax,[SYSIDIR+4*eax]
	ret
@nof:
	xor eax,eax
	ret

;===============================================
SYSLOAD: ; ( 'from "filename" -- 'to )
	invoke CreateFile,eax,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0
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
	invoke CreateFile,eax,GENERIC_WRITE,0,0,CREATE_ALWAYS,0,0
	mov [hdir],eax
	or eax,eax
	jz saveend
	mov edx,[esi+4]
	mov ecx,[esi]
    invoke WriteFile,[hdir],edx,ecx,cntr,0
    cmp [cntr],ecx
    je	saveend
    or eax,eax
    jz	saveend
    invoke CloseHandle,[hdir]
saveend:
	lea esi,[esi+8]
	lodsd
	ret

;--------------------------------------
proc WindowProc hwnd,wmsg,wparam,lparam
	mov	eax,[wmsg]
	cmp eax,WM_MOUSEMOVE
	je	wmmousemove
	cmp eax,WM_LBUTTONUP
	je	wmmouseev
	cmp eax,WM_MBUTTONUP
	je	wmmouseev
	cmp eax,WM_RBUTTONUP
	je	wmmouseev
	cmp eax,WM_LBUTTONDOWN
	je	wmmouseev
	cmp eax,WM_MBUTTONDOWN
	je	wmmouseev
	cmp eax,WM_RBUTTONDOWN
	je	wmmouseev
	cmp eax,WM_KEYUP
	je	wmkeyup
	cmp	eax,WM_KEYDOWN
	je	wmkeydown
;       cmp     eax,WM_CREATE
;       je      wmcreate
	cmp	eax,WM_DESTROY
	je	wmdestroy
	cmp	eax,WM_ACTIVATEAPP
	je	wmactivate
  defwindowproc:
	invoke	DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
	ret
  wmmousemove:
	mov eax,[lparam]
	cmp eax,[SYSXYM]
	je finish
	mov [SYSXYM],eax
	mov eax,[SYSiPEN]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmmouseev:
	mov eax,[wparam]
	mov [SYSBM],eax
	mov eax,[SYSiPEN]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmkeyup:
	mov eax,[lparam]
	shr eax,16
	test eax,$100
	jz @noeu
	and eax,$7f
	mov al,[mapex+eax]
@noeu:
	and eax,$7f
	or eax,$80
	mov [SYSKEY],eax
	mov eax,[SYSiKEY]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmkeydown:			; cmp [wparam],VK_ESCAPE ; je wmdestroy
	mov eax,[lparam]
	shr eax,16
	test eax,$100
	jz @noed
	and eax,$7f
	mov al,[mapex+eax]
@noed:
	and eax,$7f
	mov [SYSKEY],eax
	mov eax,[SYSiKEY]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
;         lParam>>=16;
;         SYSKEY=lParam&0x7f;
;         if (SYSKEY>0x34 && SYSKEY!=0x38) SYSKEY+=((lParam&0x100)>>4);

;  wmcreate:
;       xor eax,eax
;       ret
  wmactivate:
	mov	eax,[wparam]
	and	eax,$ff
	mov	[active],eax
	cmp eax,WA_INACTIVE
	je @na
	invoke ShowWindow,[hwnd],SW_NORMAL ;            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
	invoke UpdateWindow,[hwnd]	;            UpdateWindow(hWnd);
	xor eax,eax
	ret
@na:
	invoke ChangeDisplaySettings,0,0		;            ChangeDisplaySettings(NULL,0);
	invoke ShowWindow,[hwnd],SW_MINIMIZE	;            ShowWindow(hWnd,SW_MINIMIZE);
	xor eax,eax
	ret
  wmdestroy:
	invoke PostQuitMessage,0
	ret
  finish:
	xor eax,eax
	ret
endp

;----------------------------------------------
sys_error:
	mov	eax,_error
	invoke	MessageBox,[hwnd],eax,_error,MB_OK
	invoke	DestroyWindow,[hwnd]
	invoke	PostQuitMessage,1
	ret

section '.idata' import data readable

library kernel,'KERNEL32.DLL', user,'USER32.DLL', gdi,'GDI32.DLL'

import kernel,\
	 GetModuleHandle,'GetModuleHandleA',\
	 CreateFile,'CreateFileA',\
	 ReadFile,'ReadFile',\
	 WriteFile,'WriteFile',\
	 CloseHandle,'CloseHandle',\
	 GetTickCount,'GetTickCount',\
	 ExitProcess,'ExitProcess',\
	 GetLocalTime,'GetLocalTime',\
	 SetCurrentDirectory,'SetCurrentDirectoryA',\
	 FindFirstFile,'FindFirstFileA',\
	 FindNextFile,'FindNextFileA',\
	 FindClose,'FindClose'
;        GetFileSize,'GetFileSize',\

import user,\
	 RegisterClass,'RegisterClassA',\
	 CreateWindowEx,'CreateWindowExA',\
	 DestroyWindow,'DestroyWindow',\
	 DefWindowProc,'DefWindowProcA',\
	 GetMessage,'GetMessageA',\
	 PeekMessage,'PeekMessageA',\
	 TranslateMessage,'TranslateMessage',\
	 DispatchMessage,'DispatchMessageA',\
	 LoadCursor,'LoadCursorA',\
	 LoadIcon,'LoadIconA',\
	 SetCursor,'SetCursor',\
	 MessageBox,'MessageBoxA',\
	 PostQuitMessage,'PostQuitMessage',\
	 WaitMessage,'WaitMessage'	 ,\
	 ShowWindow,'ShowWindow',\
	 UpdateWindow,'UpdateWindow',\
	 ChangeDisplaySettings,'ChangeDisplaySettingsA',\
	 GetDC,'GetDC',\
	 ReleaseDC,'ReleaseDC',\
	 AdjustWindowRect,'AdjustWindowRect',\
	 ShowCursor,'ShowCursor'

import gdi,\
       StretchDIBits,'StretchDIBits'

include 'rsrc.rc'
