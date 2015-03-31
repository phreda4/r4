; from revolution in http://board.flatassembler.net/topic.php?t=13621
macro jmp dest {
        local .x
        virtual
                jmp near dest
                load .x dword from $-4
        end virtual
        if .x >= 0xffffff80 | .x <= 0x0000007f
                jmp short dest
        else if dest and not 0xffff = 0
                jmp word dest
        else
                jmp dest
        end if
}

; form Tomasz Grysztar in http://board.flatassembler.net/topic.php?t=3331
macro align value
 {
  virtual
   align value
   ..align = $ - $$
  end virtual
  times ..align/8 db $66, $8D, $04, $05, $00, $00, $00, $00
  ..align = ..align mod 8
  if ..align = 7
   db $8D, $04, $05, $00, $00, $00, $00
  else if ..align = 6
   db $8D, $80, $00, $00, $00, $00
  else if ..align = 5
   db $66, $8D, $54, $22, $00
  else if ..align = 4
   db $8D, $44, $20, $00
  else if ..align = 3
   db $8D, $40, $00
  else if ..align = 2
   db $8B, $C0
  else if ..align = 1
   db 90h
  end if
 }