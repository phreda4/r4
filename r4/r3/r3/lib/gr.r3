^lib/sys.r3

| r3 lib VFRAME play
| PHREDA 2018

##ink $ff00ff
##paper $ff

##xa 0 ##ya 0

::cls
  paper vframe sw sh * fill ;

::xy>v | x y -- adr
  sw * + 2 << vframe + ;

::pset | x y --
  xy>v ink swap ! ;

::pget | x y -- c
  xy>v @ ;

:hline | xd yd xa --
  pick2 - 0? ( drop pset ; )
  -? ( rot over + rot rot neg )
  >r xy>v ink swap r> fill ;

:hlineo | xmin yd xmax --
  pick2 - 0? ( drop pset ; )
  >r xy>v ink swap r> fill ;

:vline | x1 y1 cnt
	rot rot xy>v >a
	( 1? 1 - ink a! sw 2 << a+ ) drop ;

:iline | xd yd --
  ya =? ( xa hline ; )
  xa ya
  pick2 <? ( 2swap )   | xm ym xM yM
  pick2 - 1 + >r	   | xm ym xM  r:canty
  pick2 - 0? ( drop r> vline ; )
  r@ 16 <</
  rot 16 << $8000 +
  rot rot r>           | xm<<16 ym delta canty
  ( 1? 1 - >r >r
    over 16 >> over pick3 r@ + 16 >> hline
    1 + swap
    r@ + swap
    r> r> ) 4drop ;

::line | x y --
  2dup iline

::op | x y --
  'ya ! 'xa ! ;

::rect  | w h x y --
  xy>v >a
  ( 1? 1 -
    ink a> pick3 fill
	sw 2 << a+
    ) 2drop ;

#ym #xm
#dx #dy

:qf
	xm pick2 - ym pick2 - xm pick4 + hlineo
	xm pick2 - ym pick2 + xm pick4 + hlineo ;

::ellipse | x y rx ry --
	'ym ! 'xm !
	over dup * dup 1 <<		| a b c 2aa
	swap dup >a 'dy ! 		| a b 2aa
	rot rot over neg 1 << 1 +	| 2aa a b c
	swap dup * dup 1 << 		| 2aa a c b 2bb
	rot rot * dup a+ 'dx !	| 2aa a 2bb
	swap 1				| 2aa 2bb x y
	pick3 'dy +! dy a+
	xm pick2 - ym xm pick4 + hlineo
	( swap +? swap 		| 2aa 2bb x y
		a> 1 <<
		dx >=? ( rot 1 - rot rot pick3 'dx +! dx a+ )
		dy <=? ( rot rot qf 1 + rot pick4 'dy +! dy a+ )
		drop
		)
	4drop ;

::circle | x y r --
	dup ellipse ;

::circleb | x y r --
	dup 1 << 'ym ! 1 - 0
	1 'dx ! 1 'dy !
	1 ym - 'xm !
	( over <?  | x0 y0 x y
		pick3 pick2 + pick3 pick2 + pset
		pick3 pick2 - pick3 pick2 + pset
		pick3 pick2 + pick3 pick2 - pset
		pick3 pick2 - pick3 pick2 - pset
		pick3 over + pick3 pick3 + pset
		pick3 over - pick3 pick3 + pset
		pick3 over + pick3 pick3 - pset
		pick3 over - pick3 pick3 - pset
		xm
		0 <=? (
			swap 1 + swap
			dy +
			2 'dy +!
			)
		0 >? (
			rot 1 - rot rot
			2 'dx +!
			dx ym - +
			)
		'xm !
		) 4drop ;

