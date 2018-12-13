| Example 5 DRAW in Canvas

^lib/gr.r3
^lib/rand.r3

#last 0

:show
  bmouse 0? ( 'last ! ; ) drop
  last 0? ( drop 1 'last ! xymouse op
  	rand $ff or 'ink !
  	; ) drop
  xymouse line ;

:
'show onshow
;