;===========================================================================================
; directxproc.asm    AsmGges France                http://www.chez.com/asmgges/index.htm
;===========================================================================================

;===========================================================================================
; Création d'une surface
;-------------------------------------------------------------------------------------------
; @AdrSurface = adresse de la variable qui va contenir l'adresse de la surface crée
; @LSurface   = largeur de la surface en pixels
; @HSurface   = hauteur de la surface en pixels
;===========================================================================================
proc CreateSurf @AdrSurface, @LSurface, @HSurface

    stdcall ZeroMemory,ddsd,sizeof.DDSURFACEDESC
    mov [ddsd.dwSize],sizeof.DDSURFACEDESC
    mov [ddsd.dwFlags],DDSD_CAPS+DDSD_WIDTH+DDSD_HEIGHT
    mov [ddsd.ddsCaps.dwCaps],DDSCAPS_OFFSCREENPLAIN
    mov eax,[@LSurface]
    mov [ddsd.dwWidth],eax
    mov eax,[@HSurface]
    mov [ddsd.dwHeight],eax
    ddcall DD_CreateSurface,[DDraw],ddsd,[@AdrSurface],0

    ret
endp
;===========================================================================================
; Remplir une surface avec une couleur
;-------------------------------------------------------------------------------------------
; @NumSurf = [Nom] Surface à remplir
; @Color   = couleur de remplissage format RGB 000000h
;===========================================================================================
proc FillSurface @NumSurf, @Color

    stdcall ZeroMemory,ddbltfx,sizeof.DDBLTFX
    mov [ddbltfx.dwSize],sizeof.DDBLTFX
    mov eax,[@Color]
    mov [ddbltfx.dwFillColor],eax
    ddcall DDS_Blt,[@NumSurf],0,0,0,DDBLT_COLORFILL+DDBLT_WAIT,ddbltfx
    
    ret
endp
;===========================================================================================
; Flip surface Back => surface Primary (Window Mode)
;===========================================================================================
FlipBackWinMode:
    invoke GetWindowRect,[hWin],rect2

    mov [rect1.left],0
    mov [rect1.top],0
    mov [rect1.right],WSCREEN
    mov [rect1.bottom],HSCREEN

    mov eax,[rect2.left]
    add eax,WSCREEN
    mov [rect2.right],eax

    mov eax,[rect2.top]
    add eax,[HBarTitle]
    mov [rect2.top],eax

    add eax,HSCREEN
    mov [rect2.bottom],eax
    ddcall DDS_Blt,[Primary],rect2,[Back],rect1,DDBLT_WAIT,0

    ret
;===========================================================================================
;///////////////////////////////////////////////////////////////////////////////////////////
;===========================================================================================