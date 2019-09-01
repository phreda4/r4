;---------- INICIO
inicio:
;        call test1
        call test2
        jmp SYSEND

;--- ejemplo 1 llena la pantalla
test1:
        xor ebx,ebx
loopi:
        inc edx
        mov [SYSFRAME+ebx*4],edx
        add ebx,1
        cmp ebx,XRES*YRES
        jl loopi
        add edx,1
        call SYSREDRAW
        call SYSUPDATE
        cmp [SYSKEY],1
        jne test1

        ret
;---ejemplo 2 uso de mouse
test2:
        call SYSCLS
loop2:
        mov eax, dword[SYSXYM]
        mov ebx,eax
        shr eax,16
        and ebx,$ffff
        imul eax,XRES
        add eax,ebx
        mov [SYSFRAME+eax*4],$ffffff

        call SYSREDRAW
        call SYSUPDATE
        cmp [SYSKEY],1
        jne loop2
        ret

SYSCLS:         ; ( -- )
        push rax
        mov rax,0
        lea rdi,dword [SYSFRAME]
        mov rcx,(XRES*YRES)/2
        rep stosq
        pop rax
        ret
