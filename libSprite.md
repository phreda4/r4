# libsprite.txt #

Libreria para dibujar sprites vectoriales

# WORDS #

Dibuja sprite en el CG
```
::nsprite | adr --
```

Dibuja sprite en el CG rotado en angulo ang
```
::rnsprite | adr ang --
```

Dibuja sprite segun la matriz3d activa
```
::3dnsprite | adr --
```

```
::nDraw | 'adr --
```
```
::nDrawLayer | 'adr --
```

| n 0.0 .. 1.0
| s1 sprite fuente 1
| s2 sprite fuente 2
| s3 sprite destino
|----------------------------------
```
::nSprInter | n s1 s2 s3 --
```