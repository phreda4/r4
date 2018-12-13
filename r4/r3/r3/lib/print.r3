^lib/sys.r3
^lib/fontpc.r3
|---------------
| PRINT LIB
| PHREDA 2018
|---------------

##ccx 0 ##ccy 0
##cch 16 ##ccw 8

#_charemit 'char8pc
#_charsize 'size8pc

::font! | 'vemit 'vsize --
  '_charsize ! '_charemit ! ;

::emit | c --
  $ff and _charemit ex
  _charsize ex 'ccx +! ;

::home
  0 'ccx ! 0 'ccy ! ;

::print | "" --
  ccx ccy xy>v >a
  ( c@+ 1?
    emit ) 2drop ;

::cr
  cch 'ccy +! 0 'ccx ! ;