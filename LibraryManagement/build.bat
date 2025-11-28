@echo off
REM build.bat - Build and run helper for LibraryManagement (Windows cmd)

if /I "%~1"=="clean" (
    if exist "LibraryManagement.exe" del /Q "LibraryManagement.exe"
    echo Cleaned.
    exit /b 0
)

where gcc >nul 2>&1
if errorlevel 1 (
    echo GCC not found. Please install MinGW or add gcc to PATH.
    exit /b 1
)

echo Compiling LibraryManagement...
gcc -g "LibraryManagement.c" "library_management_impl.c" -o "LibraryManagement.exe"
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: LibraryManagement.exe

if /I "%~1"=="run" (
    echo Running LibraryManagement.exe
    .\LibraryManagement.exe
)

exit /b 0
