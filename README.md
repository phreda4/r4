# :r4
Computer Programming Language based on ColorForth ideas

Start in 2005 when I study Forth.
:r4 is a Forth but more simpler but not less powerfull.

## Quick overview

The behavior of languaje is guided by prefix

* : prefix define code
* # prefix define data
* ^ prefix include definitions 
* ' prefix get the adress of code or data
* | prefix are comments, end at end of line
* " prefix define strings, end with "
* $ hex numbers
* % binary number
* : alone is the start point

example
```
#x 2
#y 3

:cuad | a -- a^2 
  dup * ;  
  
:dist | -- d^2   distance to x y
  x cuad y cuad + ;

: dist ;
```  

The conditionals:<br/>
0?, 1?, +?, -? are simple conditional, test but not destroy the top of stack (TOS), 0? are TOS=0.. and so on.<br/>
=?, <? .. and? .. are conditional with two values to compare, destroy the TOS.

Flow control is diferent from other forth, there are build in, with block of code construction.
```
?? ( .. ) are IF
?? ( .. )( .. ) are IF-ELSE
( ..?? )( .. ) are WHILE
( ..?? ) are UNTIL
```

example
```
:countdown
  10 ( 1? )( 1-     | while TOS are diferent from 0
    dup "%d" print cr
    ) drop ;
    
```  

# Actual development

This version is a bytecode interpreter for WINE, WINCE and ANDROID platform.

* forth-like language to program computers.
* uses prefixes to guide compiler behavior, like Colorforth but without colors..a colorless colorforth.
* has a VM, editor, games, programming samples.
* has a compiler for FASM asembler, can make standalone .exe

- Only can generate win exec, waiting for a smart coder for lin,mac etc.

# More info

* e-mail: pabloreda@gmail.com
* group: http://groups.google.com/group/reda4
* twitch: https://www.twitch.tv/phreda4
* youtube: http://www.youtube.com/user/pablohreda
* tools for compile r4VM (devcpp+fmod): https://drive.google.com/drive/folders/0Bz3UnwydnNGhRl9RSElYbkZhUU0
* some versions and test: https://drive.google.com/open?id=0Bz3UnwydnNGhQmlOSGRwaXJmX3c
