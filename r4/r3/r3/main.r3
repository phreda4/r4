^lib/str.r3
^lib/print.r3
^lib/gr.r3

| pixel mix (stress aex register!)
:gr_mix1 | a b al -- c
	over $ff00ff and
	pick3 $ff00ff and over -
	pick2 * 8 >> + $ff00ff and
	>r
	swap $ff00 and
	rot $ff00 and over -
	rot * 8 >> + $ff00 and
	r> or ;

:gr_mix2 | alpha a b -- c
	dup $ff00ff and
	pick2 $ff00ff and over -
	pick4 * 8 >> + $ff00ff and
	>r
	$ff00 and
	swap $ff00 and over -
	rot * 8 >> + $ff00 and
	r> or ;


#cte 33
#v 0

:main
 cls home
 "key " print
 key .d print
 cr
 v .h print
 cte 'v +!
 $7f $ff00 $ff00ff gr_mix2
 vframe !
 ;

:
$ff00ff 'ink !
'main onshow
;