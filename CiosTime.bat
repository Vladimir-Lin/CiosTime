@echo off

set NAME=libnations
set CIOSNATIONS=%~dp0
set ORIGINAL=%CD%
set COMPILEPATH=%CD%\Nations
set /p VERSION=<%CIOSNATIONS%\VERSION.txt

mkdir %COMPILEPATH%
cd %COMPILEPATH%

cmd /A /Q /K %CIOSNATIONS%\scripts\x86.bat %COMPILEPATH% Release static 1 0
cmd /A /Q /K %CIOSNATIONS%\scripts\x86.bat %COMPILEPATH% Release shared 0 1
cmd /A /Q /K %CIOSNATIONS%\scripts\x86.bat %COMPILEPATH% Debug   static 1 0
cmd /A /Q /K %CIOSNATIONS%\scripts\x86.bat %COMPILEPATH% Debug   shared 0 1
cmd /A /Q /K %CIOSNATIONS%\scripts\x64.bat %COMPILEPATH% Release static 1 0
cmd /A /Q /K %CIOSNATIONS%\scripts\x64.bat %COMPILEPATH% Release shared 0 1
cmd /A /Q /K %CIOSNATIONS%\scripts\x64.bat %COMPILEPATH% Debug   static 1 0
cmd /A /Q /K %CIOSNATIONS%\scripts\x64.bat %COMPILEPATH% Debug   shared 0 1

cd %ORIGINAL%
rd /S /Q %COMPILEPATH%
echo Compile Done
rem exit
