@echo off
REM build.bat - Build and run helper for ShowReservation (Windows cmd)

if /I "%~1"=="clean" (
    if exist "ShowReservation.exe" del /Q "ShowReservation.exe"
    echo Cleaned.
    exit /b 0
)

where gcc >nul 2>&1
if errorlevel 1 (
    echo GCC not found. Please install MinGW or add gcc to PATH.
    exit /b 1
)

echo Compiling ShowReservation...
gcc -g "ShowReservation.c" "show_reservation_impl.c" -o "ShowReservation.exe"
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: ShowReservation.exe

if /I "%~1"=="run" (
    echo Running ShowReservation.exe
    .\ShowReservation.exe
)

exit /b 0
