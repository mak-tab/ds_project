@echo off
echo Compiling...
g++ src/*.cpp -I include -o library_app.exe
if %errorlevel% equ 0 (
    echo Compilation successful! Running app...
    echo -------------------------------------
    library_app.exe
) else (
    echo Compilation FAILED! Check your code.
    pause
)