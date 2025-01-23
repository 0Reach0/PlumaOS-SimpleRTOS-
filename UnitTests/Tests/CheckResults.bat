@echo off


set results_dir=build\test\results


dir /b %results_dir% | find ".fail" >nul 2>&1
if %errorlevel% equ 0 (
    echo Tests failed!
    exit /b 1
) else (
    echo Tests passed!
    exit /b 0
)