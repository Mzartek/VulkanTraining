@echo off
setlocal

set "BASEDIR=%~dp0"
set "SRCDIR=%BASEDIR%src\"
set "COMPILER=%BASEDIR%glslangValidator.exe"

if "%1" equ "" (
    call :compile_shaders *.vert
    call :compile_shaders *.tesc
    call :compile_shaders *.tese
    call :compile_shaders *.geom
    call :compile_shaders *.frag
    call :compile_shaders *.comp
) else if "%1" equ "clean" (
    call :clean_shaders
)
goto :eof

:compile_shaders
for /f %%f in ('dir /b /s "%SRCDIR%%1" 2^>nul') do (
    pushd %%~dpf
    call "%COMPILER%" -V %%f
    popd
)
goto :eof

:clean_shaders
for /f %%f in ('dir /b /s "%SRCDIR%*.spv" 2^>nul') do (
    del "%%f"
)
goto :eof

endlocal
