| SYSTEM
| PHREDA 2019
|----------------

::xymouse | -- xmouse ymouse
	xypen dup $ffff and swap 16 >> ;

#.exit 0

::onshow | 'word --
	0 '.exit !
	0 ( drop
		10 update drop
		dup ex
		redraw
		.exit 1? )
	2drop
	0 '.exit !
	;

::exit
	1 '.exit ! ;