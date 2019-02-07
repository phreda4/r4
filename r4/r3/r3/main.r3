^lib/str.r3
^lib/print.r3
^lib/gr.r3

#cte 33
#v 0

:main
 cls home
 "key " print
 keychar .d print
 cr
 v .h print
 cte 'v +!
 ;

:
$ff00ff 'ink !
'main onshow
;