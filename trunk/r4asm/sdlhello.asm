;
; Hello World In SDL 1.2.11 with FASM
; By Ralph Eastwood (tcmeastwood@ntlworld.com)
;
; Version Date: 07/11/2006 (dd/mm/yyyy)
;
; Thanks to gunblade and vid for support and help
; Utilises vid's crossplatform fasmlib 0.3
;
; Following Madis731's suggestion, SDL_Delay is included so
; that CPU usage isn't 100%
;
; Remember to set your include directory to FASM/INCLUDE
;
; Please use FASM 1.67.14 (or higher?)
;
format PE console
entry start

; Code
section '.code' code executable readable

; Include FASMLIB
SYSTEM equ win32
include "fasmlib/fasmlib.inc"
include "fasmlib/process.inc"
include "fasmlib/mem.inc"
include "fasmlib/file.inc"
include "fasmlib/str.inc"
include "fasmlib/conv.inc"
include "fasmlib/stream.inc"
include "fasmlib/text.inc"

; Includes for SDL
include 'SDL/SDL.inc'

; General Includes
include 'macro/proc32.inc'
include 'macro/com32.inc'
include 'macro/import32.inc'
include 'macro/export.inc'
include 'macro/resource.inc'
;include 'macro/struct.inc'

; Win32 header
;include 'include/win32ax.inc'
include 'include/win32a.inc'

; Actual Code starts here

start:
	; Initialize modules
	libcall stream.init
	jc	error
	libcall mem.init
	jc	error

	; Init SDL
	cinvoke SDL_Init, SDL_INIT_NOPARACHUTE

	; Give our module handle to SDL
	invoke	GetModuleHandle, 0
	cinvoke SDL_SetModuleHandle, eax

	; Call main procedure
	stdcall main

	; End program with exit code in eax
	jmp exit

; FASMLIB error handling

	; On error, EAX contains error code
error:
	; EBX = error message associated with error code in EAX
	libcall err.text, eax
	mov	ebx, eax

	; Write error
	libcall stream.write, stream.stdout, <10,"Error: ",10>
	libcall text.write, stream.stdout, ebx

	; Errors run into the exit code
	mov	[exitcode], 1

; Exiting Code
exit:
	mov	[exitcode], eax

	; If SDL has been init, quit it
	test	[sdlinit], 1
	jz	@F
	cinvoke SDL_Quit
@@:

	; Unintialize modules
	libcall mem.uninit
	libcall stream.uninit

	; End program with exit code 1
	libcall process.exit, [exitcode]

proc main

	; Local variables
	local event:SDL_Event

	; Write to console that SDL managed to initialised
	libcall text.write, stream.stdout, <"Raedwulf's SDL Demo ported from Sol's SDL Tutorials  02",10,"http://sol.gfxile.net/gp/ch02.html",10,10>
	jc	error
	libcall text.write, stream.stdout, <"Suggestions, bug fixes or general comments welcome at",10,"tcmreastwood@ntlworld.com",10,10>
	jc	error
	libcall text.write, stream.stdout, <"Utilises vid's wonderful FASMLIB 0.3, Thanks vid!",10,10>
	jc	error

	; Initialize SDL's subsystems - in this case, only video.
	cinvoke SDL_Init, SDL_INIT_VIDEO
	test	eax, eax
	jz	@F			   ; Jump if Successful

	; Not very successful, error
	; Get SDL Error text
	cinvoke SDL_GetError
	mov	[sdl_errorstring], eax	    ; Error string pointer

	libcall text.write, stream.stdout, <10,"Unable to init SDL: ">
	jc	error
	libcall text.write, stream.stdout, sdl_errorstring
	jc	error
	libcall text.write, stream.stdout, <10>
	jc	error

	mov	eax, 1			   ; Exit code 1
	ret				   ; Exit the program

@@:
	; Write to console that SDL managed to initialised
	libcall text.write, stream.stdout, <"SDL init sucessfully.",10>
	jc error

	; Flag that SDL has been initialised
	mov [sdlinit], 1

	; Attempt to create a 640x480 window with 32bit pixels
	cinvoke SDL_SetVideoMode, 640, 480, 32, SDL_SWSURFACE

	; If it failed, error and quit
	test	eax, eax
	jnz	 @F			    ; Jump if Successful

	; Not very successful, error
	; Get SDL Error text
	cinvoke SDL_GetError
	mov	[sdl_errorstring], eax	    ; Error string pointer

	libcall text.write, stream.stdout, <10,"Unable to set 640x480 video: ",10>
	jc	error
	libcall text.write, stream.stdout, sdl_errorstring
	jc	error
	libcall text.write, stream.stdout, <10>
	jc	error

	mov	eax, 1			   ; Exit code 1
	ret				   ; Exit the program
@@:

	; Store the surface info
	mov	[screen], eax
	mov	edx, eax

	; Write to console that SDL managed to set the window
	libcall text.write, stream.stdout, <"SDL window set to 640x480.",10,10,"Press Escape or the [X] to exit the demo.">
	jc	error

	; Main loop that loops forever
MainLoop:

	; Render stuff
	stdcall render
	; Just draw a pixel on top
	; stdcall drawpixel,10,20

	; Poll for events, and handle the ones we care about.
PollAgain:
	lea	eax, [event]
	cinvoke SDL_PollEvent, eax
	test	eax, eax
	jz	DontPoll		   ; No events, jump to DontPoll

	movzx	edx, [event.type]	   ; Get the event type

	cmp	edx, SDL_KEYDOWN	   ; Key has been pressed
	jne	@F
@@:
	cmp	edx, SDL_KEYUP		   ; Key has been lifted
	jne	@F
	cmp	[event.key.keysym.sym], SDLK_ESCAPE	   ; If escape key is pressed
	jne	@F					   ; No it wasn't
	xor	eax, eax
	ret						   ; Return
@@:
	cmp	edx, SDL_QUIT		   ; Window has been closed - quit
	jne	@F
	xor	eax, eax
	ret
@@:
	jmp	PollAgain
DontPoll:
	jmp	MainLoop

	; We shouldn't ever get here!!!
       ret
endp

proc render
	push	     esi edi ebx

	; Access the surface via edx
	virtual at edx
		surface SDL_Surface
	end virtual

	local pitch:DWORD, yofs:DWORD, ofs:DWORD, pixelptr:DWORD

	; Store screen surface ptr in edx
	mov	     edx, [screen]

	; Lock Surface If Needed
	SDL_MUSTLOCK eax, edx
	jz	     @F 			   ; No Lock needed
	cinvoke      SDL_LockSurface, edx	   ; Lock the surface
	test	     eax, eax			   ; Is Locking successful
	jz	     @F 			   ; Jump If yes
	; Failed to lock, return
	ret
@@:
	; Ask SDL for the time in milliseconds
	cinvoke      SDL_GetTicks
	mov	     ecx, eax			   ; Store tick time in ecx

	; Draw to screen
	mov	     edx, [screen]
	movzx	     eax, [surface.pitch]
	mov	     [pitch], eax	     ; Store surface.pitch \4

	; Get the pixel pointer into edx
	mov	     edx, [surface.pixels]

	; Clear the registers
	xor	     edi, edi
	xor	     ebx, ebx
	xor	     eax, eax
	xor	     esi, esi			   ; Clear esi

	; Loop through height
LoopHeight:
	mov	     eax, ebx
	mov	     [yofs], ebx		   ; Preserve ebx

	; Loop through width
LoopWidth:
	mov	     [ofs], eax 		   ; Preserve eax
	mov	     ebx, esi
	imul	     ebx, esi			   ; ebx = esi * esi
	mov	     eax, edi
	imul	     eax, edi			   ; eax = edi * edi
	add	     ebx, eax			   ; ebx = ebx + eax
	add	     ebx, ecx			   ; ebx = ebx + ecx(tick)
	mov	     eax, [ofs] 		   ; Restore eax
	mov	     [edx+eax], ebx		   ; store pixel
	add	     edi, 1			   ; edi++
	add	     eax, 4			   ; Increment by 4! - 4 bytes a pixel
	cmp	     edi, 640
	jl	     LoopWidth			   ; <640 goto LoopWidth

	mov	     ebx, [yofs]		   ; Restore ebx
	add	     ebx, [pitch]
	add	     esi, 1
	xor	     edi, edi
	cmp	     esi, 480			   ; <480 goto LoopHeight
	jl	     LoopHeight

	; Unlock if needed
	mov	     edx, [screen]
	SDL_MUSTLOCK eax, edx
	jz	     @F 			   ; No Lock needed
	cinvoke      SDL_UnlockSurface, edx	   ; UnLock the surface
	test	     eax, eax			   ; Is Locking succesful
	jz	     @F 			   ; Jump If yes
	; Failed to unlock, return
	ret
@@:

	; Tell SDL to update the whole screen
	cinvoke SDL_UpdateRect, [screen], 0, 0, 640, 480

	pop	     ebx edi esi
	ret
endp

proc drawpixel,x:DWORD,y:DWORD

	mov	     edx, [screen]

	; Access the surface via edx
	virtual at edx
		surface SDL_Surface
	end virtual

	; Access the pixel format via ecx
	virtual at ecx
		     pixelformat SDL_PixelFormat
	end virtual

	; Make p point to the place we want to draw the pixel
	mov	     eax, [surface.pixels]
	movzx	     ecx, [surface.pitch]
	imul	     ecx, [y]
	add	     eax, ecx
	mov	     ecx, [surface.format]
	movzx	     ecx, [pixelformat.BytesPerPixel]
	imul	     ecx, [x]
	lea	     eax, [eax+ecx]

	; Draw the pixel!
	mov	     [eax], dword 0xFFFFFF

	; Update the screen (aka double buffering) - alternative to below line?
	;cinvoke SDL_Flip, edx

	; Tell SDL to update the whole screen
	cinvoke SDL_UpdateRect, [screen], 0, 0, 640, 480

	ret
endp

; Data
section '.data' data readable writeable

	screen		dd ?
	sdlinit 	dd 0
	exitcode	dd 0
	sdl_errorstring dd ?

	;define data from idata{} and udata{} macros
	IncludeIData
	IncludeUData

; Imports
section '.import' data import readable

	;imports that FASMLIB needs
	library kernel32, "kernel32.dll", \
		user32, "user32.dll", \
		opengl32, "opengl32.dll", \
		sdl, "sdl.dll"

	include "API/kernel32.inc"
	include "API/user32.inc"
	include 'SDL/WIN32/SDLA.INC'