<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: redamationcolor - Win32 (WCE ARM) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMRel/reda4.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC=310" /d "ARM" /d "_ARM_" /r "C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\reda4.rc"" 
Creating temporary file "C:\Windows\Temp\RSPE522.tmp" with contents
[
/nologo /W3 /O2 /Ob2 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC=310" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /FAs /Fa"ARMRel/" /Fp"ARMRel/reda4.pch" /YX /Fo"ARMRel/" /Oxs /MC /c 
"C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\graf.cpp"
"C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\mat.cpp"
"C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\redalib.cpp"
"C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\redam.cpp"
"C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\StdAfx.cpp"
]
Creating command line "clarm.exe @C:\Windows\Temp\RSPE522.tmp" 
Creating temporary file "C:\Windows\Temp\RSPE523.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib gx.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMRel/reda4.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"ARMRel/reda4.exe" /subsystem:windowsce,3.00 /align:"4096" /MACHINE:ARM 
".\ARMRel\graf.obj"
".\ARMRel\mat.obj"
".\ARMRel\redalib.obj"
".\ARMRel\redam.obj"
".\ARMRel\StdAfx.obj"
".\ARMRel\reda4.res"
]
Creating command line "link.exe @C:\Windows\Temp\RSPE523.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
graf.cpp
mat.cpp
redalib.cpp
redam.cpp
C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\redam.cpp(212) : warning C4244: '=' : conversion from '__int64' to 'int', possible loss of data
StdAfx.cpp
Linking...
LINK : warning LNK4089: all references to "AYGSHELL.dll" discarded by /OPT:REF




<h3>Results</h3>
reda4.exe - 0 error(s), 2 warning(s)
</pre>
</body>
</html>
