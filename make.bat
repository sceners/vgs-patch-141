@echo off
\mcpp60\bin\cl.exe -c -MD -G6 -O2 -nologo -I\mcpp60\include *.c
\mcpp60\bin\rc.exe -r -i\mcpp60\include rsrc.rc
\masm32\bin\link.exe -out:VGSPatch141.exe -subsystem:windows -nologo -libpath:\mcpp60\lib -defaultlib:user32.lib -defaultlib:gdi32.lib *.obj rsrc.res
del *.obj
del *.res