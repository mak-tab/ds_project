@echo off
echo ==========================================
echo       BUILDING LIBRARY SYSTEM
echo ==========================================

if exist library_app.exe del library_app.exe

g++ main.cpp src/Book.cpp src/Queue.cpp src/Library.cpp src/FileManager.cpp src/AuthManager.cpp src/FineManager.cpp src/LoanManager.cpp -I include -o library_app.exe

if %errorlevel% equ 0 (
    echo [SUCCESS] Compilation finished.
    echo [INFO] Starting application...
    echo ------------------------------------------
    library_app.exe
) else (
    echo [ERROR] Compilation FAILED! 
    pause
)