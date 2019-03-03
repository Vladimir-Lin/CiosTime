@echo off

set ARCHX=%1
set BTYPE=%2
set DLLX=%3
set TARGET=%NAME%-%ARCHX%-%BTYPE%-%DLLX%
set ARCHPATH=%ARCHX%\%DLLX%\%BTYPE%
set LIBPLACE=%CIOS%\lib\%ARCHPATH%
set PKGPLACE=%CIOS%\Packages\%ARCHPATH%

7z x %CIOSNATIONS%\Packages\%TARGET%.7z

cd %COMPILEPATH%\%TARGET%\lib\packages

fart libnations.pc "$${INCLUDEPATH}" "%CIOSPATH%/include"
fart libnations.pc "$${LIBPATH}" "%CIOSPATH%/lib/%ARCHX%/%DLLX%/%BTYPE%"

cd %COMPILEPATH%\%TARGET%

xcopy /Y %COMPILEPATH%\%TARGET%\lib\libnations.lib %LIBPLACE%\libnations.lib
xcopy /Y %COMPILEPATH%\%TARGET%\lib\packages\libnations.pc %PKGPLACE%\libnations.pc
xcopy /Y %COMPILEPATH%\%TARGET%\bin\libnations.dll %LIBPLACE%\DLL\libnations.dll

cd %COMPILEPATH%

rd /S /Q %COMPILEPATH%\%TARGET%
exit
