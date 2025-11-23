@echo off
echo ==========================================
echo      BUILDING LIBRARY SYSTEM
echo ==========================================

:: Удаляем старый exe, если есть
if exist library_app.exe del library_app.exe

:: Компиляция с явным указанием всех файлов
g++ main.cpp src/Book.cpp src/Queue.cpp src/Library.cpp src/FileManager.cpp src/AuthManager.cpp src/FineManager.cpp -I include -o library_app.exe
:: Проверка результата
if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Compilation finished.
    echo [INFO] Starting application...
    echo ------------------------------------------
    library_app.exe
) else (
    echo.
    echo [ERROR] Compilation FAILED! 
    echo Please check if all files exist in 'src' folder and are saved.
    pause
)