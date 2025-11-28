@echo off
REM build.bat - Build and run helper for BankTransaction (Windows cmd)

if /I "%~1"=="clean" (
    if exist "BankTransaction.exe" del /Q "BankTransaction.exe"
    echo Cleaned.
    exit /b 0
)

where gcc >nul 2>&1
if errorlevel 1 (
    echo GCC not found. Please install MinGW or add gcc to PATH.
    exit /b 1
)

echo Compiling BankTransaction...
gcc -g "BankTransaction.c" "bank_transaction_impl.c" -o "BankTransaction.exe"
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: BankTransaction.exe

if /I "%~1"=="run" (
    echo Running BankTransaction.exe
    .\BankTransaction.exe
)

exit /b 0
