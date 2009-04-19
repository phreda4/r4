;=========================================================;
; VesaR4                                         02/03/07 ;
; R4dex interface
;---------------------------------------------------------;
; Vesa/mouse Demo.                                        ;
;                                                         ;
; DexOS V0.01                                             ;
; (c) Craig Bamford, All rights reserved.                 ;
; version :r4
; Pablo H. Reda                          
;=========================================================;

XRES equ 640
YRES equ 480
VMODO equ $4112

;XRES equ 1024
;YRES equ 768
;VMODO equ $4118

use32
	ORG   0x400000				       ; where our program is loaded to
	jmp   start				       ; jump to the start of program.
	db    'DEX1'				       ; We check for this, to make shore it a valid Dex4u file.
msg1:	
	db " Vesa/Mouse Error",13
	db " Press any key to exit. ",13,0 
	
 ;----------------------------------------------------;
 ; Start of program.                                  ;
 ;----------------------------------------------------;
start:
	mov   ax,18h
	mov   ds,ax
	mov   es,ax
 ;----------------------------------------------------;
 ; Get calltable address.                             ;
 ;----------------------------------------------------;
	mov   edi,Functions			; this is the interrupt
	mov   al,0					; we use to load the DexFunction.inc
	mov   ah,0x0a				; with the address to dex4u functions.
	int   40h
 ;----------------------------------------------------;Some vesa modes 0x4118 0x411B 0x4115 0x4112
 ; Do realmode int (vesa).                            ;
 ;----------------------------------------------------;
	mov   ecx,VMODO
	call  [SetVesaMode]
	cmp   ah,1
	je    INIERROR
 ;----------------------------------------------------;
 ; Load vesa info.                                    ;
 ;----------------------------------------------------;
	call  [LoadVesaInfo]		; Load vesa info into the vars in Dex.inc
	mov   edi,VESA_Info
	mov   ecx,193
	cld
	cli
	rep   movsd
	sti
 ;----------------------------------------------------;
 ; start 
 ;----------------------------------------------------;
	call  [ResetMouse]
	cmp   ax,0xffff
	jne  INIERROR
	xor   eax,eax
	mov   ebx,eax
 ;----------------------------------------------------;
 ; Mouse set Min Max XY.                              ;
 ;----------------------------------------------------;  
	mov   ax,[ModeInfo_XResolution]
	mov   bx,[ModeInfo_YResolution]
;	sub   bx,4
;	sub   ax,10
	call  [SetMouseMaxMinXY]
 ;----------------------------------------------------;
 ; Mouse set start XY.                                ;
 ;----------------------------------------------------; 
	mov   ax,[ModeInfo_XResolution]
	mov   bx,[ModeInfo_YResolution]
	shr   bx,1
	shr   ax,1
	call  [SetMouseXY]
;---- Inicio R4	
	mov [NIVEL0],esp	
 	call SYSUPDATE
	call SYSREDRAW
    mov	esi,pila
    xor eax,eax
	jmp inicio
;.................compilado.....................
include 'cod.asm'
;.................compilado.....................
	
;===============================================
SYSEND:
	call  [SetMouseOff]		; Turn mouse off
	call  [SetDex4uFonts]	; Set text mode
	mov esp,[NIVEL0]		; nivel de llamada 0
	ret						; Return control to DexOS

;===============================================
SYSUPDATE:
	push eax
	call [KeyPressedScanNW]
	cmp  al,0
	je sigue
	cmp ah,1
	je SYSEND
	shr eax,8
	and eax,$7f
	mov [SYSKEY],eax
;	call  [KeyPressedNoWait]		     ; See if key pressed
;	cmp   ax,1
	je   SYSEND			      ; if not loop
sigue:
	xor   ecx,ecx	; mouse
	xor   edx,edx
	call  [GetMousePos] ; BL = button pressed, 01 = rightbutton, 10 = centerbutton, 100 = leftbutton. CX=X, DX=Y.
	and ebx,$7
	and ecx,$ffff
	shl edx,16
	mov eax,ecx
	or eax,edx
	cmp eax,[SYSXYM]
	je nomueve
	mov [SYSXYM],eax	
	mov eax,[SYSMM]
	mov [SYSEVENT],eax
	jmp dispara
nomueve:
	cmp ebx,[SYSBM]
	je endev
	or ebx,ebx
	jnz mousestart
	mov eax,[SYSME]
	jmp mouseev
mousestart:	
	mov eax,[SYSMS]
mouseev:
	mov [SYSBM],ebx
dispara:	
	mov eax,[SYSEVENT]
	or eax,eax
	jz endev
	mov [SYSEVENT],0
;	mov ebx,eax
;	pop eax
;	jmp ebx
endev:
	pop eax
	ret

;===============================================	
SYSRUN: ; ( "nombre" -- )
	ret

;===============================================
SYSREDRAW: ; BuffToScreen32:
	pushad
	push es
	mov   ax,8h 
	mov   es,ax
	mov   edi,[ModeInfo_PhysBasePtr]
	mov   esi,SYSFRAME
	mov   ecx,[SYSVSIZE]
	cld
	cli
	rep   movsd
	sti
	;<--- here draw the mouse if active...
	pop es
	popad
	ret
	
;===============================================
SYSIFILL: ; ( v cnt src -- )     
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
SYSMSEC:
	lea esi,[esi-4]
	mov [esi], eax
	mov eax,[last_tick]
	inc eax
	mov [last_tick],eax
;	invoke	GetTickCount 	;mov	[last_tick],eax
	ret
	
;===============================================	
SYSTIME: 
	lea esi,[esi-12]
	mov [esi+8],eax
	cli
	mov   al,4			                 ; RTC  04h
	out   70h,al
	in    al,71h		                 ; read hour
	call Bcd2Bin
	mov [esi+4],eax ; NOS-1
	mov   al,2			                 ; RTC  02h
	out   70h,al
	in    al,71h		                 ; read minute
	call Bcd2Bin
	mov [esi],eax ; NOS
	xor   al,al			                 ; RTC  00h
	out   70h,al
	in    al,71h		                 ; read second
	call Bcd2Bin
	sti
	ret
	
;===============================================	
SYSDATE:
	lea esi,[esi-12]
	mov [esi+8],eax
	cli
    xor eax,eax
	mov   al,9			                 ; RTC 09h
	out   70h,al
	in    al,71h			                 ; read year
	call Bcd2Bin
	mov [esi+4],eax	; NOS-1
	mov   al,8			                 ; RTC 08h
	out   70h,al
	in    al,71h			                 ; read month
	call Bcd2Bin
	mov [esi],eax	; NOS
	mov   al,7			                 ; RTC 07h
	out   70h,al
	in    al,71h			                 ; read day
	call Bcd2Bin	;TOS
    sti
    ret

Bcd2Bin: ; ebx trash
	xor eax,eax
	mov   bl,0x0a
	mov   bh,al
	shr   al,4
	mul   bl
	and   bh,0x0f
	add   al,bh
	ret
	
;===============================================		
SYSDIR: ; ( "path" -- )
	ret
	
;===============================================	
SYSFILE: ; ( nro -- "name" )
	ret

;===============================================	
SYSLOAD: ; ( 'from "filename" -- 'to )
;FloppyfileLoad	     rd 1	    
; 18.Loads a file from floppy,
;ESI points to name of file to load,
;EDI = place to load file to,
;set's CF to 1 on error ,sucsess EBX = number of sector loaded..
	ret

;===============================================	
SYSSAVE: ; ( 'from cnt "filename" -- )
;|WriteCommand	     rd 1	    
; 43.Writes a file to floppy, 
;ESI points to name of file to make, 
;EDI = place to load file from, 
;EAX = size of file to load in bytes, 
;set's CF to 1 on error, error code in AH, 
;sucsess EBX = number of sectors loaded, ECX = file size in bytes.
	ret

 ;----------------------------------------------------;
 ; Display Vesa Error message.                        ;
 ;----------------------------------------------------;
INIERROR:
	call  [SetDex4uFonts]			      ; We end up here if vesa mode not supported.
	mov   esi,msg1
	call  [PrintString]
	call  [WaitForKeyPress]
	ret
	
 ;----------------------------------------------------;
 ; Data.                                              ;
 ;----------------------------------------------------;
align 4

  include 'Dex.inc'
  
align 4

last_tick dd 0

  NIVEL0	dd 0	; pila de codigo
  
  SYSEVENT	dd 0
  SYSXYM	dd 0
  SYSBM		dd 0
  SYSKEY	dd 0
  SYSMS		dd 0
  SYSMM		dd 0
  SYSME		dd 0
  
  SYSBPP	dd 32
  SYSW		dd XRES
  SYSH		dd YRES
  SYSVSIZE	dd XRES*YRES
  
include 'dat.asm'

align 4

  SYSKEYM	rd 256
  ppila		rd 1024
  pila  	rd 1024
  SYSFRAME	rd XRES*YRES
  FREE_MEM	rd 1024*4 ; 4M(32bits) 16MB