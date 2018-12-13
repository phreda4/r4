| SYS IO
| PHREDA 2018

::vframe | -- video.buffer.memory
 0 sysmem ;
::sw | -- screen.width
 1 sysmem ;
::sh | -- screen.heigth
 2 sysmem ;
::msec | -- system.miliseconds
 3 sysmem ;
::time | -- hhmmss
 4 sysmem ;
::date | -- yyyymmdd
 5 sysmem ;

::xymouse | -- xmouse ymouse
 8 sysmem dup $ffff and swap 16 >> ;
::bmouse | -- mouse.button
 9 sysmem ;

::keycode | -- kcode
 6 sysmem ;
::keychar | -- kchar
 7 sysmem ;

::mem | -- start.free.memory
 10 sysmem ;

::echo | "" --    ; echo to dom
 0 syscall ;
::ondom | 'word --  ; when change the dom
 1 syscall ;

::onshow | 'word -- ; call every 30fps
 2 syscall ;
