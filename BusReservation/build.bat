@echo off
REM build.bat - Build and run helper for BusReservation (Windows cmd)

if /I "%~1"=="clean" (
    if exist "BusReservation.exe" del /Q "BusReservation.exe"
    echo Cleaned.
    exit /b 0
)

where gcc >nul 2>&1
if errorlevel 1 (
    echo GCC not found. Please install MinGW or add gcc to PATH.
    exit /b 1
)

echo Compiling BusReservation...
gcc -g "BusReservation.c" "bus_reservation_impl.c" -o "BusReservation.exe"
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: BusReservation.exe

if /I "%~1"=="run" (
    echo Running BusReservation.exe
    .\BusReservation.exe
)

exit /b 0
