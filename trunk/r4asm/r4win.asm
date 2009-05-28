;-------------------------------------
; Inteface Windows :R4 - PHReda 2007/2
;-------------------------------------
format PE GUI 4.0
entry start

XRES equ 1024
YRES equ 768

include 'include\win32a.inc'
include 'ddraw.inc'

section '.data' data readable writeable

  _title db 'r4',0
  _class db 'r4',0
  _error db 'error',0
  _dir db '*',0
  
align 4

  hinstance		dd 0
  hwnd			dd 0
  wc			WNDCLASS
  msg			MSG
  ddsd			DDSURFACEDESC
  ddscaps		DDSCAPS
  DDraw			DirectDraw
  DDSPrimary	DirectDrawSurface
  DDSBack		DirectDrawSurface  
  SysTime		SYSTEMTIME
  Sfinddata		FINDDATA
  active		dd 0
  hdir			dd 0
  sfile			dd 0
  afile			dd 0
  cntr			dd 0

align 4

  SYSEVENT	dd 0
  SYSXYM	dd 0
  SYSBM		dd 0
  SYSKEY	dd 0

  SYSiKEY	dd 0
  SYSiPEN	dd 0
    
  SYSBPP	dd 32
  SYSW		dd XRES
  SYSH		dd YRES
  SYSCDIR	dd 0

include 'dat.asm'

align 4
  
  SYSKEYM	rd 256
  Fpila		rd 1024
  Dpila  	rd 1024
  Apila		rd 1024
  
  SYSNDIR	rd 8192
  SYSIDIR	rd 1024
  
align 8  
  SYSFRAME	rd XRES*YRES
  FREE_MEM	rd 1024*4 ; 4M(32bits) 16MB

section '.code' code readable executable

start:
	invoke	GetModuleHandle,0
	mov	[hinstance],eax
	invoke	LoadIcon,0,IDI_APPLICATION
	mov	[wc.hIcon],eax
	invoke	LoadCursor,0,IDC_ARROW
	mov	[wc.hCursor],eax
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
	invoke	CreateWindowEx,0,_class,_title,WS_POPUP+WS_VISIBLE,0,0,0,0,0,0,[hinstance],0
	mov	[hwnd],eax
	
;	invoke ShowWindow,[hwnd],0	;ShowWindow(hWnd,nCmdShow);
;	invoke UpdateWindow,[hwnd] ;UpdateWindow(hWnd);

	invoke	DirectDrawCreate,0,DDraw,0
	or	eax,eax
	jnz	ddraw_error
	;---
	cominvk DDraw,SetCooperativeLevel,[hwnd],DDSCL_EXCLUSIVE+DDSCL_FULLSCREEN
	or	eax,eax
	jnz	ddraw_error
	;---
	cominvk DDraw,SetDisplayMode,XRES,YRES,32
	or	eax,eax
	jnz	ddraw_error
	;---
	mov	[ddsd.dwSize],sizeof.DDSURFACEDESC
	mov	[ddsd.dwFlags],DDSD_CAPS+DDSD_BACKBUFFERCOUNT
	mov	[ddsd.ddsCaps.dwCaps],DDSCAPS_PRIMARYSURFACE+DDSCAPS_FLIP+DDSCAPS_COMPLEX
	mov	[ddsd.dwBackBufferCount],1
	
	mov [ddsd.dwWidth],XRES
	mov [ddsd.dwHeight],YRES
	
	cominvk DDraw,CreateSurface,ddsd,DDSPrimary,0
	or	eax,eax
	jnz	ddraw_error
	;---
	mov	[ddscaps.dwCaps],DDSCAPS_BACKBUFFER
	cominvk DDSPrimary,GetAttachedSurface,ddscaps,DDSBack
	or	eax,eax
	jnz	ddraw_error
	
restart:
    mov	esi,Dpila
    mov ebx,Apila
    xor eax,eax
	jmp inicio
;.................compilado.....................
include 'cod.asm'
;.................compilado.....................
	jmp SYSEND

; OS inteface
; stack............
; [esi+4] [esi] eax	  ( [esi+4] [esi] eax -- 
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
	cmp [active],0
	je	SYSPAUSA
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
	cominvk DDraw,RestoreDisplayMode 
	cominvk DDraw,Release	
;	invoke  ExitProcess,[msg.wParam]
;	invoke ShowWindow,[hwnd],SW_NORMAL ;            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
;	invoke UpdateWindow,[hwnd]	;            UpdateWindow(hWnd);
	invoke	DestroyWindow,[hwnd]
	ret

SYSPAUSA:
	invoke	WaitMessage
	invoke	PeekMessage,msg,0,0,0,PM_NOREMOVE
	or	eax,eax
	jz	SYSPAUSA
	invoke	GetMessage,msg,0,0,0
	or	eax,eax
	jz	@isyse
	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
	cmp [active],0
	je	SYSPAUSA
	cominvk DDSPrimary,Restore
@noevent:
	pop ebx eax
	ret

;===============================================
SYSRUN: ; ( "nombre" -- )

	lodsd
	ret

;===============================================
SYSREDRAW: ; ( -- )
	push edi esi eax ebx ecx
	mov [ddsd.dwSize],sizeof.DDSURFACEDESC
	cominvk DDSBack,LockSurface,0,ddsd,DDLOCK_WAIT,0
	mov	edi,[ddsd.lpSurface] 	;--- copy vframe->video
	mov	edx,[ddsd.lPitch]
	mov	esi,SYSFRAME
	mov ebx,[SYSH]
	mov eax,[SYSW]
@loopre:
	push edi
	mov ecx,eax
	rep movsd
	pop edi
	add edi,edx
	dec ebx
	jnz @loopre
	cominvk DDSBack,UnlockSurface,0
	cominvk DDSPrimary,Flip,0,DDFLIP_WAIT
	pop ecx ebx eax esi edi
	ret


;===============================================
SYSIFILL: ; ( v cnt src -- )
	push edi esi eax ebx ecx
	mov ebx,eax
	mov ecx,[esi]
	mov eax,[esi+4]
;	cld
loopf:
	mov [ebx],eax
	dec ecx
	add ebx,4
	or ecx,ecx
	jnz loopf

	;rep stosd
	;pop edi
	pop ecx ebx eax esi edi
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
	movzx eax,word [SysTime.wSecond]
	mov [esi+4],eax
	movzx eax,word [SysTime.wMinute]
	mov [esi],eax
	movzx eax,word [SysTime.wHour]
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
	invoke ReadFile,[hdir],[afile],$ffffff,cntr,0 ; hasta 1M archivo (16)
;	or	eax,eax
;	jnz	@loadend
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
    je  saveend
    or eax,eax
    jz  saveend
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
	je	wmmouseup
	cmp eax,WM_MBUTTONUP
	je	wmmouseup
	cmp eax,WM_RBUTTONUP
	je	wmmouseup
	cmp eax,WM_LBUTTONDOWN
	je	wmmousedown
	cmp eax,WM_MBUTTONDOWN
	je	wmmousedown
	cmp eax,WM_RBUTTONDOWN
	je	wmmousedown
	cmp eax,WM_KEYUP
	je	wmkeyup
	cmp	eax,WM_KEYDOWN
	je	wmkeydown
	cmp	eax,WM_CREATE
	je	wmcreate
	cmp	eax,WM_DESTROY
	je	wmdestroy
	cmp	eax,WM_ACTIVATEAPP
	je	wmactivate
;	cmp	eax,WM_QUIT
;	je wmquit
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
  wmmouseup:
	mov eax,[wparam]
	and eax,$3
	mov [SYSBM],eax
	mov eax,[SYSiPEN]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmmousedown:
	mov eax,[wparam]
	and eax,$3
	mov [SYSBM],eax
	mov eax,[SYSiPEN]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmkeyup:
	mov eax,[lparam]
	shr eax,16
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
	and eax,$7f
	mov [SYSKEY],eax
	mov eax,[SYSiKEY]
	mov [SYSEVENT],eax
	xor eax,eax
	ret
  wmdestroy:
	invoke	PostQuitMessage,0
	ret
  wmcreate:
	xor	eax,eax
	ret
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
 ; wmquit:
;	cominvk DDraw,RestoreDisplayMode
;	cominvk DDraw,Release
  finish:
	ret
endp

;----------------------------------------------
ddraw_error:
	mov	eax,_error
	invoke	MessageBox,[hwnd],eax,_error,MB_OK
	invoke	DestroyWindow,[hwnd]
	invoke	PostQuitMessage,1
errloop:	
	call SYSUPDATE
	jmp	errloop

section '.idata' import data readable

library kernel,'KERNEL32.DLL', user,'USER32.DLL', ddraw,'DDRAW.DLL'

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
;	 GetFileSize,'GetFileSize',\	 

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
	 ChangeDisplaySettings,'ChangeDisplaySettingsA'


import ddraw,\
	 DirectDrawCreate,'DirectDrawCreate'
	 
include 'rsrc.rc'
