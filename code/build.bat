
@echo off
set code_path=..\code
set debug_fg=/permissive- /nologo /W4 /WX /Zi /DDEBUG=1

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

REM c code compilation
cl %debug_fg% /Fe:app.exe %code_path%\main.c

echo Running application ../

REM run application
app.exe > image.ppm
popd
