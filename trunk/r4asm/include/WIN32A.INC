
; Win32 programming headers (ASCII)

include 'macro/struct.inc'
include 'macro/proc32.inc'
include 'macro/com32.inc'
include 'macro/import32.inc'
include 'macro/export.inc'
include 'macro/resource.inc'

struc CHAR val { match any, val \{ . db val \}
		 match , val \{ . db ? \} }

include 'api/kernel32.inc'
include 'api/user32.inc'
include 'api/gdi32.inc'
include 'api/comctl32.inc'
include 'api/comdlg32.inc'
include 'api/shell32.inc'
include 'api/wsock32.inc'

