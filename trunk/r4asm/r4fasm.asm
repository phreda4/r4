;-------------------------------------
; Inteface Windows :R4 - PHReda 2009/10
;-------------------------------------
format PE GUI 4.0
entry start

DWEXSTYLE	equ WS_EX_APPWINDOW
DWSTYLE		equ WS_VISIBLE+WS_CAPTION+WS_SYSMENU

;XRES equ 640
;YRES equ 480
XRES equ 800
YRES equ 600
;XRES equ 1024
;YRES equ 768
;XRES equ 1280
;YRES equ 800

;		"if XRES=640" ,ln
;	"mov ebx,eax" ,ln
;	"shr eax,7" ,ln
;	"shr ebx,9" ,ln
;	"add eax,[esi]" ,ln
;	"lea ebp,[SYSFRAME+ebx+eax*4]" ,ln
;		"else if XRES=800" ,ln
;	"mov ebx,eax" ,ln
;	"shr eax,5" ,ln
;	"shr ebx,8" ,ln
;	"add eax,ebx" ,ln
;	"shr ebx,1" ,ln
;	"add eax,[esi]" ,ln
;	"lea ebp,[SYSFRAME+ebx+eax*4]" ,ln
;		"else if XRES=1024" ,ln
;	"shr eax,10" ,ln
;	"add eax,[esi]" ,ln
;	"lea ebp,[SYSFRAME+eax*4]" ,ln
;		"else if XRES=1280" ,ln
;;	"mov ebx,eax" ,ln
;	"shr eax,8" ,ln
;	"shr ebx,10" ,ln
;	"add eax,[esi]" ,ln
;;	"lea ebp,[SYSFRAME+ebx+eax*4]" ,ln
;		"else" ,ln
;	"cdq" ,ln
;	"imul dword [SYSW]" ,ln
;	"add eax,[esi]" ,ln
;	"lea ebp,[SYSFRAME+eax*4]" ,ln
;		"end if" ,ln

include 'r4asm\include\win32a.inc'

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
	invoke RegisterClass,wc
	invoke ShowCursor,0
	xor eax,eax
	mov [rec.left],eax
	mov [rec.top],eax
	mov [rec.right],XRES
	mov [rec.bottom],YRES
	invoke AdjustWindowRect,rec,DWSTYLE,0
	mov eax,[rec.left]
	sub [rec.right],eax
	mov eax,[rec.top]
	sub [rec.bottom],eax
	xor eax,eax
	mov [rec.left],eax
	mov [rec.top],eax

	;hWnd=CreateWindowEx( dwExStyle,wc.lpszClassName, wc.lpszClassName,dwStyle,
    ; (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
    ; rec.right-rec.left, rec.bottom-rec.top,0,0,wc.hInstance,0);

;	invoke GetSystemMetrics,SM_CXSCREEN
;	mov [WSCR],eax
;	invoke GetSystemMetrics,SM_CYSCREEN
;	mov [HSCR],eax

	invoke	CreateWindowEx,DWEXSTYLE,_class,_title,DWSTYLE,0,0,[rec.right],[rec.bottom],0,0,[hinstance],0
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
;----- CODE -----
include 'cod.asm'
;----- CODE -----
	jmp SYSEND

; OS inteface
; stack............
; [esi+4] [esi] eax       ( [esi+4] [esi] eax --
;===============================================
align 16
SYSUPDATE: ; ( -- )
	push eax ebx edx ; falta guardar ecx!! y esi,edi!!
	invoke Sleep,eax
	xor eax,eax
	mov [SYSKEY],eax
	invoke PeekMessage,msg,eax,eax,eax,PM_NOREMOVE
	or	eax,eax
	jz	.end
	invoke	GetMessage,msg,0,0,0
	or	eax,eax
	jz	.endstop
;	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
.end:
	pop edx ebx eax
	ret
.endstop:
	pop edx ebx eax
;===============================================
align 16
SYSEND: ; ( -- )
	invoke ReleaseDC,[hwnd],[hDC]
	invoke DestroyWindow,[hwnd]
	invoke ExitProcess,0
	ret

;===============================================
align 16
SYSRUN: ; ( "nombre" -- )
	lodsd
	ret

;===============================================
align 16
SYSREDRAW: ; ( -- )
	pusha
	xor eax,eax
	invoke SetDIBitsToDevice,[hDC],eax,eax,XRES,YRES,eax,eax,eax,YRES,SYSFRAME,bmi,eax
	popa
	ret

;===============================================
align 16
SYSCLS:		; ( -- )
	push eax edi ecx
	mov eax,[SYSPAPER]
	lea edi,[SYSFRAME]
	mov ecx,XRES*YRES
	rep stosd
	pop ecx edi eax
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
	mov eax,Sfinddata.cFileName
@dircp:
	mov cl,byte [eax]
	mov byte [edi],cl
	inc edi
	inc eax
	or cl,cl
	jnz @dircp
	mov eax,[Sfinddata.nFileSizeLow]
	mov edx,[Sfinddata.nFileSizeHigh] ; en bytes.. pasar a kb para que sea 32bit?
	mov [SYSSDIR+4*ebx],eax
	inc ebx
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
SYSFSIZE: ; nro -- size
	cmp eax,[SYSCDIR]
	jnl @nof
	mov eax,[SYSSDIR+4*eax]
	ret
@nof:
	xor eax,eax
	ret

;===============================================
SYSTOXFB:
	pusha
	lea esi,[SYSFRAME]
	lea edi,[XFB]
	mov ecx,XRES*YRES
	rep movsd
	popa
	ret

;===============================================
SYSXFBTO:
	pusha
	lea esi,[XFB]
	lea edi,[SYSFRAME]
	mov ecx,XRES*YRES
	rep movsd
	popa
	ret

;===============================================
SYSLOAD: ; ( 'from "filename" -- 'to )
	invoke CreateFile,eax,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	mov eax,[esi]
	jz @loadend

	mov [afile],eax
@loadagain:
	invoke ReadFile,[hdir],[afile],$3fffff,cntr,0 ; hasta 4MB
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
	invoke CreateFile,eax,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,0
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
    cmp eax,WM_SYSKEYUP
    je	wmkeyup
	cmp	eax,WM_KEYDOWN
	je	wmkeydown
    cmp	eax,WM_SYSKEYDOWN
    je	wmkeydown
    cmp	eax,WM_CLOSE
    je  SYSEND
    cmp	eax,WM_DESTROY
    je  SYSEND
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
	test eax,$100
	jz @f
	and eax,$7f
	mov al,[mapex+eax]
  @@:
	and eax,$7f
	or eax,$80
	mov [SYSKEY],eax
	xor eax,eax
	ret
  wmkeydown:			; cmp [wparam],VK_ESCAPE ; je wmdestroy
	mov eax,[lparam]
	shr eax,16
	test eax,$100
	jz @f
	and eax,$7f
	mov al,[mapex+eax]
  @@:
	and eax,$7f
	mov [SYSKEY],eax
	xor eax,eax
	ret
endp

;----- DATA -----
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
	 Sleep,'Sleep',\
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
	SetDIBitsToDevice,'SetDIBitsToDevice'

include 'rsrc.rc'

section '.data' data readable writeable

	mapex 	db    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
			db	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
			db	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47
			db	 48, 49, 50, 51, 52, 69, 70, 71, 56, 73, 74, 75, 76, 77, 78, 79
			db	 80, 81, 82, 83, 84, 85, 86,103,104, 89, 90, 91, 92, 93, 94, 95
			db	 96, 97, 98, 99, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
			db	 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111
			db	112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127
	_title	db ':r4',0
	_class	db ':r4',0
	_dir 	db '*',0

align 4
	hinstance	dd 0
	hwnd		dd 0
	wc			WNDCLASS ;EX?
	msg			MSG
	hDC			dd 0
	rec			RECT
	bmi			BITMAPINFOHEADER
	SysTime		SYSTEMTIME
	Sfinddata	FINDDATA
	hdir		dd 0
	sfile 		dd 0
	afile 		dd 0
	cntr		dd 0

align 4
	SYSXYM	dd 0
	SYSBM 	dd 0
	SYSKEY	dd 0

	SYSW	dd XRES
	SYSH	dd YRES
	SYSPAPER dd 0
	SYSCDIR	dd 0

include 'dat.asm'

align 16
	SYSNDIR	rd 8192
	SYSIDIR	rd 1024
	SYSSDIR	rd 1024
	Dpila 	rd 1024
align 16
	SYSFRAME	rd XRES*YRES
align 16
	XFB			rd XRES*YRES
align 16
	FREE_MEM	rd 1024*1024*16 ; 16M(32bits) 64MB(8bits)


