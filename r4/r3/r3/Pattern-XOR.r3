| Example 1

^lib/gr.r3

:patternxor
 vframe >a
 sh ( 1? 1 -
  sw ( 1? 1 -
    2dup xor 16 <<
	$ff or | opacity
	a!+
    ) drop
  ) drop ;

:
 patternxor
| 'patternxor onshow
;
