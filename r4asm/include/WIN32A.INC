
; Win32 programming headers (ASCII)

include 'r4asm/macro/struct.inc'
include 'r4asm/macro/proc32.inc'
include 'r4asm/macro/com32.inc'
include 'r4asm/macro/import32.inc'
include 'r4asm/macro/export.inc'
include 'r4asm/macro/resource.inc'

struc CHAR val { match any, val \{ . db val \}
		 match , val \{ . db ? \} }

include 'r4asm/api/kernel32.inc'
include 'r4asm/api/user32.inc'
include 'r4asm/api/gdi32.inc'
include 'r4asm/api/comctl32.inc'
include 'r4asm/api/comdlg32.inc'
include 'r4asm/api/shell32.inc'
include 'r4asm/api/wsock32.inc'

