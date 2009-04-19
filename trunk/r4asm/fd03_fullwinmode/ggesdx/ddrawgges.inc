;===========================================================================================
; ddrawgges.inc
; 11/10/2006 Fasm assembler
; Programmed by AsmGges            Asmges@AOL.com     http://www.chez.com/asmgges/index.htm
;===========================================================================================

macro ddcall function,surfdest,[arg]
{
  common
  if ~ arg eq
     reverse
     pushd arg
     common
  end if
  mov eax,surfdest
  push eax
  mov eax,[eax]
  call dword[eax+function]
}
;===========================================================================================
struct DDCOLORKEY
  dwColorSpaceLowValue   dd 0
  dwColorSpaceHighValue  dd 0
ends

struct DDPIXELFORMAT
  dwSize                 dd 0
  dwFlags                dd 0
  dwFourCC               dd 0
 union
  dwRGBBitCount          dd 0
  dwYUVBitCount          dd 0
  dwZBufferBitDepth      dd 0
  dwAlphaBitDepth        dd 0
  dwLuminanceBitCount    dd 0
  dwBumpBitCount         dd 0
 ends
 union
  dwRBitMask             dd 0
  dwYBitMask             dd 0
  dwStencilBitDepth      dd 0
  dwLuminanceBitMask     dd 0
  dwBumpDuBitMask        dd 0
 ends
 union
  dwGBitMask             dd 0
  dwUBitMask             dd 0
  dwZBitMask             dd 0
  dwBumpDvBitMask        dd 0
 ends
 union
  dwBBitMask             dd 0
  dwVBitMask             dd 0
  dwStencilBitMask       dd 0
  dwBumpLuminanceBitMask dd 0
 ends
 union
  dwRGBAlphaBitMask       dd 0
  dwYUVAlphaBitMask       dd 0
  dwLuminanceAlphaBitMask dd 0
  dwRGBZBitMask           dd 0
  dwYUVZBitMask           dd 0
 ends
ends

struct DDSCAPS
  dwCaps dd 0
ends

struct DDSURFACEDESC
  dwSize            dd 0
  dwFlags           dd 0
  dwHeight          dd 0
  dwWidth           dd 0
 union
  lPitch            dd 0
  dwLinearSize      dd 0
 ends
  dwBackBufferCount dd 0
 union
  dwMipMapCount     dd 0
  dwZBufferBitDepth dd 0
  dwRefreshRate     dd 0
 ends
  dwAlphaBitDepth   dd 0
  dwReserved        dd 0
  lpSurface         dd 0
  ddckCKDestOverlay DDCOLORKEY
  ddckCKDestBlt     DDCOLORKEY
  ddckCKSrcOverlay  DDCOLORKEY
  ddckCKSrcBlt      DDCOLORKEY
  ddpfPixelFormat   DDPIXELFORMAT
  ddsCaps           DDSCAPS
ends

struct DDBLTFX
  dwSize                   dd 0
  dwDDFX                   dd 0
  dwROP                    dd 0
  dwDDROP                  dd 0
  dwRotationAngle          dd 0
  dwZBufferOpCode          dd 0
  dwZBufferLow             dd 0
  dwZBufferHigh            dd 0
  dwZBufferBaseDest        dd 0
  dwZDestConstBitDepth     dd 0
union
  dwZDestConst             dd 0
  lpDDSZBufferDest         dd 0
ends
  dwZSrcConstBitDepth      dd 0
union
  dwZSrcConst              dd 0
  lpDDSZBufferSrc          dd 0
ends
  dwAlphaEdgeBlendBitDepth dd 0
  dwAlphaEdgeBlend         dd 0
  dwReserved               dd 0
  dwAlphaDestConstBitDepth dd 0
union
  dwAlphaDestConst         dd 0
  lpDDSAlphaDest           dd 0
ends
  dwAlphaSrcConstBitDepth  dd 0
union
  dwAlphaSrcCont           dd 0
  lpDDSAlphaSrc            dd 0
ends
union
  dwFillColor              dd 0
  dwFillDepth              dd 0
  dwFillPixel              dd 0
  lpDDSPattern             dd 0
ends
  ddckDestColorKey         DDCOLORKEY
  ddckSrcColorKey          DDCOLORKEY
ends

struct OPEN_MCI
  dwCallback       dd 0
  wDeviceID        dd 0
  lpstrDeviceType  dd 0
  lpstrElementName dd 0
  lpstrAlias       dd 0
ends

struct GENERIC_CALLBACK
  dwCallback       dd 0
ends

struct PLAY_MCI
  dwCallback        dd 0
  dwFrom            dd 0
  dwTo              dd 0
ends

;DirectDraw
 DD_QueryInterface          = 000h
 DD_AddRef                  = 004h
 DD_Release                 = 008h
 DD_Compact                 = 00Ch
 DD_CreateClipper           = 010h
 DD_CreatePalette           = 014h
 DD_CreateSurface           = 018h
 DD_DuplicateSurface        = 01Ch
 DD_EnumDisplayModes        = 020h
 DD_EnumSurfaces            = 024h
 DD_FlipToGDISurface        = 028h
 DD_GetCaps                 = 02Ch
 DD_GetDisplayMode          = 030h
 DD_GetFourCCCodes          = 034h
 DD_GetGDISurface           = 038h
 DD_GetMonitorFrequency     = 03Ch
 DD_GetScanLine             = 040h
 DD_GetVerticalBlankStatus  = 044h
 DD_Initialize              = 048h
 DD_RestoreDisplayMode      = 04Ch
 DD_SetCooperativeLevel     = 050h
 DD_SetDisplayMode          = 054h
 DD_WaitForVerticalBlank    = 058h
 DD_GetAvailableVidMem      = 05Ch
 DD_GetSurfaceFromDC        = 060h
 DD_RestoreAllSurfaces      = 064h
 DD_TestCooperativeLevel    = 068h
 DD_GetDeviceIdentifier     = 06Ch
 DD_StartModeTest           = 070h
 DD_EvaluateMode            = 074h

;DirectDrawSurface
 DDS_QueryInterface         = 000h
 DDS_AddRef                 = 004h
 DDS_Release                = 008h
 DDS_AddAttachedSurface     = 00Ch
 DDS_AddOverlayDirtyRect    = 010h
 DDS_Blt                    = 014h
 DDS_BltBatch               = 018h
 DDS_BltFast                = 01Ch
 DDS_DeleteAttachedSurface  = 020h
 DDS_EnumAttachedSurfaces   = 024h
 DDS_EnumOverlayZOrders     = 028h
 DDS_Flip                   = 02Ch
 DDS_GetAttachedSurface     = 030h
 DDS_GetBltStatus           = 034h
 DDS_GetCaps                = 038h
 DDS_GetClipper             = 03Ch
 DDS_GetColorKey            = 040h
 DDS_GetDC                  = 044h
 DDS_GetFlipStatus          = 048h
 DDS_GetOverlayPosition     = 04Ch
 DDS_GetPalette             = 050h
 DDS_GetPixelFormat         = 054h
 DDS_GetSurfaceDesc         = 058h
 DDS_Initialize             = 05Ch
 DDS_IsLost                 = 060h
 DDS_Lock                   = 064h
 DDS_ReleaseDC              = 068h
 DDS_Restore                = 06Ch
 DDS_SetClipper             = 070h
 DDS_SetColorKey            = 074h
 DDS_SetOverlayPosition     = 078h
 DDS_SetPalette             = 07Ch
 DDS_Unlock                 = 080h
 DDS_UpdateOverlay          = 084h
 DDS_UpdateOverlayDisplay   = 088h
 DDS_UpdateOverlayZOrder    = 08Ch
 DDS_GetDDInterface         = 090h
 DDS_PageLock               = 094h
 DDS_PageUnlock             = 098h
 DDS_SetSurfaceDesc         = 09Ch
 DDS_SetPrivateData         = 0A0h
 DDS_GetPrivateData         = 0A4h
 DDS_FreePrivateData        = 0A8h
 DDS_GetUniquenessValue     = 0ACh
 DDS_ChangeUniquenessValue  = 0B0h
 DDS_SetPriority            = 0B4h
 DDS_GetPriority            = 0B8h
 DDS_SetLOD                 = 0BCh
 DDS_GetLOD                 = 0C0h

;DirectDrawClipper
 DDC_QueryInterface         = 000h
 DDC_AddRef                 = 004h
 DDC_Release                = 008h
 DDC_GetClipList            = 00Ch
 DDC_GetHWnd                = 010h
 DDC_Initialize             = 014h
 DDC_IsClipListChanged      = 018h
 DDC_SetClipList            = 01Ch
 DDC_SetHWnd                = 020h

;DirectDrawPalette
 DDP_QueryInterface         = 000h
 DDP_AddRef                 = 004h
 DDP_Release                = 008h
 DDP_GetCaps                = 00Ch
 DDP_GetEntries             = 010h
 DDP_Initialize             = 014h
 DDP_SetEntries             = 018h

;DirectDrawColorControl
 DDCC_QueryInterface        = 000h
 DDCC_AddRef                = 004h
 DDCC_Release               = 008h
 DDCC_GetColorControls      = 00Ch
 DDCC_SetColorControls      = 010h

;DirectDrawGammaControl
 DDGC_QueryInterface        = 000h
 DDGC_AddRef                = 004h
 DDGC_Release               = 008h
 DDGC_GetGammaRamp          = 00Ch
 DDGC_SetGammaRamp          = 010h

;Equates directDraw
 DDLOCK_WAIT               = 000000001h
 DDSCL_FULLSCREEN          = 000000001h
 DDSCL_EXCLUSIVE           = 000000010h
 DDSCL_NORMAL              = 000000008h
 DDSD_CAPS                 = 000000001h
 DDSD_HEIGHT               = 000000002h
 DDSD_WIDTH                = 000000004h
 DDSD_PITCH                = 000000008h
 DDSD_BACKBUFFERCOUNT      = 000000020h
 DDSCAPS_BACKBUFFER        = 000000004h
 DDSCAPS_COMPLEX           = 000000008h
 DDSCAPS_FLIP              = 000000010h
 DDSCAPS_OFFSCREENPLAIN    = 000000040h
 DDSCAPS_PRIMARYSURFACE    = 000000200h
 DDSCAPS_SYSTEMMEMORY      = 000000800h
 DDBLT_KEYSRC              = 000008000h
 DDBLT_WAIT                = 001000000h
 DDBLT_COLORFILL           = 000000400h
 DDBLT_DDFX                = 000000800h
 DDFLIP_WAIT               = 000000001h
 DDBLTFAST_NOCOLORKEY      = 000000000h
 DDBLTFAST_SRCCOLORKEY     = 000000001h
 DDBLTFAST_WAIT            = 000000010h
 DDCKEY_SRCBLT             = 000000008h
 DDPCAPS_8BIT              = 000000004h
 DDPCAPS_ALLOW256          = 000000040h
 DDERR_SURFACELOST         = 0887601C2h

;===========================================================================================
;///////////////////////////////////////////////////////////////////////////////////////////
;===========================================================================================