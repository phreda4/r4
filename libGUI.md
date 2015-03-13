# libgui.txt #

la GUI se maneja con una descripcion de las zonas sensibles que ejecutan diferentes palabras.

# Descripcion #

Mostrar y ejecutar GUI
```
::gui | 'tablegui --
```

Acciones
```
::onIn | vec --
::onUp | vec --
::onDn | vec --
::onMove | vec --
```

Contenedores
```
::.vlist | cnt 'acc --
::.hlist | cnt 'acc --
::.table | row col 'acc --
```

Botones
```
::.hbtns | 'dir --
::.vbtns | 'dir --
::.btns | acc dib color  --
::.btnl |  acc "str" color --
::.btnt |  acc "str" color --
::.hbtnt | 'lista --
::.hradio | 'var 'dir --
::.vradio | 'var 'dir --
::.hslide | 'var --
::.vslide | 'var --
```

Dibujo del cursor
```
::ccruz | --
::cflecha | --
::cmano | --
::clapiz | --
::cgoma | --
```

Dibujos predefinidos para usar en botones
```
#:iaba 
#:iarr 
#:iizq 
#:ider 
#:ilupa 
#:ireloj
#:iborrar
#:ifin 
#:iok 
#:idibuja
#:icopia 
#:irec 
#:istop
#:iplay
#:iff
#:ibb
#:icolor
#:itacho
#:irecicla
#:icurva
#:imas 
#:imenos
#:icorazon
#:ipica
#:idiamante
#:itrebol
#:itrazo 
#:ipreg 
```