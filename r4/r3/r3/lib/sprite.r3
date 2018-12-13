| sprite
| PHREDA 2015,2018
|------------------------
| pal-type-w-h
| 4-4-12-12

^lib/gr.r3

#pal0
$000000ff $808080ff $C0C0C0ff $FFFFFFff $800000ff $FF0000ff $808000ff $FFFF00ff
$008000ff $00FF00ff $008080ff $00FFFFff $000080ff $0000FFff $800080ff $FF00FFff

#pal8
$000000ff $1D2B53ff $7E2553ff $008751ff $AB5236ff $5F574Fff $C2C3C7ff $FFF1E8ff
$FF004Dff $FFA300ff $FFEC27ff $00E436ff $29ADFFff $83769Cff $FF77A8ff $FFCCAAff


#wb #hb		| ancho alto
#paleta 'pal0

|-- internas para clip
#addm
#wi #hi

|-- internas para scale
#wr #hr
#sx #sy
#xa #ya


|---- w/alpha
:alp!+ | col --
|	$ff nan? ( drop 4 a+ ; )
	dup $ff and 
	0? ( drop a!+ ; )
	$ff =? ( 2drop 4 a+ ; )
	swap
	dup $ff00ff00 and				| alpha color colorand
	a@ dup $ff00ff00 and 		| alpha color colorand inkc inkcand
	pick2 - pick4 8 *>> rot +	| alpha color inkc inkcandl
	$ff00ff00 and >r				| alpha color inkc
	swap $ff0000 and 				| alpha px colorand
	swap $ff0000 and 				| alpha colorand pxa
	over - rot 8 *>> + $ff0000 and
	r> or $ff or a!+ ;

|----- 1:1

:clipw
	sw >? ( sw pick2 - ; ) wb ;

:negw
	-? ( dup 'wi +! neg 'addm ! 0 ; ) 0 'addm ! ;

:cliph
	sh >? ( sh pick2 - ; ) hb ;
	
:clip | x y	-- x y 
	swap wb over + clipw 'wi ! drop
	negw
	swap hb over + cliph 'hi ! drop
	-? ( dup 'hi +! neg wb * 'addm +! 0 )
	;
	
|---- opaque
:d0 | adr -- ;32 bit/pixel
	addm 2 << + >b
	wb wi - 2 <<
   	sw wi - 2 <<
	hi ( 1?
		wi ( 1? 
			b@+ a!+ 
			1 - ) drop
		over a+
		pick2 b+
		1 - ) 3drop ;
:d1 | adr -- ;8		
:d2 | adr -- ;4
:d3 | adr -- ;2
:d4 | adr -- ;1
	;
	
#odraw d0 d1 d2 d3 d4 0 0 0

::sprite | x y 'spr  --
	0? ( 3drop ; )
	@+
	dup $fff and 'wb !
	dup 12 >> $fff and 'hb !
	2swap clip | adr h x y
	wi hi or -? ( drop 4drop ; ) drop
	xy>v >a
	dup 28 >> 1? ( rot @+ 'paleta ! rot rot ) drop
	24 >> $f and 2 << 'odraw + @ ex ;

|----- DRAW ROT 1:1
:rotlim
	rot -? ( min ; ) rot max swap ;

:neglim
	-? ( 0 swap ; ) 0 ;

:inirot | x y r -- x y
	sincos 'xa ! 'ya !	| calc w&h
	xa wb * ya hb * neg 2dup +
	neglim rotlim rotlim
	- 16 >> 'wi !
	ya wb * xa hb * 2dup +
	neglim rotlim rotlim
	- 16 >> 'hi !		| calc ori
	wb 15 << wi xa * hi ya * - 1 >> - 'sx !
	hb 15 << hi xa * wi ya * + 1 >> - 'sy !
	swap wi wb - 1 >> -	| adjust & clip
	wi over + sw >? ( sw over - 'wi +! ) drop
	-? ( dup 'wi +! neg dup xa * 'sx +! ya * 'sy +! 0 )
	swap hi hb - 1 >> -
	hi over + sh >? ( sh over - 'hi +! ) drop
	-? ( dup 'hi +! dup ya * 'sx +! neg xa * 'sy +! 0 )
	;

:dotrot | xa ya w -- n
	over -? ( ; )
	16 >> hb >=? ( drop -1 ; )
	wb *
	pick3 -? ( nip ; )
	16 >> wb >=? ( 2drop -1 ; )
	+ ;

:point0
	-? ( drop 4 a+ ; ) 2 << b> + @ a!+ ;
	
:r0
	>b 
	inirot
	wi hi or -? ( 3drop ; ) drop
	xy>v >a
	sx sy
	hi ( 1?
		pick2 pick2
		wi ( 1?
			dotrot point0
			rot xa + rot ya +
			rot 1 - ) 3drop
		sw wi - 2 << a+
		rot ya - rot xa +
		rot 1 - )
	3drop ;

:point1
	-? ( drop 4 a+ ; ) 2 << b> + @ alp!+ ;
	
:r1 | x y r adr --
	>b 
	inirot
	wi hi or -? ( 3drop ; ) drop
	xy>v >a
	sx sy
	hi ( 1?
		pick2 pick2
		wi ( 1?
			dotrot point1
			rot xa + rot ya +
			rot 1 - ) 3drop
		sw wi - 2 << a+
		rot ya - rot xa +
		rot 1 - )
	3drop ;

#rdraw r0 r1 0 0 0 0 0 0 

::rsprite | x y r 'bmr --
	0? ( 3drop ; )
	@+ dup
	dup $fff and 'wb ! 
	12 >> $fff and 'hb !
	2swap clip | adr h x y
	wi hi or -? ( drop 4drop ; ) drop
	xy>v >a
	dup 28 >> 1? ( rot @+ 'paleta ! rot rot ) drop
	24 >> $7 and 2 << 'rdraw + @ ex ;


#nav32 $008008 | 8x8 32bits
$. $. $. $ffff $. $. $. $.
$. $. $. $ffff $. $. $. $.
$. $. $ffff $ffff $ffff $. $. $.
$. $. $ffff $ffff $ffff $. $. $.
$. $ffff $ffff $ffff $ffff $ffff $. $.
$. $ffff $ffff $ffff $ffff $ffff $. $.
$. $. $. $. $. $. $. $.
$. $. $. $. $. $. $. $.

:
cls
10 10 'nav32 sprite
;