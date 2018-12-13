| Example PRINT

^lib/print.r3

:
cls
$ff0000ff 'ink !
"Hello Word!" print cr
$ff00ff 'ink !
"Hola Mundo!" print cr
$ffff 'ink !
"r3" print cr
;