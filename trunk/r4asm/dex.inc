;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                                  ;;
;; Project          :   DexOS                                                       ;;
;; Ver              :   00.01                                                       ;;
;; Author           :   Dex                                                         ;;
;; Website          :   www.dex4u.com                                               ;;
;; Forum            :   http://jas2o.forthworks.com/dexforum/                       ;;
;; wiki             :   http://tonymac.asmhackers.net/Wiki/pmwiki.php               ;;
;; Date             :   October 10, 2006                                            ;;
;; Filename         :   DexFunction.inc                                             ;;
;; Assembler Command:   FASM kernel32.asm kernel32.exe                              ;;
;; Copy Right Owners:   Team DexOS                                                  ;;
;;                                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                                  ;;
;; Team DexOS       :   0x4e71, bubach, crc, Dex, hidnplayr, jas2o, Solidus         ;;
;;                  :   smiddy, tony(mac), viki.                                    ;;
;;                                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                                  ;;
;; Disclaimer       :                                                               ;;
;; This software is provided "AS IS" without warranty of any kind, either           ;;
;; expressed or implied, including, but not limited to, the implied                 ;;
;; warranties of merchantability and fitness for a particular purpose. The          ;;
;; entire risk as to the quality and performance of this software is with           ;;
;; you.                                                                             ;;
;; In no event will the author's, distributor or any other party be liable to       ;;
;; you for damages, including any general, special, incidental or                   ;;
;; consequential damages arising out of the use, misuse or inability to use         ;;
;; this software (including but not limited to loss of data or losses               ;;
;; sustained by you or third parties or a failure of this software to operate       ;;
;; with any other software), even if such party has been advised of the             ;;
;; possibility of such damages.                                                     ;;
;;                                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Functions                                                    Function calltable. ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Functions:
CallTableAddress     rd 1	    ;  0.call-table address,DO NOT call as function.
Clstext 	     rd 1	    ;  1.Clears text mode screen, but leaves top 4 rows uncleared.
RealModeInt10h	     rd 1	    ;  2.Call realmode int 10h,fill in AX,BX,CX,DX, with function number etc, be carefull may not work will all functions.
RealModeRegs	     rd 1	    ;  3.Fills in AX,BX,CX,DX with result from above function,set CF to 1 on error.
WaitForKeyPress      rd 1	    ;  4.Wait for keypress,Exit: ASCII code of keypressed in AL .
KeyPressedNoWait     rd 1	    ;  5.If keyperssed AL=1,if no keypressed AL=0.
ExtendedMemory	     rd 1	    ;  6.puts extended memory in eax (in KBs),puts total ram in ebx (in MB)
ConvenMemorySize     rd 1	    ;  7.puts conventional memory in eax (in KBs)
TextColor	     rd 1	    ;  8.Sets the text color, Entry: AL=color.
PrintString	     rd 1	    ;  9.prints a string,esi should point to a 0 termanated string.
PrintChar	     rd 1	    ; 10.prints the char,in al
PrintCharCursor      rd 1	    ; 11.prints the char,in al and moves cursor
SetCursorPos	     rd 1	    ; 12.Sets Cursor Pos, Entry: AL=X, AH=Y, if the X or Y is bigger than screen size, CF to 1, succes AH=0. 
WriteHex32	     rd 1	    ; 13.print the hex value,in eax
WriteHex16	     rd 1	    ; 14.print the hex value,in al
UpperCase	     rd 1	    ; 15.Converts a 0 termanated string,to uppercase (es:edi = string buffer)
CompearString	     rd 1	    ; 16.Compear two strings,set CF to 1, if strings are not the same
SetDex4uFonts	     rd 1	    ; 17.Goes to realmode and back sets 50x80 mode/fonts
FloppyfileLoad	     rd 1	    ; 18.Loads a file from floppy,ESI points to name of file to load,EDI = place to load file to,set's CF to 1 on error ,sucsess EBX = number of sector loaded..
CdfileLoad	     rd 1	    ; 19.Loads a file from CD, CX = file name lenth,ESI = name of file to load,EDI points to place to load to,set's CF to 1 on error.
SetDelay	     rd 1	    ; 20.Sets a delay, ax = delay,18.2 = 1 second.
DetectPciBus	     rd 1	    ; 21.Detect Pci Bus present, set's CF to 1, if no pci bus
PciFindDevice	     rd 1	    ; 22.Scan through PCI space looking for a device+vendor ID,CF to 1,if no vender/device found. 
PciRegWrite8	     rd 1	    ; 23.Entry: EAX=PCI Bus/Device/fn/register number,DL=data to write.
PciRegWrite16	     rd 1	    ; 24.Entry: EAX=PCI Bus/Device/fn/register number,DX=data to write.
PciRegWrite32	     rd 1	    ; 25.Entry: EAX=PCI Bus/Device/fn/register number,EDX=data to write.
PciRegRead8	     rd 1	    ; 26.Entry: EAX=PCI Bus/Device/fn/register number,Exit: DL register data. 
PciRegRead16	     rd 1	    ; 27.Entry: EAX=PCI Bus/Device/fn/register number,Exit: DX register data. 
PciRegRead32	     rd 1	    ; 28.Entry: EAX=PCI Bus/Device/fn/register number,Exit: EDX register data. 
InterruptTimer	     rd 1	    ; 29.Reprograms interrupt timer, CX = number of times a second, at program end the timer is restored with CX = 0 .
GetUserInput	     rd 1	    ; 30.Gets user input, until enter pressed. Exit: EDI = buffer address, cx = string len.
LoadVesaInfo	     rd 1	    ; 31.loads the address of vesainfo in esi, use this to fill a vesa info structure (in Dex.inc).
SetVesaMode	     rd 1	    ; 32.Sets vesa mode, CX = MODE NUMBER, Return CF to 1 on error. NOTE: You need to call the above function after this one.
GameKeyBoardOn	     rd 1	    ; 33.Puts the game keyboard on, ESI points to KeyDown a 128 byte array.
GameKeyBoardOff      rd 1	    ; 34.Turns the Game keyboard off.
TimerNoWait	     rd 1	    ; 35.Sets a delay, but does not wait, AX=timer to delay, AL=0 is call if AL returns 1 than timer not finished, if AL returns 0 them timer finished.
ResetMouse	     rd 1	    ; 36.enables mouse, AX = 0x0000 if no mouse found, AX = 0xffff if found, next function needed to show mouse.
ShowMouse	     rd 1	    ; 37.Shows mouse pointer (text mode).
HideMouse	     rd 1	    ; 38.Hides mouse text mode.
GetMousePos	     rd 1	    ; 39.Gets the XY and button press, on return BL = button pressed, 00000001 = rightbutton, 00000010 = centerbutton, 00000100 = leftbutton. CX=X, DX=Y.
SetMouseMaxMinXY     rd 1	    ; 40.Set mouses min/max xy,input EAX bits 32to17=minX bits16to1=maxX, EBX bits 32to17=minY bits16to1=maxY.
SetMouseXY	     rd 1	    ; 41.Sets mouse xy, input AX=X, BX=Y.
SetMouseOff	     rd 1	    ; 42.Turns the mouse off.
WriteCommand	     rd 1	    ; 43.Writes a file to floppy, ESI points to name of file to make, EDI = place to load file from, EAX = size of file to load in bytes, set's CF to 1 on error, error code in AH, sucsess EBX = number of sectors loaded, ECX = file size in bytes.
FddMotorOff	     rd 1	    ; 44.Turns floppy motor off.
FddMotorOn	     rd 1	    ; 45.Turns floppy motor on.
FddReSet	     rd 1	    ; 46.ReSets floppy.
FddSeek 	     rd 1	    ; 47.Floppy seek, NOTE: this will need moding to be used by out side progs, but will be add soon, so i have include it.
FddRecalibrate	     rd 1	    ; 48.Floppy recalibrate.
FddRead 	     rd 1	    ; 49.Floppy read sector, CH=Track/cylinder, CL=Sector, DH=Head, DL=Drive (only A: drive used 00 ), RETURN AH=Status, AL=Sector number read, CF=1 If error. 
FddWrite	     rd 1	    ; 50.Floppy write sector, CH=Track/cylinder, CL=Sector, DH=Head, DL=Drive (only A: drive used 00 ), RETURN AH=Status, AL=Sector number read, CF=1 If error.
DriveLetter	     rd 1	    ; 51.Gets the currant Drive letter, On return, AL = Currant drive letter
CurrutDir	     rd 1	    ; 52.Gets the currant Dir, ES:EDI must point to a 128byte buffer, if curant dir = root, than 00 is returned in buffer .
DeleteFile	     rd 1	    ; 53.Delete's the named file on A:\, ESI=Name of file,nomore than 8 letters, a "." and 3 exten letters, CF to 1 on error, AH=error code.
OpenFile	     rd 1	    ; 54.Checks that a file by a certain name, is on the floppy, ESI=FileName, CF to 1 on error or no file by that name, AH=error code
DeleteFile1	     rd 1	    ; 55.A simpler ver of "DeleteFile" only needs, ESI=Name of file to delete, CF to 1 on error or no file by that name, AH=error code.
Play_cd 	     rd 1	    ; 56.Play CD.
Stop_cd 	     rd 1	    ; 57.Stop CD
Eject_cd	     rd 1	    ; 58.Eject CD
Close_cd	     rd 1	    ; 59.Close CD
GetParams	     rd 1	    ; 60.Gets the address of the command line buffer,return ESI=Command line buffer address.
GetTime 	     rd 1	    ; 61.Gets the currant time return : EAX=hour, minute, second, each a byte in bcd format.
GetClockTicks	     rd 1	    ; 62.Count clock ticks.
ModuleFunction	     rd 1	    ; 63.Call a Module function, ESI=Address of module function ID string, AH=Module function number, Return CF=1 If error, AH=Error code.
KeyPressedScanNW     rd 1	    ; 64.IF keyperssed AL= ASCII code, Ah = Scancode, if no keypressed AL=0, eg no wait.
GetDate 	     rd 1	    ; 65.Gets the currant time return : EAX=century, year, month,day, each a byte in bcd format.
DirCommandGuiHdd32   rd 1	    ; 66.Fills a list, of gui file (eg:"gex" ext), from HDD root dir, returns ESI = list address, EDI= "HDD32GuiFileCount", EBX = "FileNumberCountHDD", error = CF to 1.
ReadCdDirGui	     rd 1	    ; 67.Fills a list, of gui file (eg:"gex" ext), from CD root dir, returns ESI = list address, EDI= "CdGuiFileCount", EBX = "FileNumberCountCd", error = CF to 1.
DirCommandGui	     rd 1	    ; 68.Fills a list, of gui file (eg:"gex" ext), from floppy root dir, on entering, AX= first 2 letters of ext ,(eg: AX='GE' or AX=00 for all ext), returns ESI = list address, error = CF to 1.
RebootSystem	     rd 1	    ; 69.Reboots the machine.
ExitSystem	     rd 1	    ; 70.Exits to DOS, if in DOS, Reboots otherwise.
HddfileLoad	     rd 1	    ; 71.Loads a file from first fat16/32 Hdd, EDI points to name of file to load,EDX = place to load file to,return set's CF to 1 on error,sucess EBX = number of sector load, ECX = file size in bytes.
Pause_cd	     rd 1	    ; 72.Pause CD 
PlayAllTracks	     rd 1	    ; 73.Play all tracks on CD, Return number of tracks in AL.      
PlayTrack	     rd 1	    ; 74.Play one track, AL = Track to play, returns AL = Number of tracks on cd. 
CheckCdBusy	     rd 1	    ; 75.Checks if CD is busy, return set's CF to 1 on error (busy).  
CheckCdStateus	     rd 1	    ; 76.Checks CD stateus, return AL = Stateus code, set's CF to 1 on error.
TrackInFo	     rd 1	    ; 77.Returns number of tracks on audio CD, AL= Number.
SetInt		     rd 1	    ; 78.Sets a pointer to a function that is call on keypress or clock tick, EAX=1 for keypress, EAX=2 for clocktick, EAX=3 for int-52h, EAX=4 for int-53h, EDI=address of new function, RETURN EDI=old function address, error = CF to 1
CloseInt	     rd 1	    ; 79. Restore old address, for above function, EAX=1 for keypress, EAX=2 for clocktick, EDI= OLD address restored, error = CF to 1.
GetBaseAddOn	     rd 1	    ; 80. Returns the base add on, in EAX.
TimerSecondCount     rd 1	    ; 81. Returns in EAX,the number of ticks, since OS started, 18.2 ticks a second are added. 
TopOfMemory	     rd 1	    ; 82. Returns in EAX top of useable memory, in bytes.
GetCommandStored     rd 1	    ; 83. Gets user input,until enter is pressed. Exit: EDI = buffer address, cx = string len.This ver work with right arrow key, to get last input.
CountTicks	     rd 1	    ; 84. Returns CF to 1 on clock tick (defaults to 18.2 times a second), CF = 0, the rest of the time. 
HddWrite1Sector      rd 1	    ; 85. Fat16 HDD Write 1 sector, ESI= 512bytes towrite, CH=Track/cylinder, CL=Sector, DH=Head, DL=Drive (only C: drive used 80 ), RETURN AH=Status, AL=Sector number read, CF=1 If error.
WriteHex8	     rd 1	    ; 86. Print's the hex value, in AL
WriteFileHdd	     rd 1	    ; 87. Writes a file to fat16 Hdd, ESI points to name of file to make, EDI = place to load file from, EAX = size of file to load in bytes, set's CF to 1 on error,error code in AH, sucess EBX = number of sectors loaded, ECX = file size in bytes.
DeleteFileHdd	     rd 1	    ; 88. Deletes file on fat16 HDD, ESI=Name of file to delete, CF to 1 on error or no file by that name, AH=error code.
Function89	     rd 1
Function90	     rd 1
Function91	     rd 1
Function92	     rd 1
Function93	     rd 1
Function94	     rd 1
Function95	     rd 1
Function96	     rd 1
Function97	     rd 1
Function98	     rd 1
Function99	     rd 1
Function100	     rd 1
Function101	     rd 1
Function102	     rd 1
Function103	     rd 1
Function104	     rd 1
Function105	     rd 1
Function106	     rd 1
Function107	     rd 1
Function108	     rd 1
Function109	     rd 1
Function110	     rd 1
Function111	     rd 1
Function112	     rd 1
Function113	     rd 1
Function114	     rd 1
Function115	     rd 1
Function116	     rd 1
Function117	     rd 1
Function118	     rd 1
Function119	     rd 1
Function120	     rd 1
Function121	     rd 1
Function122	     rd 1
Function123	     rd 1
Function124	     rd 1
Function125	     rd 1
Function126	     rd 1
Function127	     rd 1
Function128	     rd 1
Function129	     rd 1
Function130	     rd 1
Function131	     rd 1
Function132	     rd 1
Function133	     rd 1
Function134	     rd 1
Function135	     rd 1
Function136	     rd 1
Function137	     rd 1
Function138	     rd 1
Function139	     rd 1
Function140	     rd 1
Function141	     rd 1
Function142	     rd 1
Function143	     rd 1
Function144	     rd 1
Function145	     rd 1
Function146	     rd 1
Function147	     rd 1
Function148	     rd 1
Function149	     rd 1
Function150	     rd 1
Function151	     rd 1
Function152	     rd 1
Function153	     rd 1
Function154	     rd 1
Function155	     rd 1
Function156	     rd 1
Function157	     rd 1
Function158	     rd 1
Function159	     rd 1
Function160	     rd 1
Function161	     rd 1
Function162	     rd 1
Function163	     rd 1
Function164	     rd 1
Function165	     rd 1
Function166	     rd 1
Function167	     rd 1
Function168	     rd 1
Function169	     rd 1
Function170	     rd 1
Function171	     rd 1
Function172	     rd 1
Function173	     rd 1
Function174	     rd 1
Function175	     rd 1
Function176	     rd 1
Function177	     rd 1
Function178	     rd 1
Function179	     rd 1
Function180	     rd 1
Function181	     rd 1
Function182	     rd 1
Function183	     rd 1
Function184	     rd 1
Function185	     rd 1
Function186	     rd 1
Function187	     rd 1
Function188	     rd 1
Function189	     rd 1
Function190	     rd 1
Function191	     rd 1
Function192	     rd 1
Function193	     rd 1
Function194	     rd 1
Function195	     rd 1
Function196	     rd 1
Function197	     rd 1
Function198	     rd 1
Function199	     rd 1
Function200	     rd 1
Function201	     rd 1
Function202	     rd 1
Function203	     rd 1
Function204	     rd 1
Function205	     rd 1
Function206	     rd 1
Function207	     rd 1
Function208	     rd 1
Function209	     rd 1
Function210	     rd 1
Function211	     rd 1
Function212	     rd 1
Function213	     rd 1
Function214	     rd 1
Function215	     rd 1
Function216	     rd 1
Function217	     rd 1
Function218	     rd 1
Function219	     rd 1
Function220	     rd 1
Function221	     rd 1
Function222	     rd 1
Function223	     rd 1
Function224	     rd 1
Function225	     rd 1
Function226	     rd 1
Function227	     rd 1
Function228	     rd 1
Function229	     rd 1
Function230	     rd 1
Function231	     rd 1
Function232	     rd 1
Function233	     rd 1
Function234	     rd 1
Function235	     rd 1
Function236	     rd 1
Function237	     rd 1
Function238	     rd 1
Function239	     rd 1
Function240	     rd 1
Function241	     rd 1
Function242	     rd 1
Function243	     rd 1
Function244	     rd 1
Function245	     rd 1
Function246	     rd 1
Function247	     rd 1
Function248	     rd 1
Function249	     rd 1
Function250	     rd 1
Function251	     rd 1
Function252	     rd 1
Function253	     rd 1
Function254	     rd 1
Function255	     rd 1
Function256	     rd 256

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; FASM VESA INFORMATION BLOCK.                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

VESA_Info:		
VESAInfo_Signature		rb	4
VESAInfo_Version		rw	1
VESAInfo_OEMStringPtr		rd	1
VESAInfo_Capabilities		rb	4
VESAInfo_VideoModePtr		rd	1
VESAInfo_TotalMemory		rw	1
VESAInfo_OEMSoftwareRev 	rw	1
VESAInfo_OEMVendorNamePtr	rd	1
VESAInfo_OEMProductNamePtr	rd	1
VESAInfo_OEMProductRevPtr	rd	1
VESAInfo_Reserved		rb	222
VESAInfo_OEMData		rb	256

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; VESA MODE INFORMATION.                                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Mode_Info:		
ModeInfo_ModeAttributes 	rw	1
ModeInfo_WinAAttributes 	rb	1
ModeInfo_WinBAttributes 	rb	1
ModeInfo_WinGranularity 	rw	1
ModeInfo_WinSize		rw	1
ModeInfo_WinASegment		rw	1
ModeInfo_WinBSegment		rw	1
ModeInfo_WinFuncPtr		rd	1
ModeInfo_BytesPerScanLine	rw	1
ModeInfo_XResolution		rw	1
ModeInfo_YResolution		rw	1
ModeInfo_XCharSize		rb	1
ModeInfo_YCharSize		rb	1
ModeInfo_NumberOfPlanes 	rb	1
ModeInfo_BitsPerPixel		rb	1
ModeInfo_NumberOfBanks		rb	1
ModeInfo_MemoryModel		rb	1
ModeInfo_BankSize		rb	1
ModeInfo_NumberOfImagePages	rb	1
ModeInfo_Reserved_page		rb	1
ModeInfo_RedMaskSize		rb	1
ModeInfo_RedMaskPos		rb	1
ModeInfo_GreenMaskSize		rb	1
ModeInfo_GreenMaskPos		rb	1
ModeInfo_BlueMaskSize		rb	1
ModeInfo_BlueMaskPos		rb	1
ModeInfo_ReservedMaskSize	rb	1
ModeInfo_ReservedMaskPos	rb	1
ModeInfo_DirectColorModeInfo	rb	1
; VBE 2.0 extensions
ModeInfo_PhysBasePtr		rd	1
ModeInfo_OffScreenMemOffset	rd	1
ModeInfo_OffScreenMemSize	rw	1
; VBE 3.0 extensions
ModeInfo_LinBytesPerScanLine	rw	1
ModeInfo_BnkNumberOfPages	rb	1
ModeInfo_LinNumberOfPages	rb	1
ModeInfo_LinRedMaskSize 	rb	1
ModeInfo_LinRedFieldPos 	rb	1
ModeInfo_LinGreenMaskSize	rb	1
ModeInfo_LinGreenFieldPos	rb	1
ModeInfo_LinBlueMaskSize	rb	1
ModeInfo_LinBlueFieldPos	rb	1
ModeInfo_LinRsvdMaskSize	rb	1
ModeInfo_LinRsvdFieldPos	rb	1
ModeInfo_MaxPixelClock		rd	1
; Reserved
ModeInfo_Reserved		rb	190*4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; VESA MODE INFORMATION END.                                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

