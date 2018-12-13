| Array 16 vals
| PHREDA 2018
|------

::p.ini | cantidad list --
	here dup rot !+ ! 6 << 'here +! ;

::p.clear | list --
	dup 4+ @ swap ! ;

::p.cnt | list --
	@+ swap @ | last fist
	- 6 >> ;

::p!+ | 'act list -- adr
	dup >r @ !+
	64 r> +! ;

::p! | list -- adr
	dup >r @
	64 r> +! ;

:delp | list end now -- list end- now-
	nip over @ swap	| recalc end!!
	swap 64 - 2dup 16 move
	dup pick3 !
	swap 64 - ;

::p.draw | list --
	dup @+ swap @
	( over <? )(
		dup @+ exec 0? ( drop delp )
		64 + ) 3drop ;

::p.del | adr list --
	>r r@ @ 64 - 16 move
	-64 r> +! ;
|dup @ 64 - swap ! ;

::p.mapv | 'vector list --
	@+ swap @
	( over <? )(
		pick2 exec
		64 + ) 3drop ;

::p.mapd | 'vector list --
	@+ swap @
	( over <? )(
		pick2 exec 0? ( drop dup delp )
		64 + ) 3drop ;

|........
:pmapmap | 'adr 'list 'vec --
	>r
	@+ swap @
	( over <? )(
		pick2 over <>? ( r@ exec )( drop )
		64 + )
	2drop r> drop ;

::p.map2 | 'vec 'list ---
	@+ swap @
	( over <? )(
		dup 64 + ( pick2 <? )(
			pick3 exec
			64 + ) drop
		64 + )
	3drop ;


:p.up | adr -- adr ; swap 64 -
	dup dup 64 - >a | p1 r:p2
	16 ( 1? )( 1- swap
		a@ over @ a!+ swap !+
		swap )
	2drop ;

::p.lastsort | col 'list --
	@+ swap @ swap 64 - | first last
	( over >? )(
		dup 64 -
		pick3 2 << + @
		over pick4 2 << + @
		<? ( 4drop ; ) drop
		p.up
		64 - ) 3drop ;
