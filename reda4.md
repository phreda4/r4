# reda4.txt #

Libreria inicial o de bajo nivel.
Palabra para el manejo de  Teclado, Memoria, Conversion y otros.

incluye la tabla de conversion de scancodes a Ascii
```
^key-es1.txt	| 
```

# Words #

Variable de tecla SHIFT
```
#:mshift 
```

Asigna vector a tecla presionada o suelta.
nro es el scancode.
```
::>key | vector nro --
::>ukey | vector nro --
```

Limpia todas las acciones del teclado.
```
::clearkey | --
```

Convierte el scancode en ascii
```
::toasc | nro -- ascii
```

Inicia la interrupcion del teclado
```
:inikey | --
```

Accion tocando cualquier tecla
```
:<todas> | vec --
```

Accion soltando cualquier tecla
```
:>todas< | vec --
```

Accion para teclas con caracter visible
```
:<visible> | vec --
```

Asignacion de accion para diferentes teclas:
```
:<cntrl>  :>cntrl< 
:<esc> 	  :>esc< 
:<esp>   :>esp< 
:<f1>   :>f1<
::<f2>
::<f3>
::<f4>
::<f5> 
::<f6> 
::<f7> 
::<f8> 
::<f9> 
::<f10> 
::<f11> 
::<f12> 
::<back>
::<tab> 
::<enter> 
::<home> ::<end> 
::<arr> ::<aba> 
::<der> ::<izq> 
::<ins> ::<del> 
::<pgup> ::<pgdn> 
::>home< ::>end< 
::>arr< ::>aba< 
::>der< ::>izq< 
::>ins< ::>del< 
::>pgup< ::>pgdn< 
```

Apila y desapila teclado, sirve para guardad el estado que estaba.
```
::key.push | --
::key.pop | --
```

Punto fijo 16.16bits, multiplicacion y Division.
```
::*.	| a b -- c
::/.	| a b -- c
```

Memoria y strings
```
::zcopy | destino fuente -- destino' con 0
::strcat | src des --
::strcpy | src des --
::strcpyl | src des -- ndes
::strcpyln | src des --
```

Contar y convertir strings
```
::count | s1 -- s1 cnt
::toupp | c -- C
::tolow | C -- c
```

Comparacion de cadenas
```
::=word= | s1 s2 -- 0 \ s2' 1
::= | s1 s2 -- 1/0
::=pre | s1 s2 -- 1/0
::=w | s1 s2 -- 1/0
```

Memoria libre
```
#:here
::clear 
::>, 
::, 
::,c 
::,s 
::,w 
::,n | dec --
::,h | hex --
::,b | bin --
::,ln 
::,cr 
::,eol 
::,sp 
::,emit | c --
::,print | adr --
```

Numero aleatorios
```
#:seed 
::rand | -- v
::rerand | --

::min | a b -- c
::max | a b -- c

::blink | -- 0/1
```

Variable que marca salida
```
#:.exit
```

Manejo de tiempo dentro del SHOW
```
::.restart | --
::.segs | seg --
::.mseg | seg --  R:X?
```

Salir de show
```
::exit | --
```

Palabra de interaccion.
luego de SHOW debe haber 1 palabra por lo menos y esta se repetira 30 veces por segundo.
```
::show  | --
```

Igual a SH pero sin limitador de frames
```
::showo | --
```

Espera hasta exit
```
::wait | --
```

Tiempo
```
::late | amp -- n
::pinpon | amp -- n
```

Vector 3d
vector3d a 10 bits
x=10 bits y=10 bits z=10 bits control=2bit
```
::>z
::>y 
::>x 
::>xyz | v -- x y z
::3d> | x y z -- v
```

Vector 2d
vector2d de 14 bits c/control
x=14 bits	y=14 bits  control=4bits
```
:xy>d | x y -- v
:d>xy | v -- x y
:d>y | v -- y
:d>x | v -- x

:dxy |v1 v2 -- dx dy
```

Vector uv
x=16 bits y= 16bits
```
:uv> | u v -- uv
:>u 
:>v 
:>uv | v -- u v
```