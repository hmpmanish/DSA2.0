@echo off
echo =================================================================
echo   Compiling and Testing all CSCR2501 DSA Lab Experiments
echo =================================================================

for %%f in (Exp*.c Value_Added*.c) do (
    echo Compiling %%f...
    gcc -Wall -Wextra -std=c99 "%%f" -o "%%~nf.exe" -lm
    if errorlevel 1 (
        echo [ERROR] Failed to compile %%f
    ) else (
        echo [SUCCESS] %%f compiled successfully.
    )
)

echo.
echo All compilations finished!
pause
