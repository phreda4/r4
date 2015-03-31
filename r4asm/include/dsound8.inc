 ;=============================================================================;
 ;  Copyright (C) Microsoft Corporation.  All Rights Reserved.                 ;
 ;                                                                             ;
 ;  File:       dsound.h ( dsound.inc - MASM32 version )                       ;
 ;  Content:    DirectSound include file                                       ;
 ;                                                                             ;
 ; Все замечания и пожелания прошу направлять по адресу:   vertexland@narod.ru ;
 ; Страничка где вы можете скачать свежую версию:          vertexland.narod.ru ;
 ;                                                                             ;
 ;                          Converted (c) 2003-2004. keYMax (Пономарев Михаил) ;
 ;=============================================================================;

  DIRECTSOUND_VERSION	EQU   00800h


 ; Type definitions shared with Direct3D


 D3DVALUE                EQU   DWORD
 LPD3DVALUE              EQU   DWORD

 D3DCOLOR_DEFINED        EQU   1

 LPD3DCOLOR              EQU   DWORD
 LPD3DCOLOR_DEFINED      EQU   1

 D3DVECTOR_DEFINED       EQU   1
 LPD3DVECTOR_DEFINED     EQU   1
 
 DX_SHARED_DEFINES       EQU   1
 LPWAVEFORMATEX	         EQU   DWORD

 FACDS	                 EQU 00000878h                ;  DirectSound's facility code  

 macro MAKE_DSHRESULT result, code
 {
       result = ((1 shl 31) or ((FACDS and 0fffh) shl 16) or (code and 0ffffh))
 }

 struct CLSID_DirectSound
	.data1  dd  047d4d946h
	.data2  dw  062e8h,011cfh
	.data3  db  093h,0bch,044h,045h,053h,054h,000h,000h
 ends
 struct CLSID_DirectSound8	
	.data1  dd  03901cc3fh
	.data2  dw  084b5h,04fa4h
	.data3  db  0bah,035h,0aah,081h,072h,0b8h,0a0h,09bh
 ends
 struct CLSID_DirectSoundCapture
	.data1  dd  0b0210780h
	.data2  dw  089cdh,011d0h
	.data3  db  0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h
 ends
 struct CLSID_DirectSoundCapture8	
	.data1  dd  0e4bcac13h
	.data2  dw  07f99h,04908h
	.data3  db  09ah,08eh,074h,0e3h,0bfh,024h,0b6h,0e1h
 ends
 struct CLSID_DirectSoundFullDuplex
	.data1  dd  0fea4300ch
	.data2  dw  07959h,04147h
	.data3  db  0b2h,06ah,023h,077h,0b9h,0e7h,0a9h,01dh
 ends
 struct DSDEVID_DefaultPlayback	
	.data1  dd  0def00000h
	.data2  dw  09c6dh,047edh
	.data3  db  0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h
 ends
 struct DSDEVID_DefaultCapture	
	.data1  dd  0def00001h
	.data2  dw  09c6dh,047edh
	.data3  db  0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h
 ends
 struct DSDEVID_DefaultVoicePlayback	 
	.data1  dd  0def00002h
	.data2  dw  09c6dh,047edh
	.data3  db  0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h
 ends
 struct DSDEVID_DefaultVoiceCapture	
	.data1  dd  0def00003h
	.data2  dw  09c6dh,047edh
	.data3  db  0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h
 ends

 ; DirectSound 8.0 interfaces.
 ; -------------------------------------------------------------------------
 ; IDirectSound8, IDirectSoundBuffer8 and IDirectSoundCaptureBuffer8 are the
 ; only DirectSound 7.0 interfaces with changed functionality in version 8.0.
 ; The other level 8 interfaces as EQUivalent to their level 7 counterparts:

 IDirectSoundCapture8			EQU   IDirectSoundCapture
 IDirectSound3DListener8		EQU   IDirectSound3DListener
 IDirectSound3DBuffer8			EQU   IDirectSound3DBuffer
 IDirectSoundNotify8			EQU   IDirectSoundNotify
 IDirectSoundFXGargle8			EQU   IDirectSoundFXGargle
 IDirectSoundFXChorus8			EQU   IDirectSoundFXChorus
 IDirectSoundFXFlanger8			EQU   IDirectSoundFXFlanger
 IDirectSoundFXEcho8			EQU   IDirectSoundFXEcho
 IDirectSoundFXDistortion8		EQU   IDirectSoundFXDistortion
 IDirectSoundFXCompressor8		EQU   IDirectSoundFXCompressor
 IDirectSoundFXParamEq8			EQU   IDirectSoundFXParamEq
 IDirectSoundFXWavesReverb8		EQU   IDirectSoundFXWavesReverb
 IDirectSoundFXI3DL2Reverb8		EQU   IDirectSoundFXI3DL2Reverb
 IDirectSoundCaptureFXAec8		EQU   IDirectSoundCaptureFXAec
 IDirectSoundCaptureFXNoiseSuppress8	EQU   IDirectSoundCaptureFXNoiseSuppress
 IDirectSoundFullDuplex8		EQU   IDirectSoundFullDuplex

 LPDIRECTSOUND				EQU IDirectSound
 LPDIRECTSOUNDBUFFER			EQU IDirectSoundBuffer
 LPDIRECTSOUND3DLISTENER		EQU IDirectSound3DListener
 LPDIRECTSOUND3DBUFFER			EQU IDirectSound3DBuffer
 LPDIRECTSOUNDCAPTURE			EQU IDirectSoundCapture
 LPDIRECTSOUNDCAPTUREBUFFER		EQU IDirectSoundCaptureBuffer
 LPDIRECTSOUNDNOTIFY			EQU IDirectSoundNotify
 
 LPDIRECTSOUNDFXGARGLE			EQU IDirectSoundFXGargle
 LPDIRECTSOUNDFXCHORUS			EQU IDirectSoundFXChorus
 LPDIRECTSOUNDFXFLANGER			EQU IDirectSoundFXFlanger
 LPDIRECTSOUNDFXECHO			EQU IDirectSoundFXEcho
 LPDIRECTSOUNDFXDISTORTION		EQU IDirectSoundFXDistortion
 LPDIRECTSOUNDFXCOMPRESSOR		EQU IDirectSoundFXCompressor
 LPDIRECTSOUNDFXPARAMEQ			EQU IDirectSoundFXParamEq
 LPDIRECTSOUNDFXWAVESREVERB		EQU IDirectSoundFXWavesReverb
 LPDIRECTSOUNDFXI3DL2REVERB		EQU IDirectSoundFXI3DL2Reverb
 LPDIRECTSOUNDCAPTUREFXAEC		EQU IDirectSoundCaptureFXAec
 LPDIRECTSOUNDCAPTUREFXNOISESUPPRESS	EQU IDirectSoundCaptureFXNoiseSuppress
 LPDIRECTSOUNDFULLDUPLEX		EQU IDirectSoundFullDuplex

 LPDIRECTSOUND8				EQU IDirectSound8
 LPDIRECTSOUNDBUFFER8			EQU IDirectSoundBuffer8
 LPDIRECTSOUND3DLISTENER8		EQU IDirectSound3DListener8
 LPDIRECTSOUND3DBUFFER8			EQU IDirectSound3DBuffer8
 LPDIRECTSOUNDCAPTURE8			EQU IDirectSoundCapture8
 LPDIRECTSOUNDCAPTUREBUFFER8		EQU IDirectSoundCaptureBuffer8
 LPDIRECTSOUNDNOTIFY8			EQU IDirectSoundNotify8
 LPDIRECTSOUNDFXGARGLE8			EQU IDirectSoundFXGargle8
 LPDIRECTSOUNDFXCHORUS8			EQU IDirectSoundFXChorus8
 LPDIRECTSOUNDFXFLANGER8		EQU IDirectSoundFXFlanger8
 LPDIRECTSOUNDFXECHO8			EQU IDirectSoundFXEcho8
 LPDIRECTSOUNDFXDISTORTION8		EQU IDirectSoundFXDistortion8
 LPDIRECTSOUNDFXCOMPRESSOR8		EQU IDirectSoundFXCompressor8
 LPDIRECTSOUNDFXPARAMEQ8		EQU IDirectSoundFXParamEq8
 LPDIRECTSOUNDFXWAVESREVERB8		EQU IDirectSoundFXWavesReverb8
 LPDIRECTSOUNDFXI3DL2REVERB8		EQU IDirectSoundFXI3DL2Reverb8
 LPDIRECTSOUNDCAPTUREFXAEC8		EQU IDirectSoundCaptureFXAec8
 LPDIRECTSOUNDCAPTUREFXNOISESUPPRESS8	EQU IDirectSoundCaptureFXNoiseSuppress8
 LPDIRECTSOUNDFULLDUPLEX8		EQU IDirectSoundFullDuplex8

 ; IID definitions for the unchanged DirectSound 8.0 interfaces
 ; ------------------------------------------------------------------------------------

 IID_IDirectSoundCapture8		  EQU   IID_IDirectSoundCapture
 IID_IDirectSound3DListener8		  EQU   IID_IDirectSound3DListener
 IID_IDirectSound3DBuffer8		  EQU   IID_IDirectSound3DBuffer
 IID_IDirectSoundNotify8		  EQU   IID_IDirectSoundNotify
 IID_IDirectSoundFXGargle8		  EQU   IID_IDirectSoundFXGargle
 IID_IDirectSoundFXChorus8		  EQU   IID_IDirectSoundFXChorus
 IID_IDirectSoundFXFlanger8		  EQU   IID_IDirectSoundFXFlanger
 IID_IDirectSoundFXEcho8		  EQU   IID_IDirectSoundFXEcho
 IID_IDirectSoundFXDistortion8		  EQU   IID_IDirectSoundFXDistortion
 IID_IDirectSoundFXCompressor8		  EQU   IID_IDirectSoundFXCompressor
 IID_IDirectSoundFXParamEq8		  EQU   IID_IDirectSoundFXParamEq
 IID_IDirectSoundFXWavesReverb8		  EQU   IID_IDirectSoundFXWavesReverb
 IID_IDirectSoundFXI3DL2Reverb8		  EQU   IID_IDirectSoundFXI3DL2Reverb
 IID_IDirectSoundCaptureFXAec8		  EQU   IID_IDirectSoundCaptureFXAec
 IID_IDirectSoundCaptureFXNoiseSuppress8  EQU   IID_IDirectSoundCaptureFXNoiseSuppress
 IID_IDirectSoundFullDuplex8		  EQU   IID_IDirectSoundFullDuplex

 ; Compatibility TYPEDEFs
 ; -----------------------------------------------------------------------------------

 LPCWAVEFORMATEX_DEFINED                EQU   1
 LPCWAVEFORMATEX                        EQU   DWORD

 LPCGUID_DEFINED                        EQU   1
 LPCGUID                                EQU   DWORD

 LPLPDIRECTSOUND			EQU  LPDIRECTSOUND
 LPLPDIRECTSOUNDBUFFER			EQU  LPDIRECTSOUNDBUFFER
 LPLPDIRECTSOUND3DLISTENER		EQU  LPDIRECTSOUND3DLISTENER
 LPLPDIRECTSOUND3DBUFFER		EQU  LPDIRECTSOUND3DBUFFER
 LPLPDIRECTSOUNDCAPTURE			EQU  LPDIRECTSOUNDCAPTURE
 LPLPDIRECTSOUNDCAPTUREBUFFER		EQU  LPDIRECTSOUNDCAPTUREBUFFER
 LPLPDIRECTSOUNDNOTIFY			EQU  LPDIRECTSOUNDNOTIFY

 LPLPDIRECTSOUND8			EQU  LPDIRECTSOUND8
 LPLPDIRECTSOUNDBUFFER8			EQU  LPDIRECTSOUNDBUFFER8
 LPLPDIRECTSOUNDCAPTURE8		EQU  LPDIRECTSOUNDCAPTURE8
 LPLPDIRECTSOUNDCAPTUREBUFFER8		EQU  LPDIRECTSOUNDCAPTUREBUFFER8

 ; STRUCures
 ; ------------------------------------------------------------------------------

   struct DSCAPS
	.dwSize				dd  ?
	.dwFlags			dd  ?
	.dwMinSecondarySampleRate	dd  ?
	.dwMaxSecondarySampleRate	dd  ?
	.dwPrimaryBuffers		dd  ?
	.dwMaxHwMixingAllBuffers	dd  ?
	.dwMaxHwMixingStaticBuffers	dd  ?
	.dwMaxHwMixingStreamingBuffers	dd  ?
	.dwFreeHwMixingAllBuffers	dd  ?
	.dwFreeHwMixingStaticBuffers	dd  ?
	.dwFreeHwMixingStreamingBuffers	dd  ?
	.dwMaxHw3DAllBuffers		dd  ?
	.dwMaxHw3DStaticBuffers		dd  ?
	.dwMaxHw3DStreamingBuffers	dd  ?
	.dwFreeHw3DAllBuffers		dd  ?
	.dwFreeHw3DStaticBuffers	dd  ?
	.dwFreeHw3DStreamingBuffers	dd  ?
	.dwTotalHwMemBytes		dd  ?
	.dwFreeHwMemBytes		dd  ?
	.dwMaxContigFreeHwMemBytes	dd  ?
	.dwUnlockTransferRateHwBuffers	dd  ?
	.dwPlayCpuOverheadSwBuffers	dd  ?
	.dwReserved1			dd  ?
	.dwReserved2			dd  ?
   ends
   LPDSCAPS                             EQU  DWORD
   LPCDSCAPS                            EQU  DWORD

   struct DSBCAPS
	.dwSize				dd  ?
	.dwFlags			dd  ? 
	.dwBufferBytes			dd  ?
	.dwUnlockTransferRate		dd  ?
	.dwPlayCpuOverhead		dd  ?
   ends
   LPDSBCAPS                            EQU  DWORD
   LPCDSBCAPS                           EQU  DWORD

   struct DSEFFECTDESC
	.dwSize				dd   ?
	.dwFlags			dd   ?
	.guidDSFXClass			GUID
	.dwReserved1			dd   ?
	.dwReserved2			dd   ?
   ends
   LPDSEFFECTDESC			EQU  DWORD
   LPCDSEFFECTDESC			EQU  DWORD

   DSFX_LOCHARDWARE		EQU  000000001h
   DSFX_LOCSOFTWARE		EQU  000000002h

   DSFXR_PRESENT		EQU  0
   DSFXR_LOCHARDWARE		EQU  1
   DSFXR_LOCSOFTWARE		EQU  2
   DSFXR_UNALLOCATED		EQU  3
   DSFXR_FAILED			EQU  4
   DSFXR_UNKNOWN		EQU  5
   DSFXR_SENDLOOP		EQU  6

   struct DSCEFFECTDESC
	.dwSize			dd   ?
	.dwFlags		dd   ?
	.guidDSCFXClass		GUID
	.guidDSCFXInstance	GUID
	.dwReserved1		dd   ?
	.dwReserved2		dd   ?
   ends
   LPDSCEFFECTDESC              EQU  DWORD
   LPCDSCEFFECTDESC	        EQU  DWORD

   DSCFX_LOCHARDWARE		EQU   000000001h
   DSCFX_LOCSOFTWARE		EQU   000000002h

   DSCFXR_LOCHARDWARE		EQU   000000010h
   DSCFXR_LOCSOFTWARE		EQU   000000020h

   struct DSBUFFERDESC
	.dwSize			dd            ?
	.dwFlags		dd            ?
	.dwBufferBytes		dd            ?
	.dwReserved		dd            ?
	.lpwfxFormat		dd            ?
	.guid3DAlgorithm	GUID
   ends
   LPDSBUFFERDESC		EQU  DWORD
   LPCDSBUFFERDESC		EQU  DWORD

 ; Older version of this STRUCture:
 ; --------------------------------------------------------
   struct DSBUFFERDESC1
	.dwSize			dd           ?
	.dwFlags		dd           ?
	.dwBufferBytes		dd           ?
	.dwReserved		dd           ?
	.lpwfxFormat		dd           ? ;LPWAVEFORMATEX
   ends
   LPDSBUFFERDESC1		EQU  DWORD
   LPCDSBUFFERDESC1		EQU  DWORD

   struct DS3DBUFFER
	.dwSize			dd	      ?
	.vPosition		D3DVECTOR
	.vVelocity		D3DVECTOR
	.dwInsideConeAngle	dd	      ?
	.dwOutsideConeAngle	dd	      ?
	.vConeOrientation	D3DVECTOR
	.lConeOutsideVolume	dd	      ?
	.flMinDistance		dd            ?
	.flMaxDistance		dd            ?
	.dwMode			dd	      ?
   ends
   LPDS3DBUFFER		        EQU  DWORD
   LPCDS3DBUFFER                EQU  DWORD

   struct DS3DLISTENER
	.dwSize			dd	      ?
	.vPosition		D3DVECTOR   
	.vVelocity		D3DVECTOR    
	.vOrientFront		D3DVECTOR    
	.vOrientTop		D3DVECTOR    
	.flDistanceFactor	dd            ?
	.flRolloffFactor	dd            ?
	.flDopplerFactor	dd            ?
   ends
   LPDS3DLISTENER		EQU  DWORD
   LPCDS3DLISTENER		EQU  DWORD

   struct DSCCAPS
	.dwSize			dd   ?
	.dwFlags		dd   ?
	.dwFormats		dd   ?
	.dwChannels		dd   ?
   ends
   LPDSCCAPS			EQU  DWORD
   LPCDSCCAPS			EQU  DWORD

   struct DSCBUFFERDESC1
	.dwSize			dd           ?
	.dwFlags		dd           ?
	.dwBufferBytes		dd           ?
	.dwReserved		dd           ?
	.lpwfxFormat		dd           ?
   ends
   LPDSCBUFFERDESC1		EQU  DWORD

   struct DSCBUFFERDESC
	.dwSize			dd            ?
	.dwFlags		dd            ?
	.dwBufferBytes		dd            ?
	.dwReserved		dd            ?
	.lpwfxFormat		dd            ?
	.dwFXCount		dd            ?
	.lpDSCFXDesc		dd            ?
   ends
   LPDSCBUFFERDESC		EQU  DWORD
   LPCDSCBUFFERDESC		EQU  DWORD

   struct DSCBCAPS
	.dwSize			dd  ?
	.dwFlags		dd  ?
	.dwBufferBytes		dd  ?
	.dwReserved		dd  ?
   ends
   LPDSCBCAPS			EQU  DWORD
   LPCDSCBCAPS			EQU  DWORD

   struct DSBPOSITIONNOTIFY
	.dwOffset		dd  ?
	.hEventNotify		dd  ?
   ends
   LPDSBPOSITIONNOTIFY		EQU  DWORD
   LPCDSBPOSITIONNOTIFY		EQU  DWORD

 ; DirectSound API
 ; ----------------------------------------------------------------------------

 ; TYPEDEF BOOL (CALLBACK *LPDSENUMCALLBACKA)(LPGUID, LPCSTR, LPCSTR, LPVOID);
   LPDSENUMCALLBACKA		EQU  DWORD

 ;TYPEDEF BOOL (CALLBACK *LPDSENUMCALLBACKW)(LPGUID, LPCWSTR, LPCWSTR, LPVOID);
   LPDSENUMCALLBACKW		EQU  DWORD

 DirectSoundCreate% =  3
 DirectSoundEnumerateA% = 2
 DirectSoundEnumerateW% = 2
 DirectSoundCaptureCreate% = 3
 DirectSoundCaptureEnumerateA% = 2
 DirectSoundCaptureEnumerateW% = 2

 ; DirectSound 8
 ; ---------------------------------------------------------------------

 DirectSoundCreate8% = 3
 DirectSoundCaptureCreate8% = 3
 DirectSoundFullDuplexCreate% = 10
 DirectSoundFullDuplexCreate8% = 10
 GetDeviceID% = 2

 REFERENCE_TIME	        EQU        QWORD
 LPREFERENCE_TIME       EQU        QWORD

 ;pGetTimeProto	TYPEDEF PROTO :DWORD,:QWORD
 ;pGetTime		TYPEDEF PTR pGetTimeProto
 ;pAdviseProto	TYPEDEF PROTO :DWORD,:QWORD,:QWORD,:DWORD,:DWORD
 ;pAdvise		TYPEDEF PTR pAdviseProto

 struct IID_IReferenceClock	
	.data1  dd  056a86897h
	.data2  dw  00ad4h,011ceh
	.data3  db  0b0h,03ah,000h,020h,0afh,00bh,0a7h,070h
 ends

 ;=============================================================================
 ;  ReferenceClock  Виртуальная таблица методов
 ;=============================================================================
 struct ReferenceClock

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;ReferenceClock methods

    STDMETHOD	GetTime,                        3    ; DWORD + QWORD
    STDMETHOD	AdviseTime,			7    ; DWORD + QWORD + QWORD + DWORD + DWORD
    STDMETHOD	AdvisePeriodic,	                7    ; DWORD + QWORD + QWORD + DWORD + DWORD
    STDMETHOD	Unadvise,			2

    end virtual

 ends

 ;
 ; IDirectSound
 ; ----------------------------------------------------------------------------

 struct IID_IDirectSound 
	.data1  dd  0279AFA83h
	.data2  dw  04981h,011CEh
	.data3  db  0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h
 ends

 ;=============================================================================
 ;  IDirectSound  Виртуальная таблица методов
 ;=============================================================================
 struct DirectSound

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSound methods

    STDMETHOD	CreateSoundBuffer,		4
    STDMETHOD	GetCaps,			2
    STDMETHOD	DuplicateSoundBuffer,		3
    STDMETHOD	SetCooperativeLevel,		3
    STDMETHOD	Compact,			1
    STDMETHOD	GetSpeakerConfig,		2
    STDMETHOD	SetSpeakerConfig,		2
    STDMETHOD	Initialize,			2

    end virtual

 ends

 ; IDirectSound8
 ; ----------------------------------------------------------------------------

 struct IID_IDirectSound8  
	.data1  dd  0C50A7E93h
	.data2  dw  0F395h,04834h
	.data3  db  09Eh,0F6h,07Fh,0A9h,09Dh,0E5h,009h,066h
 ends

 ;=============================================================================
 ;  IDirectSound8  Виртуальная таблица методов
 ;=============================================================================
 struct DirectSound8

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSound8 methods

    STDMETHOD	CreateSoundBuffer,		4
    STDMETHOD	GetCaps,			2
    STDMETHOD	DuplicateSoundBuffer,		3
    STDMETHOD	SetCooperativeLevel,		3
    STDMETHOD	Compact,			1
    STDMETHOD	GetSpeakerConfig,		2
    STDMETHOD	SetSpeakerConfig,		2
    STDMETHOD	Initialize,			2
    STDMETHOD	VerifyCertification,		2

    end virtual

 ends


 ; IDirectSoundBuffer
 ; ----------------------------------------------------------------------------

 struct IID_IDirectSoundBuffer 
	.data1  dd  0279AFA85h
	.data2  dw  04981h,011CEh
	.data3  db  0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060
 ends

 ;=============================================================================
 ;  IDirectSoundBuffer  Виртуальная таблица методов
 ;=============================================================================
 struct DirectSoundBuffer

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundBuffer methods

    STDMETHOD	GetCaps,			2
    STDMETHOD	GetCurrentPosition,		3
    STDMETHOD	GetFormat,			4
    STDMETHOD	GetVolume,			2
    STDMETHOD	GetPan,				2
    STDMETHOD	GetFrequency,			2
    STDMETHOD	GetStatus,			2
    STDMETHOD	Initialize,			3
    STDMETHOD	Lock1,				8
    STDMETHOD	Play,				4
    STDMETHOD	SetCurrentPosition,		2
    STDMETHOD	SetFormat,			2
    STDMETHOD	SetVolume,			2
    STDMETHOD	SetPan,				2
    STDMETHOD	SetFrequency,			2
    STDMETHOD	Stop,				1
    STDMETHOD	Unlock,				5
    STDMETHOD	Restore,			1

    end virtual

 ends

 ; IDirectSoundBuffer8
 ; ----------------------------------------------------------------------------

 struct IID_IDirectSoundBuffer8  
	.data1  dd  06825a449h
	.data2  dw  07524h,04d82h
	.data3  db  092h,00fh,050h,0e3h,06ah,0b3h,0abh,01eh
 ends

 ; Special GUID meaning "select all objects" for use in GetObjectInPath()

 struct GUID_All_Objects         
	.data1  dd  0aa114de5h
	.data2  dw  0c262h,04169h
	.data3  db  0a1h,0c8h,023h,0d6h,098h,0cch,073h,0b5h
 ends

 ;=============================================================================
 ;  IDirectSoundBuffer8  Виртуальная таблица методов
 ;=============================================================================
 struct DirectSoundBuffer8

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundBuffer8 methods

    STDMETHOD	GetCaps,			2
    STDMETHOD	GetCurrentPosition,		3
    STDMETHOD	GetFormat,			4
    STDMETHOD	GetVolume,			2
    STDMETHOD	GetPan,				2
    STDMETHOD	GetFrequency,			2
    STDMETHOD	GetStatus,			2
    STDMETHOD	Initialize,			3
    STDMETHOD	Lock1,				8
    STDMETHOD	Play,				4
    STDMETHOD	SetCurrentPosition,		2
    STDMETHOD	SetFormat,			2
    STDMETHOD	SetVolume,			2
    STDMETHOD	SetPan,				2
    STDMETHOD	SetFrequency,			2
    STDMETHOD	Stop,				1
    STDMETHOD	Unlock,				5
    STDMETHOD	Restore,			1

    STDMETHOD	SetFX,				4
    STDMETHOD	AcquireResources,		4
    STDMETHOD	GetObjectInPath,		5

    end virtual

 ends

 struct IID_IDirectSound3DListener
	.data1  dd  0279AFA84h
	.data2  dw  04981h,011CEh
	.data3  db  0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h
 ends

 ;=============================================================================
 ;  DirectSound3DListener  Виртуальная таблица методов
 ;=============================================================================
 struct DirectSound3DListener

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSound3DListener methods

    STDMETHOD	GetAllParameters,		2
    STDMETHOD	GetDistanceFactor,		2
    STDMETHOD	GetDopplerFactor,		2
    STDMETHOD	GetOrientation,			3
    STDMETHOD	GetPosition,			2
    STDMETHOD	GetRolloffFactor,		2
    STDMETHOD	GetVelocity,			2
    STDMETHOD	SetAllParameters,		3
    STDMETHOD	SetDistanceFactor,		3
    STDMETHOD	SetDopplerFactor,		3
    STDMETHOD	SetOrientation,			8
    STDMETHOD	SetPosition,			5
    STDMETHOD	SetRolloffFactor,		3
    STDMETHOD	SetVelocity,			5
    STDMETHOD	CommitDeferredSettings,		1

    end virtual

 ends

 ; IDirectSound3DBuffer
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSound3DBuffer  
	.data1  dd  0279AFA86h
	.data2  dw  04981h,011CEh
	.data3  db  0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h
  ends

 ;=============================================================================
 ;  DirectSound3DBuffer  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSound3DBuffer

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSound3DBuffer methods

    STDMETHOD	GetAllParameters,		2
    STDMETHOD	GetConeAngles,			3
    STDMETHOD	GetConeOrientation,		2
    STDMETHOD	GetConeOutsideVolume,		2
    STDMETHOD	GetMaxDistance,			2
    STDMETHOD	GetMinDistance,			2
    STDMETHOD	GetMode,			2
    STDMETHOD	GetPosition,			2
    STDMETHOD	GetVelocity,			2
    STDMETHOD	SetAllParameters,		3
    STDMETHOD	SetConeAngles,			4
    STDMETHOD	SetConeOrientation,		5
    STDMETHOD	SetConeOutsideVolume,		3
    STDMETHOD	SetMaxDistance,			3
    STDMETHOD	SetMinDistance,			3
    STDMETHOD	SetMode,			3
    STDMETHOD	SetPosition,			5
    STDMETHOD	SetVelocity,			5

    end virtual

 ends

 ; IDirectSoundCapture
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundCapture 
	.data1  dd  0b0210781h
	.data2  dw  089cdh,011d0h
	.data3  db  0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h
  ends

 ;=============================================================================
 ;  DirectSoundCapture  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundCapture

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundCapture methods

    STDMETHOD	CreateCaptureBuffer,		4
    STDMETHOD	GetCaps,			2
    STDMETHOD	Initialize,			2

    end virtual

 ends

 ; IDirectSoundCaptureBuffer
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundCaptureBuffer 
	.data1  dd  0b0210782h
	.data2  dw  089cdh,011d0h
	.data3  db  0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h
  ends

 ;=============================================================================
 ;  DirectSoundCaptureBuffer  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundCaptureBuffer

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundCaptureBuffer methods

    STDMETHOD	GetCaps,			2
    STDMETHOD	GetCurrentPosition,		3
    STDMETHOD	GetFormat,			4
    STDMETHOD	GetStatus,			2
    STDMETHOD	Initialize,			3
    STDMETHOD	Lock1,				8
    STDMETHOD	Start,				2
    STDMETHOD	Stop,				1
    STDMETHOD	Unlock,				5

    end virtual

 ends

 ; IDirectSoundCaptureBuffer8
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundCaptureBuffer8  
	.data1  dd  000990df4h
	.data2  dw  00dbbh,04872h
	.data3  db  083h,03eh,06dh,030h,03eh,080h,0aeh,0b6h
  ends

 ;=============================================================================
 ;  DirectSoundCaptureBuffer8  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundCaptureBuffer8

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundCaptureBuffer8 methods

    STDMETHOD	GetCaps,			2
    STDMETHOD	GetCurrentPosition,		3
    STDMETHOD	GetFormat,			4
    STDMETHOD	GetStatus,			2
    STDMETHOD	Initialize,			3
    STDMETHOD	Lock1,				8
    STDMETHOD	Start,				2
    STDMETHOD	Stop,				1
    STDMETHOD	Unlock,				5

    STDMETHOD	GetObjectInPath,		5
    STDMETHOD	GetFXStatus,			3

    end virtual

 ends

 ; IDirectSoundNotify
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundNotify 
	.data1  dd  0b0210783h
	.data2  dw  089cdh,011d0h
	.data3  db  0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h
  ends

 ;=============================================================================
 ;  IDirectSoundNotify  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundNotify

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundNotify methods

    STDMETHOD	SetNotificationPositions,	3

    end virtual

 ends

 ; IKsPropertySet
 ; ----------------------------------------------------------------------------

  LPKSPROPERTYSET		EQU  DWORD

  KSPROPERTY_SUPPORT_GET	EQU  000000001h
  KSPROPERTY_SUPPORT_SET	EQU  000000002h

  struct IID_IKsPropertySet  
	.data1  dd  031efac30h
	.data2  dw  0515ch,011d0h
	.data3  db  0a9h,0aah,000h,0aah,000h,061h,0beh,093h
  ends

 ;=============================================================================
 ;  IKsPropertySet  Виртуальная таблица методов
 ;=============================================================================
  struct KsPropertySet

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IKsPropertySet methods

    STDMETHOD	Get,				8
    STDMETHOD	Set,				7
    STDMETHOD	QuerySupport,			4

    end virtual

 ends

 ; IDirectSoundFXGargle
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXGargle 
	.data1  dd  0d616f352h
	.data2  dw  0d622h,011ceh
	.data3  db  0aah,0c5h,000h,020h,0afh,00bh,099h,0a3h
  ends

  struct DSFXGargle
     .dwRateHz	        dd  ?    ; Rate of modulation in hz
     .dwWaveShape	dd  ?    ; DSFXGARGLE_WAVE_xxx
  ends

  LPDSFXGargle		EQU  DWORD
  LPCDSFXGargle		EQU  DWORD

  DSFXGARGLE_WAVE_TRIANGLE       EQU  0
  DSFXGARGLE_WAVE_SQUARE         EQU  1

  DSFXGARGLE_RATEHZ_MIN          EQU  1
  DSFXGARGLE_RATEHZ_MAX          EQU  1000

 ;=============================================================================
 ;  DirectSoundFXGargle  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXGargle

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXGargle methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

 ends

 ; IDirectSoundFXChorus
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXChorus  
	.data1  dd  0880842e3h
	.data2  dw  0145fh,043e6h
	.data3  db  0a9h,034h,0a7h,018h,006h,0e5h,005h,047h
  ends

   struct DSFXChorus
	.fWetDryMix	dd   ?
	.fDepth		dd   ?
	.fFeedback	dd   ?
	.fFrEQUency	dd   ?
	.lWaveform	dd   ?	 ; LFO shape; DSFXCHORUS_WAVE_xxx
	.fDelay		dd   ?
	.lPhase		dd   ?
   ends
   LPDSFXChorus		EQU  DWORD
   LPCDSFXChorus	EQU  DWORD

   DSFXCHORUS_WAVE_TRIANGLE	EQU   0
   DSFXCHORUS_WAVE_SIN		EQU   1

   DSFXCHORUS_WETDRYMIX_MIN	EQU   0.0f
   DSFXCHORUS_WETDRYMIX_MAX	EQU   100.0f
   DSFXCHORUS_DEPTH_MIN		EQU   0.0f
   DSFXCHORUS_DEPTH_MAX		EQU   100.0f
   DSFXCHORUS_FEEDBACK_MIN	EQU  -99.0f
   DSFXCHORUS_FEEDBACK_MAX	EQU   99.0f
   DSFXCHORUS_FREQUENCY_MIN	EQU   0.0f
   DSFXCHORUS_FREQUENCY_MAX	EQU   10.0f
   DSFXCHORUS_DELAY_MIN		EQU   0.0f
   DSFXCHORUS_DELAY_MAX		EQU   20.0f
   DSFXCHORUS_PHASE_MIN		EQU   0
   DSFXCHORUS_PHASE_MAX		EQU   4

   DSFXCHORUS_PHASE_NEG_180	EQU   0
   DSFXCHORUS_PHASE_NEG_90	EQU   1
   DSFXCHORUS_PHASE_ZERO	EQU   2
   DSFXCHORUS_PHASE_90		EQU   3
   DSFXCHORUS_PHASE_180		EQU   4

 ;=============================================================================
 ;  DirectSoundFXChorus  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXChorus

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXChorus methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXFlanger
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXFlanger 
	.data1  dd  0903e9878h
	.data2  dw  02c92h,04072h
	.data3  db  09bh,02ch,0eah,068h,0f5h,039h,067h,083h
  ends

   struct DSFXFlanger
	.fWetDryMix	dd   ?
	.fDepth		dd   ?
	.fFeedback	dd   ?
	.fFrEQUency	dd   ?
	.lWaveform	dd   ?
	.fDelay		dd   ?
	.lPhase		dd   ?
   ends
   LPDSFXFlanger	EQU  DWORD
   LPCDSFXFlanger	EQU  DWORD

   DSFXFLANGER_WAVE_TRIANGLE	EQU   0
   DSFXFLANGER_WAVE_SIN		EQU   1

   DSFXFLANGER_WETDRYMIX_MIN	EQU   0.0f
   DSFXFLANGER_WETDRYMIX_MAX	EQU   100.0f
   DSFXFLANGER_FREQUENCY_MIN	EQU   0.0f
   DSFXFLANGER_FREQUENCY_MAX	EQU   10.0f
   DSFXFLANGER_DEPTH_MIN	EQU   0.0f
   DSFXFLANGER_DEPTH_MAX	EQU   100.0f
   DSFXFLANGER_PHASE_MIN	EQU   0
   DSFXFLANGER_PHASE_MAX	EQU   4
   DSFXFLANGER_FEEDBACK_MIN	EQU  -99.0f
   DSFXFLANGER_FEEDBACK_MAX	EQU   99.0f
   DSFXFLANGER_DELAY_MIN	EQU   0.0f
   DSFXFLANGER_DELAY_MAX	EQU   4.0f

   DSFXFLANGER_PHASE_NEG_180	EQU   0
   DSFXFLANGER_PHASE_NEG_90	EQU   1
   DSFXFLANGER_PHASE_ZERO	EQU   2
   DSFXFLANGER_PHASE_90		EQU   3
   DSFXFLANGER_PHASE_180	EQU   4

 ;=============================================================================
 ;  IDirectSoundFXFlanger  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXFlanger

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXFlanger methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXEcho
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXEcho  
	.data1  dd  08bd28edfh
	.data2  dw  050dbh,04e92h
	.data3  db  0a2h,0bdh,044h,054h,088h,0d1h,0edh,042h
  ends

   struct DSFXEcho
      .fWetDryMix          dd   ?
      .fFeedback           dd   ?
      .fLeftDelay          dd   ?
      .fRightDelay         dd   ?
      .lPanDelay           dd   ?
   ends
   LPDSFXEcho		  EQU  DWORD
   LPCDSFXEcho		  EQU  DWORD

   DSFXECHO_WETDRYMIX_MIN	EQU   0.0f
   DSFXECHO_WETDRYMIX_MAX	EQU   100.0f
   DSFXECHO_FEEDBACK_MIN	EQU   0.0f
   DSFXECHO_FEEDBACK_MAX	EQU   100.0f
   DSFXECHO_LEFTDELAY_MIN	EQU   1.0f
   DSFXECHO_LEFTDELAY_MAX	EQU   2000.0f
   DSFXECHO_RIGHTDELAY_MIN	EQU   1.0f
   DSFXECHO_RIGHTDELAY_MAX	EQU   2000.0f
   DSFXECHO_PANDELAY_MIN	EQU   0
   DSFXECHO_PANDELAY_MAX	EQU   1

 ;=============================================================================
 ;  IDirectSoundFXEcho  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXEcho

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXEcho methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXDistortion
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXDistortion  
	.data1  dd  08ecf4326h
	.data2  dw  0455fh,04d8bh
	.data3  db  0bdh,0a9h,08dh,05dh,03eh,09eh,03eh,00bh
  ends

   struct DSFXDistortion
	.fGain			dd   ?
	.fEdge			dd   ?
	.fPostEQCenterFrEQUency	dd   ?
	.fPostEQBandwidth	dd   ?
	.fPreLowpassCutoff	dd   ?
   ends
   LPDSFXDistortion		EQU  DWORD
   LPCDSFXDistortion		EQU  DWORD

   DSFXDISTORTION_GAIN_MIN			EQU  -60.0f
   DSFXDISTORTION_GAIN_MAX			EQU   0.0f
   DSFXDISTORTION_EDGE_MIN			EQU   0.0f
   DSFXDISTORTION_EDGE_MAX			EQU   100.0f
   DSFXDISTORTION_POSTEQCENTERFREQUENCY_MIN	EQU   100.0f
   DSFXDISTORTION_POSTEQCENTERFREQUENCY_MAX	EQU   8000.0f
   DSFXDISTORTION_POSTEQBANDWIDTH_MIN		EQU   100.0f
   DSFXDISTORTION_POSTEQBANDWIDTH_MAX		EQU   8000.0f
   DSFXDISTORTION_PRELOWPASSCUTOFF_MIN		EQU   100.0f
   DSFXDISTORTION_PRELOWPASSCUTOFF_MAX		EQU   8000.0f

 ;=============================================================================
 ;  IDirectSoundFXDistortion  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXDistortion

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXDistortion methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXCompressor
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXCompressor 
	.data1  dd  04bbd1154h
	.data2  dw  062f6h,04e2ch
	.data3  db  0a1h,05ch,0d3h,0b6h,0c4h,017h,0f7h,0a0h
  ends

   struct DSFXCompressor
	.fGain			dd   ?
	.fAttack		dd   ?
	.fRelease		dd   ?
	.fThreshold		dd   ?
	.fRatio			dd   ?
	.fPredelay		dd   ?
   ends
   LPDSFXCompressor		EQU  DWORD
   LPCDSFXCompressor		EQU  DWORD

   DSFXCOMPRESSOR_GAIN_MIN		EQU  -60.0f
   DSFXCOMPRESSOR_GAIN_MAX		EQU   60.0f
   DSFXCOMPRESSOR_ATTACK_MIN		EQU   0.01f
   DSFXCOMPRESSOR_ATTACK_MAX		EQU   500.0f
   DSFXCOMPRESSOR_RELEASE_MIN		EQU   50.0f
   DSFXCOMPRESSOR_RELEASE_MAX		EQU   3000.0f
   DSFXCOMPRESSOR_THRESHOLD_MIN		EQU  -60.0f
   DSFXCOMPRESSOR_THRESHOLD_MAX		EQU   0.0f
   DSFXCOMPRESSOR_RATIO_MIN		EQU   1.0f
   DSFXCOMPRESSOR_RATIO_MAX		EQU   100.0f
   DSFXCOMPRESSOR_PREDELAY_MIN		EQU   0.0f
   DSFXCOMPRESSOR_PREDELAY_MAX		EQU   4.0f

 ;=============================================================================
 ;  IDirectSoundFXCompressor  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXCompressor

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXCompressor methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXParamEq
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXParamEq  
	.data1  dd  0c03ca9feh
	.data2  dw  0fe90h,04204h
	.data3  db  080h,078h,082h,033h,04ch,0d1h,077h,0dah
  ends

   struct DSFXParamEq
	.fCenter		dd   ?
	.fBandwidth		dd   ?
	.fGain			dd   ?
   ends
   LPDSFXParamEq                EQU  DWORD
   LPCDSFXParamEq               EQU  DWORD

   DSFXPARAMEQ_CENTER_MIN	EQU   80.0f
   DSFXPARAMEQ_CENTER_MAX	EQU   16000.0f
   DSFXPARAMEQ_BANDWIDTH_MIN	EQU   1.0f
   DSFXPARAMEQ_BANDWIDTH_MAX	EQU   36.0f
   DSFXPARAMEQ_GAIN_MIN		EQU  -15.0f
   DSFXPARAMEQ_GAIN_MAX		EQU   15.0f

 ;=============================================================================
 ;  IDirectSoundFXParamEq  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXParamEq

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXParamEq methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundFXI3DL2Reverb
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXI3DL2Reverb 
	.data1  dd  04b166a6ah
	.data2  dw  00d66h,043f3h
	.data3  db  080h,0e3h,0eeh,062h,080h,0deh,0e1h,0a4h
  ends

   struct DSFXI3DL2Reverb
	.lRoom			dd   ?	 ; [-10000, 0]      default: -1000 mB
	.lRoomHF		dd   ?	 ; [-10000, 0]      default: 0 mB
	.flRoomRolloffFactor	dd   ?	 ; [0.0, 10.0]      default: 0.0
	.flDecayTime		dd   ?	 ; [0.1, 20.0]      default: 1.49s
	.flDecayHFRatio		dd   ?	 ; [0.1, 2.0]       default: 0.83
	.lReflections		dd   ?	 ; [-10000, 1000]   default: -2602 mB
	.flReflectionsDelay	dd   ?	 ; [0.0, 0.3]       default: 0.007 s
	.lReverb		dd   ?	 ; [-10000, 2000]   default: 200 mB
	.flReverbDelay		dd   ?	 ; [0.0, 0.1]       default: 0.011 s
	.flDiffusion		dd   ?	 ; [0.0, 100.0]     default: 100.0 %
	.flDensity		dd   ?	 ; [0.0, 100.0]     default: 100.0 %
	.flHFReference		dd   ?	 ; [20.0, 20000.0]  default: 5000.0 Hz
   ends
   LPCDSFXI3DL2Reverb	        EQU  DWORD

   DSFX_I3DL2REVERB_ROOM_MIN                   EQU (-10000)
   DSFX_I3DL2REVERB_ROOM_MAX                   EQU 0
   DSFX_I3DL2REVERB_ROOM_DEFAULT               EQU (-1000)

   DSFX_I3DL2REVERB_ROOMHF_MIN                 EQU (-10000)
   DSFX_I3DL2REVERB_ROOMHF_MAX                 EQU 0
   DSFX_I3DL2REVERB_ROOMHF_DEFAULT             EQU (-100)

   DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MIN      EQU 0.0f
   DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MAX      EQU 10.0f
   DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_DEFAULT  EQU 0.0f

   DSFX_I3DL2REVERB_DECAYTIME_MIN              EQU 0.1f
   DSFX_I3DL2REVERB_DECAYTIME_MAX              EQU 20.0f
   DSFX_I3DL2REVERB_DECAYTIME_DEFAULT          EQU 1.49f

   DSFX_I3DL2REVERB_DECAYHFRATIO_MIN           EQU 0.1f
   DSFX_I3DL2REVERB_DECAYHFRATIO_MAX           EQU 2.0f
   DSFX_I3DL2REVERB_DECAYHFRATIO_DEFAULT       EQU 0.83f

   DSFX_I3DL2REVERB_REFLECTIONS_MIN            EQU (-10000)
   DSFX_I3DL2REVERB_REFLECTIONS_MAX            EQU 1000
   DSFX_I3DL2REVERB_REFLECTIONS_DEFAULT        EQU (-2602)

   DSFX_I3DL2REVERB_REFLECTIONSDELAY_MIN       EQU 0.0f
   DSFX_I3DL2REVERB_REFLECTIONSDELAY_MAX       EQU 0.3f
   DSFX_I3DL2REVERB_REFLECTIONSDELAY_DEFAULT   EQU 0.007f

   DSFX_I3DL2REVERB_REVERB_MIN                 EQU (-10000)
   DSFX_I3DL2REVERB_REVERB_MAX                 EQU 2000
   DSFX_I3DL2REVERB_REVERB_DEFAULT             EQU (200)

   DSFX_I3DL2REVERB_REVERBDELAY_MIN            EQU 0.0f
   DSFX_I3DL2REVERB_REVERBDELAY_MAX            EQU 0.1f
   DSFX_I3DL2REVERB_REVERBDELAY_DEFAULT        EQU 0.011f

   DSFX_I3DL2REVERB_DIFFUSION_MIN              EQU 0.0f
   DSFX_I3DL2REVERB_DIFFUSION_MAX              EQU 100.0f
   DSFX_I3DL2REVERB_DIFFUSION_DEFAULT          EQU 100.0f

   DSFX_I3DL2REVERB_DENSITY_MIN                EQU 0.0f
   DSFX_I3DL2REVERB_DENSITY_MAX                EQU 100.0f
   DSFX_I3DL2REVERB_DENSITY_DEFAULT            EQU 100.0f

   DSFX_I3DL2REVERB_HFREFERENCE_MIN            EQU 20.0f
   DSFX_I3DL2REVERB_HFREFERENCE_MAX            EQU 20000.0f
   DSFX_I3DL2REVERB_HFREFERENCE_DEFAULT        EQU 5000.0f

   DSFX_I3DL2REVERB_QUALITY_MIN                EQU 0
   DSFX_I3DL2REVERB_QUALITY_MAX                EQU 3
   DSFX_I3DL2REVERB_QUALITY_DEFAULT            EQU 2

 ;=============================================================================
 ;  IDirectSoundFXI3DL2Reverb  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXI3DL2Reverb

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXI3DL2Reverb methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2
    STDMETHOD	SetPreset,			2
    STDMETHOD	GetPreset,			2
    STDMETHOD	SetQuality,			2
    STDMETHOD	GetQuality,			2

    end virtual

  ends

 ; IDirectSoundFXWavesReverb
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundFXWavesReverb  
	.data1  dd  046858c3ah
	.data2  dw  00dc6h,045e3h
	.data3  db  0b7h,060h,0d4h,0eeh,0f1h,06ch,0b3h,025h
  ends

   struct DSFXWavesReverb
	.fInGain		dd   ?    ;[-96.0,0.0]      default: 0.0 dB
	.fReverbMix		dd   ?    ;[-96.0,0.0]      default: 0.0 db
	.fReverbTime		dd   ?    ;[0.001,3000.0]   default: 1000.0 ms
	.fHighFreqRTRatio	dd   ?    ;[0.001,0.999]    default: 0.001
   ends

   LPDSFXWavesReverb		EQU  DWORD
   LPCDSFXWavesReverb		EQU  DWORD

   DSFX_WAVESREVERB_INGAIN_MIN                 EQU  -96.0f
   DSFX_WAVESREVERB_INGAIN_MAX                 EQU   0.0f
   DSFX_WAVESREVERB_INGAIN_DEFAULT             EQU   0.0f
   DSFX_WAVESREVERB_REVERBMIX_MIN              EQU  -96.0f
   DSFX_WAVESREVERB_REVERBMIX_MAX              EQU   0.0f
   DSFX_WAVESREVERB_REVERBMIX_DEFAULT          EQU   0.0f
   DSFX_WAVESREVERB_REVERBTIME_MIN             EQU   0.001f
   DSFX_WAVESREVERB_REVERBTIME_MAX             EQU   3000.0f
   DSFX_WAVESREVERB_REVERBTIME_DEFAULT         EQU   1000.0f
   DSFX_WAVESREVERB_HIGHFREQRTRATIO_MIN        EQU   0.001f
   DSFX_WAVESREVERB_HIGHFREQRTRATIO_MAX        EQU   0.999f
   DSFX_WAVESREVERB_HIGHFREQRTRATIO_DEFAULT    EQU   0.001f

 ;=============================================================================
 ;  IDirectSoundFXWavesReverb  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFXWavesReverb

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFXWavesReverb methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2

    end virtual

  ends

 ; IDirectSoundCaptureFXAec
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundCaptureFXAec 
	.data1  dd  0ad74143dh
	.data2  dw  0903dh,04ab7h
	.data3  db  080h,066h,028h,0d3h,063h,003h,06dh,065h
  ends

   struct DSCFXAec
	.fEnable	dd   ?
	.fNoiseFill	dd   ?
	.dwMode		dd   ?
   ends
   LPDSCFXAec	 	EQU  DWORD
   LPCDSCFXAec		EQU  DWORD

 ; These match the AEC_MODE_* constants in the DDK's ksmedia.h file
 ; ----------------------------------------------------------------
   DSCFX_AEC_MODE_PASS_THROUGH                     EQU   00h
   DSCFX_AEC_MODE_HALF_DUPLEX                      EQU   01h
   DSCFX_AEC_MODE_FULL_DUPLEX                      EQU   02h

 ; These match the AEC_STATUS_* constants in ksmedia.h
 ; ----------------------------------------------------------------
   DSCFX_AEC_STATUS_HISTORY_UNINITIALIZED          EQU   00h
   DSCFX_AEC_STATUS_HISTORY_CONTINUOUSLY_CONVERGED EQU   01h
   DSCFX_AEC_STATUS_HISTORY_PREVIOUSLY_DIVERGED    EQU   02h
   DSCFX_AEC_STATUS_CURRENTLY_CONVERGED            EQU   08h

 ;=============================================================================
 ;  IDirectSoundCaptureFXAec  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundCaptureFXAec

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundCaptureFXAec methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2
    STDMETHOD	GetStatus,			2
    STDMETHOD	Reset,				1

    end virtual

  ends

 ; IDirectSoundCaptureFXNoiseSuppress
 ; ----------------------------------------------------------------------------

  struct IID_IDirectSoundCaptureFXNoiseSuppress 
	.data1  dd  0ed311e41h
	.data2  dw  0fbaeh,04175h
	.data3  db  096h,025h,0cdh,008h,054h,0f6h,093h,0cah
  ends

   struct DSCFXNoiseSuppress
	.fEnable			dd  ?
   ends
   LPDSCFXNoiseSuppress		EQU  DWORD
   LPCDSCFXNoiseSuppress	EQU  DWORD

 ;=============================================================================
 ;  IDirectSoundCaptureFXNoiseSuppress  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundCaptureFXNoiseSuppress

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundCaptureFXNoiseSuppress methods

    STDMETHOD	SetAllParameters,		2
    STDMETHOD	GetAllParameters,		2
    STDMETHOD	Reset,				1

    end virtual

  ends

 ; IDirectSoundFullDuplex
 ; ----------------------------------------------------------------------------

   LPDIRECTSOUNDFULLDUPLEX      EQU  DWORD

  struct IID_IDirectSoundFullDuplex 
	.data1  dd  0edcb4c7ah
	.data2  dw  0daabh,04216h
	.data3  db  0a4h,02eh,06ch,050h,059h,06dh,0dch,01dh
  ends

 ;=============================================================================
 ;  IDirectSoundFullDuplex  Виртуальная таблица методов
 ;=============================================================================
  struct DirectSoundFullDuplex

   .handle  dd ?
    virtual at 0

    ;IUnknown methods

    STDMETHOD	QueryInterface, 		3
    STDMETHOD	AddRef, 			1
    STDMETHOD	Release, 			1

    ;IDirectSoundFullDuplex methods

    STDMETHOD	Initialize,			9

    end virtual

  ends

 ; Return Codes
 ; ----------------------------------------------------------------------------
   macro MAKE_HRESULT hres_name, severity, facility, code
   {
     hres_name EQU (severity SHL 31) OR ((facility AND 0FFFh) SHL 16) OR (code AND 0FFFFh)
   }

 ; The function completed successfully
 ; -------------------------------------
   DS_OK    EQU   S_OK

 ; The call succeeded, but we had to substitute the 3D algorithm
 ; -------------------------------------------------------------
   MAKE_HRESULT  DS_NO_VIRTUALIZATION, 0, _FACDS, 10

 ; The call failed because resources (such as a priority level)
 ; were already being used by another caller
 ; ------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_ALLOCATED, 10

 ; The control (vol, pan, etc.) rEQUested by the caller is not available
 ; ----------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_CONTROLUNAVAIL, 30

 ; An invalid parameter was passed to the returning function
 ; ---------------------------------------------------------
   DSERR_INVALIDPARAM		EQU   E_INVALIDARG

 ; This call is not valid for the current state of this object
 ; -----------------------------------------------------------
   MAKE_DSHRESULT  DSERR_INVALIDCALL, 50

 ; An undetermined error occurred inside the DirectSound subsystem
 ; ---------------------------------------------------------------
   DSERR_GENERIC		EQU   E_FAIL

 ; The caller does not have the priority level rEQUired for the function to
 ; succeed
 ; -------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_PRIOLEVELNEEDED, 70

 ; Not enough free memory is available to complete the operation
 ; -------------------------------------------------------------------------
   DSERR_OUTOFMEMORY		EQU   E_OUTOFMEMORY

 ; The specified WAVE format is not supported
 ; -------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_BADFORMAT, 100

 ; The function called is not supported at this time
 ; -------------------------------------------------------------------------
   DSERR_UNSUPPORTED		EQU   E_NOTIMPL

 ; No sound driver is available for use
 ; -------------------------------------
   MAKE_DSHRESULT  DSERR_NODRIVER, 120

 ; This object is already initialized
 ; -----------------------------------
   MAKE_DSHRESULT  DSERR_ALREADYINITIALIZED, 130

 ; This object does not support aggregation
 ; -----------------------------------------
   DSERR_NOAGGREGATION		EQU   CLASS_E_NOAGGREGATION

 ; The buffer memory has been lost, and must be restored
 ; -----------------------------------------------------
   MAKE_DSHRESULT  DSERR_BUFFERLOST, 150

 ; Another app has a higher priority level, preventing this call from
 ; succeeding
 ; -------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_OTHERAPPHASPRIO, 160

 ; This object has not been initialized
 ; -------------------------------------
   MAKE_DSHRESULT  DSERR_UNINITIALIZED, 170

 ; The rEQUested COM interface is not available
 ; ---------------------------------------------
   DSERR_NOINTERFACE		EQU   E_NOINTERFACE

 ; Access is denied
 ; ------------------------------------------------
   DSERR_ACCESSDENIED		EQU   E_ACCESSDENIED

 ; Tried to create a DSBCAPS_CTRLFX buffer shorter than DSBSIZE_FX_MIN milliseconds
 ; --------------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_BUFFERTOOSMALL, 180

 ; Attempt to use DirectSound 8 functionality on an older DirectSound object
 ; --------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_DS8_REQUIRED, 190

 ; A circular loop of send effects was detected
 ; ----------------------------------------------
   MAKE_DSHRESULT DSERR_SENDLOOP, 200

 ; The GUID specified in an audiopath file does not match a valid MIXIN buffer
 ; ---------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_BADSENDBUFFERGUID, 210

 ; The object rEQUested was not found (numerically EQUal to DMUS_E_NOT_FOUND)
 ; ---------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_OBJECTNOTFOUND, 4449

 ; The effects rEQUested could not be found on the system, or they were found
 ; but in the wrong order, or in the wrong hardware/software locations.
 ; ---------------------------------------------------------------------------
   MAKE_DSHRESULT  DSERR_FXUNAVAILABLE, 220

 ; Flags
 ; ----------------------------------------------------------------------------

   DSCAPS_PRIMARYMONO          EQU 000000001h
   DSCAPS_PRIMARYSTEREO        EQU 000000002h
   DSCAPS_PRIMARY8BIT          EQU 000000004h
   DSCAPS_PRIMARY16BIT         EQU 000000008h
   DSCAPS_CONTINUOUSRATE       EQU 000000010h
   DSCAPS_EMULDRIVER           EQU 000000020h
   DSCAPS_CERTIFIED            EQU 000000040h
   DSCAPS_SECONDARYMONO        EQU 000000100h
   DSCAPS_SECONDARYSTEREO      EQU 000000200h
   DSCAPS_SECONDARY8BIT        EQU 000000400h
   DSCAPS_SECONDARY16BIT       EQU 000000800h

   DSSCL_NORMAL                EQU 000000001h
   DSSCL_PRIORITY              EQU 000000002h
   DSSCL_EXCLUSIVE             EQU 000000003h
   DSSCL_WRITEPRIMARY          EQU 000000004h

   DSSPEAKER_DIRECTOUT         EQU 000000000h
   DSSPEAKER_HEADPHONE         EQU 000000001h
   DSSPEAKER_MONO              EQU 000000002h
   DSSPEAKER_QUAD              EQU 000000003h
   DSSPEAKER_STEREO            EQU 000000004h
   DSSPEAKER_SURROUND          EQU 000000005h
   DSSPEAKER_5POINT1           EQU 000000006h
   DSSPEAKER_7POINT1           EQU 000000007h

   DSSPEAKER_GEOMETRY_MIN      EQU 000000005h  ;   5 degrees
   DSSPEAKER_GEOMETRY_NARROW   EQU 00000000Ah  ;  10 degrees
   DSSPEAKER_GEOMETRY_WIDE     EQU 000000014h  ;  20 degrees
   DSSPEAKER_GEOMETRY_MAX      EQU 0000000B4h  ; 180 degrees

  ;DSSPEAKER_COMBINED(c, g)    ((DWORD)(((BYTE)(c)) | ((DWORD)((BYTE)(g))) << 16))
   macro DSSPEAKER_COMBINED res,c,g
   {
	res = ((DWORD)(((BYTE)(c)) or ((DWORD)((BYTE)(g))) shl 16))
   }

  ;DSSPEAKER_CONFIG(a)         ((BYTE)(a))
   macro DSSPEAKER_CONFIG res, a
   {
	res = ((BYTE)(a))
   }

  ;DSSPEAKER_GEOMETRY(a)       ((BYTE)(((DWORD)(a) >> 16) & 0x000FF))
   macro DSSPEAKER_CONFIG res, a
   {
	res = ((BYTE)(((DWORD)(a) shr 16) and 0FFh))
   }

   DSBCAPS_PRIMARYBUFFER       EQU 000000001h
   DSBCAPS_STATIC              EQU 000000002h
   DSBCAPS_LOCHARDWARE         EQU 000000004h
   DSBCAPS_LOCSOFTWARE         EQU 000000008h
   DSBCAPS_CTRL3D              EQU 000000010h
   DSBCAPS_CTRLFREQUENCY       EQU 000000020h
   DSBCAPS_CTRLPAN             EQU 000000040h
   DSBCAPS_CTRLVOLUME          EQU 000000080h
   DSBCAPS_CTRLPOSITIONNOTIFY  EQU 000000100h
   DSBCAPS_CTRLFX              EQU 000000200h
   DSBCAPS_STICKYFOCUS         EQU 000004000h
   DSBCAPS_GLOBALFOCUS         EQU 000008000h
   DSBCAPS_GETCURRENTPOSITION2 EQU 000010000h
   DSBCAPS_MUTE3DATMAXDISTANCE EQU 000020000h
   DSBCAPS_LOCDEFER            EQU 000040000h

   DSBPLAY_LOOPING             EQU 000000001h
   DSBPLAY_LOCHARDWARE         EQU 000000002h
   DSBPLAY_LOCSOFTWARE         EQU 000000004h
   DSBPLAY_TERMINATEBY_TIME    EQU 000000008h
   DSBPLAY_TERMINATEBY_DISTANCE    EQU 0000000010h
   DSBPLAY_TERMINATEBY_PRIORITY    EQU 0000000020h

   DSBSTATUS_PLAYING           EQU 000000001h
   DSBSTATUS_BUFFERLOST        EQU 000000002h
   DSBSTATUS_LOOPING           EQU 000000004h
   DSBSTATUS_LOCHARDWARE       EQU 000000008h
   DSBSTATUS_LOCSOFTWARE       EQU 000000010h
   DSBSTATUS_TERMINATED        EQU 000000020h

   DSBLOCK_FROMWRITECURSOR     EQU 000000001h
   DSBLOCK_ENTIREBUFFER        EQU 000000002h

   DSBFREQUENCY_ORIGINAL       EQU 0
   DSBFREQUENCY_MIN            EQU 100

   DSBFREQUENCY_MAX            EQU 100000

   DSBPAN_LEFT                 EQU -10000
   DSBPAN_CENTER               EQU 0
   DSBPAN_RIGHT                EQU 10000

   DSBVOLUME_MIN               EQU -10000
   DSBVOLUME_MAX               EQU 0

   DSBSIZE_MIN                 EQU 4
   DSBSIZE_MAX                 EQU 00FFFFFFFh
   DSBSIZE_FX_MIN              EQU 150   ; NOTE: Milliseconds, not bytes

   DS3DMODE_NORMAL             EQU 000000000h
   DS3DMODE_HEADRELATIVE       EQU 000000001h
   DS3DMODE_DISABLE            EQU 000000002h

   DS3D_IMMEDIATE              EQU 000000000h
   DS3D_DEFERRED               EQU 000000001h

   DS3D_MINDISTANCEFACTOR      EQU 1.175494351e-38f ;FLT_MIN
   DS3D_MAXDISTANCEFACTOR      EQU 3.402823466e+38f ;FLT_MAX
   DS3D_DEFAULTDISTANCEFACTOR  EQU 1.0f

   DS3D_MINROLLOFFFACTOR       EQU 0.0f
   DS3D_MAXROLLOFFFACTOR       EQU 10.0f
   DS3D_DEFAULTROLLOFFFACTOR   EQU 1.0f

   DS3D_MINDOPPLERFACTOR       EQU 0.0f
   DS3D_MAXDOPPLERFACTOR       EQU 10.0f
   DS3D_DEFAULTDOPPLERFACTOR   EQU 1.0f
   
   DS3D_DEFAULTMINDISTANCE     EQU 1.0f
   DS3D_DEFAULTMAXDISTANCE     EQU 1000000000.0f

   DS3D_MINCONEANGLE           EQU 0
   DS3D_MAXCONEANGLE           EQU 360
   DS3D_DEFAULTCONEANGLE       EQU 360

   DS3D_DEFAULTCONEOUTSIDEVOLUME EQU DSBVOLUME_MAX

 ; IDirectSoundCapture attributes
 ; ----------------------------------------------------------------------------

   DSCCAPS_EMULDRIVER          EQU DSCAPS_EMULDRIVER
   DSCCAPS_CERTIFIED           EQU DSCAPS_CERTIFIED
   DSCCAPS_MULTIPLECAPTURE     EQU 000000001h

 ; IDirectSoundCaptureBuffer attributes
 ; ----------------------------------------------------------------------------

   DSCBCAPS_WAVEMAPPED         EQU 080000000h
   DSCBCAPS_CTRLFX             EQU 000000200h

   DSCBLOCK_ENTIREBUFFER       EQU 000000001h

   DSCBSTATUS_CAPTURING        EQU 000000001h
   DSCBSTATUS_LOOPING          EQU 000000002h

   DSCBSTART_LOOPING           EQU 000000001h

   DSBPN_OFFSETSTOP            EQU 0FFFFFFFFh

   DS_CERTIFIED                EQU 000000000h
   DS_UNCERTIFIED              EQU 000000001h

 ; Flags for the I3DL2 effects
 ; ----------------------------------------------------------------------------

 ; I3DL2 Material Presets
 ; ----------------------------------------------------------------------------

   DSFX_I3DL2_MATERIAL_PRESET_SINGLEWINDOW	EQU 0
   DSFX_I3DL2_MATERIAL_PRESET_DOUBLEWINDOW	EQU 1
   DSFX_I3DL2_MATERIAL_PRESET_THINDOOR		EQU 2
   DSFX_I3DL2_MATERIAL_PRESET_THICKDOOR		EQU 3
   DSFX_I3DL2_MATERIAL_PRESET_WOODWALL		EQU 4
   DSFX_I3DL2_MATERIAL_PRESET_BRICKWALL		EQU 5
   DSFX_I3DL2_MATERIAL_PRESET_STONEWALL		EQU 6
   DSFX_I3DL2_MATERIAL_PRESET_CURTAIN		EQU 7

   struct I3DL2_MATERIAL_PRESET_SINGLEWINDOW   
	.data1 dd -2800, 0.71f
   ends
   struct I3DL2_MATERIAL_PRESET_DOUBLEWINDOW  
	.data1 dd -5000, 0.40f
   ends
   struct I3DL2_MATERIAL_PRESET_THINDOOR       
	.data1 dd -1800, 0.66f
   ends
   struct I3DL2_MATERIAL_PRESET_THICKDOOR      
	.data1 dd -4400, 0.64f
   ends
   struct I3DL2_MATERIAL_PRESET_WOODWALL       
	.data1 dd -4000, 0.50f
   ends
   struct I3DL2_MATERIAL_PRESET_BRICKWALL       	
	.data1 dd -5000, 0.60f
   ends
   struct I3DL2_MATERIAL_PRESET_STONEWALL       	
	.data1 dd -6000, 0.68f
   ends
   struct I3DL2_MATERIAL_PRESET_CURTAIN         	
	.data1 dd -1200, 0.15f
   ends

   DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT		EQU  0
   DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC		EQU  1
   DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL		EQU  2
   DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM			EQU  3
   DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM		EQU  4
   DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM		EQU  5
   DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM		EQU  6
   DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM		EQU  7
   DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL		EQU  8
   DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE			EQU  9
   DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA			EQU  10
   DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR			EQU  11
   DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY	EQU  12
   DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY		EQU  13
   DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR		EQU  14
   DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY			EQU  15
   DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST			EQU  16
   DSFX_I3DL2_ENVIRONMENT_PRESET_CITY			EQU  17
   DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS		EQU  18
   DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY			EQU  19
   DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN			EQU  20
   DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT		EQU  21
   DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE		EQU  22
   DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER		EQU  23
   DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM		EQU  24
   DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM		EQU  25
   DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM		EQU  26
   DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL		EQU  27
   DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL		EQU  28
   DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE			EQU  29

 ; I3DL2 Reverberation Presets Values
 ; ----------------------------------------------------------------------------

   struct I3DL2_ENVIRONMENT_PRESET_DEFAULT  
	dd -1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f,   200, 0.011f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_GENERIC
	dd -1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f,   200, 0.011f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_PADDEDCELL
	dd -1000,-6000, 0.0f, 0.17f, 0.10f, -1204, 0.001f,   207, 0.002f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_ROOM
	dd -1000, -454, 0.0f, 0.40f, 0.83f, -1646, 0.002f,    53, 0.003f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_BATHROOM
	dd -1000,-1200, 0.0f, 1.49f, 0.54f,  -370, 0.007f,  1030, 0.011f, 100.0f,  60.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_LIVINGROOM
	dd -1000,-6000, 0.0f, 0.50f, 0.10f, -1376, 0.003f, -1104, 0.004f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_STONEROOM
	dd -1000, -300, 0.0f, 2.31f, 0.64f,  -711, 0.012f,    83, 0.017f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_AUDITORIUM
	dd -1000, -476, 0.0f, 4.32f, 0.59f,  -789, 0.020f,  -289, 0.030f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_CONCERTHALL
	dd -1000, -500, 0.0f, 3.92f, 0.70f, -1230, 0.020f,    -2, 0.029f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_CAVE
	dd -1000,    0, 0.0f, 2.91f, 1.30f,  -602, 0.015f,  -302, 0.022f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_ARENA
	dd -1000, -698, 0.0f, 7.24f, 0.33f, -1166, 0.020f,    16, 0.030f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_HANGAR
	dd -1000,-1000, 0.0f,10.05f, 0.23f,  -602, 0.020f,   198, 0.030f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY
	dd -1000,-4000, 0.0f, 0.30f, 0.10f, -1831, 0.002f, -1630, 0.030f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_HALLWAY
	dd -1000, -300, 0.0f, 1.49f, 0.59f, -1219, 0.007f,   441, 0.011f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR
	dd -1000, -237, 0.0f, 2.70f, 0.79f, -1214, 0.013f,   395, 0.020f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_ALLEY
	dd -1000, -270, 0.0f, 1.49f, 0.86f, -1204, 0.007f,    -4, 0.011f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_FOREST
	dd -1000,-3300, 0.0f, 1.49f, 0.54f, -2560, 0.162f,  -613, 0.088f,  79.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_CITY
	dd -1000, -800, 0.0f, 1.49f, 0.67f, -2273, 0.007f, -2217, 0.011f,  50.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_MOUNTAINS
	dd -1000,-2500, 0.0f, 1.49f, 0.21f, -2780, 0.300f, -2014, 0.100f,  27.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_QUARRY
	dd -1000,-1000, 0.0f, 1.49f, 0.83f,-10000, 0.061f,   500, 0.025f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_PLAIN
	dd -1000,-2000, 0.0f, 1.49f, 0.50f, -2466, 0.179f, -2514, 0.100f,  21.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_PARKINGLOT
	dd -1000,    0, 0.0f, 1.65f, 1.50f, -1363, 0.008f, -1153, 0.012f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_SEWERPIPE
	dd -1000,-1000, 0.0f, 2.81f, 0.14f,   429, 0.014f,   648, 0.021f,  80.0f,  60.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_UNDERWATER
	dd -1000,-4000, 0.0f, 1.49f, 0.10f,  -449, 0.007f,  1700, 0.011f, 100.0f, 100.0f, 5000.0f
   ends

 ; Examples simulating 'musical' reverb presets
 ;
 ; Name       Decay time   Description
 ; Small Room    1.1s      A small size room with a length of 5m or so.
 ; Medium Room   1.3s      A medium size room with a length of 10m or so.
 ; Large Room    1.5s      A large size room suitable for live performances.
 ; Medium Hall   1.8s      A medium size concert hall.
 ; Large Hall    1.8s      A large size concert hall suitable for a full orchestra.
 ; Plate         1.3s      A plate reverb simulation.
 ; ----------------------------------------------------------------------------

   struct I3DL2_ENVIRONMENT_PRESET_SMALLROOM
	dd -1000, -600, 0.0f, 1.10f, 0.83f,  -400, 0.005f,   500, 0.010f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM
	dd -1000, -600, 0.0f, 1.30f, 0.83f, -1000, 0.010f,  -200, 0.020f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_LARGEROOM
	dd -1000, -600, 0.0f, 1.50f, 0.83f, -1600, 0.020f, -1000, 0.040f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL
	dd -1000, -600, 0.0f, 1.80f, 0.70f, -1300, 0.015f,  -800, 0.030f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_LARGEHALL
	dd -1000, -600, 0.0f, 1.80f, 0.70f, -2000, 0.030f, -1400, 0.060f, 100.0f, 100.0f, 5000.0f
   ends
   struct I3DL2_ENVIRONMENT_PRESET_PLATE
	dd -1000, -200, 0.0f, 1.30f, 0.90f,     0, 0.002f,     0, 0.010f, 100.0f,  75.0f, 5000.0f
   ends

 ; DirectSound3D Algorithms
 ; ----------------------------------------------------------------------------

 ; Default DirectSound3D algorithm {00000000-0000-0000-0000-000000000000}
   DS3DALG_DEFAULT		EQU  GUID_NULL

 ; No virtualization (Pan3D) {C241333F-1C1B-11d2-94F5-00C04FC28ACA}
   struct DS3DALG_NO_VIRTUALIZATION	
	.data1  dd  0c241333fh
	.data2  dw  01c1bh,011d2h
	.data3  db  094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah
   ends

 ; High-quality HRTF algorithm {C2413340-1C1B-11d2-94F5-00C04FC28ACA}
   struct DS3DALG_HRTF_FULL		
	.data1  dd  0c2413340h
	.data2  dw  01c1bh,011d2h
	.data3  db  094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah
   ends

 ; Lower-quality HRTF algorithm {C2413342-1C1B-11d2-94F5-00C04FC28ACA}
   struct DS3DALG_HRTF_LIGHT		
	.data1  dd  0c2413342h
	.data2  dw  01c1bh,011d2h
	.data3  db  094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah
   ends

 ; DirectSound Internal Effect Algorithms
 ; ----------------------------------------------------------------------------

 ; Gargle {DAFD8210-5711-4B91-9FE3-F75B7AE279BF}
   struct GUID_DSFX_STANDARD_GARGLE
	.data1  dd  0dafd8210h
	.data2  dw  05711h,04b91h
	.data3  db  09fh,0e3h,0f7h,05bh,07ah,0e2h,079h,0bfh
   ends

 ; Chorus {EFE6629C-81F7-4281-BD91-C9D604A95AF6}
   struct GUID_DSFX_STANDARD_CHORUS
	.data1  dd  0efe6629ch
	.data2  dw  081f7h,04281h
	.data3  db  0bdh,091h,0c9h,0d6h,004h,0a9h,05ah,0f6h
   ends

 ; Flanger {EFCA3D92-DFD8-4672-A603-7420894BAD98}
   struct GUID_DSFX_STANDARD_FLANGER
	.data1  dd  0efca3d92h
	.data2  dw  0dfd8h,04672h
	.data3  db  0a6h,003h,074h,020h,089h,04bh,0adh,098h
   ends

 ; Echo/Delay {EF3E932C-D40B-4F51-8CCF-3F98F1B29D5D}
   struct GUID_DSFX_STANDARD_ECHO		
	.data1  dd  0ef3e932ch
	.data2  dw  0d40bh,04f51h
	.data3  db  08ch,0cfh,03fh,098h,0f1h,0b2h,09dh,05dh
   ends

 ; Distortion {EF114C90-CD1D-484E-96E5-09CFAF912A21}
   struct GUID_DSFX_STANDARD_DISTORTION
	.data1  dd  0ef114c90h
	.data2  dw  0cd1dh,0484eh
	.data3  db  096h,0e5h,009h,0cfh,0afh,091h,02ah,021h
   ends

 ; Compressor/Limiter {EF011F79-4000-406D-87AF-BFFB3FC39D57}
   struct GUID_DSFX_STANDARD_COMPRESSOR
	.data1  dd  0ef011f79h
	.data2  dw  04000h,0406dh
	.data3  db  087h,0afh,0bfh,0fbh,03fh,0c3h,09dh,057h
   ends

 ; Parametric EQUalization {120CED89-3BF4-4173-A132-3CB406CF3231}
   struct GUID_DSFX_STANDARD_PARAMEQ
	.data1  dd  0120ced89h
	.data2  dw  03bf4h,04173h
	.data3  db  0a1h,032h,03ch,0b4h,006h,0cfh,032h,031h
   ends

 ; I3DL2 Environmental Reverberation: Reverb (Listener) Effect {EF985E71-D5C7-42D4-BA4D-2D073E2E96F4}
   struct GUID_DSFX_STANDARD_I3DL2REVERB
	.data1  dd  0ef985e71h
	.data2  dw  0d5c7h,042d4h
	.data3  db  0bah,04dh,02dh,007h,03eh,02eh,096h,0f4h
   ends

 ; Waves Reverberation {87FC0268-9A55-4360-95AA-004A1D9DE26C}
   struct GUID_DSFX_WAVES_REVERB
	.data1  dd  087fc0268h
	.data2  dw  09a55h,04360h
	.data3  db  095h,0aah,000h,04ah,01dh,09dh,0e2h,06ch
   ends

 ; DirectSound Capture Effect Algorithms
 ; ----------------------------------------------------------------------------

 ; Acoustic Echo Canceller {BF963D80-C559-11D0-8A2B-00A0C9255AC1}
 ; Matches KSNODETYPE_ACOUSTIC_ECHO_CANCEL in ksmedia.h
   struct GUID_DSCFX_CLASS_AEC
	.data1  dd  0BF963D80h
	.data2  dw  0C559h,011D0h
	.data3  db  08Ah,02Bh,000h,0A0h,0C9h,025h,05Ah,0C1h
   ends

 ; Microsoft AEC {CDEBB919-379A-488a-8765-F53CFD36DE40}
   struct GUID_DSCFX_MS_AEC
	.data1  dd  0cdebb919h
	.data2  dw  0379ah,0488ah
	.data3  db  087h,065h,0f5h,03ch,0fdh,036h,0deh,040h
   ends

 ; System AEC {1C22C56D-9879-4f5b-A389-27996DDC2810}
   struct GUID_DSCFX_SYSTEM_AEC
	.data1  dd  01c22c56dh
	.data2  dw  09879h,04f5bh
	.data3  db  0a3h,089h,027h,099h,06dh,0dch,028h,010h
   ends

 ; Noise Supression {E07F903F-62FD-4e60-8CDD-DEA7236665B5}
 ; Matches KSNODETYPE_NOISE_SUPPRESS in post Windows ME DDK's ksmedia.h
   struct GUID_DSCFX_CLASS_NS
	.data1  dd  0e07f903fh
	.data2  dw  062fdh,04e60h
	.data3  db  08ch,0ddh,0deh,0a7h,023h,066h,065h,0b5h
   ends

 ; Microsoft Noise Suppresion {11C5C73B-66E9-4ba1-A0BA-E814C6EED92D}
   struct GUID_DSCFX_MS_NS
	.data1  dd  011c5c73bh
	.data2  dw  066e9h,04ba1h
	.data3  db  0a0h,0bah,0e8h,014h,0c6h,0eeh,0d9h,02dh
   ends

 ; System Noise Suppresion {5AB0882E-7274-4516-877D-4EEE99BA4FD0}
   struct GUID_DSCFX_SYSTEM_NS
	.data1  dd  05ab0882eh
	.data2  dw  07274h,04516h
	.data3  db  087h,07dh,04eh,0eeh,099h,0bah,04fh,0d0h
   ends

 ; Структуры для функций winmm
 ; -----------------------------------------------------

  struct MMCKINFO
    .ckid          dd      ?
    .ckSize        dd      ?
    .fccType       dd      ?
    .dwDataOffset  dd      ?
    .dwFlags       dd      ?
  ends
 
  struct WAVEFORMATEX
     .wFormatTag       dw ?
     .nChannels        dw ?
     .nSamplesPerSec   dd ?
     .nAvgBytesPerSec  dd ?
     .nBlockAlign      dw ?
     .wBitsPerSample   dw ?
     .cbSize           dw ?
  ends

 ; Константы для функций winmm
 ; -----------------------------------------------------

  MMIOERR_BASE                         equ 256
  MMIOERR_FILENOTFOUND                 equ MMIOERR_BASE + 1
  MMIOERR_OUTOFMEMORY                  equ MMIOERR_BASE + 2
  MMIOERR_CANNOTOPEN                   equ MMIOERR_BASE + 3
  MMIOERR_CANNOTCLOSE                  equ MMIOERR_BASE + 4
  MMIOERR_CANNOTREAD                   equ MMIOERR_BASE + 5
  MMIOERR_CANNOTWRITE                  equ MMIOERR_BASE + 6
  MMIOERR_CANNOTSEEK                   equ MMIOERR_BASE + 7
  MMIOERR_CANNOTEXPAND                 equ MMIOERR_BASE + 8
  MMIOERR_CHUNKNOTFOUND                equ MMIOERR_BASE + 9
  MMIOERR_UNBUFFERED                   equ MMIOERR_BASE + 10
  MMIO_RWMODE                          equ 3h
  MMIO_SHAREMODE                       equ 70h
  MMIO_CREATE                          equ 1000h
  MMIO_PARSE                           equ 100h
  MMIO_DELETE                          equ 200h
  MMIO_EXIST                           equ 4000h
  MMIO_ALLOCBUF                        equ 10000h
  MMIO_GETTEMP                         equ 20000h
  MMIO_DIRTY                           equ 10000000h
  MMIO_OPEN_VALID                      equ 3FFFFh
  MMIO_READ                            equ 0h
  MMIO_WRITE                           equ 1h
  MMIO_READWRITE                       equ 2h
  MMIO_COMPAT                          equ 0h
  MMIO_EXCLUSIVE                       equ 10h
  MMIO_DENYWRITE                       equ 20h
  MMIO_DENYREAD                        equ 30h
  MMIO_DENYNONE                        equ 40h
  MMIO_FHOPEN                          equ 10h
  MMIO_EMPTYBUF                        equ 10h
  MMIO_TOUPPER                         equ 10h
  MMIO_INSTALLPROC                     equ 10000h
  MMIO_GLOBALPROC                      equ 10000000h
  MMIO_UNICODEPROC                     equ 1000000h
  MMIO_REMOVEPROC                      equ 20000h
  MMIO_FINDPROC                        equ 40000h
  MMIO_FINDCHUNK                       equ 10h
  MMIO_FINDRIFF                        equ 20h
  MMIO_FINDLIST                        equ 40h
  MMIO_CREATERIFF                      equ 20h
  MMIO_CREATELIST                      equ 40h
  MMIO_VALIDPROC                       equ 11070000h
