# Introduction #

The executables in the distribution ( [r4](https://code.google.com/p/reda4/source/detail?r=4).exe, r4gl.exe) are compiled for the windows environment. They won't work directly in Linux.

# Details #

All that's needed is _**Wine**_ (http://www.winehq.org/). Thanks to that great project you can run windows executables in the linux operating system.

In ubuntu, you'd run **sudo apt-get install wine** to have the package installed.

Once Wine is installed, just go to the directory in which :[r4](https://code.google.com/p/reda4/source/detail?r=4) was installed and type in :

**wine [r4](https://code.google.com/p/reda4/source/detail?r=4).exe**

to have the system run in the default resolution.

Otherwise, all command line parameters are available, amongst which :

**wine [r4](https://code.google.com/p/reda4/source/detail?r=4).exe w1280 h800**

which opens the system in a 1280X800 resolution.

It's really that simple, audio works fine too !