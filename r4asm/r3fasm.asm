;-------------------------------------
; Inteface Windows :R3 - PHREDA 2019
;-------------------------------------
format PE GUI 4.0
entry start

;MAXMEM         equ     1373741824
;MAXMEM         equ 1073741824  ; 1GB
MAXMEM		equ 536870912	; 512MB

DWEXSTYLE	equ WS_EX_APPWINDOW
DWSTYLE 	equ WS_VISIBLE+WS_CAPTION+WS_SYSMENU

;XRES equ 640
;YRES equ 480
XRES equ 1024
;XRES equ 800
YRES equ 600
;XRES equ 1024
;YRES equ 768
;XRES equ 1280
;YRES equ 800

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
	mov	dword [wc.lpszClassName],_title
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

	invoke	CreateWindowEx,DWEXSTYLE,_title,_title,DWSTYLE,0,0,[rec.right],[rec.bottom],0,0,[hinstance],0
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

	invoke VirtualAlloc,0,MAXMEM,MEM_COMMIT+MEM_RESERVE,PAGE_READWRITE ;
	or eax,eax
	jz SYSEND
	mov [FREE_MEM],eax

;---------- INICIO
	mov ebp,DATASTK
	xor eax,eax
	call INICIO
	jmp SYSEND
;----- CODE -----
include 'code.asm'
;----- CODE -----

;--------------------------------------
align 16
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
    cmp eax,WM_SYSKEYDOWN
    je	wmkeydown
    cmp eax,WM_CLOSE
    je	SYSEND
    cmp eax,WM_DESTROY
    je	SYSEND
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
	and eax,$ff
	or eax,$100
	mov [SYSKEY],eax
	xor eax,eax
	ret
  wmkeydown:			; cmp [wparam],VK_ESCAPE ; je wmdestroy
	mov eax,[lparam]
	shr eax,16
	and eax,$ff
	mov [SYSKEY],eax
	xor eax,eax
	ret
endp

; OS inteface
; stack............
; [ebp+4] [ebp] eax       ( [ebp+4] [ebp] eax --
;===============================================
align 16
SYSUPDATE: ; ( sleep -- sleep )
	pusha
	invoke Sleep,eax
	xor eax,eax
	mov [SYSKEY],eax
	invoke PeekMessage,msg,eax,eax,eax,PM_NOREMOVE
	or	eax,eax
	jz	.end
	invoke	GetMessage,msg,0,0,0
	or	eax,eax
	jz	.endstop
;       invoke  TranslateMessage,msg
	invoke	DispatchMessage,msg
.end:
	popa
	ret
.endstop:
	popa
;===============================================
align 16
SYSEND: ; ( -- )
	invoke ReleaseDC,[hwnd],[hDC]
	invoke DestroyWindow,[hwnd]
	invoke VirtualFree, [FREE_MEM], 0, MEM_RELEASE
	invoke ExitProcess,0
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
SYSMSEC: ;  ( -- msec )
	mov [ebp],eax
	lea ebp,[ebp+4]
	invoke GetTickCount
	ret

;===============================================
align 16
SYSTIME: ;  ( -- hhmmss )
	mov [ebp],eax
	lea ebp,[ebp+4]
	invoke GetLocalTime,SysTime
	movzx eax,word [SysTime.wHour]
	shl eax,16
	movzx ebx,word [SysTime.wMinute]
	shl ebx,8
	or eax,ebx
	movzx ebx,word [SysTime.wSecond]
	or eax,ebx
	ret

;===============================================
align 16
SYSDATE: ;  ( -- yyyymmdd )
	mov [ebp],eax
	lea ebp,[ebp+4]
	invoke GetLocalTime,SysTime
	movzx eax,word [SysTime.wYear]
	shl eax,16
	movzx ebx,word [SysTime.wMonth]
	shl ebx,8
	or eax,ebx
	movzx ebx,word [SysTime.wDay]
	or eax,ebx
	ret

;===============================================
align 16
SYSFFIRST: ; ( "path" -- fdd )
	push ebx ecx edx edi esi
	mov esi,_dir
.bcpy:
	mov bl,[eax]
	or bl,bl
	jz .ends
	mov byte[esi],bl
	add eax,1
	add esi,1
	jmp .bcpy
.ends:
	mov dword [esi],$002A2f2f
	invoke FindFirstFile,_dir,fdd
	mov [hfind],eax
	cmp eax,INVALID_HANDLE_VALUE
	je .nin
	mov eax,fdd
	jmp .fin
.nin:
	xor eax,eax
.fin:
	pop esi edi edx ecx ebx
	ret

;===============================================
align 16
SYSFNEXT: ; ( -- fdd/0)
	mov [ebp], eax
	lea ebp,[ebp+4]
	push ebx ecx edx edi esi
	invoke FindNextFile,[hfind],fdd
	or eax,eax
	jz .nin
	mov eax,fdd
	jmp .fin
.nin:
	invoke FindClose,[hfind]
	xor eax,eax
.fin:
	pop esi edi edx ecx ebx
	ret

;===============================================
align 16
SYSLOAD: ; ( 'from "filename" -- 'to )
	invoke CreateFile,eax,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	mov eax,[ebp]
	jz .end
	mov [afile],eax
.again:
	invoke ReadFile,[hdir],[afile],$fffff,cntr,0
	mov eax,[cntr]
	add [afile],eax
	or eax,eax
	jnz .again
	invoke CloseHandle,[hdir]
	mov eax,[afile]
.end:
	lea ebp,[ebp-4]
	ret

;===============================================
align 16
SYSSAVE: ; ( 'from cnt "filename" -- )
	invoke CreateFile,eax,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	jz .end
	mov edx,[ebp+4]
	mov ecx,[ebp]
    invoke WriteFile,[hdir],edx,ecx,cntr,0
    cmp [cntr],ecx
    je	.end
    or eax,eax
    jz	.end
    invoke CloseHandle,[hdir]
.end:
	lea ebp,[ebp-12]
	mov eax,[ebp]
	ret

;===============================================
align 16
;FILE_APPEND_DATA=4
SYSAPPEND: ; ( 'from cnt "filename" -- )
	invoke CreateFile,eax,4,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,0
	mov [hdir],eax
	or eax,eax
	jz .end
	mov edx,[ebp+4]
	mov ecx,[ebp]
    invoke WriteFile,[hdir],edx,ecx,cntr,0
    cmp [cntr],ecx
    je	.end
    or eax,eax
    jz	.end
    invoke CloseHandle,[hdir]
.end:
	lea ebp,[ebp-12]
	mov eax,[ebp]
	ret

;===============================================
align 16
SYSYSTEM: ; ( "system" -- )
	or eax,eax
	jnz .no0
	mov eax,[ProcessInfo.hProcess]
	or eax,eax
	jz .termp
	invoke TerminateProcess,eax,0
	invoke CloseHandle,[ProcessInfo.hThread]
	invoke CloseHandle,[ProcessInfo.hProcess]
	xor eax,eax
    mov [ProcessInfo.hProcess],eax
.termp:
	mov eax,-1
	ret
.no0:
	cmp eax,-1
	jne .non
	mov eax,[ProcessInfo.hProcess]
	or eax,eax
	jz .end
	invoke WaitForSingleObject,[ProcessInfo.hProcess],0
	cmp eax,WAIT_TIMEOUT
	jne .termp
	xor eax,eax
	ret
.non:
	push eax edi ecx
	xor eax,eax
	mov edi,StartupInfo
	mov ecx,17
	rep stosd
;	invoke ZeroMemory,StartupInfo,StartupInfo.size
	mov eax,17*4
	mov [StartupInfo.cb],eax
	pop ecx edi eax
	invoke CreateProcess,0,eax,0,0,FALSE, 0x08000000,0,0,StartupInfo,ProcessInfo
.end:
	lea ebp,[ebp-4]
	mov eax,[ebp]
	ret

; from user revolution in
; https://board.flatassembler.net/topic.php?t=3978&postdays=0&postorder=asc&start=0
;isqrt_eax_p6: ;for processors with CMOV
;SYSQRT:
;	xor ebx,ebx
;	xor edx,edx
;	bsr edi,eax
;	cmovz edi,eax
;	and edi,-2
;	lea ecx,[edi+2]
;	ror eax,cl
;.dig: shld ebx,eax,2
;	lea ecx,[edx*4+1]
;	mov esi,ebx
;	sub ebx,ecx
;	cmovb ebx,esi
;	cmc
;	adc edx,edx
;	shl eax,2
;	sub edi,2
;	jns .dig
;	mov eax,edx
;	ret

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
	CreateProcess, "CreateProcessA",\
	TerminateProcess ,  'TerminateProcess' , \
	WaitForSingleObject, 'WaitForSingleObject',\
	 GetLocalTime,'GetLocalTime',\
	 SetCurrentDirectory,'SetCurrentDirectoryA',\
	 FindFirstFile,'FindFirstFileA',\
	 FindNextFile,'FindNextFileA',\
	 Sleep,'Sleep',\
	 VirtualAlloc,'VirtualAlloc',\
	 VirtualFree,'VirtualFree',\
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

	_title	db ':r4',0
	_dir	rb 1024

align 4
	SYSXYM		dd 0
	SYSBM		dd 0
	SYSKEY		dd 0
	FREE_MEM	dd 0
	hinstance	dd 0
	hwnd		dd 0
	hDC			dd 0
	hfind		dd 0
	hdir		dd 0
	afile		dd 0
	cntr		dd 0

	wc		WNDCLASS ;EX?
	msg		MSG
	rec		RECT
	bmi		BITMAPINFOHEADER
	SysTime SYSTEMTIME
	fdd		WIN32_FIND_DATAA

	ProcessInfo	PROCESS_INFORMATION
	StartupInfo STARTUPINFO

;*** optimizable
;       SYSW    dd XRES
;       SYSH    dd YRES
;*** optimizable
align 16
	include 'data.asm'

align 16
	SYSFRAME	rd XRES*YRES
	DATASTK 	rd 1024
;	FREE_MEM        rd 1024*1024*16 ; 16M(32bits) 64MB(8bits)
