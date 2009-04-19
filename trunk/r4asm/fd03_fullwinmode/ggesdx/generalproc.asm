;===========================================================================================
; generalproc.asm AsmGges France                   http://www.chez.com/asmgges/index.htm
;===========================================================================================

;===========================================================================================
; Mettre à zéro une zone mémoire
;-------------------------------------------------------------------------------------------
; @AdrZone = adresse zone mémoire à mettre à zéro
; @Len     = longueur de la zone en octets
;===========================================================================================
proc ZeroMemory uses ecx edi, @AdrZone, @Len

    mov edi,[@AdrZone]
    mov ecx,[@Len]
    mov eax,0
    rep stosb

    ret
endp
;===========================================================================================
; Limiter le nombre de frames par seconde
;-------------------------------------------------------------------------------------------
; @FpsMax = nombre de frames par secondes maximum
;-------------------------------------------------------------------------------------------
; Utilisation:
; invoke timeBeginPeriod,1    ;au début du programme
; mov [FpsMax],75
;
; invoke GetTickCount         ;dans MessageLoop
; mov [TickCount],eax
; call FpsLimiter,[FpsMax]
;
; invoke timeEndPeriod,1      ;a la fin du programme
;===========================================================================================
proc FpsLimiter uses ebx edx, @FpsMaxi
    local .DelayTicks:DWORD, .MinTicksForSleep:DWORD

    .if [@FpsMaxi] = 0
        ret
    .endif

    invoke QueryPerformanceFrequency,PerfFreq

    mov eax,dword[PerfFreq]
    mov edx,dword[PerfFreq+4]
    div [@FpsMaxi]
    mov [.DelayTicks],eax

    mov eax,dword[PerfFreq]
    mov edx,dword[PerfFreq+4]
    mov ebx,500
    div ebx
    mov [.MinTicksForSleep],eax

    .L1:
        .repeat
            invoke QueryPerformanceCounter,PerfCounter
            mov eax,dword[PerfCounter]
            mov edx,dword[PerfCounter+4]
            .if edx <> [NextTimeEdx]
                jmp .finish
            .elseif eax >= [NextTimeEax]
                jmp .finish
            .endif
            mov ebx,[NextTimeEax]
            sub ebx,eax
        .until ebx >= [.MinTicksForSleep]
        push eax
        invoke Sleep,1
        pop eax
    jmp .L1

 .finish:
    add eax,[.DelayTicks]
    mov [NextTimeEax],eax
    mov [NextTimeEdx],edx

    ret
endp
;===========================================================================================
;///////////////////////////////////////////////////////////////////////////////////////////
;===========================================================================================