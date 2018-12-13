| Example 3

^lib/dom.r3

#var 0

:1+ 1 'var +! ;
:1- -1 'var +! ;

:dom
  <br>
  "Hola Mundo" echo <br>
  '1- " -1 " <btn>
  " " echo var .d echo " " echo
  '1+ " +1 " <btn>
  <br>
  ;

:  
'dom ondom
dom
;