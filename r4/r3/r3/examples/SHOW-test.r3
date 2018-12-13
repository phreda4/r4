| Example 4

^lib/gr.r3

|--------------------
#x 10 #vx 1
#y 10 #vy 1

:hitx vx neg 'vx ! ;
:hity vy neg 'vy ! ;

:box
 xy>v >a $ff00ff a! ;

:show
 cls

 x sw 4 - >=? ( hitx ) 4 <=? ( hitx )
 y sh 4 - >=? ( hity ) 4 <=? ( hity )
 box
 vx 'x +!
 vy 'y +!
 ;

|--------------------
:
'show onshow
;
