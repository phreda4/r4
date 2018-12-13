| r3 lib string
| PHREDA 2018

#mbuff * 48

:mbuffi |-- adr
  'mbuff 47 + 0 over c! 1 - ;
  
:sign | sign --
  -? ( drop $2d over c! ; ) drop 1 + ;
 
::.d | val -- str
  dup abs mbuffi swap 
  ( 10 /mod $30 + pick2 c! swap 1 - swap 1? ) drop
  swap sign ;

::.b | bin -- str
  mbuffi swap
  ( dup $1 and $30 + pick2 c! swap 1 - swap 1 >>> 1? ) drop
  1 + ;

::.h | hex -- str
  mbuffi swap
  ( dup $f and $30 + $39 >? ( 8 + ) pick2 c! swap 1 - swap 4 >>> 1? ) drop
  1 + ;

