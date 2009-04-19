;===========================================================================================
; fullwinmode.asm  Fasm assembler
; Initialisation DirectX Direct Draw en mode plein écran ou en mode fenêtre
; Programmé par AsmGges France                       http://www.chez.com/asmgges/index.htm
;===========================================================================================

format PE GUI 4.0
entry start

    include 'win32a.inc'
    include 'macro\if.inc'
    include 'ggesdx\ddrawgges.inc'

    WSCREEN = 640
    HSCREEN = 480

;===========================================================================================
section '.code' code readable executable

start:
    invoke  MessageBox,HWND_DESKTOP,MsgMode,WinCaption,MB_YESNO
    .if eax = IDYES
        mov [FullMode],1
    .endif

    invoke GetModuleHandle,NULL
    mov [wc.hInstance],eax

    invoke LoadIcon,[wc.hInstance],17
    mov [wc.hIcon],eax

    invoke LoadCursor,NULL,IDC_ARROW
    mov [wc.hCursor],eax

    invoke RegisterClass,wc

    invoke GetSystemMetrics,SM_CXSCREEN
    mov [rectuser.right],eax           ;sauve le clipping actuel en x dans rectuser (WinMode)
    sub eax,WSCREEN
    shr eax,1
    mov [rect2.left],eax

    invoke GetSystemMetrics,SM_CYSCREEN
    mov [rectuser.bottom],eax          ;sauve le clipping actuel en y dans rectuser (WinMode)
    sub eax,HSCREEN
    shr eax,1
    mov [rect2.top],eax

    .if [FullMode] = 1
        ;----------------------------------
        ; Création feneêtre pour plein écran
        ;----------------------------------
        invoke CreateWindowEx,0,ClassName,WinCaption,WS_POPUP+WS_VISIBLE,\
                                            0,0,0,0,0,0,[wc.hInstance],0
        mov [hWin],eax

    .else
        mov [rect1.left],0
        mov [rect1.top],0
        mov [rect1.right],WSCREEN
        mov [rect1.bottom],HSCREEN
        invoke AdjustWindowRectEx,rect1,04CA0000h,0,NULL

        mov eax,[rect1.bottom]
        sub eax,[rect1.top]
        sub eax,HSCREEN
        sub eax,3            ;moins bord inférieur menu/fenêtre active
        mov [HBarTitle],eax  ;hauteur du bandeau titre

        invoke GetSystemMetrics,SM_CYSCREEN
        mov [rectuser.bottom],eax
        sub eax,HSCREEN
        sub eax,[HBarTitle]
        shr eax,TRUE
        mov [rect2.top],eax

        mov eax,HSCREEN
        add eax,[HBarTitle]

        ;----------------------------------
        ; Création fenêtre barre supérieure
        ;----------------------------------
        invoke CreateWindowEx,NULL,ClassName,WinCaption,04CA0000h,[rect2.left],[rect2.top],\
                              WSCREEN,eax,NULL,0,[wc.hInstance],NULL
        mov [hWin],eax
    .endif

    invoke ShowWindow,[hWin],SW_SHOWDEFAULT
    invoke UpdateWindow,[hWin]

    ;-----------------------------
    ; Initialisation de DirectDraw
    ;-----------------------------
    invoke DirectDrawCreate,0,DDraw,0
    or eax,eax
    jnz DdrawError

    .if [FullMode] = 1
        ;--------------------
        ; Demande plein écran
        ;--------------------
        ddcall DD_SetCooperativeLevel,[DDraw],[hWin],DDSCL_EXCLUSIVE+DDSCL_FULLSCREEN
        or eax,eax
        jnz DdrawError

        ;---------------------------------
        ; Passage en 640x480 pixels 16bits
        ;---------------------------------
        ddcall DD_SetDisplayMode,[DDraw],WSCREEN,HSCREEN,16
        or eax,eax
        jnz DdrawError

        ;----------------------------------------------------
        ; Création d'une surface primaire avec un back-buffer
        ;----------------------------------------------------
        stdcall ZeroMemory,ddsd,sizeof.DDSURFACEDESC
        mov [ddsd.dwSize],sizeof.DDSURFACEDESC
        mov [ddsd.dwFlags],DDSD_CAPS + DDSD_BACKBUFFERCOUNT
        mov [ddsd.ddsCaps.dwCaps],DDSCAPS_PRIMARYSURFACE+DDSCAPS_FLIP+DDSCAPS_COMPLEX
        mov [ddsd.dwBackBufferCount],1
        ddcall DD_CreateSurface,[DDraw],ddsd,Primary,0
        or eax,eax
        jnz DdrawError

        stdcall ZeroMemory,ddscaps,sizeof.DDSCAPS
        mov [ddscaps.dwCaps],DDSCAPS_BACKBUFFER
        ddcall DDS_GetAttachedSurface,[Primary],ddscaps,Back
        or eax,eax
        jnz DdrawError

    .else
        ;---------
        ; Win Mode
        ;---------
        ddcall DD_SetCooperativeLevel,[DDraw],[hWin],DDSCL_NORMAL
        or eax,eax
        jnz DdrawError

        ;--------------------------------
        ; Création de la surface primaire
        ;--------------------------------
        stdcall ZeroMemory,ddsd,sizeof.DDSURFACEDESC
        mov [ddsd.dwSize],sizeof.DDSURFACEDESC
        mov [ddsd.dwFlags],DDSD_CAPS
        mov [ddsd.ddsCaps.dwCaps],DDSCAPS_PRIMARYSURFACE
        ddcall DD_CreateSurface,[DDraw],ddsd,Primary,0
        or eax,eax
        jnz DdrawError

        ;-----------------------------------
        ; Création de la surface Back-buffer
        ;-----------------------------------
        stdcall ZeroMemory,ddsd,sizeof.DDSURFACEDESC
        mov [ddsd.dwSize],sizeof.DDSURFACEDESC
        mov [ddsd.dwFlags],DDSD_CAPS+DDSD_WIDTH+DDSD_HEIGHT
        mov [ddsd.ddsCaps.dwCaps],DDSCAPS_OFFSCREENPLAIN
        mov [ddsd.dwWidth],WSCREEN
        mov eax,HSCREEN
        add eax,[HBarTitle]
        mov [ddsd.dwHeight],eax
        ddcall DD_CreateSurface,[DDraw],ddsd,Back,0
        or eax,eax
        jnz DdrawError

        ;----------------------
        ; Création d'un clipper
        ;----------------------
        ddcall DD_CreateClipper,[DDraw],0,lpClipper,0
        or eax,eax
        jnz DdrawError

        ddcall DDC_SetHWnd,[lpClipper],0,[hWin]
        or eax,eax
        jnz DdrawError

        ddcall DDS_SetClipper,[Primary],[lpClipper]
        or eax,eax
        jnz DdrawError

    .endif

    invoke timeBeginPeriod,1
    mov [FpsMax],60

    jmp MenuLoop

Debut:


;===========================================================================================

GameLoop:

    stdcall FillSurface,[Back],0ffh

    ;----------------------------
    ; Ecrire dans la surface Back
    ;----------------------------
    ddcall DDS_GetDC,[Back],hdc
    .if eax = 0
        invoke SetBkColor,[hdc],0ff0000h

        invoke SetTextColor,[hdc],0ffh
        .if [FullMode] = 0
            mov eax,MsgWinMode

        .else
            mov eax,MsgFullMode

        .endif
        mov [rect1.left],0
        mov [rect1.top],170
        mov [rect1.right],WSCREEN
        mov [rect1.bottom],230
        invoke DrawText,[hdc],eax,0-1,rect1,DT_CENTER+DT_SINGLELINE+DT_BOTTOM

        ddcall DDS_ReleaseDC,[Back],[hdc]
    .endif

    jmp MessageLoop

;===========================================================================================
MenuLoop:



;===========================================================================================

MessageLoop:

    invoke PeekMessage,msg,0,0,0,PM_NOREMOVE
    .if eax <> 0
        invoke GetMessage,msg,0,0,0
        .if eax = 0
            jmp ExitGame
        .endif
        invoke TranslateMessage,msg
        invoke DispatchMessage,msg
        jmp MessageLoop
    .endif

    .if [bActive] = 0
        invoke WaitMessage
        jmp MessageLoop
    .endif

    ddcall DDS_IsLost,[Primary]
    .if eax <> 0
        .if eax = DDERR_SURFACELOST
            ddcall DDS_Restore,[Primary]
        .else
            jmp ExitGame
        .endif
    .endif

    ;-------------------------------------------------
    ; Régule la vitesse de rafraichissement de l'écran
    ;-------------------------------------------------
    stdcall FpsLimiter,[FpsMax]

    ;-----
    ; Flip
    ;-----
    .if [FullMode] = 1
        ddcall DDS_Flip,[Primary],0,DDFLIP_WAIT
    .else
        call FlipBackWinMode
    .endif

    ;-----------------------
    ; Ecran de dessin et jeu
    ;-----------------------
    jmp GameLoop

;===========================================================================================

DdrawError:
    mov eax,MsgDdError
    jmp Error

DataError:
    mov eax,MsgDataError

Error:
    invoke MessageBox,[hWin],eax,WinCaption,0
    call LibereSurf
    invoke DestroyWindow,[hWin]
    invoke PostQuitMessage,1
    jmp MessageLoop

ExitGame:
    invoke ExitProcess,[msg.wParam]

;===========================================================================================
;===========================================================================================
proc WindowProc uses ebx esi edi, @hWnd, @uMsg, @wParam, @lParam

    .if [@uMsg] = WM_CLOSE
        call LibereSurf

    .elseif [@uMsg] = WM_ACTIVATE
        mov eax,[@wParam]
        mov [bActive],al

    .elseif [@uMsg] = WM_KEYDOWN
        .if [@wParam] = VK_ESCAPE
            invoke SendMessage,[@hWnd],WM_CLOSE,0,0
        .endif

    .else
        invoke DefWindowProc,[@hWnd],[@uMsg],[@wParam],[@lParam]
        ret

    .endif

    mov eax,0
    ret
endp

;===========================================================================================
; Libère les surfaces
;===========================================================================================
LibereSurf:

    invoke timeEndPeriod,1

    .if [DDraw] <> 0
        .if [lpClipper] <> 0
            ddcall DDC_Release,[lpClipper]
            mov [lpClipper],0
        .endif
        .if [Back] <> 0
            ddcall DDS_Release,[Back]
            mov [Back],0
        .endif
        .if [Primary] <> 0
            ddcall DDS_Release,[Primary]
            mov [Primary],0
        .endif
        ddcall DD_Release,[DDraw]
        mov [DDraw],0
    .endif
 
    invoke PostQuitMessage,0

    ret
;===========================================================================================

    include 'ggesdx\directxproc.asm'
    include 'ggesdx\generalproc.asm'

;===========================================================================================
section '.data' data readable writeable

 ClassName     db 'AsmGges',0
 WinCaption    db ' AsmGges Win32Asm Fasm DirectX',0
 BoxCaption    db ' AsmGges Win32Asm',0
 MsgMode       db '            Full screen mode ?',0
 MsgDdError    db 'Direct Draw: failed',0
 MsgWinMode    db 'Fasm DirectX Window mode  Exit=ESC',0
 MsgFullMode   db 'Fasm DirectX Full screen mode  Exit=ESC',0
 MsgDataError  db 'Opening data file: failed',0
 align 4

 hdc           dd 0
 hWin          dd 0
 FullMode      dd 0
 HBarTitle     dd 0
 bActive       db 0
 align 4

 FpsMax        dd 0
 NextTimeEdx   dd 0
 NextTimeEax   dd 0
 PerfFreq      dq 0
 PerfCounter   dq 0

 DDraw         dd 0 
 lpClipper     dd 0

 Primary       dd 0   
 Back          dd 0   

section '.bss' readable writeable

 wc            WNDCLASS      0,WindowProc,0,0,0,0,0,0,0,ClassName
 msg           MSG           

 ddsd          DDSURFACEDESC 
 ddscaps       DDSCAPS       
 ddbltfx       DDBLTFX       
 ddpixelformat DDPIXELFORMAT
 ddcolorkey    DDCOLORKEY    

 rect1         RECT 
 rect2         RECT 
 rectuser      RECT 

;===========================================================================================
section '.idata' import data readable

  library kernel32,'KERNEL32.DLL',\
            user32,'USER32.DLL',\
             gdi32,'GDI32.DLL',\
             winmm,'WINMM.DLL',\
             ddraw,'DDRAW.DLL'

  include 'apia\kernel32.inc'
  include 'apia\user32.inc'
  include 'apia\gdi32.inc'

  import winmm,\
         timeBeginPeriod,'timeBeginPeriod',\
         timeEndPeriod,'timeEndPeriod',\
         PlaySound,'PlaySoundA',\
         mciSendCommand,'mciSendCommandA'

  import ddraw,\
         DirectDrawCreate,'DirectDrawCreate'

;===========================================================================================
section '.rsrc' resource data readable

  directory RT_ICON,icons,\
     RT_GROUP_ICON,group_icons

  resource icons,\
    1,LANG_NEUTRAL,icon_data

  resource group_icons,\
    17,LANG_NEUTRAL,main_icon

  icon main_icon,icon_data,'res\france.ico'

;===========================================================================================
;///////////////////////////////////////////////////////////////////////////////////////////
;===========================================================================================
