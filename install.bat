@echo off

set NAME=libnations
set CIOSNATIONS=%~dp0
set ORIGINAL=%CD%
set COMPILEPATH=%CD%\Nations
set /p VERSION=<%CIOSNATIONS%\VERSION.txt

mkdir %COMPILEPATH%
cd %COMPILEPATH%

cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x86 release static
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x86 release shared
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x86 debug   static
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x86 debug   shared
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x64 release static
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x64 release shared
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x64 debug   static
cmd /A /Q /K %CIOSNATIONS%\scripts\install.bat x64 debug   shared

cd %ORIGINAL%
rd /S /Q %COMPILEPATH%
echo Compile Done
rem exit
