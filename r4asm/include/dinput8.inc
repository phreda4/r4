 ;=============================================================================;
 ;  Copyright (C) Microsoft Corporation.  All Rights Reserved.                 ;
 ;                                                                             ;
 ;  File:       dinput.h ( dinput8.inc - FASM version )                        ;
 ;  Content:    DirectInput include file                                       ;
 ;                                                                             ;
 ; Все замечания и пожелания прошу направлять по адресу:   vertexland@narod.ru ;
 ; Страничка где вы можете скачать свежую версию:          vertexland.narod.ru ;
 ;                                                                             ;
 ;                              Converted (c) 2004. Denis Kozyr (Денис Козырь) ;
 ;                                            2005.  keYMax (Пономарев Михаил) ;
 ;=============================================================================;

 DIRECTINPUT_VERSION	 EQU   0800h

 LPDIRECTINPUT8 	 EQU   DWORD
 LPDIRECTINPUTDEVICE8	 EQU   DWORD
 MAX_PATH		 EQU   260

 ; ***************************************************************************
 ; *      Interfaces
 ; ***************************************************************************

  struct IID_IDirectInput8A
      .data1   dd 0BF798030h
      .data2   dw 0483Ah
      .data3   dw 04DA2h
      .data4   db 0AAh,099h,05Dh,064h,0EDh,036h,097h,00h
  ends
 
 ; ***************************************************************************
 ; *      Predefined object types
 ; ***************************************************************************

  struct GUID_XAxis
      .data1    dd 0A36D02E0h
      .data2    dw 0C9F3h
      .data3    dw 011CFh
      .data4    db 0BFh, 0C7h, 044h, 045h, 053h, 054h, 000h, 000h
  ends
  struct GUID_YAxis
      .data1    dd 0A36D02E1h
      .data2    dw 0C9F3h
      .data3    dw 011CFh
      .data4    db 0BFh, 0C7h, 044h, 045h, 053h, 054h, 000h, 000h
  ends
  struct GUID_ZAxis
      .data1    dd 0A36D02E2h
      .data2    dw 0C9F3h
      .data3    dw 011CFh
      .data4    db 0BFh, 0C7h, 044h, 045h, 053h, 054h, 000h, 000h
  ends

  struct GUID_Key
       .data1   dd 055728220h
       .data2   dw 0D33Ch
       .data3   dw 011CFh
       .data4   db 0BFh, 0C7h, 044h, 045h, 053h, 054h, 000h, 000h
  ends

 ; ***************************************************************************
 ; *      Predefined product GUIDs
 ; ***************************************************************************

  struct GUID_SysMouse
        .data1   dd 06F1D2B60h
        .data2   dw 0D5A0h
        .data3   dw 011CFh
        .data4   db 0BFh,0C7h,044h,045h,053h,054h,000h,000h
  ends

  struct GUID_SysKeyboard
      .data1  dd  06F1D2B61h
      .data2  dw  0D5A0h
      .data3  dw  011CFh
      .data4  db  0BFh,0C7h,044h,045h,053h,054h,000h,000h
  ends

 ;***************************************************************************
 ;*      IDirectInputEffect
 ;***************************************************************************
   DIEFT_ALL			      EQU  000000000h

   DIEFT_CONSTANTFORCE		      EQU  000000001h
   DIEFT_RAMPFORCE		      EQU  000000002h
   DIEFT_PERIODIC		      EQU  000000003h
   DIEFT_CONDITION		      EQU  000000004h
   DIEFT_CUSTOMFORCE		      EQU  000000005h
   DIEFT_HARDWARE		      EQU  0000000FFh
   DIEFT_FFATTACK		      EQU  000000200h
   DIEFT_FFFADE 		      EQU  000000400h
   DIEFT_SATURATION		      EQU  000000800h
   DIEFT_POSNEGCOEFFICIENTS	      EQU  000001000h
   DIEFT_POSNEGSATURATION	      EQU  000002000h
   DIEFT_DEADBAND		      EQU  000004000h
   DIEFT_STARTDELAY		      EQU  000008000h

   ;DIEFT_GETTYPE                     MACRO  n
   ;                                   ENDM   LOW n

   DI_DEGREES			      EQU  100
   DI_FFNOMINALMAX		      EQU  10000
   DI_SECONDS			      EQU  1000000

 ; ------------------------------------------------
 ; Structure: DICONSTANTFORCE
 ; ------------------------------------------------
   struct DICONSTANTFORCE
       .lMagnitude	    dd	?  ; LONG
   ends
   LPDICONSTANTFORCE   EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIRAMPFORCE
 ; ------------------------------------------------
   struct DIRAMPFORCE
       .lStart		    dd	?  ; LONG
       .lEnd		    dd	?  ; LONG
   ends
   LPDIRAMPFORCE       EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIPERIODIC
 ; ------------------------------------------------
   struct DIPERIODIC
       .dwMagnitude	    dd	?
       .lOffset 	    dd	?  ; LONG
       .dwPhase 	    dd	?
       .dwPeriod	    dd	?
   ends
   LPDIPERIODIC        EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DICONDITION
 ; ------------------------------------------------
   struct DICONDITION
       .lOffset 		 dd  ?	; LONG
       .lPositiveCoefficient	 dd  ?	; LONG
       .lNegativeCoefficient	 dd  ?	; LONG
       .dwPositiveSaturation	 dd  ?
       .dwNegativeSaturation	 dd  ?
       .lDeadBand		 dd  ?	; LONG
   ends
   LPDICONDITION       EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DICUSTOMFORCE
 ; ------------------------------------------------
   struct DICUSTOMFORCE
       .cChannels	    dd	?
       .dwSamplePeriod	    dd	?
       .cSamples	    dd	?
       .rglForceData	    dd	?  ; LPLONG
   ends
   LPDICUSTOMFORCE     EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIENVELOPE
 ; ------------------------------------------------
   struct DIENVELOPE
       .dwSize		    dd	?  ;  sizeof(DIENVELOPE)
       .dwAttackLevel	    dd	?
       .dwAttackTime	    dd	?  ;  Microseconds
       .dwFadeLevel	    dd	?
       .dwFadeTime	    dd	?  ;  Microseconds
   ends
   LPDIENVELOPE        EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIEFFECT_DX5
 ; ------------------------------------------------
   struct DIEFFECT_DX5
       .dwSize			 dd  ?	   ;  sizeof(DIEFFECT)
       .dwFlags 		 dd  ?	   ;  DIEFF_*
       .dwDuration		 dd  ?	   ;  Microseconds
       .dwSamplePeriod		 dd  ?	   ;  Microseconds
       .dwGain			 dd  ?
       .dwTriggerButton 	 dd  ?	   ;  or DIEB_NOTRIGGER
       .dwTriggerRepeatInterval  dd  ?	   ;  Microseconds
       .cAxes			 dd  ?	   ;  Number of axes
       .rgdwAxes		 dd  ?	   ;  LPDWORD          ;  Array of axes
       .rglDirection		 dd  ?	   ;  LPLONG           ;  Array of directions
       .lpEnvelope		 dd  ?	   ;  LPDIENVELOPE     ;  Optional
       .cbTypeSpecificParams	 dd  ?	   ;  Size of params
       .lpvTypeSpecificParams	 dd  ?	   ;  LPVOID           ;  Pointer to params
   ends
   LPDIEFFECT_DX5      EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIEFFECT
 ; ------------------------------------------------
   struct  DIEFFECT
       .dwSize			 dd  ?	   ;  sizeof(DIEFFECT)
       .dwFlags 		 dd  ?	   ;  DIEFF_*
       .dwDuration		 dd  ?	   ;  Microseconds
       .dwSamplePeriod		 dd  ?	   ;  Microseconds
       .dwGain			 dd  ?
       .dwTriggerButton 	 dd  ?	   ;  or DIEB_NOTRIGGER
       .dwTriggerRepeatInterval  dd  ?	   ;  Microseconds
       .cAxes			 dd  ?	   ;  Number of axes
       .rgdwAxes		 dd  ?	   ;  LPDWORD          ;  Array of axes
       .rglDirection		 dd  ?	   ;  LPLONG           ;  Array of directions
       .lpEnvelope		 dd  ?	   ;  LPDIENVELOPE     ;  Optional
       .cbTypeSpecificParams	 dd  ?	   ;  Size of param
       .lpvTypeSpecificParams	 dd  ?	   ;  LPVOID           ;  Pointer to params
       .dwStartDelay		 dd  ?	   ;  Microseconds
   ends
   LPDIEFFECT	       EQU  DWORD

 ; ------------------------------------------------
 ; Structure: DIFILEEFFECT
 ; ------------------------------------------------
   struct DIFILEEFFECT
       .dwSize		    dd	?
       .GuidEffect	    GUID
       .lpDiEffect	    dd	?		; LPCDIEFFECT
       .szFriendlyName	    rb	 MAX_PATH	; CHAR
   ends
   LPDIFILEEFFECT      EQU  DWORD

   DIEFF_OBJECTIDS		      EQU   000000001h
   DIEFF_OBJECTOFFSETS		      EQU   000000002h
   DIEFF_CARTESIAN		      EQU   000000010h
   DIEFF_POLAR			      EQU   000000020h
   DIEFF_SPHERICAL		      EQU   000000040h

   DIEP_DURATION		      EQU   000000001h
   DIEP_SAMPLEPERIOD		      EQU   000000002h
   DIEP_GAIN			      EQU   000000004h
   DIEP_TRIGGERBUTTON		      EQU   000000008h
   DIEP_TRIGGERREPEATINTERVAL	      EQU   000000010h
   DIEP_AXES			      EQU   000000020h
   DIEP_DIRECTION		      EQU   000000040h
   DIEP_ENVELOPE		      EQU   000000080h
   DIEP_TYPESPECIFICPARAMS	      EQU   000000100h
   DIEP_STARTDELAY		      EQU   000000200h
   DIEP_ALLPARAMS_DX5		      EQU   0000001FFh
   DIEP_ALLPARAMS		      EQU   0000003FFh
   DIEP_START			      EQU   020000000h
   DIEP_NORESTART		      EQU   040000000h
   DIEP_NODOWNLOAD		      EQU   080000000h
   DIEB_NOTRIGGER		      EQU   0FFFFFFFFh

   DIES_SOLO			      EQU   000000001h
   DIES_NODOWNLOAD		      EQU   080000000h

   DIEGES_PLAYING		      EQU   000000001h
   DIEGES_EMULATED		      EQU   000000002h

 ; ------------------------------------------------
 ; Structure: DIEFFESCAPE
 ; ------------------------------------------------
   struct DIEFFESCAPE
       .dwSize		    dd	 ?
       .dwCommand	    dd	 ?
       .lpvInBuffer	    dd	 ?     ; LPVOID
       .cbInBuffer	    dd	 ?
       .lpvOutBuffer	    dd	 ?     ; LPVOID
       .cbOutBuffer	    dd	 ?
   ends
   LPDIEFFESCAPE	EQU  DWORD

 ;==============================================================================
 ;  DirectInputEffect  Виртуальная таблица методов
 ;==============================================================================
  struct DirectInputEffect

   .handle  dd ?
    virtual at 0

     ;IUnknown methods

     STDMETHOD QueryInterface,	   3
     STDMETHOD AddRef,		   1
     STDMETHOD Release, 	   1

     ;IDirectInputEffect methods

     STDMETHOD Initialize,	   4
     STDMETHOD GetEffectGuid,	   2
     STDMETHOD GetParameters,	   3
     STDMETHOD SetParameters,	   3
     STDMETHOD Start,		   3
     STDMETHOD Stop,		   1
     STDMETHOD GetEffectStatus,    2
     STDMETHOD Download,	   1
     STDMETHOD Unload,		   1
     STDMETHOD Escape,		   2

     end virtual

  ends

 ; ***************************************************************************
 ; *      IDirectInputDevice
 ; ***************************************************************************

   DI8DEVCLASS_ALL		      EQU   0
   DI8DEVCLASS_DEVICE		      EQU   1
   DI8DEVCLASS_POINTER		      EQU   2
   DI8DEVCLASS_KEYBOARD 	      EQU   3
   DI8DEVCLASS_GAMECTRL 	      EQU   4

   DI8DEVTYPE_DEVICE		      EQU   011h
   DI8DEVTYPE_MOUSE		      EQU   012h
   DI8DEVTYPE_KEYBOARD		      EQU   013h
   DI8DEVTYPE_JOYSTICK		      EQU   014h
   DI8DEVTYPE_GAMEPAD		      EQU   015h
   DI8DEVTYPE_DRIVING		      EQU   016h
   DI8DEVTYPE_FLIGHT		      EQU   017h
   DI8DEVTYPE_1STPERSON 	      EQU   018h
   DI8DEVTYPE_DEVICECTRL	      EQU   019h
   DI8DEVTYPE_SCREENPOINTER	      EQU   01Ah
   DI8DEVTYPE_REMOTE		      EQU   01Bh
   DI8DEVTYPE_SUPPLEMENTAL	      EQU   01Ch

   DIDEVTYPE_HID		      EQU   000010000h

   DI8DEVTYPEMOUSE_UNKNOWN	      EQU   1
   DI8DEVTYPEMOUSE_TRADITIONAL	      EQU   2
   DI8DEVTYPEMOUSE_FINGERSTICK	      EQU   3
   DI8DEVTYPEMOUSE_TOUCHPAD	      EQU   4
   DI8DEVTYPEMOUSE_TRACKBALL	      EQU   5
   DI8DEVTYPEMOUSE_ABSOLUTE	      EQU   6

   DI8DEVTYPEKEYBOARD_UNKNOWN	      EQU   0
   DI8DEVTYPEKEYBOARD_PCXT	      EQU   1
   DI8DEVTYPEKEYBOARD_OLIVETTI	      EQU   2
   DI8DEVTYPEKEYBOARD_PCAT	      EQU   3
   DI8DEVTYPEKEYBOARD_PCENH	      EQU   4
   DI8DEVTYPEKEYBOARD_NOKIA1050       EQU   5
   DI8DEVTYPEKEYBOARD_NOKIA9140       EQU   6
   DI8DEVTYPEKEYBOARD_NEC98	      EQU   7
   DI8DEVTYPEKEYBOARD_NEC98LAPTOP     EQU   8
   DI8DEVTYPEKEYBOARD_NEC98106	      EQU   9
   DI8DEVTYPEKEYBOARD_JAPAN106	      EQU   10
   DI8DEVTYPEKEYBOARD_JAPANAX	      EQU   11
   DI8DEVTYPEKEYBOARD_J3100	      EQU   12

   DI8DEVTYPE_LIMITEDGAMESUBTYPE      EQU   1

   DI8DEVTYPEJOYSTICK_LIMITED	      EQU   DI8DEVTYPE_LIMITEDGAMESUBTYPE
   DI8DEVTYPEJOYSTICK_STANDARD	      EQU   2

   DI8DEVTYPEGAMEPAD_LIMITED	      EQU   DI8DEVTYPE_LIMITEDGAMESUBTYPE
   DI8DEVTYPEGAMEPAD_STANDARD	      EQU   2
   DI8DEVTYPEGAMEPAD_TILT	      EQU   3

   DI8DEVTYPEDRIVING_LIMITED	      EQU   DI8DEVTYPE_LIMITEDGAMESUBTYPE
   DI8DEVTYPEDRIVING_COMBINEDPEDALS   EQU   2
   DI8DEVTYPEDRIVING_DUALPEDALS       EQU   3
   DI8DEVTYPEDRIVING_THREEPEDALS      EQU   4
   DI8DEVTYPEDRIVING_HANDHELD	      EQU   5

   DI8DEVTYPEFLIGHT_LIMITED	      EQU   DI8DEVTYPE_LIMITEDGAMESUBTYPE
   DI8DEVTYPEFLIGHT_STICK	      EQU   2
   DI8DEVTYPEFLIGHT_YOKE	      EQU   3
   DI8DEVTYPEFLIGHT_RC		      EQU   4

   DI8DEVTYPE1STPERSON_LIMITED	      EQU   DI8DEVTYPE_LIMITEDGAMESUBTYPE
   DI8DEVTYPE1STPERSON_UNKNOWN	      EQU   2
   DI8DEVTYPE1STPERSON_SIXDOF	      EQU   3
   DI8DEVTYPE1STPERSON_SHOOTER	      EQU   4

   DI8DEVTYPESCREENPTR_UNKNOWN	      EQU   2
   DI8DEVTYPESCREENPTR_LIGHTGUN       EQU   3
   DI8DEVTYPESCREENPTR_LIGHTPEN       EQU   4
   DI8DEVTYPESCREENPTR_TOUCH	      EQU   5

   DI8DEVTYPEREMOTE_UNKNOWN	      EQU	   2

   DI8DEVTYPEDEVICECTRL_UNKNOWN 		     EQU   2
   DI8DEVTYPEDEVICECTRL_COMMSSELECTION		     EQU   3
   DI8DEVTYPEDEVICECTRL_COMMSSELECTION_HARDWIRED     EQU   4

   DI8DEVTYPESUPPLEMENTAL_UNKNOWN		     EQU   2
   DI8DEVTYPESUPPLEMENTAL_2NDHANDCONTROLLER	     EQU   3
   DI8DEVTYPESUPPLEMENTAL_HEADTRACKER		     EQU   4
   DI8DEVTYPESUPPLEMENTAL_HANDTRACKER		     EQU   5
   DI8DEVTYPESUPPLEMENTAL_SHIFTSTICKGATE	     EQU   6
   DI8DEVTYPESUPPLEMENTAL_SHIFTER		     EQU   7
   DI8DEVTYPESUPPLEMENTAL_THROTTLE		     EQU   8
   DI8DEVTYPESUPPLEMENTAL_SPLITTHROTTLE 	     EQU   9
   DI8DEVTYPESUPPLEMENTAL_COMBINEDPEDALS	     EQU   10
   DI8DEVTYPESUPPLEMENTAL_DUALPEDALS		     EQU   11
   DI8DEVTYPESUPPLEMENTAL_THREEPEDALS		     EQU   12
   DI8DEVTYPESUPPLEMENTAL_RUDDERPEDALS		     EQU   13

   macro GET_DIDEVICE_TYPE  type, dwDevType
   {
      type = (dwDevType and 000ffh)
   }

   macro GET_DIDEVICE_SUBTYPE type, dwDevType
   {
      type = ((dwDevType and 0ff00h) shr 8))
   }

 ; ------------------------------------------------
 ; Structure: DIDEVCAPS
 ; ------------------------------------------------
   struct DIDEVCAPS
       .dwSize			 dd   ?
       .dwFlags 		 dd   ?
       .dwDevType		 dd   ?
       .dwAxes			 dd   ?
       .dwButtons		 dd   ?
       .dwPOVs			 dd   ?
       .dwFFSamplePeriod	 dd   ?
       .dwFFMinTimeResolution	 dd   ?
       .dwFirmwareRevision	 dd   ?
       .dwHardwareRevision	 dd   ?
       .dwFFDriverVersion	 dd   ?
   ends
   LPDIDEVCAPS		   EQU	DWORD

   DIDC_ATTACHED		EQU	000000001h
   DIDC_POLLEDDEVICE		EQU	000000002h
   DIDC_EMULATED		EQU	000000004h
   DIDC_POLLEDDATAFORMAT	EQU	000000008h
   DIDC_FORCEFEEDBACK		EQU	000000100h
   DIDC_FFATTACK		EQU	000000200h
   DIDC_FFFADE			EQU	000000400h
   DIDC_SATURATION		EQU	000000800h
   DIDC_POSNEGCOEFFICIENTS	EQU	000001000h
   DIDC_POSNEGSATURATION	EQU	000002000h
   DIDC_DEADBAND		EQU	000004000h
   DIDC_STARTDELAY		EQU	000008000h
   DIDC_ALIAS			EQU	000010000h
   DIDC_PHANTOM 		EQU	000020000h
   DIDC_HIDDEN			EQU	000040000h

   DIDFT_ALL			EQU	000000000h

   DIDFT_RELAXIS		EQU	000000001h
   DIDFT_ABSAXIS		EQU	000000002h
   DIDFT_AXIS			EQU	000000003h

   DIDFT_PSHBUTTON		EQU	000000004h
   DIDFT_TGLBUTTON		EQU	000000008h
   DIDFT_BUTTON 		EQU	00000000Ch

   DIDFT_POV			EQU	000000010h
   DIDFT_COLLECTION		EQU	000000040h
   DIDFT_NODATA 		EQU	000000080h

   DIDFT_ANYINSTANCE		EQU	000FFFF00h
   DIDFT_INSTANCEMASK		EQU	DIDFT_ANYINSTANCE
   DIDFT_FFACTUATOR		EQU	001000000h
   DIDFT_FFEFFECTTRIGGER	EQU	002000000h
   DIDFT_OUTPUT 		EQU	010000000h
   DIDFT_VENDORDEFINED		EQU	004000000h
   DIDFT_ALIAS			EQU	008000000h
   DIDFT_NOCOLLECTION		EQU	000FFFF00h

   macro DIDFT_MAKEINSTANCE  num, n
   {
     num = (n shl 8)
   }

   macro DIDFT_GETTYPE  num, n
   {
     num = (n and 000ffh)
   }

   macro DIDFT_GETINSTANCE  num, n
   {
     num = ((n and 0ffffh) shr 8)
   }

   macro DIDFT_ENUMCOLLECTION num, n
   {
     num = (n shl 8)
   }

 ;------------------------------------------------
 ;Structure: DIOBJECTDATAFORMAT
 ;------------------------------------------------
   struct DIOBJECTDATAFORMAT
     .pguid		       dd     ?      ;GUID*  ; Внимательней
     .dwOfs		       dd     ?
     .dwType		       dd     ?
     .dwFlags		       dd     ?
   ends
   LPDIOBJECTDATAFORMAT    EQU	DWORD

 ;------------------------------------------------
 ;Structure: DIDATAFORMAT
 ;------------------------------------------------
   struct DIDATAFORMAT
     .dwSize		       dd      ?
     .dwObjSize 	       dd      ?
     .dwFlags		       dd      ?
     .dwDataSize	       dd      ?
     .dwNumObjs 	       dd      ?
     .rgodf		       dd      ?      ;LPDIOBJECTDATAFORMAT
   ends
   LPDIDATAFORMAT	  EQU  DWORD

   DIDF_ABSAXIS 	      EQU     000000001h
   DIDF_RELAXIS 	      EQU     000000002h

   ;externdef C c_dfDIMouse:DIDATAFORMAT
   ;externdef C c_dfDIMouse2:DIDATAFORMAT
   ;externdef C c_dfDIKeyboard:DIDATAFORMAT
   ;externdef C c_dfDIJoystick:DIDATAFORMAT
   ;externdef C c_dfDIJoystick2:DIDATAFORMAT

 ;------------------------------------------------
 ;Structure: DIACTION
 ;------------------------------------------------
   struct DIACTION
     .uAppData		       dd    ?	    ;UINT_PTR
     .dwSemantic	       dd    ?
     .dwFlags		       dd    ?	    ;OPTIONAL (???)
     ;UNION                                 ;OPTIONAL (???)
	  .lptszActionName     dd    ?	    ;LPCSTR
	  .uResIdString        dd    ?	    ;UINT
     ;ENDS
     .guidInstance	       GUID	    ;OPTIONAL (???)
     .dwObjID		       dd    ?	    ;OPTIONAL (???)
     .dwHow		       dd    ?	    ;OPTIONAL (???)
   ends
   LPDIACTION	       EQU  DWORD
   DIACTIONA	       EQU   DIACTION
   DIACTIONW	       EQU   DIACTION

   DIA_FORCEFEEDBACK	      EQU     000000001h
   DIA_APPMAPPED	      EQU     000000002h
   DIA_APPNOMAP 	      EQU     000000004h
   DIA_NORANGE		      EQU     000000008h
   DIA_APPFIXED 	      EQU     000000010h

   DIAH_UNMAPPED	      EQU     000000000h
   DIAH_USERCONFIG	      EQU     000000001h
   DIAH_APPREQUESTED	      EQU     000000002h
   DIAH_HWAPP		      EQU     000000004h
   DIAH_HWDEFAULT	      EQU     000000008h
   DIAH_DEFAULT 	      EQU     000000020h
   DIAH_ERROR		      EQU     080000000h

 ;------------------------------------------------
 ;Structure: DIACTIONFORMAT
 ;------------------------------------------------
   struct DIACTIONFORMAT
     .dwSize		       dd	?
     .dwActionSize	       dd	?
     .dwDataSize	       dd	?
     .dwNumActions	       dd	?
     .rgoAction 	       dd	?      ;LPDIACTIONA
     .guidActionMap	       GUID
     .dwGenre		       dd	?
     .dwBufferSize	       dd	?
     .lAxisMin		       dd	?      ;LONG          OPTIONAL
     .lAxisMax		       dd	?      ;LONG          OPTIONAL
     .hInstString	       dd	?      ;HINSTANCE     OPTIONAL
     .ftTimeStamp	       FILETIME
     .dwCRC		       dd	?
     .tszActionMap	       rb  MAX_PATH    ;CHAR
   ends
   LPDIACTIONFORMAT	EQU  DWORD

   DIAFTS_NEWDEVICELOW	      EQU     0FFFFFFFFh
   DIAFTS_NEWDEVICEHIGH       EQU     0FFFFFFFFh
   DIAFTS_UNUSEDDEVICELOW     EQU     000000000h
   DIAFTS_UNUSEDDEVICEHIGH    EQU     000000000h

   DIDBAM_DEFAULT	      EQU     000000000h
   DIDBAM_PRESERVE	      EQU     000000001h
   DIDBAM_INITIALIZE	      EQU     000000002h
   DIDBAM_HWDEFAULTS	      EQU     000000004h

   DIDSAM_DEFAULT	      EQU     000000000h
   DIDSAM_NOUSER	      EQU     000000001h
   DIDSAM_FORCESAVE	      EQU     000000002h

   DICD_DEFAULT 	      EQU     000000000h
   DICD_EDIT		      EQU     000000001h

 ;------------------------------------------------
 ;Structure: DICOLORSET
 ;------------------------------------------------
   struct DICOLORSET
     .dwSize		       dd   ?
     .cTextFore 	       dd   ?	   ;D3DCOLOR
     .cTextHighlight	       dd   ?	   ;D3DCOLOR
     .cCalloutLine	       dd   ?	   ;D3DCOLOR
     .cCalloutHighlight        dd   ?	   ;D3DCOLOR
     .cBorder		       dd   ?	   ;D3DCOLOR
     .cControlFill	       dd   ?	   ;D3DCOLOR
     .cHighlightFill	       dd   ?	   ;D3DCOLOR
     .cAreaFill 	       dd   ?	   ;D3DCOLOR
   ends
   LPDICOLORSET 	EQU  DWORD

 ;------------------------------------------------
 ;Structure: DICONFIGUREDEVICESPARAMS
 ;------------------------------------------------
   struct DICONFIGUREDEVICESPARAMS
     .dwSize		       dd   ?
     .dwcUsers		       dd   ?
     .lptszUserNames	       dd   ?	   ;LPSTR
     .dwcFormats	       dd   ?
     .lprgFormats	       dd   ?	   ;LPDIACTIONFORMATA
     .hwnd		       dd   ?	   ;HWND
     .dics		       dd   ?	   ;DICOLORSET
     .lpUnkDDSTarget	       dd   ?	   ;IUnknown*
   ends
   LPDICONFIGUREDEVICESPARAMS	 EQU  DWORD

   DIDIFT_CONFIGURATION       EQU     000000001h
   DIDIFT_OVERLAY	      EQU     000000002h

   DIDAL_CENTERED	      EQU     000000000h
   DIDAL_LEFTALIGNED	      EQU     000000001h
   DIDAL_RIGHTALIGNED	      EQU     000000002h
   DIDAL_MIDDLE 	      EQU     000000000h
   DIDAL_TOPALIGNED	      EQU     000000004h
   DIDAL_BOTTOMALIGNED	      EQU     000000008h

 ;------------------------------------------------
 ;Structure: DIDEVICEIMAGEINFO
 ;------------------------------------------------
   struct DIDEVICEIMAGEINFO
     .tszImagePath	       rb    MAX_PATH	   ;CHAR
     .dwFlags		       dd      ?

   ; These are valid if DIDIFT_OVERLAY is present in dwFlags.
     .dwViewID		       dd      ?
     .rcOverlay 	       RECT
     .dwObjID		       dd      ?
     .dwcValidPts	       dd      ?
     .rgptCalloutLine	       POINT
     .rgptCalloutLine1	       POINT
     .rgptCalloutLine2	       POINT
     .rgptCalloutLine3	       POINT
     .rgptCalloutLine4	       POINT
     .rcCalloutRect	       RECT
     .dwTextAlign	       dd      ?
   ends
   LPDIDEVICEIMAGEINFO	  EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIDEVICEIMAGEINFOHEADER
 ;------------------------------------------------
   struct DIDEVICEIMAGEINFOHEADER
     .dwSize			    dd	 ?
     .dwSizeImageInfo		    dd	 ?
     .dwcViews			    dd	 ?
     .dwcButtons		    dd	 ?
     .dwcAxes			    dd	 ?
     .dwcPOVs			    dd	 ?
     .dwBufferSize		    dd	 ?
     .dwBufferUsed		    dd	 ?
     .lprgImageInfoArray	    dd	 ?	;LPDIDEVICEIMAGEINFOA
   ends
   LPDIDEVICEIMAGEINFOHEADER	   EQU	DWORD

 ;------------------------------------------------
 ;Structure: DIDEVICEOBJECTINSTANCE
 ;------------------------------------------------
   struct DIDEVICEOBJECTINSTANCE
     .dwSize		       dd   ?
     .guidType		       GUID
     .dwOfs		       dd   ?
     .dwType		       dd   ?
     .dwFlags		       dd   ?
     .tszName		       rb   MAX_PATH	  ;CHAR
     .dwFFMaxForce	       dd   ?
     .dwFFForceResolution      dd   ?
     .wCollectionNumber        dw    ?
     .wDesignatorIndex	       dw    ?
     .wUsagePage	       dw    ?
     .wUsage		       dw    ?
     .dwDimension	       dd   ?
     .wExponent 	       dw    ?
     .wReportId 	       dw    ?
   ends
   LPDIDEVICEOBJECTINSTANCE		  EQU  DWORD

   DIDOI_FFACTUATOR		   EQU	   000000001h
   DIDOI_FFEFFECTTRIGGER	   EQU	   000000002h
   DIDOI_POLLED 		   EQU	   000008000h
   DIDOI_ASPECTPOSITION 	   EQU	   000000100h
   DIDOI_ASPECTVELOCITY 	   EQU	   000000200h
   DIDOI_ASPECTACCEL		   EQU	   000000300h
   DIDOI_ASPECTFORCE		   EQU	   000000400h
   DIDOI_ASPECTMASK		   EQU	   000000F00h
   DIDOI_GUIDISUSAGE		   EQU	   000010000h

 ;------------------------------------------------
 ;Structure: DIPROPHEADER
 ;------------------------------------------------
   struct DIPROPHEADER
     .dwSize			    dd	 ?
     .dwHeaderSize		    dd	 ?
     .dwObj			    dd	 ?
     .dwHow			    dd	 ?
   ends
   LPDIPROPHEADER	  EQU  DWORD

   DIPH_DEVICE			   EQU	   0
   DIPH_BYOFFSET		   EQU	   1
   DIPH_BYID			   EQU	   2
   DIPH_BYUSAGE 		   EQU	   3


   ;DIMAKEUSAGEDWORD                MACRO   UsagePage, Usage
   ;                                ENDM    Usage OR (Usage SHL 16)

 ;------------------------------------------------
 ;Structure: DIPROPDWORD
 ;------------------------------------------------
   struct DIPROPDWORD
     .diph		       DIPROPHEADER
     .dwData		       dd	     ?
   ends
   LPDIPROPDWORD	 EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIPROPPOINTER
 ;------------------------------------------------
   struct DIPROPPOINTER
     .diph			   DIPROPHEADER
     .uData			   dd		 ?	;UINT_PTR
   ends
   LPDIPROPPOINTER	   EQU	DWORD

 ;------------------------------------------------
 ;Structure: DIPROPRANGE
 ;------------------------------------------------
   struct DIPROPRANGE
     .diph			   DIPROPHEADER
     .lMin			   dd	?
     .lMax			   dd	?
   ends
   LPDIPROPRANGE	 EQU  DWORD

   DIPROPRANGE_NOMIN		  EQU	  080000000h
   DIPROPRANGE_NOMAX		  EQU	  07FFFFFFFh

 ;------------------------------------------------
 ;Structure: DIPROPCAL
 ;------------------------------------------------
   struct DIPROPCAL
     .diph			   DIPROPHEADER
     .lMin			   dd		  ?
     .lCenter			   dd		  ?
     .lMax			   dd		  ?
   ends
   LPDIPROPCAL	       EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIPROPCALPOV
 ;------------------------------------------------
   struct DIPROPCALPOV
     .diph			   DIPROPHEADER
     .lMin			   rd	5      ;LONG
     .lMax			   rd	5      ;LONG
   ends
   LPDIPROPCALPOV	  EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIPROPGUIDANDPATH
 ;------------------------------------------------
   struct DIPROPGUIDANDPATH
     diph			  DIPROPHEADER
     guidClass			  GUID
     wszPath			  rw   MAX_PATH      ;WCHAR
   ends
   LPDIPROPGUIDANDPATH	  EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIPROPSTRING
 ;------------------------------------------------
   struct DIPROPSTRING
     .diph			  DIPROPHEADER
     .wsz			  rw   MAX_PATH      ;WCHAR
   ends
   LPDIPROPSTRING	  EQU  DWORD

   MAXCPOINTSNUM	  EQU	  8

 ;------------------------------------------------
 ;Structure: CPOINT
 ;------------------------------------------------
   struct CPOINT
     .lP		   dd	?      ;LONG     // raw value
     .dwLog		   dd	?      ; logical_value / max_logical_value * 10000
   ends
   LPCPOINT	    EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIPROPCPOINTS
 ;------------------------------------------------
   ;struct DIPROPCPOINTS
   ;  .diph                  DIPROPHEADER
   ;  .dwCPointsNum          dd            ?
   ;  .cp                    CPOINT   MAXCPOINTSNUM   DUP   (<>)
   ;ends
   ;LPDIPROPCPOINTS         EQU  DWORD

   DIPROP_BUFFERSIZE			   EQU	   1	  ;MAKEDIPROP(1)
   DIPROP_AXISMODE			   EQU	   2	  ;MAKEDIPROP(2)
   DIPROPAXISMODE_ABS			   EQU	   0
   DIPROPAXISMODE_REL			   EQU	   1
   DIPROP_GRANULARITY			   EQU	   3	  ;MAKEDIPROP(3)
   DIPROP_RANGE 			   EQU	   4	  ;MAKEDIPROP(4)
   DIPROP_DEADZONE			   EQU	   5	  ;MAKEDIPROP(5)
   DIPROP_SATURATION			   EQU	   6	  ;MAKEDIPROP(6)
   DIPROP_FFGAIN			   EQU	   7	  ;MAKEDIPROP(7)
   DIPROP_FFLOAD			   EQU	   8	  ;MAKEDIPROP(8)
   DIPROP_AUTOCENTER			   EQU	   9	  ;MAKEDIPROP(9)
   DIPROPAUTOCENTER_OFF 		   EQU	   0
   DIPROPAUTOCENTER_ON			   EQU	   1
   DIPROP_CALIBRATIONMODE		   EQU	   10	   ;MAKEDIPROP(10)
   DIPROPCALIBRATIONMODE_COOKED 	   EQU	   0
   DIPROPCALIBRATIONMODE_RAW		   EQU	   1
   DIPROP_CALIBRATION			   EQU	   11	   ;MAKEDIPROP(11)
   DIPROP_GUIDANDPATH			   EQU	   12	   ;MAKEDIPROP(12)
   DIPROP_INSTANCENAME			   EQU	   13	   ;MAKEDIPROP(13)
   DIPROP_PRODUCTNAME			   EQU	   14	   ;MAKEDIPROP(14)
   DIPROP_JOYSTICKID			   EQU	   15	   ;MAKEDIPROP(15)
   DIPROP_GETPORTDISPLAYNAME		   EQU	   16	   ;MAKEDIPROP(16)
   DIPROP_PHYSICALRANGE 		   EQU	   18	   ;MAKEDIPROP(18)
   DIPROP_LOGICALRANGE			   EQU	   19	   ;MAKEDIPROP(19)
   DIPROP_KEYNAME			   EQU	   20	   ;MAKEDIPROP(20)
   DIPROP_CPOINTS			   EQU	   21	   ;MAKEDIPROP(21)
   DIPROP_APPDATA			   EQU	   22	   ;MAKEDIPROP(22)
   DIPROP_SCANCODE			   EQU	   23	   ;MAKEDIPROP(23)
   DIPROP_VIDPID			   EQU	   24	   ;MAKEDIPROP(24)
   DIPROP_USERNAME			   EQU	   25	   ;MAKEDIPROP(25)
   DIPROP_TYPENAME			   EQU	   26	   ;MAKEDIPROP(26)

 ;------------------------------------------------
 ;Structure: DIDEVICEOBJECTDATA
 ;------------------------------------------------
   struct DIDEVICEOBJECTDATA
     .dwOfs		    dd	 ?
     .dwData		    dd	 ?
     .dwTimeStamp	    dd	 ?
     .dwSequence	    dd	 ?
     .uAppData		    dd	 ?	;UINT_PTR
   ends
   LPDIDEVICEOBJECTDATA    EQU	DWORD

   DIGDD_PEEK		   EQU	   000000001h

   DISCL_EXCLUSIVE	   EQU	   000000001h
   DISCL_NONEXCLUSIVE	   EQU	   000000002h
   DISCL_FOREGROUND	   EQU	   000000004h
   DISCL_BACKGROUND	   EQU	   000000008h
   DISCL_NOWINKEY	   EQU	   000000010h

 ;------------------------------------------------
 ;Structure: DIDEVICEINSTANCE
 ;------------------------------------------------
   struct DIDEVICEINSTANCE
     .dwSize		    dd	 ?
     .guidInstance	    GUID
     .guidProduct	    GUID
     .dwDevType 	    dd	 ?
     .tszInstanceName	    rb	 MAX_PATH	;CHAR
     .tszProductName	    rb	 MAX_PATH	;CHAR
     .guidFFDriver	    GUID
     .wUsagePage	    dw	 ?
     .wUsage		    dw	 ?
   ends
   LPDIDEVICEINSTANCE	 EQU  DWORD

   DISFFC_RESET 			   EQU	   000000001h
   DISFFC_STOPALL			   EQU	   000000002h
   DISFFC_PAUSE 			   EQU	   000000004h
   DISFFC_CONTINUE			   EQU	   000000008h
   DISFFC_SETACTUATORSON		   EQU	   000000010h
   DISFFC_SETACTUATORSOFF		   EQU	   000000020h

   DIGFFS_EMPTY 			   EQU	   000000001h
   DIGFFS_STOPPED			   EQU	   000000002h
   DIGFFS_PAUSED			   EQU	   000000004h
   DIGFFS_ACTUATORSON			   EQU	   000000010h
   DIGFFS_ACTUATORSOFF			   EQU	   000000020h
   DIGFFS_POWERON			   EQU	   000000040h
   DIGFFS_POWEROFF			   EQU	   000000080h
   DIGFFS_SAFETYSWITCHON		   EQU	   000000100h
   DIGFFS_SAFETYSWITCHOFF		   EQU	   000000200h
   DIGFFS_USERFFSWITCHON		   EQU	   000000400h
   DIGFFS_USERFFSWITCHOFF		   EQU	   000000800h
   DIGFFS_DEVICELOST			   EQU	   080000000h

 ;------------------------------------------------
 ;Structure: DIEFFECTINFOA
 ;------------------------------------------------
   struct DIEFFECTINFO
     .dwSize		   dd	?
     .guid		   GUID
     .dwEffType 	   dd	?
     .dwStaticParams	   dd	?
     .dwDynamicParams	   dd	?
     .tszName		   rb	 MAX_PATH     ;CHAR
   ends
   LPDIEFFECTINFO	  EQU  DWORD

   DISDD_CONTINUE	  EQU	  000000001h

 ;==============================================================================
 ; DirectInputDevice8  Виртуальная таблица методов
 ;==============================================================================
  struct DirectInputDevice8

   .handle  dd ?
    virtual at 0

     ;IUnknown methods

     STDMETHOD	QueryInterface, 	      3
     STDMETHOD	AddRef, 		      1
     STDMETHOD	Release,		      1

     ;IDirectInputDevice8 methods

     STDMETHOD	GetCapabilities,	      2
     STDMETHOD	EnumObjects,		      4
     STDMETHOD	GetProperty,		      3
     STDMETHOD	SetProperty,		      3
     STDMETHOD	Acquire,		      1
     STDMETHOD	Unacquire,		      1
     STDMETHOD	GetDeviceState, 	      3
     STDMETHOD	GetDeviceData,		      5
     STDMETHOD	SetDataFormat,		      2
     STDMETHOD	SetEventNotification,	      2
     STDMETHOD	SetCooperativeLevel,	      3
     STDMETHOD	GetObjectInfo,		      4
     STDMETHOD	GetDeviceInfo,		      2
     STDMETHOD	RunControlPanel,	      3
     STDMETHOD	Initialize,		      4
     STDMETHOD	CreateEffect,		      5
     STDMETHOD	EnumEffects,		      4
     STDMETHOD	GetEffectInfo,		      3
     STDMETHOD	GetForceFeedbackState,	      2
     STDMETHOD	SendForceFeedbackCommand,     2
     STDMETHOD	EnumCreatedEffectObjects,     4
     STDMETHOD	Escape, 		      2
     STDMETHOD	Poll,			      1
     STDMETHOD	SendDeviceData, 	      5
     STDMETHOD	EnumEffectsInFile,	      5
     STDMETHOD	WriteEffectToFile,	      5
     STDMETHOD	BuildActionMap, 	      4
     STDMETHOD	SetActionMap,		      4
     STDMETHOD	GetImageInfo,		      2

    end virtual

  ends

 ;***************************************************************************
 ;*      Mouse
 ;***************************************************************************

 ;------------------------------------------------
 ;Structure: DIMOUSESTATE
 ;------------------------------------------------
   struct DIMOUSESTATE
     .lX		   dd	?      ;LONG
     .lY		   dd	?      ;LONG
     .lZ		   dd	?      ;LONG
     .rgbButtons	   rb	4
   ends
   LPDIMOUSESTATE	  EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIMOUSESTATE2
 ;------------------------------------------------
   struct DIMOUSESTATE2
     .lX		   dd	 ?	;LONG
     .lY		   dd	 ?	;LONG
     .lZ		   dd	 ?	;LONG
     .rgbButtons	   rb	 8
   ends
   LPDIMOUSESTATE2	  EQU  DWORD

   DIMOFS_X		  EQU	  0	 ;FIELD_OFFSET(DIMOUSESTATE, lX)
   DIMOFS_Y		  EQU	  4	 ;FIELD_OFFSET(DIMOUSESTATE, lY)
   DIMOFS_Z		  EQU	  8	 ;FIELD_OFFSET(DIMOUSESTATE, lZ)
   DIMOFS_BUTTON0	  EQU	  12	 ;(FIELD_OFFSET(DIMOUSESTATE, rgbButtons) + 0)
   DIMOFS_BUTTON1	  EQU	  13	 ;(FIELD_OFFSET(DIMOUSESTATE, rgbButtons) + 1)
   DIMOFS_BUTTON2	  EQU	  14	 ;(FIELD_OFFSET(DIMOUSESTATE, rgbButtons) + 2)
   DIMOFS_BUTTON3	  EQU	  15	 ;(FIELD_OFFSET(DIMOUSESTATE, rgbButtons) + 3)
   DIMOFS_BUTTON4	  EQU	  16	 ;(FIELD_OFFSET(DIMOUSESTATE2, rgbButtons) + 4)
   DIMOFS_BUTTON5	  EQU	  17	 ;(FIELD_OFFSET(DIMOUSESTATE2, rgbButtons) + 5)
   DIMOFS_BUTTON6	  EQU	  18	 ;(FIELD_OFFSET(DIMOUSESTATE2, rgbButtons) + 6)
   DIMOFS_BUTTON7	  EQU	  19	 ;(FIELD_OFFSET(DIMOUSESTATE2, rgbButtons) + 7)

 ;***************************************************************************
 ;*      Keyboard
 ;***************************************************************************

 ;***************************************************************************
 ;*
 ;*         DIrectInput keyboard scan codes
 ;*
 ;***************************************************************************
   DIK_ESCAPE			      EQU     001h
   DIK_1			      EQU     002h
   DIK_2			      EQU     003h
   DIK_3			      EQU     004h
   DIK_4			      EQU     005h
   DIK_5			      EQU     006h
   DIK_6			      EQU     007h
   DIK_7			      EQU     008h
   DIK_8			      EQU     009h
   DIK_9			      EQU     00Ah
   DIK_0			      EQU     00Bh
   DIK_MINUS			      EQU     00Ch	    ; - on main keyboard
   DIK_EQUALS			      EQU     00Dh
   DIK_BACK			      EQU     00Eh	    ; backspace
   DIK_TAB			      EQU     00Fh
   DIK_Q			      EQU     010h
   DIK_W			      EQU     011h
   DIK_E			      EQU     012h
   DIK_R			      EQU     013h
   DIK_T			      EQU     014h
   DIK_Y			      EQU     015h
   DIK_U			      EQU     016h
   DIK_I			      EQU     017h
   DIK_O			      EQU     018h
   DIK_P			      EQU     019h
   DIK_LBRACKET 		      EQU     01Ah
   DIK_RBRACKET 		      EQU     01Bh
   DIK_RETURN			      EQU     01Ch	    ; Enter on main keyboard
   DIK_LCONTROL 		      EQU     01Dh
   DIK_A			      EQU     01Eh
   DIK_S			      EQU     01Fh
   DIK_D			      EQU     020h
   DIK_F			      EQU     021h
   DIK_G			      EQU     022h
   DIK_H			      EQU     023h
   DIK_J			      EQU     024h
   DIK_K			      EQU     025h
   DIK_L			      EQU     026h
   DIK_SEMICOLON		      EQU     027h
   DIK_APOSTROPHE		      EQU     028h
   DIK_GRAVE			      EQU     029h	    ; accent grave
   DIK_LSHIFT			      EQU     02Ah
   DIK_BACKSLASH		      EQU     02Bh
   DIK_Z			      EQU     02Ch
   DIK_X			      EQU     02Dh
   DIK_C			      EQU     02Eh
   DIK_V			      EQU     02Fh
   DIK_B			      EQU     030h
   DIK_N			      EQU     031h
   DIK_M			      EQU     032h
   DIK_COMMA			      EQU     033h
   DIK_PERIOD			      EQU     034h	    ; . on main keyboard
   DIK_SLASH			      EQU     035h	    ; / on main keyboard
   DIK_RSHIFT			      EQU     036h
   DIK_MULTIPLY 		      EQU     037h	    ; * on numeric keypad
   DIK_LMENU			      EQU     038h	    ; left Alt
   DIK_SPACE			      EQU     039h
   DIK_CAPITAL			      EQU     03Ah
   DIK_F1			      EQU     03Bh
   DIK_F2			      EQU     03Ch
   DIK_F3			      EQU     03Dh
   DIK_F4			      EQU     03Eh
   DIK_F5			      EQU     03Fh
   DIK_F6			      EQU     040h
   DIK_F7			      EQU     041h
   DIK_F8			      EQU     042h
   DIK_F9			      EQU     043h
   DIK_F10			      EQU     044h
   DIK_NUMLOCK			      EQU     045h
   DIK_SCROLL			      EQU     046h	    ; Scroll Lock
   DIK_NUMPAD7			      EQU     047h
   DIK_NUMPAD8			      EQU     048h
   DIK_NUMPAD9			      EQU     049h
   DIK_SUBTRACT 		      EQU     04Ah	    ; - on numeric keypad
   DIK_NUMPAD4			      EQU     04Bh
   DIK_NUMPAD5			      EQU     04Ch
   DIK_NUMPAD6			      EQU     04Dh
   DIK_ADD			      EQU     04Eh	    ; + on numeric keypad
   DIK_NUMPAD1			      EQU     04Fh
   DIK_NUMPAD2			      EQU     050h
   DIK_NUMPAD3			      EQU     051h
   DIK_NUMPAD0			      EQU     052h
   DIK_DECIMAL			      EQU     053h	    ; . on numeric keypad
   DIK_OEM_102			      EQU     056h	    ; <> or \| on RT 102-key keyboard (Non-U.S.)
   DIK_F11			      EQU     057h
   DIK_F12			      EQU     058h
   DIK_F13			      EQU     064h	    ;                     (NEC PC98)
   DIK_F14			      EQU     065h	    ;                     (NEC PC98)
   DIK_F15			      EQU     066h	    ;                     (NEC PC98)
   DIK_KANA			      EQU     070h	    ; (Japanese keyboard)
   DIK_ABNT_C1			      EQU     073h	    ; /? on Brazilian keyboard
   DIK_CONVERT			      EQU     079h	    ; (Japanese keyboard)
   DIK_NOCONVERT		      EQU     07Bh	    ; (Japanese keyboard)
   DIK_YEN			      EQU     07Dh	    ; (Japanese keyboard)
   DIK_ABNT_C2			      EQU     07Eh	    ; Numpad . on Brazilian keyboard
   DIK_NUMPADEQUALS		      EQU     08Dh	    ; = on numeric keypad (NEC PC98)
   DIK_PREVTRACK		      EQU     090h	    ; Previous Track (   DIK_CIRCUMFLEX on Japanese keyboard)
   DIK_AT			      EQU     091h	    ;                     (NEC PC98)
   DIK_COLON			      EQU     092h	    ;                     (NEC PC98)
   DIK_UNDERLINE		      EQU     093h	    ;                     (NEC PC98)
   DIK_KANJI			      EQU     094h	    ; (Japanese keyboard)
   DIK_STOP			      EQU     095h	    ;                     (NEC PC98)
   DIK_AX			      EQU     096h	    ;                     (Japan AX
   DIK_UNLABELED		      EQU     097h	    ;                        (J3100)
   DIK_NEXTTRACK		      EQU     099h	    ; Next Track
   DIK_NUMPADENTER		      EQU     09Ch	    ; Enter on numeric keypad
   DIK_RCONTROL 		      EQU     09Dh
   DIK_MUTE			      EQU     0A0h	    ; Mute
   DIK_CALCULATOR		      EQU     0A1h	    ; Calculator
   DIK_PLAYPAUSE		      EQU     0A2h	    ; Play / Pause
   DIK_MEDIASTOP		      EQU     0A4h	    ; Media Stop
   DIK_VOLUMEDOWN		      EQU     0AEh	    ; Volume -
   DIK_VOLUMEUP 		      EQU     0B0h	    ; Volume +
   DIK_WEBHOME			      EQU     0B2h	    ; Web home
   DIK_NUMPADCOMMA		      EQU     0B3h	    ; , on numeric keypad (NEC PC98)
   DIK_DIVIDE			      EQU     0B5h	    ; / on numeric keypad
   DIK_SYSRQ			      EQU     0B7h
   DIK_RMENU			      EQU     0B8h	    ; right Alt
   DIK_PAUSE			      EQU     0C5h	    ; Pause
   DIK_HOME			      EQU     0C7h	    ; Home on arrow keypad
   DIK_UP			      EQU     0C8h	    ; UpArrow on arrow keypad
   DIK_PRIOR			      EQU     0C9h	    ; PgUp on arrow keypad
   DIK_LEFT			      EQU     0CBh	    ; LeftArrow on arrow keypad
   DIK_RIGHT			      EQU     0CDh	    ; RightArrow on arrow keypad
   DIK_END			      EQU     0CFh	    ; End on arrow keypad
   DIK_DOWN			      EQU     0D0h	    ; DownArrow on arrow keypad
   DIK_NEXT			      EQU     0D1h	    ; PgDn on arrow keypad
   DIK_INSERT			      EQU     0D2h	    ; Insert on arrow keypad
   DIK_DELETE			      EQU     0D3h	    ; Delete on arrow keypad
   DIK_LWIN			      EQU     0DBh	    ; Left Windows key
   DIK_RWIN			      EQU     0DCh	    ; Right Windows key
   DIK_APPS			      EQU     0DDh	    ; AppMenu key
   DIK_POWER			      EQU     0DEh	    ; System Power
   DIK_SLEEP			      EQU     0DFh	    ; System Sleep
   DIK_WAKE			      EQU     0E3h	    ; System Wake
   DIK_WEBSEARCH		      EQU     0E5h	    ; Web Search
   DIK_WEBFAVORITES		      EQU     0E6h	    ; Web Favorites
   DIK_WEBREFRESH		      EQU     0E7h	    ; Web Refresh
   DIK_WEBSTOP			      EQU     0E8h	    ; Web Stop
   DIK_WEBFORWARD		      EQU     0E9h	    ; Web Forward
   DIK_WEBBACK			      EQU     0EAh	    ; Web Back
   DIK_MYCOMPUTER		      EQU     0EBh	    ; My Computer
   DIK_MAIL			      EQU     0ECh	    ; Mail
   DIK_MEDIASELECT		      EQU     0EDh	    ; Media Select

 ;
 ;*  Alternate names for keys, to facilitate transition from DOS.
 ;

   DIK_BACKSPACE		      EQU     DIK_BACK		   ; backspace
   DIK_NUMPADSTAR		      EQU     DIK_MULTIPLY	   ; * on numeric keypad
   DIK_LALT			      EQU     DIK_LMENU 	   ; left Alt
   DIK_CAPSLOCK 		      EQU     DIK_CAPITAL	   ; CapsLock
   DIK_NUMPADMINUS		      EQU     DIK_SUBTRACT	   ; - on numeric keypad
   DIK_NUMPADPLUS		      EQU     DIK_ADD		   ; + on numeric keypad
   DIK_NUMPADPERIOD		      EQU     DIK_DECIMAL	   ; . on numeric keypad
   DIK_NUMPADSLASH		      EQU     DIK_DIVIDE	   ; / on numeric keypad
   DIK_RALT			      EQU     DIK_RMENU 	   ; right Alt
   DIK_UPARROW			      EQU     DIK_UP		   ; UpArrow on arrow keypad
   DIK_PGUP			      EQU     DIK_PRIOR 	   ; PgUp on arrow keypad
   DIK_LEFTARROW		      EQU     DIK_LEFT		   ; LeftArrow on arrow keypad
   DIK_RIGHTARROW		      EQU     DIK_RIGHT 	   ; RightArrow on arrow keypad
   DIK_DOWNARROW		      EQU     DIK_DOWN		   ; DownArrow on arrow keypad
   DIK_PGDN			      EQU     DIK_NEXT		   ; PgDn on arrow keypad

 ;
 ;*  Alternate names for keys originally not used on US keyboards.
 ;

   DIK_CIRCUMFLEX			  EQU	  DIK_PREVTRACK        ; Japanese keyboard

 ;***************************************************************************
 ;*      Joystick
 ;***************************************************************************

 ;------------------------------------------------
 ;Structure: DIJOYSTATE
 ;------------------------------------------------
   struct DIJOYSTATE
     .lX		 dd	?		 ;LONG      ; x-axis position
     .lY		 dd	?		 ;LONG      ; y-axis position
     .lZ		 dd	?		 ;LONG      ; z-axis position
     .lRx		 dd	?		 ;LONG      ; x-axis rotation
     .lRy		 dd	?		 ;LONG      ; y-axis rotation
     .lRz		 dd	?		 ;LONG      ; z-axis rotation
     .rglSlider 	 rd	2		 ;LONG      ; extra axes positions
     .rgdwPOV		 rd	4		 ; POV directions
     .rgbButtons	 rb	32		 ; 32 buttons
   ends
   LPDIJOYSTATE 	 EQU  DWORD

 ;------------------------------------------------
 ;Structure: DIJOYSTATE2
 ;------------------------------------------------
   struct DIJOYSTATE2
     .lX		  dd   ?      ;LONG      ; x-axis position
     .lY		  dd   ?      ;LONG      ; y-axis position
     .lZ		  dd   ?      ;LONG      ; z-axis position
     .lRx		  dd   ?      ;LONG      ; x-axis rotation
     .lRy		  dd   ?      ;LONG      ; y-axis rotation
     .lRz		  dd   ?      ;LONG      ; z-axis rotation
     .rglSlider 	  rd   2      ;LONG      ; extra axes positions
     .rgdwPOV		  rd   4		 ; POV directions
     .rgbButtons	  rb   128		 ; 128 buttons
     .lVX		  dd   ?      ;LONG      ; x-axis velocity
     .lVY		  dd   ?      ;LONG      ; y-axis velocity
     .lVZ		  dd   ?      ;LONG      ; z-axis velocity
     .lVRx		  dd   ?      ;LONG      ; x-axis angular velocity
     .lVRy		  dd   ?      ;LONG      ; y-axis angular velocity
     .lVRz		  dd   ?      ;LONG      ; z-axis angular velocity
     .rglVSlider	  rd   2      ;LONG      ; extra axes velocities
     .lAX		  dd   ?      ;LONG      ; x-axis acceleration
     .lAY		  dd   ?      ;LONG      ; y-axis acceleration
     .lAZ		  dd   ?      ;LONG      ; z-axis acceleration
     .lARx		  dd   ?      ;LONG      ; x-axis angular acceleration
     .lARy		  dd   ?      ;LONG      ; y-axis angular acceleration
     .lARz		  dd   ?      ;LONG      ; z-axis angular acceleration
     .rglASlider	  rd   2      ;LONG      ; extra axes accelerations
     .lFX		  dd   ?      ;LONG      ; x-axis force
     .lFY		  dd   ?      ;LONG      ; y-axis force
     .lFZ		  dd   ?      ;LONG      ; z-axis force
     .lFRx		  dd   ?      ;LONG      ; x-axis torque
     .lFRy		  dd   ?      ;LONG      ; y-axis torque
     .lFRz		  dd   ?      ;LONG      ; z-axis torque
     .rglFSlider	  rd   2      ;LONG      ; extra axes forces
   ends
   LPDIJOYSTATE2	  EQU  DWORD

 ;***************************************************************************
 ;*  IDirectInput
 ;***************************************************************************

   DIENUM_STOP				   EQU	   0
   DIENUM_CONTINUE			   EQU	   1

   DIEDFL_ALLDEVICES			   EQU	   000000000h
   DIEDFL_ATTACHEDONLY			   EQU	   000000001h
   DIEDFL_FORCEFEEDBACK 		   EQU	   000000100h
   DIEDFL_INCLUDEALIASES		   EQU	   000010000h
   DIEDFL_INCLUDEPHANTOMS		   EQU	   000020000h
   DIEDFL_INCLUDEHIDDEN 		   EQU	   000040000h

   DIEDBS_MAPPEDPRI1			   EQU	   000000001h
   DIEDBS_MAPPEDPRI2			   EQU	   000000002h
   DIEDBS_RECENTDEVICE			   EQU	   000000010h
   DIEDBS_NEWDEVICE			   EQU	   000000020h

   DIEDBSFL_ATTACHEDONLY		   EQU	   000000000h
   DIEDBSFL_THISUSER			   EQU	   000000010h
   DIEDBSFL_FORCEFEEDBACK		   EQU	   DIEDFL_FORCEFEEDBACK
   DIEDBSFL_AVAILABLEDEVICES		   EQU	   000001000h
   DIEDBSFL_MULTIMICEKEYBOARDS		   EQU	   000002000h
   DIEDBSFL_NONGAMINGDEVICES		   EQU	   000004000h
   DIEDBSFL_VALID			   EQU	   000007110h


   DirectInput8Create%	=  5

 ;==============================================================================
 ; DirectInput8  Виртуальная таблица методов
 ;==============================================================================
  struct DirectInput8

   .handle  dd ?
    virtual at 0

     ;IUnknown methods

     STDMETHOD QueryInterface,		3
     STDMETHOD AddRef,			1
     STDMETHOD Release, 		1

     ;IDirectInput8 methods

     STDMETHOD CreateDevice,		4
     STDMETHOD EnumDevices,		5
     STDMETHOD GetDeviceStatus, 	2
     STDMETHOD RunControlPanel, 	3
     STDMETHOD Initialize,		3
     STDMETHOD FindDevice,		4
     STDMETHOD EnumDevicesBySemantics,	6
     STDMETHOD ConfigureDevices,	5

    end virtual

  ends

 ;-------------------------------------------------------
 ;Macro: MAKE_HRESULT
 ;-------------------------------------------------------

 ;IFNDEF MAKE_HRESULT
 ;MAKE_HRESULT   MACRO  hres_name, severity, facility, code
 ;    hres_name EQU  (severity SHL 31) OR ((facility AND 0FFFh) SHL 16) OR (code AND 0FFFFh)
 ;ENDM
 ;ENDIF

   FACILITY_WINDOWS		EQU	8
   FACILITY_STORAGE		EQU	3
   FACILITY_RPC 		EQU	1
   FACILITY_SSPI		EQU	9
   FACILITY_WIN32		EQU	7
   FACILITY_CONTROL		EQU	10
   FACILITY_NULL		EQU	0
   FACILITY_ITF 		EQU	4
   FACILITY_DISPATCH		EQU	2

 ;***************************************************************************
 ;*
 ;*  Return Codes
 ;*
 ;***************************************************************************

 ; The operation completed successfully.

   DI_OK		       EQU     S_OK

 ; The device exists but is not currently attached.

   DI_NOTATTACHED	       EQU     S_FALSE

 ; The device buffer overflowed.  Some input was lost.

   DI_BUFFEROVERFLOW	       EQU     S_FALSE

 ; The change in device properties had no effect

   DI_PROPNOEFFECT	       EQU     S_FALSE

 ; The operation had no effect.

   DI_NOEFFECT		       EQU     S_FALSE

 ; The device is a polled device.  As a result, device buffering
 ; will not collect any data and event notifications will not be
 ; signalled until GetDeviceState is called.

   DI_POLLEDDEVICE	       EQU     000000002h

 ;  The parameters of the effect were successfully updated by
 ;  IDirectInputEffect::SetParameters, but the effect was not
 ;  downloaded because the device is not exclusively acquired
 ;  or because the DIEP_NODOWNLOAD flag was passed.

   DI_DOWNLOADSKIPPED	       EQU     000000003h

 ;  The parameters of the effect were successfully updated by
 ;  IDirectInputEffect::SetParameters, but in order to change
 ;  the parameters, the effect needed to be restarted.

   DI_EFFECTRESTARTED	       EQU     000000004h

 ;  The parameters of the effect were successfully updated by
 ;  IDirectInputEffect::SetParameters, but some of them were
 ;  beyond the capabilities of the device and were truncated.

   DI_TRUNCATED 	      EQU     000000008h

 ;  The settings have been successfully applied but could not be
 ;  persisted.

   DI_SETTINGSNOTSAVED		EQU	00000000Bh

 ;  Equal to DI_EFFECTRESTARTED | DI_TRUNCATED.

   DI_TRUNCATEDANDRESTARTED	EQU	00000000Ch

 ;  A SUCCESS code indicating that settings cannot be modified.

   DI_WRITEPROTECT		 EQU	 000000013h

 ; The application requires a newer version of DirectInput.

   ;MAKE_HRESULT  DIERR_OLDDIRECTINPUTVERSION, SEVERITY_ERROR, FACILITY_WIN32, ERROR_OLD_WIN_VERSION

 ; The application was written for an unsupported prerelease version
 ; of DirectInput.

   ;MAKE_HRESULT   DIERR_BETADIRECTINPUTVERSION, SEVERITY_ERROR, FACILITY_WIN32, ERROR_RMODE_APP

 ; The object could not be created due to an incompatible driver version
 ; or mismatched or incomplete driver components.

   ;MAKE_HRESULT   DIERR_BADDRIVERVER, SEVERITY_ERROR, FACILITY_WIN32, ERROR_BAD_DRIVER_LEVEL

 ; The device or device instance or effect is not registered with DirectInput.

   DIERR_DEVICENOTREG	       EQU     REGDB_E_CLASSNOTREG

 ; The requested object does not exist.

   ;MAKE_HRESULT   DIERR_NOTFOUND, SEVERITY_ERROR, FACILITY_WIN32, ERROR_FILE_NOT_FOUND

 ; The requested object does not exist.

   ;MAKE_HRESULT   DIERR_OBJECTNOTFOUND, SEVERITY_ERROR, FACILITY_WIN32, ERROR_FILE_NOT_FOUND

 ; An invalid parameter was passed to the returning function,
 ; or the object was not in a state that admitted the function
 ; to be called.

   DIERR_INVALIDPARAM	       EQU     E_INVALIDARG

 ; The specified interface is not supported by the object

   DIERR_NOINTERFACE	       EQU     E_NOINTERFACE

 ; An undetermined error occured inside the DInput subsystem

   DIERR_GENERIC	       EQU     E_FAIL

 ; The DInput subsystem couldn't allocate sufficient memory to complete the
 ; caller's request.

   DIERR_OUTOFMEMORY	       EQU     E_OUTOFMEMORY

 ; The function called is not supported at this time

   DIERR_UNSUPPORTED	       EQU     E_NOTIMPL

 ; This object has not been initialized

   ;MAKE_HRESULT   DIERR_NOTINITIALIZED, SEVERITY_ERROR, FACILITY_WIN32, ERROR_NOT_READY

 ; This object is already initialized

   ;MAKE_HRESULT   DIERR_ALREADYINITIALIZED, SEVERITY_ERROR, FACILITY_WIN32, ERROR_ALREADY_INITIALIZED

 ; This object does not support aggregation

   DIERR_NOAGGREGATION	       EQU     CLASS_E_NOAGGREGATION

 ; Another app has a higher priority level, preventing this call from
 ; succeeding.

   DIERR_OTHERAPPHASPRIO       EQU     E_ACCESSDENIED

 ; Access to the device has been lost.  It must be re-acquired.

   ;MAKE_HRESULT   DIERR_INPUTLOST, SEVERITY_ERROR, FACILITY_WIN32, ERROR_READ_FAULT

 ; The operation cannot be performed while the device is acquired.

   ;MAKE_HRESULT   DIERR_ACQUIRED, SEVERITY_ERROR, FACILITY_WIN32, ERROR_BUSY

 ; The operation cannot be performed unless the device is acquired.

   ;MAKE_HRESULT   DIERR_NOTACQUIRED, SEVERITY_ERROR, FACILITY_WIN32, ERROR_INVALID_ACCESS

 ; The specified property cannot be changed.

   DIERR_READONLY	       EQU     E_ACCESSDENIED

 ; The device already has an event notification associated with it.

   DIERR_HANDLEEXISTS	       EQU     E_ACCESSDENIED

 ; Data is not yet available.

   ;ifndef E_PENDING
   ; E_PENDING                  EQU     08000000Ah
   ;endif

 ; Unable to IDirectInputJoyConfig_Acquire because the user
 ; does not have sufficient privileges to change the joystick
 ; configuration.

   DIERR_INSUFFICIENTPRIVS     EQU     080040200h

 ; The device is full.

   DIERR_DEVICEFULL	       EQU     080040201h

 ; Not all the requested information fit into the buffer.

   DIERR_MOREDATA	       EQU     080040202h

 ; The effect is not downloaded.

   DIERR_NOTDOWNLOADED	       EQU     080040203h

 ;  The device cannot be reinitialized because there are still effects
 ;  attached to it.

   DIERR_HASEFFECTS	       EQU     080040204h

 ; The operation cannot be performed unless the device is acquired
 ; in DISCL_EXCLUSIVE mode.

   DIERR_NOTEXCLUSIVEACQUIRED  EQU     080040205h

 ;  The effect could not be downloaded because essential information
 ;  is missing.  For example, no axes have been associated with the
 ;  effect, or no type-specific information has been created.

   DIERR_INCOMPLETEEFFECT      EQU     080040206h

 ;  Attempted to read buffered device data from a device that is
 ;  not buffered.

   DIERR_NOTBUFFERED	       EQU     080040207h

 ;  An attempt was made to modify parameters of an effect while it is
 ;  playing.  Not all hardware devices support altering the parameters
 ;  of an effect while it is playing.

   DIERR_EFFECTPLAYING	       EQU     080040208h

 ;  The operation could not be completed because the device is not
 ;  plugged in.

   DIERR_UNPLUGGED	       EQU     080040209h

 ;  SendDeviceData failed because more information was requested
 ;  to be sent than can be sent to the device.  Some devices have
 ;  restrictions on how much data can be sent to them.  (For example,
 ;  there might be a limit on the number of buttons that can be
 ;  pressed at once.)

   DIERR_REPORTFULL	       EQU     08004020Ah

 ;  A mapper file function failed because reading or writing the user or IHV
 ;  settings file failed.

   DIERR_MAPFILEFAIL	       EQU     08004020Bh


 ;--- DINPUT Mapper Definitions: New for Dx8         ---*/


 ;--- Keyboard
 ;     Physical Keyboard Device       ---


   DIKEYBOARD_ESCAPE			EQU	081000401h
   DIKEYBOARD_1 			EQU	081000402h
   DIKEYBOARD_2 			EQU	081000403h
   DIKEYBOARD_3 			EQU	081000404h
   DIKEYBOARD_4 			EQU	081000405h
   DIKEYBOARD_5 			EQU	081000406h
   DIKEYBOARD_6 			EQU	081000407h
   DIKEYBOARD_7 			EQU	081000408h
   DIKEYBOARD_8 			EQU	081000409h
   DIKEYBOARD_9 			EQU	08100040Ah
   DIKEYBOARD_0 			EQU	08100040Bh
   DIKEYBOARD_MINUS			EQU	08100040Ch	    ; - on main keyboard
   DIKEYBOARD_EQUALS			EQU	08100040Dh
   DIKEYBOARD_BACK			EQU	08100040Eh	    ; backspace
   DIKEYBOARD_TAB			EQU	08100040Fh
   DIKEYBOARD_Q 			EQU	081000410h
   DIKEYBOARD_W 			EQU	081000411h
   DIKEYBOARD_E 			EQU	081000412h
   DIKEYBOARD_R 			EQU	081000413h
   DIKEYBOARD_T 			EQU	081000414h
   DIKEYBOARD_Y 			EQU	081000415h
   DIKEYBOARD_U 			EQU	081000416h
   DIKEYBOARD_I 			EQU	081000417h
   DIKEYBOARD_O 			EQU	081000418h
   DIKEYBOARD_P 			EQU	081000419h
   DIKEYBOARD_LBRACKET			EQU	08100041Ah
   DIKEYBOARD_RBRACKET			EQU	08100041Bh
   DIKEYBOARD_RETURN			EQU	08100041Ch	    ; Enter on main keyboard
   DIKEYBOARD_LCONTROL			EQU	08100041Dh
   DIKEYBOARD_A 			EQU	08100041Eh
   DIKEYBOARD_S 			EQU	08100041Fh
   DIKEYBOARD_D 			EQU	081000420h
   DIKEYBOARD_F 			EQU	081000421h
   DIKEYBOARD_G 			EQU	081000422h
   DIKEYBOARD_H 			EQU	081000423h
   DIKEYBOARD_J 			EQU	081000424h
   DIKEYBOARD_K 			EQU	081000425h
   DIKEYBOARD_L 			EQU	081000426h
   DIKEYBOARD_SEMICOLON 		EQU	081000427h
   DIKEYBOARD_APOSTROPHE		EQU	081000428h
   DIKEYBOARD_GRAVE			EQU	081000429h	    ; accent grave
   DIKEYBOARD_LSHIFT			EQU	08100042Ah
   DIKEYBOARD_BACKSLASH 		EQU	08100042Bh
   DIKEYBOARD_Z 			EQU	08100042Ch
   DIKEYBOARD_X 			EQU	08100042Dh
   DIKEYBOARD_C 			EQU	08100042Eh
   DIKEYBOARD_V 			EQU	08100042Fh
   DIKEYBOARD_B 			EQU	081000430h
   DIKEYBOARD_N 			EQU	081000431h
   DIKEYBOARD_M 			EQU	081000432h
   DIKEYBOARD_COMMA			EQU	081000433h
   DIKEYBOARD_PERIOD			EQU	081000434h	    ; . on main keyboard
   DIKEYBOARD_SLASH			EQU	081000435h	    ; / on main keyboard
   DIKEYBOARD_RSHIFT			EQU	081000436h
   DIKEYBOARD_MULTIPLY			EQU	081000437h	    ; * on numeric keypad
   DIKEYBOARD_LMENU			EQU	081000438h	    ; left Alt
   DIKEYBOARD_SPACE			EQU	081000439h
   DIKEYBOARD_CAPITAL			EQU	08100043Ah
   DIKEYBOARD_F1			EQU	08100043Bh
   DIKEYBOARD_F2			EQU	08100043Ch
   DIKEYBOARD_F3			EQU	08100043Dh
   DIKEYBOARD_F4			EQU	08100043Eh
   DIKEYBOARD_F5			EQU	08100043Fh
   DIKEYBOARD_F6			EQU	081000440h
   DIKEYBOARD_F7			EQU	081000441h
   DIKEYBOARD_F8			EQU	081000442h
   DIKEYBOARD_F9			EQU	081000443h
   DIKEYBOARD_F10			EQU	081000444h
   DIKEYBOARD_NUMLOCK			EQU	081000445h
   DIKEYBOARD_SCROLL			EQU	081000446h	    ; Scroll Lock
   DIKEYBOARD_NUMPAD7			EQU	081000447h
   DIKEYBOARD_NUMPAD8			EQU	081000448h
   DIKEYBOARD_NUMPAD9			EQU	081000449h
   DIKEYBOARD_SUBTRACT			EQU	08100044Ah	    ; - on numeric keypad
   DIKEYBOARD_NUMPAD4			EQU	08100044Bh
   DIKEYBOARD_NUMPAD5			EQU	08100044Ch
   DIKEYBOARD_NUMPAD6			EQU	08100044Dh
   DIKEYBOARD_ADD			EQU	08100044Eh	    ; + on numeric keypad
   DIKEYBOARD_NUMPAD1			EQU	08100044Fh
   DIKEYBOARD_NUMPAD2			EQU	081000450h
   DIKEYBOARD_NUMPAD3			EQU	081000451h
   DIKEYBOARD_NUMPAD0			EQU	081000452h
   DIKEYBOARD_DECIMAL			EQU	081000453h	    ; . on numeric keypad
   DIKEYBOARD_OEM_102			EQU	081000456h	    ; <> or \| on RT 102-key keyboard (Non-U.S.)
   DIKEYBOARD_F11			EQU	081000457h
   DIKEYBOARD_F12			EQU	081000458h
   DIKEYBOARD_F13			EQU	081000464h	    ;                     (NEC PC98)
   DIKEYBOARD_F14			EQU	081000465h	    ;                     (NEC PC98)
   DIKEYBOARD_F15			EQU	081000466h	    ;                     (NEC PC98)
   DIKEYBOARD_KANA			EQU	081000470h	    ; (Japanese keyboard)
   DIKEYBOARD_ABNT_C1			EQU	081000473h	    ; /? on Brazilian keyboard
   DIKEYBOARD_CONVERT			EQU	081000479h	    ; (Japanese keyboard)
   DIKEYBOARD_NOCONVERT 		EQU	08100047Bh	    ; (Japanese keyboard)
   DIKEYBOARD_YEN			EQU	08100047Dh	    ; (Japanese keyboard)
   DIKEYBOARD_ABNT_C2			EQU	08100047Eh	    ; Numpad . on Brazilian keyboard
   DIKEYBOARD_NUMPADEQUALS		EQU	08100048Dh	    ; = on numeric keypad (NEC PC98)
   DIKEYBOARD_PREVTRACK 		EQU	081000490h	    ; Previous Track (   DIK_CIRCUMFLEX on Japanese keyboard)
   DIKEYBOARD_AT			EQU	081000491h	    ;                     (NEC PC98)
   DIKEYBOARD_COLON			EQU	081000492h	    ;                     (NEC PC98)
   DIKEYBOARD_UNDERLINE 		EQU	081000493h	    ;                     (NEC PC98)
   DIKEYBOARD_KANJI			EQU	081000494h	    ; (Japanese keyboard)
   DIKEYBOARD_STOP			EQU	081000495h	    ;                     (NEC PC98)
   DIKEYBOARD_AX			EQU	081000496h	    ;                     (Japan AX)
   DIKEYBOARD_UNLABELED 		EQU	081000497h	    ;                        (J3100)
   DIKEYBOARD_NEXTTRACK 		EQU	081000499h	    ; Next Track
   DIKEYBOARD_NUMPADENTER		EQU	08100049Ch	    ; Enter on numeric keypad
   DIKEYBOARD_RCONTROL			EQU	08100049Dh
   DIKEYBOARD_MUTE			EQU	0810004A0h	    ; Mute
   DIKEYBOARD_CALCULATOR		EQU	0810004A1h	    ; Calculator
   DIKEYBOARD_PLAYPAUSE 		EQU	0810004A2h	    ; Play / Pause
   DIKEYBOARD_MEDIASTOP 		EQU	0810004A4h	    ; Me   DIa Stop
   DIKEYBOARD_VOLUMEDOWN		EQU	0810004AEh	    ; Volume -
   DIKEYBOARD_VOLUMEUP			EQU	0810004B0h	    ; Volume +
   DIKEYBOARD_WEBHOME			EQU	0810004B2h	    ; Web home
   DIKEYBOARD_NUMPADCOMMA		EQU	0810004B3h	    ; , on numeric keypad (NEC PC98)
   DIKEYBOARD_DIVIDE			EQU	0810004B5h	    ; / on numeric keypad
   DIKEYBOARD_SYSRQ			EQU	0810004B7h
   DIKEYBOARD_RMENU			EQU	0810004B8h	    ; right Alt
   DIKEYBOARD_PAUSE			EQU	0810004C5h	    ; Pause
   DIKEYBOARD_HOME			EQU	0810004C7h	    ; Home on arrow keypad
   DIKEYBOARD_UP			EQU	0810004C8h	    ; UpArrow on arrow keypad
   DIKEYBOARD_PRIOR			EQU	0810004C9h	    ; PgUp on arrow keypad
   DIKEYBOARD_LEFT			EQU	0810004CBh	    ; LeftArrow on arrow keypad
   DIKEYBOARD_RIGHT			EQU	0810004CDh	    ; RightArrow on arrow keypad
   DIKEYBOARD_END			EQU	0810004CFh	    ; End on arrow keypad
   DIKEYBOARD_DOWN			EQU	0810004D0h	    ; DownArrow on arrow keypad
   DIKEYBOARD_NEXT			EQU	0810004D1h	    ; PgDn on arrow keypad
   DIKEYBOARD_INSERT			EQU	0810004D2h	    ; Insert on arrow keypad
   DIKEYBOARD_DELETE			EQU	0810004D3h	    ; Delete on arrow keypad
   DIKEYBOARD_LWIN			EQU	0810004DBh	    ; Left Windows key
   DIKEYBOARD_RWIN			EQU	0810004DCh	    ; Right Windows key
   DIKEYBOARD_APPS			EQU	0810004DDh	    ; AppMenu key
   DIKEYBOARD_POWER			EQU	0810004DEh	    ; System Power
   DIKEYBOARD_SLEEP			EQU	0810004DFh	    ; System Sleep
   DIKEYBOARD_WAKE			EQU	0810004E3h	    ; System Wake
   DIKEYBOARD_WEBSEARCH 		EQU	0810004E5h	    ; Web Search
   DIKEYBOARD_WEBFAVORITES		EQU	0810004E6h	    ; Web Favorites
   DIKEYBOARD_WEBREFRESH		EQU	0810004E7h	    ; Web Refresh
   DIKEYBOARD_WEBSTOP			EQU	0810004E8h	    ; Web Stop
   DIKEYBOARD_WEBFORWARD		EQU	0810004E9h	    ; Web Forward
   DIKEYBOARD_WEBBACK			EQU	0810004EAh	    ; Web Back
   DIKEYBOARD_MYCOMPUTER		EQU	0810004EBh	    ; My Computer
   DIKEYBOARD_MAIL			EQU	0810004ECh	    ; Mail
   DIKEYBOARD_MEDIASELECT		EQU	0810004EDh	    ; Media Select


 ;--- MOUSE
 ;     Physical Mouse Device             ---


   DIMOUSE_XAXISAB			EQU	(082000200h OR DIMOFS_X )  ; X Axis-absolute: Some mice natively report absolute coordinates
   DIMOUSE_YAXISAB			EQU	(082000200h OR DIMOFS_Y )  ; Y Axis-absolute: Some mice natively report absolute coordinates
   DIMOUSE_XAXIS			EQU	(082000300h OR DIMOFS_X )  ; X Axis
   DIMOUSE_YAXIS			EQU	(082000300h OR DIMOFS_Y )  ; Y Axis
   DIMOUSE_WHEEL			EQU	(082000300h OR DIMOFS_Z )  ; Z Axis
   DIMOUSE_BUTTON0			EQU	(082000400h OR DIMOFS_BUTTON0)	; Button 0
   DIMOUSE_BUTTON1			EQU	(082000400h OR DIMOFS_BUTTON1)	; Button 1
   DIMOUSE_BUTTON2			EQU	(082000400h OR DIMOFS_BUTTON2)	; Button 2
   DIMOUSE_BUTTON3			EQU	(082000400h OR DIMOFS_BUTTON3)	; Button 3
   DIMOUSE_BUTTON4			EQU	(082000400h OR DIMOFS_BUTTON4)	; Button 4
   DIMOUSE_BUTTON5			EQU	(082000400h OR DIMOFS_BUTTON5)	; Button 5
   DIMOUSE_BUTTON6			EQU	(082000400h OR DIMOFS_BUTTON6)	; Button 6
   DIMOUSE_BUTTON7			EQU	(082000400h OR DIMOFS_BUTTON7)	; Button 7


 ;--- VOICE
 ;     Physical Dplay Voice Device       ---


   DIVOICE_CHANNEL1			EQU	083000401h
   DIVOICE_CHANNEL2			EQU	083000402h
   DIVOICE_CHANNEL3			EQU	083000403h
   DIVOICE_CHANNEL4			EQU	083000404h
   DIVOICE_CHANNEL5			EQU	083000405h
   DIVOICE_CHANNEL6			EQU	083000406h
   DIVOICE_CHANNEL7			EQU	083000407h
   DIVOICE_CHANNEL8			EQU	083000408h
   DIVOICE_TEAM 			EQU	083000409h
   DIVOICE_ALL				EQU	08300040Ah
   DIVOICE_RECORDMUTE			EQU	08300040Bh
   DIVOICE_PLAYBACKMUTE 		EQU	08300040Ch
   DIVOICE_TRANSMIT			EQU	08300040Dh

   DIVOICE_VOICECOMMAND 		EQU	083000410h


 ;--- Driving Simulator - Racing
 ;     Vehicle control is primary objective  ---

   DIVIRTUAL_DRIVING_RACE		EQU	001000000h
   DIAXIS_DRIVINGR_STEER		EQU	001008A01h	 ; Steering
   DIAXIS_DRIVINGR_ACCELERATE		EQU	001039202h	 ; Accelerate
   DIAXIS_DRIVINGR_BRAKE		EQU	001041203h	 ; Brake-Axis
   DIBUTTON_DRIVINGR_SHIFTUP		EQU	001000C01h	 ; Shift to next higher gear
   DIBUTTON_DRIVINGR_SHIFTDOWN		EQU	001000C02h	 ; Shift to next lower gear
   DIBUTTON_DRIVINGR_VIEW		EQU	001001C03h	 ; Cycle through view options
   DIBUTTON_DRIVINGR_MENU		EQU	0010004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIAXIS_DRIVINGR_ACCEL_AND_BRAKE	EQU	001014A04h	 ; Some devices combine accelerate and brake in a single axis
   DIHATSWITCH_DRIVINGR_GLANCE		EQU	001004601h	 ; Look around
   DIBUTTON_DRIVINGR_BRAKE		EQU	001004C04h	 ; Brake-button
   DIBUTTON_DRIVINGR_DASHBOARD		EQU	001004405h	 ; Select next dashboard option
   DIBUTTON_DRIVINGR_AIDS		EQU	001004406h	 ; Driver correction aids
   DIBUTTON_DRIVINGR_MAP		EQU	001004407h	 ;    DIsplay Driving Map
   DIBUTTON_DRIVINGR_BOOST		EQU	001004408h	 ; Turbo Boost
   DIBUTTON_DRIVINGR_PIT		EQU	001004409h	 ; Pit stop notification
   DIBUTTON_DRIVINGR_ACCELERATE_LINK	EQU	00103D4E0h	 ; Fallback Accelerate button
   DIBUTTON_DRIVINGR_STEER_LEFT_LINK	EQU	00100CCE4h	 ; Fallback Steer Left button
   DIBUTTON_DRIVINGR_STEER_RIGHT_LINK	EQU	00100CCECh	 ; Fallback Steer Right button
   DIBUTTON_DRIVINGR_GLANCE_LEFT_LINK	EQU	00107C4E4h	 ; Fallback Glance Left button
   DIBUTTON_DRIVINGR_GLANCE_RIGHT_LINK	EQU	00107C4ECh	 ; Fallback Glance Right button
   DIBUTTON_DRIVINGR_DEVICE		EQU	0010044FEh	 ; Show input device and controls
   DIBUTTON_DRIVINGR_PAUSE		EQU	0010044FCh	 ; Start / Pause / Restart game

 ;--- Driving Simulator - Combat
 ;     Combat from within a vehicle is primary objective  ---

   DIVIRTUAL_DRIVING_COMBAT		EQU	002000000h
   DIAXIS_DRIVINGC_STEER		EQU	002008A01h	 ; Steering
   DIAXIS_DRIVINGC_ACCELERATE		EQU	002039202h	 ; Accelerate
   DIAXIS_DRIVINGC_BRAKE		EQU	002041203h	 ; Brake-axis
   DIBUTTON_DRIVINGC_FIRE		EQU	002000C01h	 ; Fire
   DIBUTTON_DRIVINGC_WEAPONS		EQU	002000C02h	 ; Select next weapon
   DIBUTTON_DRIVINGC_TARGET		EQU	002000C03h	 ; Select next available target
   DIBUTTON_DRIVINGC_MENU		EQU	0020004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIAXIS_DRIVINGC_ACCEL_AND_BRAKE	EQU	002014A04h	 ; Some devices combine accelerate and brake in a single axis
   DIHATSWITCH_DRIVINGC_GLANCE		EQU	002004601h	 ; Look around
   DIBUTTON_DRIVINGC_SHIFTUP		EQU	002004C04h	 ; Shift to next higher gear
   DIBUTTON_DRIVINGC_SHIFTDOWN		EQU	002004C05h	 ; Shift to next lower gear
   DIBUTTON_DRIVINGC_DASHBOARD		EQU	002004406h	 ; Select next dashboard option
   DIBUTTON_DRIVINGC_AIDS		EQU	002004407h	 ; Driver correction aids
   DIBUTTON_DRIVINGC_BRAKE		EQU	002004C08h	 ; Brake-button
   DIBUTTON_DRIVINGC_FIRESECONDARY	EQU	002004C09h	 ; Alternative fire button
   DIBUTTON_DRIVINGC_ACCELERATE_LINK	EQU	00203D4E0h	 ; Fallback Accelerate button
   DIBUTTON_DRIVINGC_STEER_LEFT_LINK	EQU	00200CCE4h	 ; Fallback Steer Left button
   DIBUTTON_DRIVINGC_STEER_RIGHT_LINK	EQU	00200CCECh	 ; Fallback Steer Right button
   DIBUTTON_DRIVINGC_GLANCE_LEFT_LINK	EQU	00207C4E4h	 ; Fallback Glance Left button
   DIBUTTON_DRIVINGC_GLANCE_RIGHT_LINK	EQU	00207C4ECh	 ; Fallback Glance Right button
   DIBUTTON_DRIVINGC_DEVICE		EQU	0020044FEh	 ; Show input device and controls
   DIBUTTON_DRIVINGC_PAUSE		EQU	0020044FCh	 ; Start / Pause / Restart game

 ;--- Driving Simulator - Tank
 ;     Combat from withing a tank is primary objective  ---

   DIVIRTUAL_DRIVING_TANK		EQU	003000000h
   DIAXIS_DRIVINGT_STEER		EQU	003008A01h	 ; Turn tank left / right
   DIAXIS_DRIVINGT_BARREL		EQU	003010202h	 ; Raise / lower barrel
   DIAXIS_DRIVINGT_ACCELERATE		EQU	003039203h	 ; Accelerate
   DIAXIS_DRIVINGT_ROTATE		EQU	003020204h	 ; Turn barrel left / right
   DIBUTTON_DRIVINGT_FIRE		EQU	003000C01h	 ; Fire
   DIBUTTON_DRIVINGT_WEAPONS		EQU	003000C02h	 ; Select next weapon
   DIBUTTON_DRIVINGT_TARGET		EQU	003000C03h	 ; Selects next available target
   DIBUTTON_DRIVINGT_MENU		EQU	0030004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_DRIVINGT_GLANCE		EQU	003004601h	 ; Look around
   DIAXIS_DRIVINGT_BRAKE		EQU	003045205h	 ; Brake-axis
   DIAXIS_DRIVINGT_ACCEL_AND_BRAKE	EQU	003014A06h	 ; Some devices combine accelerate and brake in a single axis
   DIBUTTON_DRIVINGT_VIEW		EQU	003005C04h	 ; Cycle through view options
   DIBUTTON_DRIVINGT_DASHBOARD		EQU	003005C05h	 ; Select next dashboard option
   DIBUTTON_DRIVINGT_BRAKE		EQU	003004C06h	 ; Brake-button
   DIBUTTON_DRIVINGT_FIRESECONDARY	EQU	003004C07h	 ; Alternative fire button
   DIBUTTON_DRIVINGT_ACCELERATE_LINK	EQU	00303D4E0h	 ; Fallback Accelerate button
   DIBUTTON_DRIVINGT_STEER_LEFT_LINK	EQU	00300CCE4h	 ; Fallback Steer Left button
   DIBUTTON_DRIVINGT_STEER_RIGHT_LINK	EQU	00300CCECh	 ; Fallback Steer Right button
   DIBUTTON_DRIVINGT_BARREL_UP_LINK	EQU	0030144E0h	 ; Fallback Barrel up button
   DIBUTTON_DRIVINGT_BARREL_DOWN_LINK	EQU	0030144E8h	 ; Fallback Barrel down button
   DIBUTTON_DRIVINGT_ROTATE_LEFT_LINK	EQU	0030244E4h	 ; Fallback Rotate left button
   DIBUTTON_DRIVINGT_ROTATE_RIGHT_LINK	EQU	0030244ECh	 ; Fallback Rotate right button
   DIBUTTON_DRIVINGT_GLANCE_LEFT_LINK	EQU	00307C4E4h	 ; Fallback Glance Left button
   DIBUTTON_DRIVINGT_GLANCE_RIGHT_LINK	EQU	00307C4ECh	 ; Fallback Glance Right button
   DIBUTTON_DRIVINGT_DEVICE		EQU	0030044FEh	 ; Show input device and controls
   DIBUTTON_DRIVINGT_PAUSE		EQU	0030044FCh	 ; Start / Pause / Restart game

 ;--- Flight Simulator - Civilian
 ;     Plane control is the primary objective  ---

   DIVIRTUAL_FLYING_CIVILIAN		EQU	004000000h
   DIAXIS_FLYINGC_BANK			EQU	004008A01h	 ; Roll ship left / right
   DIAXIS_FLYINGC_PITCH 		EQU	004010A02h	 ; Nose up / down
   DIAXIS_FLYINGC_THROTTLE		EQU	004039203h	 ; Throttle
   DIBUTTON_FLYINGC_VIEW		EQU	004002401h	 ; Cycle through view options
   DIBUTTON_FLYINGC_DISPLAY		EQU	004002402h	 ; Select next dashboard / heads up display option
   DIBUTTON_FLYINGC_GEAR		EQU	004002C03h	 ; Gear up / down
   DIBUTTON_FLYINGC_MENU		EQU	0040004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_FLYINGC_GLANCE		EQU	004004601h	 ; Look around
   DIAXIS_FLYINGC_BRAKE 		EQU	004046A04h	 ; Apply Brake
   DIAXIS_FLYINGC_RUDDER		EQU	004025205h	 ; Yaw ship left/right
   DIAXIS_FLYINGC_FLAPS 		EQU	004055A06h	 ; Flaps
   DIBUTTON_FLYINGC_FLAPSUP		EQU	004006404h	 ; Increment stepping up until fully retracted
   DIBUTTON_FLYINGC_FLAPSDOWN		EQU	004006405h	 ; Decrement stepping down until fully extended
   DIBUTTON_FLYINGC_BRAKE_LINK		EQU	004046CE0h	 ; Fallback brake button
   DIBUTTON_FLYINGC_FASTER_LINK 	EQU	00403D4E0h	 ; Fallback throttle up button
   DIBUTTON_FLYINGC_SLOWER_LINK 	EQU	00403D4E8h	 ; Fallback throttle down button
   DIBUTTON_FLYINGC_GLANCE_LEFT_LINK	EQU	00407C4E4h	 ; Fallback Glance Left button
   DIBUTTON_FLYINGC_GLANCE_RIGHT_LINK	EQU	00407C4ECh	 ; Fallback Glance Right button
   DIBUTTON_FLYINGC_GLANCE_UP_LINK	EQU	00407C4E0h	 ; Fallback Glance Up button
   DIBUTTON_FLYINGC_GLANCE_DOWN_LINK	EQU	00407C4E8h	 ; Fallback Glance Down button
   DIBUTTON_FLYINGC_DEVICE		EQU	0040044FEh	 ; Show input device and controls
   DIBUTTON_FLYINGC_PAUSE		EQU	0040044FCh	 ; Start / Pause / Restart game

 ;--- Flight Simulator - Military
 ;     Aerial combat is the primary objective  ---

   DIVIRTUAL_FLYING_MILITARY		EQU	005000000h
   DIAXIS_FLYINGM_BANK			EQU	005008A01h	 ; Bank - Roll ship left / right
   DIAXIS_FLYINGM_PITCH 		EQU	005010A02h	 ; Pitch - Nose up / down
   DIAXIS_FLYINGM_THROTTLE		EQU	005039203h	 ; Throttle - faster / slower
   DIBUTTON_FLYINGM_FIRE		EQU	005000C01h	 ; Fire
   DIBUTTON_FLYINGM_WEAPONS		EQU	005000C02h	 ; Select next weapon
   DIBUTTON_FLYINGM_TARGET		EQU	005000C03h	 ; Selects next available target
   DIBUTTON_FLYINGM_MENU		EQU	0050004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_FLYINGM_GLANCE		EQU	005004601h	 ; Look around
   DIBUTTON_FLYINGM_COUNTER		EQU	005005C04h	 ; Activate counter measures
   DIAXIS_FLYINGM_RUDDER		EQU	005024A04h	 ; Rudder - Yaw ship left/right
   DIAXIS_FLYINGM_BRAKE 		EQU	005046205h	 ; Brake-axis
   DIBUTTON_FLYINGM_VIEW		EQU	005006405h	 ; Cycle through view options
   DIBUTTON_FLYINGM_DISPLAY		EQU	005006406h	 ; Select next dashboard option
   DIAXIS_FLYINGM_FLAPS 		EQU	005055206h	 ; Flaps
   DIBUTTON_FLYINGM_FLAPSUP		EQU	005005407h	 ; Increment stepping up until fully retracted
   DIBUTTON_FLYINGM_FLAPSDOWN		EQU	005005408h	 ; Decrement stepping down until fully extended
   DIBUTTON_FLYINGM_FIRESECONDARY	EQU	005004C09h	 ; Alternative fire button
   DIBUTTON_FLYINGM_GEAR		EQU	00500640Ah	 ; Gear up / down
   DIBUTTON_FLYINGM_BRAKE_LINK		EQU	0050464E0h	 ; Fallback brake button
   DIBUTTON_FLYINGM_FASTER_LINK 	EQU	00503D4E0h	 ; Fallback throttle up button
   DIBUTTON_FLYINGM_SLOWER_LINK 	EQU	00503D4E8h	 ; Fallback throttle down button
   DIBUTTON_FLYINGM_GLANCE_LEFT_LINK	EQU	00507C4E4h	 ; Fallback Glance Left button
   DIBUTTON_FLYINGM_GLANCE_RIGHT_LINK	EQU	00507C4ECh	 ; Fallback Glance Right button
   DIBUTTON_FLYINGM_GLANCE_UP_LINK	EQU	00507C4E0h	 ; Fallback Glance Up button
   DIBUTTON_FLYINGM_GLANCE_DOWN_LINK	EQU	00507C4E8h	 ; Fallback Glance Down button
   DIBUTTON_FLYINGM_DEVICE		EQU	0050044FEh	 ; Show input device and controls
   DIBUTTON_FLYINGM_PAUSE		EQU	0050044FCh	 ; Start / Pause / Restart game

 ;--- Flight Simulator - Combat Helicopter
 ;     Combat from helicopter is primary objective  ---

   DIVIRTUAL_FLYING_HELICOPTER		EQU	006000000h
   DIAXIS_FLYINGH_BANK			EQU	006008A01h	 ; Bank - Roll ship left / right
   DIAXIS_FLYINGH_PITCH 		EQU	006010A02h	 ; Pitch - Nose up / down
   DIAXIS_FLYINGH_COLLECTIVE		EQU	006018A03h	 ; Collective - Blade pitch/power
   DIBUTTON_FLYINGH_FIRE		EQU	006001401h	 ; Fire
   DIBUTTON_FLYINGH_WEAPONS		EQU	006001402h	 ; Select next weapon
   DIBUTTON_FLYINGH_TARGET		EQU	006001403h	 ; Selects next available target
   DIBUTTON_FLYINGH_MENU		EQU	0060004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_FLYINGH_GLANCE		EQU	006004601h	 ; Look around
   DIAXIS_FLYINGH_TORQUE		EQU	006025A04h	 ; Torque - Rotate ship around left / right axis
   DIAXIS_FLYINGH_THROTTLE		EQU	00603DA05h	 ; Throttle
   DIBUTTON_FLYINGH_COUNTER		EQU	006005404h	 ; Activate counter measures
   DIBUTTON_FLYINGH_VIEW		EQU	006006405h	 ; Cycle through view options
   DIBUTTON_FLYINGH_GEAR		EQU	006006406h	 ; Gear up / down
   DIBUTTON_FLYINGH_FIRESECONDARY	EQU	006004C07h	 ; Alternative fire button
   DIBUTTON_FLYINGH_FASTER_LINK 	EQU	00603DCE0h	 ; Fallback throttle up button
   DIBUTTON_FLYINGH_SLOWER_LINK 	EQU	00603DCE8h	 ; Fallback throttle down button
   DIBUTTON_FLYINGH_GLANCE_LEFT_LINK	EQU	00607C4E4h	 ; Fallback Glance Left button
   DIBUTTON_FLYINGH_GLANCE_RIGHT_LINK	EQU	00607C4ECh	 ; Fallback Glance Right button
   DIBUTTON_FLYINGH_GLANCE_UP_LINK	EQU	00607C4E0h	 ; Fallback Glance Up button
   DIBUTTON_FLYINGH_GLANCE_DOWN_LINK	EQU	00607C4E8h	 ; Fallback Glance Down button
   DIBUTTON_FLYINGH_DEVICE		EQU	0060044FEh	 ; Show input device and controls
   DIBUTTON_FLYINGH_PAUSE		EQU	0060044FCh	 ; Start / Pause / Restart game

 ;--- Space Simulator - Combat
 ;     Space Simulator with weapons  ---

   DIVIRTUAL_SPACESIM			EQU	007000000h
   DIAXIS_SPACESIM_LATERAL		EQU	007008201h	 ; Move ship left / right
   DIAXIS_SPACESIM_MOVE 		EQU	007010202h	 ; Move ship forward/backward
   DIAXIS_SPACESIM_THROTTLE		EQU	007038203h	 ; Throttle - Engine speed
   DIBUTTON_SPACESIM_FIRE		EQU	007000401h	 ; Fire
   DIBUTTON_SPACESIM_WEAPONS		EQU	007000402h	 ; Select next weapon
   DIBUTTON_SPACESIM_TARGET		EQU	007000403h	 ; Selects next available target
   DIBUTTON_SPACESIM_MENU		EQU	0070004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_SPACESIM_GLANCE		EQU	007004601h	 ; Look around
   DIAXIS_SPACESIM_CLIMB		EQU	00701C204h	 ; Climb - Pitch ship up/down
   DIAXIS_SPACESIM_ROTATE		EQU	007024205h	 ; Rotate - Turn ship left/right
   DIBUTTON_SPACESIM_VIEW		EQU	007004404h	 ; Cycle through view options
   DIBUTTON_SPACESIM_DISPLAY		EQU	007004405h	 ; Select next dashboard / heads up display option
   DIBUTTON_SPACESIM_RAISE		EQU	007004406h	 ; Raise ship while maintaining current pitch
   DIBUTTON_SPACESIM_LOWER		EQU	007004407h	 ; Lower ship while maintaining current pitch
   DIBUTTON_SPACESIM_GEAR		EQU	007004408h	 ; Gear up / down
   DIBUTTON_SPACESIM_FIRESECONDARY	EQU	007004409h	 ; Alternative fire button
   DIBUTTON_SPACESIM_LEFT_LINK		EQU	00700C4E4h	 ; Fallback move left button
   DIBUTTON_SPACESIM_RIGHT_LINK 	EQU	00700C4ECh	 ; Fallback move right button
   DIBUTTON_SPACESIM_FORWARD_LINK	EQU	0070144E0h	 ; Fallback move forward button
   DIBUTTON_SPACESIM_BACKWARD_LINK	EQU	0070144E8h	 ; Fallback move backwards button
   DIBUTTON_SPACESIM_FASTER_LINK	EQU	00703C4E0h	 ; Fallback throttle up button
   DIBUTTON_SPACESIM_SLOWER_LINK	EQU	00703C4E8h	 ; Fallback throttle down button
   DIBUTTON_SPACESIM_TURN_LEFT_LINK	EQU	0070244E4h	 ; Fallback turn left button
   DIBUTTON_SPACESIM_TURN_RIGHT_LINK	EQU	0070244ECh	 ; Fallback turn right button
   DIBUTTON_SPACESIM_GLANCE_LEFT_LINK	EQU	00707C4E4h	 ; Fallback Glance Left button
   DIBUTTON_SPACESIM_GLANCE_RIGHT_LINK	EQU	00707C4ECh	 ; Fallback Glance Right button
   DIBUTTON_SPACESIM_GLANCE_UP_LINK	EQU	00707C4E0h	 ; Fallback Glance Up button
   DIBUTTON_SPACESIM_GLANCE_DOWN_LINK	EQU	00707C4E8h	 ; Fallback Glance Down button
   DIBUTTON_SPACESIM_DEVICE		EQU	0070044FEh	 ; Show input device and controls
   DIBUTTON_SPACESIM_PAUSE		EQU	0070044FCh	 ; Start / Pause / Restart game

 ;--- Fighting - First Person
 ;     Hand to Hand combat is primary objective  ---

   DIVIRTUAL_FIGHTING_HAND2HAND 	EQU	008000000h
   DIAXIS_FIGHTINGH_LATERAL		EQU	008008201h	 ; Sidestep left/right
   DIAXIS_FIGHTINGH_MOVE		EQU	008010202h	 ; Move forward/backward
   DIBUTTON_FIGHTINGH_PUNCH		EQU	008000401h	 ; Punch
   DIBUTTON_FIGHTINGH_KICK		EQU	008000402h	 ; Kick
   DIBUTTON_FIGHTINGH_BLOCK		EQU	008000403h	 ; Block
   DIBUTTON_FIGHTINGH_CROUCH		EQU	008000404h	 ; Crouch
   DIBUTTON_FIGHTINGH_JUMP		EQU	008000405h	 ; Jump
   DIBUTTON_FIGHTINGH_SPECIAL1		EQU	008000406h	 ; Apply first special move
   DIBUTTON_FIGHTINGH_SPECIAL2		EQU	008000407h	 ; Apply second special move
   DIBUTTON_FIGHTINGH_MENU		EQU	0080004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_FIGHTINGH_SELECT		EQU	008004408h	 ; Select special move
   DIHATSWITCH_FIGHTINGH_SLIDE		EQU	008004601h	 ; Look around
   DIBUTTON_FIGHTINGH_DISPLAY		EQU	008004409h	 ; Shows next on-screen display option
   DIAXIS_FIGHTINGH_ROTATE		EQU	008024203h	 ; Rotate - Turn body left/right
   DIBUTTON_FIGHTINGH_DODGE		EQU	00800440Ah	 ; Dodge
   DIBUTTON_FIGHTINGH_LEFT_LINK 	EQU	00800C4E4h	 ; Fallback left sidestep button
   DIBUTTON_FIGHTINGH_RIGHT_LINK	EQU	00800C4ECh	 ; Fallback right sidestep button
   DIBUTTON_FIGHTINGH_FORWARD_LINK	EQU	0080144E0h	 ; Fallback forward button
   DIBUTTON_FIGHTINGH_BACKWARD_LINK	EQU	0080144E8h	 ; Fallback backward button
   DIBUTTON_FIGHTINGH_DEVICE		EQU	0080044FEh	 ; Show input device and controls
   DIBUTTON_FIGHTINGH_PAUSE		EQU	0080044FCh	 ; Start / Pause / Restart game

 ;--- Fighting - First Person Shooting
 ;     Navigation and combat are primary objectives  ---

   DIVIRTUAL_FIGHTING_FPS		EQU	009000000h
   DIAXIS_FPS_ROTATE			EQU	009008201h	 ; Rotate character left/right
   DIAXIS_FPS_MOVE			EQU	009010202h	 ; Move forward/backward
   DIBUTTON_FPS_FIRE			EQU	009000401h	 ; Fire
   DIBUTTON_FPS_WEAPONS 		EQU	009000402h	 ; Select next weapon
   DIBUTTON_FPS_APPLY			EQU	009000403h	 ; Use item
   DIBUTTON_FPS_SELECT			EQU	009000404h	 ; Select next inventory item
   DIBUTTON_FPS_CROUCH			EQU	009000405h	 ; Crouch/ climb down/ swim down
   DIBUTTON_FPS_JUMP			EQU	009000406h	 ; Jump/ climb up/ swim up
   DIAXIS_FPS_LOOKUPDOWN		EQU	009018203h	 ; Look up / down
   DIBUTTON_FPS_STRAFE			EQU	009000407h	 ; Enable strafing while active
   DIBUTTON_FPS_MENU			EQU	0090004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_FPS_GLANCE		EQU	009004601h	 ; Look around
   DIBUTTON_FPS_DISPLAY 		EQU	009004408h	 ; Shows next on-screen display option/ map
   DIAXIS_FPS_SIDESTEP			EQU	009024204h	 ; Sidestep
   DIBUTTON_FPS_DODGE			EQU	009004409h	 ; Dodge
   DIBUTTON_FPS_GLANCEL 		EQU	00900440Ah	 ; Glance Left
   DIBUTTON_FPS_GLANCER 		EQU	00900440Bh	 ; Glance Right
   DIBUTTON_FPS_FIRESECONDARY		EQU	00900440Ch	 ; Alternative fire button
   DIBUTTON_FPS_ROTATE_LEFT_LINK	EQU	00900C4E4h	 ; Fallback rotate left button
   DIBUTTON_FPS_ROTATE_RIGHT_LINK	EQU	00900C4ECh	 ; Fallback rotate right button
   DIBUTTON_FPS_FORWARD_LINK		EQU	0090144E0h	 ; Fallback forward button
   DIBUTTON_FPS_BACKWARD_LINK		EQU	0090144E8h	 ; Fallback backward button
   DIBUTTON_FPS_GLANCE_UP_LINK		EQU	00901C4E0h	 ; Fallback look up button
   DIBUTTON_FPS_GLANCE_DOWN_LINK	EQU	00901C4E8h	 ; Fallback look down button
   DIBUTTON_FPS_STEP_LEFT_LINK		EQU	0090244E4h	 ; Fallback step left button
   DIBUTTON_FPS_STEP_RIGHT_LINK 	EQU	0090244ECh	 ; Fallback step right button
   DIBUTTON_FPS_DEVICE			EQU	0090044FEh	 ; Show input device and controls
   DIBUTTON_FPS_PAUSE			EQU	0090044FCh	 ; Start / Pause / Restart game

 ;--- Fighting - Third Person action
 ;     Perspective of camera is behind the main character  ---

   DIVIRTUAL_FIGHTING_THIRDPERSON	EQU	00A000000h
   DIAXIS_TPS_TURN			EQU	00A020201h	 ; Turn left/right
   DIAXIS_TPS_MOVE			EQU	00A010202h	 ; Move forward/backward
   DIBUTTON_TPS_RUN			EQU	00A000401h	 ; Run or walk toggle switch
   DIBUTTON_TPS_ACTION			EQU	00A000402h	 ; Action Button
   DIBUTTON_TPS_SELECT			EQU	00A000403h	 ; Select next weapon
   DIBUTTON_TPS_USE			EQU	00A000404h	 ; Use inventory item currently selected
   DIBUTTON_TPS_JUMP			EQU	00A000405h	 ; Character Jumps
   DIBUTTON_TPS_MENU			EQU	00A0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_TPS_GLANCE		EQU	00A004601h	 ; Look around
   DIBUTTON_TPS_VIEW			EQU	00A004406h	 ; Select camera view
   DIBUTTON_TPS_STEPLEFT		EQU	00A004407h	 ; Character takes a left step
   DIBUTTON_TPS_STEPRIGHT		EQU	00A004408h	 ; Character takes a right step
   DIAXIS_TPS_STEP			EQU	00A00C203h	 ; Character steps left/right
   DIBUTTON_TPS_DODGE			EQU	00A004409h	 ; Character dodges or ducks
   DIBUTTON_TPS_INVENTORY		EQU	00A00440Ah	 ; Cycle through inventory
   DIBUTTON_TPS_TURN_LEFT_LINK		EQU	00A0244E4h	 ; Fallback turn left button
   DIBUTTON_TPS_TURN_RIGHT_LINK 	EQU	00A0244ECh	 ; Fallback turn right button
   DIBUTTON_TPS_FORWARD_LINK		EQU	00A0144E0h	 ; Fallback forward button
   DIBUTTON_TPS_BACKWARD_LINK		EQU	00A0144E8h	 ; Fallback backward button
   DIBUTTON_TPS_GLANCE_UP_LINK		EQU	00A07C4E0h	 ; Fallback look up button
   DIBUTTON_TPS_GLANCE_DOWN_LINK	EQU	00A07C4E8h	 ; Fallback look down button
   DIBUTTON_TPS_GLANCE_LEFT_LINK	EQU	00A07C4E4h	 ; Fallback glance up button
   DIBUTTON_TPS_GLANCE_RIGHT_LINK	EQU	00A07C4ECh	 ; Fallback glance right button
   DIBUTTON_TPS_DEVICE			EQU	00A0044FEh	 ; Show input device and controls
   DIBUTTON_TPS_PAUSE			EQU	00A0044FCh	 ; Start / Pause / Restart game

 ;--- Strategy - Role Playing
 ;     Navigation and problem solving are primary actions  ---

   DIVIRTUAL_STRATEGY_ROLEPLAYING	EQU	00B000000h
   DIAXIS_STRATEGYR_LATERAL		EQU	00B008201h	 ; sidestep - left/right
   DIAXIS_STRATEGYR_MOVE		EQU	00B010202h	 ; move forward/backward
   DIBUTTON_STRATEGYR_GET		EQU	00B000401h	 ; Acquire item
   DIBUTTON_STRATEGYR_APPLY		EQU	00B000402h	 ; Use selected item
   DIBUTTON_STRATEGYR_SELECT		EQU	00B000403h	 ; Select nextitem
   DIBUTTON_STRATEGYR_ATTACK		EQU	00B000404h	 ; Attack
   DIBUTTON_STRATEGYR_CAST		EQU	00B000405h	 ; Cast Spell
   DIBUTTON_STRATEGYR_CROUCH		EQU	00B000406h	 ; Crouch
   DIBUTTON_STRATEGYR_JUMP		EQU	00B000407h	 ; Jump
   DIBUTTON_STRATEGYR_MENU		EQU	00B0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_STRATEGYR_GLANCE 	EQU	00B004601h	 ; Look around
   DIBUTTON_STRATEGYR_MAP		EQU	00B004408h	 ; Cycle through map options
   DIBUTTON_STRATEGYR_DISPLAY		EQU	00B004409h	 ; Shows next on-screen display option
   DIAXIS_STRATEGYR_ROTATE		EQU	00B024203h	 ; Turn body left/right
   DIBUTTON_STRATEGYR_LEFT_LINK 	EQU	00B00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_STRATEGYR_RIGHT_LINK	EQU	00B00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_STRATEGYR_FORWARD_LINK	EQU	00B0144E0h	 ; Fallback move forward button
   DIBUTTON_STRATEGYR_BACK_LINK 	EQU	00B0144E8h	 ; Fallback move backward button
   DIBUTTON_STRATEGYR_ROTATE_LEFT_LINK	EQU	00B0244E4h	 ; Fallback turn body left button
   DIBUTTON_STRATEGYR_ROTATE_RIGHT_LINK EQU	00B0244ECh	 ; Fallback turn body right button
   DIBUTTON_STRATEGYR_DEVICE		EQU	00B0044FEh	 ; Show input device and controls
   DIBUTTON_STRATEGYR_PAUSE		EQU	00B0044FCh	 ; Start / Pause / Restart game

 ;--- Strategy - Turn based
 ;     Navigation and problem solving are primary actions  ---

   DIVIRTUAL_STRATEGY_TURN		EQU	00C000000h
   DIAXIS_STRATEGYT_LATERAL		EQU	00C008201h	 ; Sidestep left/right
   DIAXIS_STRATEGYT_MOVE		EQU	00C010202h	 ; Move forward/backwards
   DIBUTTON_STRATEGYT_SELECT		EQU	00C000401h	 ; Select unit or object
   DIBUTTON_STRATEGYT_INSTRUCT		EQU	00C000402h	 ; Cycle through instructions
   DIBUTTON_STRATEGYT_APPLY		EQU	00C000403h	 ; Apply selected instruction
   DIBUTTON_STRATEGYT_TEAM		EQU	00C000404h	 ; Select next team / cycle through all
   DIBUTTON_STRATEGYT_TURN		EQU	00C000405h	 ; Indicate turn over
   DIBUTTON_STRATEGYT_MENU		EQU	00C0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_STRATEGYT_ZOOM		EQU	00C004406h	 ; Zoom - in / out
   DIBUTTON_STRATEGYT_MAP		EQU	00C004407h	 ; cycle through map options
   DIBUTTON_STRATEGYT_DISPLAY		EQU	00C004408h	 ; shows next on-screen display options
   DIBUTTON_STRATEGYT_LEFT_LINK 	EQU	00C00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_STRATEGYT_RIGHT_LINK	EQU	00C00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_STRATEGYT_FORWARD_LINK	EQU	00C0144E0h	 ; Fallback move forward button
   DIBUTTON_STRATEGYT_BACK_LINK 	EQU	00C0144E8h	 ; Fallback move back button
   DIBUTTON_STRATEGYT_DEVICE		EQU	00C0044FEh	 ; Show input device and controls
   DIBUTTON_STRATEGYT_PAUSE		EQU	00C0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Hunting
 ;     Hunting                ---

   DIVIRTUAL_SPORTS_HUNTING		EQU	00D000000h
   DIAXIS_HUNTING_LATERAL		EQU	00D008201h	 ; sidestep left/right
   DIAXIS_HUNTING_MOVE			EQU	00D010202h	 ; move forward/backwards
   DIBUTTON_HUNTING_FIRE		EQU	00D000401h	 ; Fire selected weapon
   DIBUTTON_HUNTING_AIM 		EQU	00D000402h	 ; Select aim/move
   DIBUTTON_HUNTING_WEAPON		EQU	00D000403h	 ; Select next weapon
   DIBUTTON_HUNTING_BINOCULAR		EQU	00D000404h	 ; Look through Binoculars
   DIBUTTON_HUNTING_CALL		EQU	00D000405h	 ; Make animal call
   DIBUTTON_HUNTING_MAP 		EQU	00D000406h	 ; View Map
   DIBUTTON_HUNTING_SPECIAL		EQU	00D000407h	 ; Special game operation
   DIBUTTON_HUNTING_MENU		EQU	00D0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_HUNTING_GLANCE		EQU	00D004601h	 ; Look around
   DIBUTTON_HUNTING_DISPLAY		EQU	00D004408h	 ; show next on-screen display option
   DIAXIS_HUNTING_ROTATE		EQU	00D024203h	 ; Turn body left/right
   DIBUTTON_HUNTING_CROUCH		EQU	00D004409h	 ; Crouch/ Climb / Swim down
   DIBUTTON_HUNTING_JUMP		EQU	00D00440Ah	 ; Jump/ Climb up / Swim up
   DIBUTTON_HUNTING_FIRESECONDARY	EQU	00D00440Bh	 ; Alternative fire button
   DIBUTTON_HUNTING_LEFT_LINK		EQU	00D00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_HUNTING_RIGHT_LINK		EQU	00D00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_HUNTING_FORWARD_LINK	EQU	00D0144E0h	 ; Fallback move forward button
   DIBUTTON_HUNTING_BACK_LINK		EQU	00D0144E8h	 ; Fallback move back button
   DIBUTTON_HUNTING_ROTATE_LEFT_LINK	EQU	00D0244E4h	 ; Fallback turn body left button
   DIBUTTON_HUNTING_ROTATE_RIGHT_LINK	EQU	00D0244ECh	 ; Fallback turn body right button
   DIBUTTON_HUNTING_DEVICE		EQU	00D0044FEh	 ; Show input device and controls
   DIBUTTON_HUNTING_PAUSE		EQU	00D0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Fishing
 ;     Catching Fish is primary objective   ---

   DIVIRTUAL_SPORTS_FISHING		EQU	00E000000h
   DIAXIS_FISHING_LATERAL		EQU	00E008201h	 ; sidestep left/right
   DIAXIS_FISHING_MOVE			EQU	00E010202h	 ; move forward/backwards
   DIBUTTON_FISHING_CAST		EQU	00E000401h	 ; Cast line
   DIBUTTON_FISHING_TYPE		EQU	00E000402h	 ; Select cast type
   DIBUTTON_FISHING_BINOCULAR		EQU	00E000403h	 ; Look through Binocular
   DIBUTTON_FISHING_BAIT		EQU	00E000404h	 ; Select type of Bait
   DIBUTTON_FISHING_MAP 		EQU	00E000405h	 ; View Map
   DIBUTTON_FISHING_MENU		EQU	00E0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_FISHING_GLANCE		EQU	00E004601h	 ; Look around
   DIBUTTON_FISHING_DISPLAY		EQU	00E004406h	 ; Show next on-screen display option
   DIAXIS_FISHING_ROTATE		EQU	00E024203h	 ; Turn character left / right
   DIBUTTON_FISHING_CROUCH		EQU	00E004407h	 ; Crouch/ Climb / Swim down
   DIBUTTON_FISHING_JUMP		EQU	00E004408h	 ; Jump/ Climb up / Swim up
   DIBUTTON_FISHING_LEFT_LINK		EQU	00E00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_FISHING_RIGHT_LINK		EQU	00E00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_FISHING_FORWARD_LINK	EQU	00E0144E0h	 ; Fallback move forward button
   DIBUTTON_FISHING_BACK_LINK		EQU	00E0144E8h	 ; Fallback move back button
   DIBUTTON_FISHING_ROTATE_LEFT_LINK	EQU	00E0244E4h	 ; Fallback turn body left button
   DIBUTTON_FISHING_ROTATE_RIGHT_LINK	EQU	00E0244ECh	 ; Fallback turn body right button
   DIBUTTON_FISHING_DEVICE		EQU	00E0044FEh	 ; Show input device and controls
   DIBUTTON_FISHING_PAUSE		EQU	00E0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Baseball - Batting
 ;     Batter control is primary objective  ---

   DIVIRTUAL_SPORTS_BASEBALL_BAT	EQU	00F000000h
   DIAXIS_BASEBALLB_LATERAL		EQU	00F008201h	 ; Aim left / right
   DIAXIS_BASEBALLB_MOVE		EQU	00F010202h	 ; Aim up / down
   DIBUTTON_BASEBALLB_SELECT		EQU	00F000401h	 ; cycle through swing options
   DIBUTTON_BASEBALLB_NORMAL		EQU	00F000402h	 ; normal swing
   DIBUTTON_BASEBALLB_POWER		EQU	00F000403h	 ; swing for the fence
   DIBUTTON_BASEBALLB_BUNT		EQU	00F000404h	 ; bunt
   DIBUTTON_BASEBALLB_STEAL		EQU	00F000405h	 ; Base runner attempts to steal a base
   DIBUTTON_BASEBALLB_BURST		EQU	00F000406h	 ; Base runner invokes burst of speed
   DIBUTTON_BASEBALLB_SLIDE		EQU	00F000407h	 ; Base runner slides into base
   DIBUTTON_BASEBALLB_CONTACT		EQU	00F000408h	 ; Contact swing
   DIBUTTON_BASEBALLB_MENU		EQU	00F0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_BASEBALLB_NOSTEAL		EQU	00F004409h	 ; Base runner goes back to a base
   DIBUTTON_BASEBALLB_BOX		EQU	00F00440Ah	 ; Enter or exit batting box
   DIBUTTON_BASEBALLB_LEFT_LINK 	EQU	00F00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_BASEBALLB_RIGHT_LINK	EQU	00F00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_BASEBALLB_FORWARD_LINK	EQU	00F0144E0h	 ; Fallback move forward button
   DIBUTTON_BASEBALLB_BACK_LINK 	EQU	00F0144E8h	 ; Fallback move back button
   DIBUTTON_BASEBALLB_DEVICE		EQU	00F0044FEh	 ; Show input device and controls
   DIBUTTON_BASEBALLB_PAUSE		EQU	00F0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Baseball - Pitching
 ;     Pitcher control is primary objective   ---

   DIVIRTUAL_SPORTS_BASEBALL_PITCH	EQU	010000000h
   DIAXIS_BASEBALLP_LATERAL		EQU	010008201h	 ; Aim left / right
   DIAXIS_BASEBALLP_MOVE		EQU	010010202h	 ; Aim up / down
   DIBUTTON_BASEBALLP_SELECT		EQU	010000401h	 ; cycle through pitch selections
   DIBUTTON_BASEBALLP_PITCH		EQU	010000402h	 ; throw pitch
   DIBUTTON_BASEBALLP_BASE		EQU	010000403h	 ; select base to throw to
   DIBUTTON_BASEBALLP_THROW		EQU	010000404h	 ; throw to base
   DIBUTTON_BASEBALLP_FAKE		EQU	010000405h	 ; Fake a throw to a base
   DIBUTTON_BASEBALLP_MENU		EQU	0100004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_BASEBALLP_WALK		EQU	010004406h	 ; Throw intentional walk / pitch out
   DIBUTTON_BASEBALLP_LOOK		EQU	010004407h	 ; Look at runners on bases
   DIBUTTON_BASEBALLP_LEFT_LINK 	EQU	01000C4E4h	 ; Fallback sidestep left button
   DIBUTTON_BASEBALLP_RIGHT_LINK	EQU	01000C4ECh	 ; Fallback sidestep right button
   DIBUTTON_BASEBALLP_FORWARD_LINK	EQU	0100144E0h	 ; Fallback move forward button
   DIBUTTON_BASEBALLP_BACK_LINK 	EQU	0100144E8h	 ; Fallback move back button
   DIBUTTON_BASEBALLP_DEVICE		EQU	0100044FEh	 ; Show input device and controls
   DIBUTTON_BASEBALLP_PAUSE		EQU	0100044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Baseball - Fielding
 ;     Fielder control is primary objective  ---

   DIVIRTUAL_SPORTS_BASEBALL_FIELD	EQU	011000000h
   DIAXIS_BASEBALLF_LATERAL		EQU	011008201h	 ; Aim left / right
   DIAXIS_BASEBALLF_MOVE		EQU	011010202h	 ; Aim up / down
   DIBUTTON_BASEBALLF_NEAREST		EQU	011000401h	 ; Switch to fielder nearest to the ball
   DIBUTTON_BASEBALLF_THROW1		EQU	011000402h	 ; Make conservative throw
   DIBUTTON_BASEBALLF_THROW2		EQU	011000403h	 ; Make aggressive throw
   DIBUTTON_BASEBALLF_BURST		EQU	011000404h	 ; Invoke burst of speed
   DIBUTTON_BASEBALLF_JUMP		EQU	011000405h	 ; Jump to catch ball
   DIBUTTON_BASEBALLF_DIVE		EQU	011000406h	 ; Dive to catch ball
   DIBUTTON_BASEBALLF_MENU		EQU	0110004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_BASEBALLF_SHIFTIN		EQU	011004407h	 ; Shift the infield positioning
   DIBUTTON_BASEBALLF_SHIFTOUT		EQU	011004408h	 ; Shift the outfield positioning
   DIBUTTON_BASEBALLF_AIM_LEFT_LINK	EQU	01100C4E4h	 ; Fallback aim left button
   DIBUTTON_BASEBALLF_AIM_RIGHT_LINK	EQU	01100C4ECh	 ; Fallback aim right button
   DIBUTTON_BASEBALLF_FORWARD_LINK	EQU	0110144E0h	 ; Fallback move forward button
   DIBUTTON_BASEBALLF_BACK_LINK 	EQU	0110144E8h	 ; Fallback move back button
   DIBUTTON_BASEBALLF_DEVICE		EQU	0110044FEh	 ; Show input device and controls
   DIBUTTON_BASEBALLF_PAUSE		EQU	0110044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Basketball - Offense
 ;     Offense  ---

   DIVIRTUAL_SPORTS_BASKETBALL_OFFENSE	EQU	012000000h
   DIAXIS_BBALLO_LATERAL		EQU	012008201h	 ; left / right
   DIAXIS_BBALLO_MOVE			EQU	012010202h	 ; up / down
   DIBUTTON_BBALLO_SHOOT		EQU	012000401h	 ; shoot basket
   DIBUTTON_BBALLO_DUNK 		EQU	012000402h	 ; dunk basket
   DIBUTTON_BBALLO_PASS 		EQU	012000403h	 ; throw pass
   DIBUTTON_BBALLO_FAKE 		EQU	012000404h	 ; fake shot or pass
   DIBUTTON_BBALLO_SPECIAL		EQU	012000405h	 ; apply special move
   DIBUTTON_BBALLO_PLAYER		EQU	012000406h	 ; select next player
   DIBUTTON_BBALLO_BURST		EQU	012000407h	 ; invoke burst
   DIBUTTON_BBALLO_CALL 		EQU	012000408h	 ; call for ball / pass to me
   DIBUTTON_BBALLO_MENU 		EQU	0120004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_BBALLO_GLANCE		EQU	012004601h	 ; scroll view
   DIBUTTON_BBALLO_SCREEN		EQU	012004409h	 ; Call for screen
   DIBUTTON_BBALLO_PLAY 		EQU	01200440Ah	 ; Call for specific offensive play
   DIBUTTON_BBALLO_JAB			EQU	01200440Bh	 ; Initiate fake drive to basket
   DIBUTTON_BBALLO_POST 		EQU	01200440Ch	 ; Perform post move
   DIBUTTON_BBALLO_TIMEOUT		EQU	01200440Dh	 ; Time Out
   DIBUTTON_BBALLO_SUBSTITUTE		EQU	01200440Eh	 ; substitute one player for another
   DIBUTTON_BBALLO_LEFT_LINK		EQU	01200C4E4h	 ; Fallback sidestep left button
   DIBUTTON_BBALLO_RIGHT_LINK		EQU	01200C4ECh	 ; Fallback sidestep right button
   DIBUTTON_BBALLO_FORWARD_LINK 	EQU	0120144E0h	 ; Fallback move forward button
   DIBUTTON_BBALLO_BACK_LINK		EQU	0120144E8h	 ; Fallback move back button
   DIBUTTON_BBALLO_DEVICE		EQU	0120044FEh	 ; Show input device and controls
   DIBUTTON_BBALLO_PAUSE		EQU	0120044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Basketball - Defense
 ;     Defense  ---

   DIVIRTUAL_SPORTS_BASKETBALL_DEFENSE	EQU	013000000h
   DIAXIS_BBALLD_LATERAL		EQU	013008201h	 ; left / right
   DIAXIS_BBALLD_MOVE			EQU	013010202h	 ; up / down
   DIBUTTON_BBALLD_JUMP 		EQU	013000401h	 ; jump to block shot
   DIBUTTON_BBALLD_STEAL		EQU	013000402h	 ; attempt to steal ball
   DIBUTTON_BBALLD_FAKE 		EQU	013000403h	 ; fake block or steal
   DIBUTTON_BBALLD_SPECIAL		EQU	013000404h	 ; apply special move
   DIBUTTON_BBALLD_PLAYER		EQU	013000405h	 ; select next player
   DIBUTTON_BBALLD_BURST		EQU	013000406h	 ; invoke burst
   DIBUTTON_BBALLD_PLAY 		EQU	013000407h	 ; call for specific defensive play
   DIBUTTON_BBALLD_MENU 		EQU	0130004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_BBALLD_GLANCE		EQU	013004601h	 ; scroll view
   DIBUTTON_BBALLD_TIMEOUT		EQU	013004408h	 ; Time Out
   DIBUTTON_BBALLD_SUBSTITUTE		EQU	013004409h	 ; substitute one player for another
   DIBUTTON_BBALLD_LEFT_LINK		EQU	01300C4E4h	 ; Fallback sidestep left button
   DIBUTTON_BBALLD_RIGHT_LINK		EQU	01300C4ECh	 ; Fallback sidestep right button
   DIBUTTON_BBALLD_FORWARD_LINK 	EQU	0130144E0h	 ; Fallback move forward button
   DIBUTTON_BBALLD_BACK_LINK		EQU	0130144E8h	 ; Fallback move back button
   DIBUTTON_BBALLD_DEVICE		EQU	0130044FEh	 ; Show input device and controls
   DIBUTTON_BBALLD_PAUSE		EQU	0130044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Football - Play
 ;     Play selection  ---

   DIVIRTUAL_SPORTS_FOOTBALL_FIELD	EQU	014000000h
   DIBUTTON_FOOTBALLP_PLAY		EQU	014000401h	 ; cycle through available plays
   DIBUTTON_FOOTBALLP_SELECT		EQU	014000402h	 ; select play
   DIBUTTON_FOOTBALLP_HELP		EQU	014000403h	 ; Bring up pop-up help
   DIBUTTON_FOOTBALLP_MENU		EQU	0140004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_FOOTBALLP_DEVICE		EQU	0140044FEh	 ; Show input device and controls
   DIBUTTON_FOOTBALLP_PAUSE		EQU	0140044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Football - QB
 ;     Offense: Quarterback / Kicker  ---

   DIVIRTUAL_SPORTS_FOOTBALL_QBCK	EQU	015000000h
   DIAXIS_FOOTBALLQ_LATERAL		EQU	015008201h	 ; Move / Aim: left / right
   DIAXIS_FOOTBALLQ_MOVE		EQU	015010202h	 ; Move / Aim: up / down
   DIBUTTON_FOOTBALLQ_SELECT		EQU	015000401h	 ; Select
   DIBUTTON_FOOTBALLQ_SNAP		EQU	015000402h	 ; snap ball - start play
   DIBUTTON_FOOTBALLQ_JUMP		EQU	015000403h	 ; jump over defender
   DIBUTTON_FOOTBALLQ_SLIDE		EQU	015000404h	 ; Dive/Slide
   DIBUTTON_FOOTBALLQ_PASS		EQU	015000405h	 ; throws pass to receiver
   DIBUTTON_FOOTBALLQ_FAKE		EQU	015000406h	 ; pump fake pass or fake kick
   DIBUTTON_FOOTBALLQ_MENU		EQU	0150004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_FOOTBALLQ_FAKESNAP		EQU	015004407h	 ; Fake snap
   DIBUTTON_FOOTBALLQ_MOTION		EQU	015004408h	 ; Send receivers in motion
   DIBUTTON_FOOTBALLQ_AUDIBLE		EQU	015004409h	 ; Change offensive play at line of scrimmage
   DIBUTTON_FOOTBALLQ_LEFT_LINK 	EQU	01500C4E4h	 ; Fallback sidestep left button
   DIBUTTON_FOOTBALLQ_RIGHT_LINK	EQU	01500C4ECh	 ; Fallback sidestep right button
   DIBUTTON_FOOTBALLQ_FORWARD_LINK	EQU	0150144E0h	 ; Fallback move forward button
   DIBUTTON_FOOTBALLQ_BACK_LINK 	EQU	0150144E8h	 ; Fallback move back button
   DIBUTTON_FOOTBALLQ_DEVICE		EQU	0150044FEh	 ; Show input device and controls
   DIBUTTON_FOOTBALLQ_PAUSE		EQU	0150044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Football - Offense
 ;     Offense - Runner  ---

   DIVIRTUAL_SPORTS_FOOTBALL_OFFENSE	EQU	016000000h
   DIAXIS_FOOTBALLO_LATERAL		EQU	016008201h	 ; Move / Aim: left / right
   DIAXIS_FOOTBALLO_MOVE		EQU	016010202h	 ; Move / Aim: up / down
   DIBUTTON_FOOTBALLO_JUMP		EQU	016000401h	 ; jump or hurdle over defender
   DIBUTTON_FOOTBALLO_LEFTARM		EQU	016000402h	 ; holds out left arm
   DIBUTTON_FOOTBALLO_RIGHTARM		EQU	016000403h	 ; holds out right arm
   DIBUTTON_FOOTBALLO_THROW		EQU	016000404h	 ; throw pass or lateral ball to another runner
   DIBUTTON_FOOTBALLO_SPIN		EQU	016000405h	 ; Spin to avoid defenders
   DIBUTTON_FOOTBALLO_MENU		EQU	0160004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_FOOTBALLO_JUKE		EQU	016004406h	 ; Use special move to avoid defenders
   DIBUTTON_FOOTBALLO_SHOULDER		EQU	016004407h	 ; Lower shoulder to run over defenders
   DIBUTTON_FOOTBALLO_TURBO		EQU	016004408h	 ; Speed burst past defenders
   DIBUTTON_FOOTBALLO_DIVE		EQU	016004409h	 ; Dive over defenders
   DIBUTTON_FOOTBALLO_ZOOM		EQU	01600440Ah	 ; Zoom view in / out
   DIBUTTON_FOOTBALLO_SUBSTITUTE	EQU	01600440Bh	 ; substitute one player for another
   DIBUTTON_FOOTBALLO_LEFT_LINK 	EQU	01600C4E4h	 ; Fallback sidestep left button
   DIBUTTON_FOOTBALLO_RIGHT_LINK	EQU	01600C4ECh	 ; Fallback sidestep right button
   DIBUTTON_FOOTBALLO_FORWARD_LINK	EQU	0160144E0h	 ; Fallback move forward button
   DIBUTTON_FOOTBALLO_BACK_LINK 	EQU	0160144E8h	 ; Fallback move back button
   DIBUTTON_FOOTBALLO_DEVICE		EQU	0160044FEh	 ; Show input device and controls
   DIBUTTON_FOOTBALLO_PAUSE		EQU	0160044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Football - Defense
 ;     Defense     ---

   DIVIRTUAL_SPORTS_FOOTBALL_DEFENSE	EQU	017000000h
   DIAXIS_FOOTBALLD_LATERAL		EQU	017008201h	 ; Move / Aim: left / right
   DIAXIS_FOOTBALLD_MOVE		EQU	017010202h	 ; Move / Aim: up / down
   DIBUTTON_FOOTBALLD_PLAY		EQU	017000401h	 ; cycle through available plays
   DIBUTTON_FOOTBALLD_SELECT		EQU	017000402h	 ; select player closest to the ball
   DIBUTTON_FOOTBALLD_JUMP		EQU	017000403h	 ; jump to intercept or block
   DIBUTTON_FOOTBALLD_TACKLE		EQU	017000404h	 ; tackler runner
   DIBUTTON_FOOTBALLD_FAKE		EQU	017000405h	 ; hold down to fake tackle or intercept
   DIBUTTON_FOOTBALLD_SUPERTACKLE	EQU	017000406h	 ; Initiate special tackle
   DIBUTTON_FOOTBALLD_MENU		EQU	0170004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_FOOTBALLD_SPIN		EQU	017004407h	 ; Spin to beat offensive line
   DIBUTTON_FOOTBALLD_SWIM		EQU	017004408h	 ; Swim to beat the offensive line
   DIBUTTON_FOOTBALLD_BULLRUSH		EQU	017004409h	 ; Bull rush the offensive line
   DIBUTTON_FOOTBALLD_RIP		EQU	01700440Ah	 ; Rip the offensive line
   DIBUTTON_FOOTBALLD_AUDIBLE		EQU	01700440Bh	 ; Change defensive play at the line of scrimmage
   DIBUTTON_FOOTBALLD_ZOOM		EQU	01700440Ch	 ; Zoom view in / out
   DIBUTTON_FOOTBALLD_SUBSTITUTE	EQU	01700440Dh	 ; substitute one player for another
   DIBUTTON_FOOTBALLD_LEFT_LINK 	EQU	01700C4E4h	 ; Fallback sidestep left button
   DIBUTTON_FOOTBALLD_RIGHT_LINK	EQU	01700C4ECh	 ; Fallback sidestep right button
   DIBUTTON_FOOTBALLD_FORWARD_LINK	EQU	0170144E0h	 ; Fallback move forward button
   DIBUTTON_FOOTBALLD_BACK_LINK 	EQU	0170144E8h	 ; Fallback move back button
   DIBUTTON_FOOTBALLD_DEVICE		EQU	0170044FEh	 ; Show input device and controls
   DIBUTTON_FOOTBALLD_PAUSE		EQU	0170044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Golf
 ;                               ---

   DIVIRTUAL_SPORTS_GOLF		EQU	018000000h
   DIAXIS_GOLF_LATERAL			EQU	018008201h	 ; Move / Aim: left / right
   DIAXIS_GOLF_MOVE			EQU	018010202h	 ; Move / Aim: up / down
   DIBUTTON_GOLF_SWING			EQU	018000401h	 ; swing club
   DIBUTTON_GOLF_SELECT 		EQU	018000402h	 ; cycle between: club / swing strength / ball arc / ball spin
   DIBUTTON_GOLF_UP			EQU	018000403h	 ; increase selection
   DIBUTTON_GOLF_DOWN			EQU	018000404h	 ; decrease selection
   DIBUTTON_GOLF_TERRAIN		EQU	018000405h	 ; shows terrain detail
   DIBUTTON_GOLF_FLYBY			EQU	018000406h	 ; view the hole via a flyby
   DIBUTTON_GOLF_MENU			EQU	0180004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_GOLF_SCROLL		EQU	018004601h	 ; scroll view
   DIBUTTON_GOLF_ZOOM			EQU	018004407h	 ; Zoom view in / out
   DIBUTTON_GOLF_TIMEOUT		EQU	018004408h	 ; Call for time out
   DIBUTTON_GOLF_SUBSTITUTE		EQU	018004409h	 ; substitute one player for another
   DIBUTTON_GOLF_LEFT_LINK		EQU	01800C4E4h	 ; Fallback sidestep left button
   DIBUTTON_GOLF_RIGHT_LINK		EQU	01800C4ECh	 ; Fallback sidestep right button
   DIBUTTON_GOLF_FORWARD_LINK		EQU	0180144E0h	 ; Fallback move forward button
   DIBUTTON_GOLF_BACK_LINK		EQU	0180144E8h	 ; Fallback move back button
   DIBUTTON_GOLF_DEVICE 		EQU	0180044FEh	 ; Show input device and controls
   DIBUTTON_GOLF_PAUSE			EQU	0180044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Hockey - Offense
 ;     Offense       ---

   DIVIRTUAL_SPORTS_HOCKEY_OFFENSE	EQU	019000000h
   DIAXIS_HOCKEYO_LATERAL		EQU	019008201h	 ; Move / Aim: left / right
   DIAXIS_HOCKEYO_MOVE			EQU	019010202h	 ; Move / Aim: up / down
   DIBUTTON_HOCKEYO_SHOOT		EQU	019000401h	 ; Shoot
   DIBUTTON_HOCKEYO_PASS		EQU	019000402h	 ; pass the puck
   DIBUTTON_HOCKEYO_BURST		EQU	019000403h	 ; invoke speed burst
   DIBUTTON_HOCKEYO_SPECIAL		EQU	019000404h	 ; invoke special move
   DIBUTTON_HOCKEYO_FAKE		EQU	019000405h	 ; hold down to fake pass or kick
   DIBUTTON_HOCKEYO_MENU		EQU	0190004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_HOCKEYO_SCROLL		EQU	019004601h	 ; scroll view
   DIBUTTON_HOCKEYO_ZOOM		EQU	019004406h	 ; Zoom view in / out
   DIBUTTON_HOCKEYO_STRATEGY		EQU	019004407h	 ; Invoke coaching menu for strategy help
   DIBUTTON_HOCKEYO_TIMEOUT		EQU	019004408h	 ; Call for time out
   DIBUTTON_HOCKEYO_SUBSTITUTE		EQU	019004409h	 ; substitute one player for another
   DIBUTTON_HOCKEYO_LEFT_LINK		EQU	01900C4E4h	 ; Fallback sidestep left button
   DIBUTTON_HOCKEYO_RIGHT_LINK		EQU	01900C4ECh	 ; Fallback sidestep right button
   DIBUTTON_HOCKEYO_FORWARD_LINK	EQU	0190144E0h	 ; Fallback move forward button
   DIBUTTON_HOCKEYO_BACK_LINK		EQU	0190144E8h	 ; Fallback move back button
   DIBUTTON_HOCKEYO_DEVICE		EQU	0190044FEh	 ; Show input device and controls
   DIBUTTON_HOCKEYO_PAUSE		EQU	0190044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Hockey - Defense
 ;     Defense       ---

   DIVIRTUAL_SPORTS_HOCKEY_DEFENSE	EQU	01A000000h
   DIAXIS_HOCKEYD_LATERAL		EQU	01A008201h	 ; Move / Aim: left / right
   DIAXIS_HOCKEYD_MOVE			EQU	01A010202h	 ; Move / Aim: up / down
   DIBUTTON_HOCKEYD_PLAYER		EQU	01A000401h	 ; control player closest to the puck
   DIBUTTON_HOCKEYD_STEAL		EQU	01A000402h	 ; attempt steal
   DIBUTTON_HOCKEYD_BURST		EQU	01A000403h	 ; speed burst or body check
   DIBUTTON_HOCKEYD_BLOCK		EQU	01A000404h	 ; block puck
   DIBUTTON_HOCKEYD_FAKE		EQU	01A000405h	 ; hold down to fake tackle or intercept
   DIBUTTON_HOCKEYD_MENU		EQU	01A0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_HOCKEYD_SCROLL		EQU	01A004601h	 ; scroll view
   DIBUTTON_HOCKEYD_ZOOM		EQU	01A004406h	 ; Zoom view in / out
   DIBUTTON_HOCKEYD_STRATEGY		EQU	01A004407h	 ; Invoke coaching menu for strategy help
   DIBUTTON_HOCKEYD_TIMEOUT		EQU	01A004408h	 ; Call for time out
   DIBUTTON_HOCKEYD_SUBSTITUTE		EQU	01A004409h	 ; substitute one player for another
   DIBUTTON_HOCKEYD_LEFT_LINK		EQU	01A00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_HOCKEYD_RIGHT_LINK		EQU	01A00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_HOCKEYD_FORWARD_LINK	EQU	01A0144E0h	 ; Fallback move forward button
   DIBUTTON_HOCKEYD_BACK_LINK		EQU	01A0144E8h	 ; Fallback move back button
   DIBUTTON_HOCKEYD_DEVICE		EQU	01A0044FEh	 ; Show input device and controls
   DIBUTTON_HOCKEYD_PAUSE		EQU	01A0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Hockey - Goalie
 ;     Goal tending  ---

   DIVIRTUAL_SPORTS_HOCKEY_GOALIE	EQU	01B000000h
   DIAXIS_HOCKEYG_LATERAL		EQU	01B008201h	 ; Move / Aim: left / right
   DIAXIS_HOCKEYG_MOVE			EQU	01B010202h	 ; Move / Aim: up / down
   DIBUTTON_HOCKEYG_PASS		EQU	01B000401h	 ; pass puck
   DIBUTTON_HOCKEYG_POKE		EQU	01B000402h	 ; poke / check / hack
   DIBUTTON_HOCKEYG_STEAL		EQU	01B000403h	 ; attempt steal
   DIBUTTON_HOCKEYG_BLOCK		EQU	01B000404h	 ; block puck
   DIBUTTON_HOCKEYG_MENU		EQU	01B0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_HOCKEYG_SCROLL		EQU	01B004601h	 ; scroll view
   DIBUTTON_HOCKEYG_ZOOM		EQU	01B004405h	 ; Zoom view in / out
   DIBUTTON_HOCKEYG_STRATEGY		EQU	01B004406h	 ; Invoke coaching menu for strategy help
   DIBUTTON_HOCKEYG_TIMEOUT		EQU	01B004407h	 ; Call for time out
   DIBUTTON_HOCKEYG_SUBSTITUTE		EQU	01B004408h	 ; substitute one player for another
   DIBUTTON_HOCKEYG_LEFT_LINK		EQU	01B00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_HOCKEYG_RIGHT_LINK		EQU	01B00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_HOCKEYG_FORWARD_LINK	EQU	01B0144E0h	 ; Fallback move forward button
   DIBUTTON_HOCKEYG_BACK_LINK		EQU	01B0144E8h	 ; Fallback move back button
   DIBUTTON_HOCKEYG_DEVICE		EQU	01B0044FEh	 ; Show input device and controls
   DIBUTTON_HOCKEYG_PAUSE		EQU	01B0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Mountain Biking
 ;                    ---

   DIVIRTUAL_SPORTS_BIKING_MOUNTAIN	EQU	01C000000h
   DIAXIS_BIKINGM_TURN			EQU	01C008201h	 ; left / right
   DIAXIS_BIKINGM_PEDAL 		EQU	01C010202h	 ; Pedal faster / slower / brake
   DIBUTTON_BIKINGM_JUMP		EQU	01C000401h	 ; jump over obstacle
   DIBUTTON_BIKINGM_CAMERA		EQU	01C000402h	 ; switch camera view
   DIBUTTON_BIKINGM_SPECIAL1		EQU	01C000403h	 ; perform first special move
   DIBUTTON_BIKINGM_SELECT		EQU	01C000404h	 ; Select
   DIBUTTON_BIKINGM_SPECIAL2		EQU	01C000405h	 ; perform second special move
   DIBUTTON_BIKINGM_MENU		EQU	01C0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_BIKINGM_SCROLL		EQU	01C004601h	 ; scroll view
   DIBUTTON_BIKINGM_ZOOM		EQU	01C004406h	 ; Zoom view in / out
   DIAXIS_BIKINGM_BRAKE 		EQU	01C044203h	 ; Brake axis
   DIBUTTON_BIKINGM_LEFT_LINK		EQU	01C00C4E4h	 ; Fallback turn left button
   DIBUTTON_BIKINGM_RIGHT_LINK		EQU	01C00C4ECh	 ; Fallback turn right button
   DIBUTTON_BIKINGM_FASTER_LINK 	EQU	01C0144E0h	 ; Fallback pedal faster button
   DIBUTTON_BIKINGM_SLOWER_LINK 	EQU	01C0144E8h	 ; Fallback pedal slower button
   DIBUTTON_BIKINGM_BRAKE_BUTTON_LINK	EQU	01C0444E8h	 ; Fallback brake button
   DIBUTTON_BIKINGM_DEVICE		EQU	01C0044FEh	 ; Show input device and controls
   DIBUTTON_BIKINGM_PAUSE		EQU	01C0044FCh	 ; Start / Pause / Restart game

 ;--- Sports: Skiing / Snowboarding / Skateboarding
 ;       ---

   DIVIRTUAL_SPORTS_SKIING		EQU	01D000000h
   DIAXIS_SKIING_TURN			EQU	01D008201h	 ; left / right
   DIAXIS_SKIING_SPEED			EQU	01D010202h	 ; faster / slower
   DIBUTTON_SKIING_JUMP 		EQU	01D000401h	 ; Jump
   DIBUTTON_SKIING_CROUCH		EQU	01D000402h	 ; crouch down
   DIBUTTON_SKIING_CAMERA		EQU	01D000403h	 ; switch camera view
   DIBUTTON_SKIING_SPECIAL1		EQU	01D000404h	 ; perform first special move
   DIBUTTON_SKIING_SELECT		EQU	01D000405h	 ; Select
   DIBUTTON_SKIING_SPECIAL2		EQU	01D000406h	 ; perform second special move
   DIBUTTON_SKIING_MENU 		EQU	01D0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_SKIING_GLANCE		EQU	01D004601h	 ; scroll view
   DIBUTTON_SKIING_ZOOM 		EQU	01D004407h	 ; Zoom view in / out
   DIBUTTON_SKIING_LEFT_LINK		EQU	01D00C4E4h	 ; Fallback turn left button
   DIBUTTON_SKIING_RIGHT_LINK		EQU	01D00C4ECh	 ; Fallback turn right button
   DIBUTTON_SKIING_FASTER_LINK		EQU	01D0144E0h	 ; Fallback increase speed button
   DIBUTTON_SKIING_SLOWER_LINK		EQU	01D0144E8h	 ; Fallback decrease speed button
   DIBUTTON_SKIING_DEVICE		EQU	01D0044FEh	 ; Show input device and controls
   DIBUTTON_SKIING_PAUSE		EQU	01D0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Soccer - Offense
 ;     Offense       ---

   DIVIRTUAL_SPORTS_SOCCER_OFFENSE	EQU	01E000000h
   DIAXIS_SOCCERO_LATERAL		EQU	01E008201h	 ; Move / Aim: left / right
   DIAXIS_SOCCERO_MOVE			EQU	01E010202h	 ; Move / Aim: up / down
   DIAXIS_SOCCERO_BEND			EQU	01E018203h	 ; Bend to soccer shot/pass
   DIBUTTON_SOCCERO_SHOOT		EQU	01E000401h	 ; Shoot the ball
   DIBUTTON_SOCCERO_PASS		EQU	01E000402h	 ; Pass
   DIBUTTON_SOCCERO_FAKE		EQU	01E000403h	 ; Fake
   DIBUTTON_SOCCERO_PLAYER		EQU	01E000404h	 ; Select next player
   DIBUTTON_SOCCERO_SPECIAL1		EQU	01E000405h	 ; Apply special move
   DIBUTTON_SOCCERO_SELECT		EQU	01E000406h	 ; Select special move
   DIBUTTON_SOCCERO_MENU		EQU	01E0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_SOCCERO_GLANCE		EQU	01E004601h	 ; scroll view
   DIBUTTON_SOCCERO_SUBSTITUTE		EQU	01E004407h	 ; Substitute one player for another
   DIBUTTON_SOCCERO_SHOOTLOW		EQU	01E004408h	 ; Shoot the ball low
   DIBUTTON_SOCCERO_SHOOTHIGH		EQU	01E004409h	 ; Shoot the ball high
   DIBUTTON_SOCCERO_PASSTHRU		EQU	01E00440Ah	 ; Make a thru pass
   DIBUTTON_SOCCERO_SPRINT		EQU	01E00440Bh	 ; Sprint / turbo boost
   DIBUTTON_SOCCERO_CONTROL		EQU	01E00440Ch	 ; Obtain control of the ball
   DIBUTTON_SOCCERO_HEAD		EQU	01E00440Dh	 ; Attempt to head the ball
   DIBUTTON_SOCCERO_LEFT_LINK		EQU	01E00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_SOCCERO_RIGHT_LINK		EQU	01E00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_SOCCERO_FORWARD_LINK	EQU	01E0144E0h	 ; Fallback move forward button
   DIBUTTON_SOCCERO_BACK_LINK		EQU	01E0144E8h	 ; Fallback move back button
   DIBUTTON_SOCCERO_DEVICE		EQU	01E0044FEh	 ; Show input device and controls
   DIBUTTON_SOCCERO_PAUSE		EQU	01E0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Soccer - Defense
 ;     Defense       ---

   DIVIRTUAL_SPORTS_SOCCER_DEFENSE	EQU	01F000000h
   DIAXIS_SOCCERD_LATERAL		EQU	01F008201h	 ; Move / Aim: left / right
   DIAXIS_SOCCERD_MOVE			EQU	01F010202h	 ; Move / Aim: up / down
   DIBUTTON_SOCCERD_BLOCK		EQU	01F000401h	 ; Attempt to block shot
   DIBUTTON_SOCCERD_STEAL		EQU	01F000402h	 ; Attempt to steal ball
   DIBUTTON_SOCCERD_FAKE		EQU	01F000403h	 ; Fake a block or a steal
   DIBUTTON_SOCCERD_PLAYER		EQU	01F000404h	 ; Select next player
   DIBUTTON_SOCCERD_SPECIAL		EQU	01F000405h	 ; Apply special move
   DIBUTTON_SOCCERD_SELECT		EQU	01F000406h	 ; Select special move
   DIBUTTON_SOCCERD_SLIDE		EQU	01F000407h	 ; Attempt a slide tackle
   DIBUTTON_SOCCERD_MENU		EQU	01F0004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_SOCCERD_GLANCE		EQU	01F004601h	 ; scroll view
   DIBUTTON_SOCCERD_FOUL		EQU	01F004408h	 ; Initiate a foul / hard-foul
   DIBUTTON_SOCCERD_HEAD		EQU	01F004409h	 ; Attempt a Header
   DIBUTTON_SOCCERD_CLEAR		EQU	01F00440Ah	 ; Attempt to clear the ball down the field
   DIBUTTON_SOCCERD_GOALIECHARGE	EQU	01F00440Bh	 ; Make the goalie charge out of the box
   DIBUTTON_SOCCERD_SUBSTITUTE		EQU	01F00440Ch	 ; Substitute one player for another
   DIBUTTON_SOCCERD_LEFT_LINK		EQU	01F00C4E4h	 ; Fallback sidestep left button
   DIBUTTON_SOCCERD_RIGHT_LINK		EQU	01F00C4ECh	 ; Fallback sidestep right button
   DIBUTTON_SOCCERD_FORWARD_LINK	EQU	01F0144E0h	 ; Fallback move forward button
   DIBUTTON_SOCCERD_BACK_LINK		EQU	01F0144E8h	 ; Fallback move back button
   DIBUTTON_SOCCERD_DEVICE		EQU	01F0044FEh	 ; Show input device and controls
   DIBUTTON_SOCCERD_PAUSE		EQU	01F0044FCh	 ; Start / Pause / Restart game

 ;--- Sports - Racquet
 ;     Tennis - Table-Tennis - Squash   ---

   DIVIRTUAL_SPORTS_RACQUET		EQU	020000000h
   DIAXIS_RACQUET_LATERAL		EQU	020008201h	 ; Move / Aim: left / right
   DIAXIS_RACQUET_MOVE			EQU	020010202h	 ; Move / Aim: up / down
   DIBUTTON_RACQUET_SWING		EQU	020000401h	 ; Swing racquet
   DIBUTTON_RACQUET_BACKSWING		EQU	020000402h	 ; Swing backhand
   DIBUTTON_RACQUET_SMASH		EQU	020000403h	 ; Smash shot
   DIBUTTON_RACQUET_SPECIAL		EQU	020000404h	 ; Special shot
   DIBUTTON_RACQUET_SELECT		EQU	020000405h	 ; Select special shot
   DIBUTTON_RACQUET_MENU		EQU	0200004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_RACQUET_GLANCE		EQU	020004601h	 ; scroll view
   DIBUTTON_RACQUET_TIMEOUT		EQU	020004406h	 ; Call for time out
   DIBUTTON_RACQUET_SUBSTITUTE		EQU	020004407h	 ; Substitute one player for another
   DIBUTTON_RACQUET_LEFT_LINK		EQU	02000C4E4h	 ; Fallback sidestep left button
   DIBUTTON_RACQUET_RIGHT_LINK		EQU	02000C4ECh	 ; Fallback sidestep right button
   DIBUTTON_RACQUET_FORWARD_LINK	EQU	0200144E0h	 ; Fallback move forward button
   DIBUTTON_RACQUET_BACK_LINK		EQU	0200144E8h	 ; Fallback move back button
   DIBUTTON_RACQUET_DEVICE		EQU	0200044FEh	 ; Show input device and controls
   DIBUTTON_RACQUET_PAUSE		EQU	0200044FCh	 ; Start / Pause / Restart game

 ;--- Arcade- 2D
 ;     Side to Side movement        ---

   DIVIRTUAL_ARCADE_SIDE2SIDE		EQU	021000000h
   DIAXIS_ARCADES_LATERAL		EQU	021008201h	 ; left / right
   DIAXIS_ARCADES_MOVE			EQU	021010202h	 ; up / down
   DIBUTTON_ARCADES_THROW		EQU	021000401h	 ; throw object
   DIBUTTON_ARCADES_CARRY		EQU	021000402h	 ; carry object
   DIBUTTON_ARCADES_ATTACK		EQU	021000403h	 ; attack
   DIBUTTON_ARCADES_SPECIAL		EQU	021000404h	 ; apply special move
   DIBUTTON_ARCADES_SELECT		EQU	021000405h	 ; select special move
   DIBUTTON_ARCADES_MENU		EQU	0210004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_ARCADES_VIEW		EQU	021004601h	 ; scroll view left / right / up / down
   DIBUTTON_ARCADES_LEFT_LINK		EQU	02100C4E4h	 ; Fallback sidestep left button
   DIBUTTON_ARCADES_RIGHT_LINK		EQU	02100C4ECh	 ; Fallback sidestep right button
   DIBUTTON_ARCADES_FORWARD_LINK	EQU	0210144E0h	 ; Fallback move forward button
   DIBUTTON_ARCADES_BACK_LINK		EQU	0210144E8h	 ; Fallback move back button
   DIBUTTON_ARCADES_VIEW_UP_LINK	EQU	02107C4E0h	 ; Fallback scroll view up button
   DIBUTTON_ARCADES_VIEW_DOWN_LINK	EQU	02107C4E8h	 ; Fallback scroll view down button
   DIBUTTON_ARCADES_VIEW_LEFT_LINK	EQU	02107C4E4h	 ; Fallback scroll view left button
   DIBUTTON_ARCADES_VIEW_RIGHT_LINK	EQU	02107C4ECh	 ; Fallback scroll view right button
   DIBUTTON_ARCADES_DEVICE		EQU	0210044FEh	 ; Show input device and controls
   DIBUTTON_ARCADES_PAUSE		EQU	0210044FCh	 ; Start / Pause / Restart game

 ;--- Arcade - Platform Game
 ;     Character moves around on screen  ---

   DIVIRTUAL_ARCADE_PLATFORM		EQU	022000000h
   DIAXIS_ARCADEP_LATERAL		EQU	022008201h	 ; Left / right
   DIAXIS_ARCADEP_MOVE			EQU	022010202h	 ; Up / down
   DIBUTTON_ARCADEP_JUMP		EQU	022000401h	 ; Jump
   DIBUTTON_ARCADEP_FIRE		EQU	022000402h	 ; Fire
   DIBUTTON_ARCADEP_CROUCH		EQU	022000403h	 ; Crouch
   DIBUTTON_ARCADEP_SPECIAL		EQU	022000404h	 ; Apply special move
   DIBUTTON_ARCADEP_SELECT		EQU	022000405h	 ; Select special move
   DIBUTTON_ARCADEP_MENU		EQU	0220004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_ARCADEP_VIEW		EQU	022004601h	 ; Scroll view
   DIBUTTON_ARCADEP_FIRESECONDARY	EQU	022004406h	 ; Alternative fire button
   DIBUTTON_ARCADEP_LEFT_LINK		EQU	02200C4E4h	 ; Fallback sidestep left button
   DIBUTTON_ARCADEP_RIGHT_LINK		EQU	02200C4ECh	 ; Fallback sidestep right button
   DIBUTTON_ARCADEP_FORWARD_LINK	EQU	0220144E0h	 ; Fallback move forward button
   DIBUTTON_ARCADEP_BACK_LINK		EQU	0220144E8h	 ; Fallback move back button
   DIBUTTON_ARCADEP_VIEW_UP_LINK	EQU	02207C4E0h	 ; Fallback scroll view up button
   DIBUTTON_ARCADEP_VIEW_DOWN_LINK	EQU	02207C4E8h	 ; Fallback scroll view down button
   DIBUTTON_ARCADEP_VIEW_LEFT_LINK	EQU	02207C4E4h	 ; Fallback scroll view left button
   DIBUTTON_ARCADEP_VIEW_RIGHT_LINK	EQU	02207C4ECh	 ; Fallback scroll view right button
   DIBUTTON_ARCADEP_DEVICE		EQU	0220044FEh	 ; Show input device and controls
   DIBUTTON_ARCADEP_PAUSE		EQU	0220044FCh	 ; Start / Pause / Restart game

 ;--- CAD - 2D Object Control
 ;     Controls to select and move objects in 2D  ---

   DIVIRTUAL_CAD_2DCONTROL		EQU	023000000h
   DIAXIS_2DCONTROL_LATERAL		EQU	023008201h	 ; Move view left / right
   DIAXIS_2DCONTROL_MOVE		EQU	023010202h	 ; Move view up / down
   DIAXIS_2DCONTROL_INOUT		EQU	023018203h	 ; Zoom - in / out
   DIBUTTON_2DCONTROL_SELECT		EQU	023000401h	 ; Select Object
   DIBUTTON_2DCONTROL_SPECIAL1		EQU	023000402h	 ; Do first special operation
   DIBUTTON_2DCONTROL_SPECIAL		EQU	023000403h	 ; Select special operation
   DIBUTTON_2DCONTROL_SPECIAL2		EQU	023000404h	 ; Do second special operation
   DIBUTTON_2DCONTROL_MENU		EQU	0230004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_2DCONTROL_HATSWITCH	EQU	023004601h	 ; Hat switch
   DIAXIS_2DCONTROL_ROTATEZ		EQU	023024204h	 ; Rotate view clockwise / counterclockwise
   DIBUTTON_2DCONTROL_DISPLAY		EQU	023004405h	 ; Shows next on-screen display options
   DIBUTTON_2DCONTROL_DEVICE		EQU	0230044FEh	 ; Show input device and controls
   DIBUTTON_2DCONTROL_PAUSE		EQU	0230044FCh	 ; Start / Pause / Restart game

 ;--- CAD - 3D object control
 ;     Controls to select and move objects within a 3D environment  ---

   DIVIRTUAL_CAD_3DCONTROL		EQU	024000000h
   DIAXIS_3DCONTROL_LATERAL		EQU	024008201h	 ; Move view left / right
   DIAXIS_3DCONTROL_MOVE		EQU	024010202h	 ; Move view up / down
   DIAXIS_3DCONTROL_INOUT		EQU	024018203h	 ; Zoom - in / out
   DIBUTTON_3DCONTROL_SELECT		EQU	024000401h	 ; Select Object
   DIBUTTON_3DCONTROL_SPECIAL1		EQU	024000402h	 ; Do first special operation
   DIBUTTON_3DCONTROL_SPECIAL		EQU	024000403h	 ; Select special operation
   DIBUTTON_3DCONTROL_SPECIAL2		EQU	024000404h	 ; Do second special operation
   DIBUTTON_3DCONTROL_MENU		EQU	0240004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_3DCONTROL_HATSWITCH	EQU	024004601h	 ; Hat switch
   DIAXIS_3DCONTROL_ROTATEX		EQU	024034204h	 ; Rotate view forward or up / backward or down
   DIAXIS_3DCONTROL_ROTATEY		EQU	02402C205h	 ; Rotate view clockwise / counterclockwise
   DIAXIS_3DCONTROL_ROTATEZ		EQU	024024206h	 ; Rotate view left / right
   DIBUTTON_3DCONTROL_DISPLAY		EQU	024004405h	 ; Show next on-screen display options
   DIBUTTON_3DCONTROL_DEVICE		EQU	0240044FEh	 ; Show input device and controls
   DIBUTTON_3DCONTROL_PAUSE		EQU	0240044FCh	 ; Start / Pause / Restart game

 ;--- CAD - 3D Navigation - Fly through
 ;     Controls for 3D modeling  ---

   DIVIRTUAL_CAD_FLYBY			EQU	025000000h
   DIAXIS_CADF_LATERAL			EQU	025008201h	 ; move view left / right
   DIAXIS_CADF_MOVE			EQU	025010202h	 ; move view up / down
   DIAXIS_CADF_INOUT			EQU	025018203h	 ; in / out
   DIBUTTON_CADF_SELECT 		EQU	025000401h	 ; Select Object
   DIBUTTON_CADF_SPECIAL1		EQU	025000402h	 ; do first special operation
   DIBUTTON_CADF_SPECIAL		EQU	025000403h	 ; Select special operation
   DIBUTTON_CADF_SPECIAL2		EQU	025000404h	 ; do second special operation
   DIBUTTON_CADF_MENU			EQU	0250004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_CADF_HATSWITCH		EQU	025004601h	 ; Hat switch
   DIAXIS_CADF_ROTATEX			EQU	025034204h	 ; Rotate view forward or up / backward or down
   DIAXIS_CADF_ROTATEY			EQU	02502C205h	 ; Rotate view clockwise / counterclockwise
   DIAXIS_CADF_ROTATEZ			EQU	025024206h	 ; Rotate view left / right
   DIBUTTON_CADF_DISPLAY		EQU	025004405h	 ; shows next on-screen display options
   DIBUTTON_CADF_DEVICE 		EQU	0250044FEh	 ; Show input device and controls
   DIBUTTON_CADF_PAUSE			EQU	0250044FCh	 ; Start / Pause / Restart game

 ;--- CAD - 3D Model Control
 ;     Controls for 3D modeling  ---

   DIVIRTUAL_CAD_MODEL			EQU	026000000h
   DIAXIS_CADM_LATERAL			EQU	026008201h	 ; move view left / right
   DIAXIS_CADM_MOVE			EQU	026010202h	 ; move view up / down
   DIAXIS_CADM_INOUT			EQU	026018203h	 ; in / out
   DIBUTTON_CADM_SELECT 		EQU	026000401h	 ; Select Object
   DIBUTTON_CADM_SPECIAL1		EQU	026000402h	 ; do first special operation
   DIBUTTON_CADM_SPECIAL		EQU	026000403h	 ; Select special operation
   DIBUTTON_CADM_SPECIAL2		EQU	026000404h	 ; do second special operation
   DIBUTTON_CADM_MENU			EQU	0260004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIHATSWITCH_CADM_HATSWITCH		EQU	026004601h	 ; Hat switch
   DIAXIS_CADM_ROTATEX			EQU	026034204h	 ; Rotate view forward or up / backward or down
   DIAXIS_CADM_ROTATEY			EQU	02602C205h	 ; Rotate view clockwise / counterclockwise
   DIAXIS_CADM_ROTATEZ			EQU	026024206h	 ; Rotate view left / right
   DIBUTTON_CADM_DISPLAY		EQU	026004405h	 ; shows next on-screen display options
   DIBUTTON_CADM_DEVICE 		EQU	0260044FEh	 ; Show input device and controls
   DIBUTTON_CADM_PAUSE			EQU	0260044FCh	 ; Start / Pause / Restart game

 ;--- Control - Media Equipment
 ;     Remote        ---

   DIVIRTUAL_REMOTE_CONTROL		EQU	027000000h
   DIAXIS_REMOTE_SLIDER 		EQU	027050201h	 ; Slider for adjustment: volume / color / bass / etc
   DIBUTTON_REMOTE_MUTE 		EQU	027000401h	 ; Set volume on current device to zero
   DIBUTTON_REMOTE_SELECT		EQU	027000402h	 ; Next/previous: channel/ track / chapter / picture / station
   DIBUTTON_REMOTE_PLAY 		EQU	027002403h	 ; Start or pause entertainment on current device
   DIBUTTON_REMOTE_CUE			EQU	027002404h	 ; Move through current me   DIa
   DIBUTTON_REMOTE_REVIEW		EQU	027002405h	 ; Move through current media
   DIBUTTON_REMOTE_CHANGE		EQU	027002406h	 ; Select next device
   DIBUTTON_REMOTE_RECORD		EQU	027002407h	 ; Start recording the current media
   DIBUTTON_REMOTE_MENU 		EQU	0270004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIAXIS_REMOTE_SLIDER2		EQU	027054202h	 ; Slider for adjustment: volume
   DIBUTTON_REMOTE_TV			EQU	027005C08h	 ; Select TV
   DIBUTTON_REMOTE_CABLE		EQU	027005C09h	 ; Select cable box
   DIBUTTON_REMOTE_CD			EQU	027005C0Ah	 ; Select CD player
   DIBUTTON_REMOTE_VCR			EQU	027005C0Bh	 ; Select VCR
   DIBUTTON_REMOTE_TUNER		EQU	027005C0Ch	 ; Select tuner
   DIBUTTON_REMOTE_DVD			EQU	027005C0Dh	 ; Select DVD player
   DIBUTTON_REMOTE_ADJUST		EQU	027005C0Eh	 ; Enter device adjustment menu
   DIBUTTON_REMOTE_DIGIT0		EQU	02700540Fh	 ; Digit 0
   DIBUTTON_REMOTE_DIGIT1		EQU	027005410h	 ; Digit 1
   DIBUTTON_REMOTE_DIGIT2		EQU	027005411h	 ; Digit 2
   DIBUTTON_REMOTE_DIGIT3		EQU	027005412h	 ; Digit 3
   DIBUTTON_REMOTE_DIGIT4		EQU	027005413h	 ; Digit 4
   DIBUTTON_REMOTE_DIGIT5		EQU	027005414h	 ; Digit 5
   DIBUTTON_REMOTE_DIGIT6		EQU	027005415h	 ; Digit 6
   DIBUTTON_REMOTE_DIGIT7		EQU	027005416h	 ; Digit 7
   DIBUTTON_REMOTE_DIGIT8		EQU	027005417h	 ; Digit 8
   DIBUTTON_REMOTE_DIGIT9		EQU	027005418h	 ; Digit 9
   DIBUTTON_REMOTE_DEVICE		EQU	0270044FEh	 ; Show input device and controls
   DIBUTTON_REMOTE_PAUSE		EQU	0270044FCh	 ; Start / Pause / Restart game

 ;--- Control- Web
 ;     Help or Browser            ---

   DIVIRTUAL_BROWSER_CONTROL		EQU	028000000h
   DIAXIS_BROWSER_LATERAL		EQU	028008201h	 ; Move on screen pointer
   DIAXIS_BROWSER_MOVE			EQU	028010202h	 ; Move on screen pointer
   DIBUTTON_BROWSER_SELECT		EQU	028000401h	 ; Select current item
   DIAXIS_BROWSER_VIEW			EQU	028018203h	 ; Move view up/down
   DIBUTTON_BROWSER_REFRESH		EQU	028000402h	 ; Refresh
   DIBUTTON_BROWSER_MENU		EQU	0280004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_BROWSER_SEARCH		EQU	028004403h	 ; Use search tool
   DIBUTTON_BROWSER_STOP		EQU	028004404h	 ; Cease current update
   DIBUTTON_BROWSER_HOME		EQU	028004405h	 ; Go directly to "home" location
   DIBUTTON_BROWSER_FAVORITES		EQU	028004406h	 ; Mark current site as favorite
   DIBUTTON_BROWSER_NEXT		EQU	028004407h	 ; Select Next page
   DIBUTTON_BROWSER_PREVIOUS		EQU	028004408h	 ; Select Previous page
   DIBUTTON_BROWSER_HISTORY		EQU	028004409h	 ; Show/Hide History
   DIBUTTON_BROWSER_PRINT		EQU	02800440Ah	 ; Print current page
   DIBUTTON_BROWSER_DEVICE		EQU	0280044FEh	 ; Show input device and controls
   DIBUTTON_BROWSER_PAUSE		EQU	0280044FCh	 ; Start / Pause / Restart game

 ;--- Driving Simulator - Giant Walking Robot
 ;     Walking tank with weapons  ---

   DIVIRTUAL_DRIVING_MECHA		EQU	029000000h
   DIAXIS_MECHA_STEER			EQU	029008201h	 ; Turns mecha left/right
   DIAXIS_MECHA_TORSO			EQU	029010202h	 ; Tilts torso forward/backward
   DIAXIS_MECHA_ROTATE			EQU	029020203h	 ; Turns torso left/right
   DIAXIS_MECHA_THROTTLE		EQU	029038204h	 ; Engine Speed
   DIBUTTON_MECHA_FIRE			EQU	029000401h	 ; Fire
   DIBUTTON_MECHA_WEAPONS		EQU	029000402h	 ; Select next weapon group
   DIBUTTON_MECHA_TARGET		EQU	029000403h	 ; Select closest enemy available target
   DIBUTTON_MECHA_REVERSE		EQU	029000404h	 ; Toggles throttle in/out of reverse
   DIBUTTON_MECHA_ZOOM			EQU	029000405h	 ; Zoom in/out targeting reticule
   DIBUTTON_MECHA_JUMP			EQU	029000406h	 ; Fires jump jets
   DIBUTTON_MECHA_MENU			EQU	0290004FDh	 ; Show menu options
 ;--- Priority 2 controls                            ---*/

   DIBUTTON_MECHA_CENTER		EQU	029004407h	 ; Center torso to legs
   DIHATSWITCH_MECHA_GLANCE		EQU	029004601h	 ; Look around
   DIBUTTON_MECHA_VIEW			EQU	029004408h	 ; Cycle through view options
   DIBUTTON_MECHA_FIRESECONDARY 	EQU	029004409h	 ; Alternative fire button
   DIBUTTON_MECHA_LEFT_LINK		EQU	02900C4E4h	 ; Fallback steer left button
   DIBUTTON_MECHA_RIGHT_LINK		EQU	02900C4ECh	 ; Fallback steer right button
   DIBUTTON_MECHA_FORWARD_LINK		EQU	0290144E0h	 ; Fallback tilt torso forward button
   DIBUTTON_MECHA_BACK_LINK		EQU	0290144E8h	 ; Fallback tilt toroso backward button
   DIBUTTON_MECHA_ROTATE_LEFT_LINK	EQU	0290244E4h	 ; Fallback rotate toroso right button
   DIBUTTON_MECHA_ROTATE_RIGHT_LINK	EQU	0290244ECh	 ; Fallback rotate torso left button
   DIBUTTON_MECHA_FASTER_LINK		EQU	02903C4E0h	 ; Fallback increase engine speed
   DIBUTTON_MECHA_SLOWER_LINK		EQU	02903C4E8h	 ; Fallback decrease engine speed
   DIBUTTON_MECHA_DEVICE		EQU	0290044FEh	 ; Show input device and controls
   DIBUTTON_MECHA_PAUSE 		EQU	0290044FCh	 ; Start / Pause / Restart game

 ;
 ;*  "ANY" semantics can be used as a last resort to get mappings for actions
 ;*  that match nothing in the chosen virtual genre.  These semantics will be
 ;*  mapped at a lower priority that virtual genre semantics.  Also, hardware
 ;*  vendors will not be able to provide sensible mappings for these unless
 ;*  they provide application specific mappings.
 ;

   DIAXIS_ANY_X_1			  EQU	  0FF00C201h
   DIAXIS_ANY_X_2			  EQU	  0FF00C202h
   DIAXIS_ANY_Y_1			  EQU	  0FF014201h
   DIAXIS_ANY_Y_2			  EQU	  0FF014202h
   DIAXIS_ANY_Z_1			  EQU	  0FF01C201h
   DIAXIS_ANY_Z_2			  EQU	  0FF01C202h
   DIAXIS_ANY_R_1			  EQU	  0FF024201h
   DIAXIS_ANY_R_2			  EQU	  0FF024202h
   DIAXIS_ANY_U_1			  EQU	  0FF02C201h
   DIAXIS_ANY_U_2			  EQU	  0FF02C202h
   DIAXIS_ANY_V_1			  EQU	  0FF034201h
   DIAXIS_ANY_V_2			  EQU	  0FF034202h
   DIAXIS_ANY_A_1			  EQU	  0FF03C201h
   DIAXIS_ANY_A_2			  EQU	  0FF03C202h
   DIAXIS_ANY_B_1			  EQU	  0FF044201h
   DIAXIS_ANY_B_2			  EQU	  0FF044202h
   DIAXIS_ANY_C_1			  EQU	  0FF04C201h
   DIAXIS_ANY_C_2			  EQU	  0FF04C202h
   DIAXIS_ANY_S_1			  EQU	  0FF054201h
   DIAXIS_ANY_S_2			  EQU	  0FF054202h

   DIAXIS_ANY_1 			  EQU	  0FF004201h
   DIAXIS_ANY_2 			  EQU	  0FF004202h
   DIAXIS_ANY_3 			  EQU	  0FF004203h
   DIAXIS_ANY_4 			  EQU	  0FF004204h

   DIPOV_ANY_1				  EQU	  0FF004601h
   DIPOV_ANY_2				  EQU	  0FF004602h
   DIPOV_ANY_3				  EQU	  0FF004603h
   DIPOV_ANY_4				  EQU	  0FF004604h

   ;DIBUTTON_ANY                           MACRO   instance
   ;                                       ENDM   (0FF004400h OR instance)

 ;***************************************************************************
 ;*  Definitions for non-IDirectInput (VJoyD) features defined more recently
 ;*  than the current sdk files
 ;***************************************************************************

 ; Flag to indicate that the dwReserved2 field of the JOYINFOEX structure
 ; contains mini-driver specific data to be passed by VJoyD to the mini-
 ; driver instead of doing a poll.

   JOY_PASSDRIVERDATA			 EQU	 010000000h

 ; Informs the joystick driver that the configuration has been changed
 ; and should be reloaded from the registery.
 ; dwFlags is reserved and should be set to zero

   ;IFNDEF joyConfigChanged

   ;externdef _imp__joyConfigChanged@4:ptr p1
   ; joyConfigChanged equ <_imp__joyConfigChanged@4>

   ;ENDIF

 ; Hardware Setting indicating that the device is a headtracker

   JOY_HWS_ISHEADTRACKER		 EQU	 002000000h

 ; Hardware Setting indicating that the VxD is used to replace
 ; the standard analog polling

   JOY_HWS_ISGAMEPORTDRIVER		 EQU	 004000000h

 ; Hardware Setting indicating that the driver needs a standard
 ; gameport in order to communicate with the device.

   JOY_HWS_ISANALOGPORTDRIVER		 EQU	 008000000h

 ; Hardware Setting indicating that VJoyD should not load this
 ; driver, it will be loaded externally and will register with
 ; VJoyD of it's own accord.

   JOY_HWS_AUTOLOAD			 EQU	 010000000h

 ; Hardware Setting indicating that the driver acquires any
 ; resources needed without needing a devnode through VJoyD.

   JOY_HWS_NODEVNODE			 EQU	 020000000h

 ; Hardware Setting indicating that the device is a gameport bus

   JOY_HWS_ISGAMEPORTBUS		 EQU	 080000000h
   JOY_HWS_GAMEPORTBUSBUSY		 EQU	 000000001h

 ; Usage Setting indicating that the settings are volatile and
 ; should be removed if still present on a reboot.

   JOY_US_VOLATILE			 EQU	 000000008h
