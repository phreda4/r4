# libtrig.txt #

Libreria de trigonometria en punto fijo
Se utiliza como unidad de angulo el 1.0 de punto fijo

| Grados | hexa | punto fijo |
|:-------|:-----|:-----------|
| 0/360 | $0/$10000 | 0.0/1.0 |
| 90 | $3fff | 0.25 |
| 180 | $7fff | 0.5 |
| 270 | $bfff | 0.75 |

Library for fixed point trigonometry

# WORDS #

Coseno, Seno por tabla de 1024 elementos

```
::cos 	| bangle -- sin

::sin 	| bangle -- sin

::sincos | bangle -- sin cos

::xy+polar | x y bangle r -- x y

::ar>xy | xc yc bangle r -- xc yc x y
```

Obtener angulo
```
::atan2 | x y -- bangle
```

Calculo de distancia (octogono en  vez de esfera)

```
::distfast | dx dy -- dis
```

Calculo de raiz cuadrada por tabla
```
::sqrt | n -- sqrt
```