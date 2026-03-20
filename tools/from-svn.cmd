@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: %~nx0 ^<svn-url^>
    exit /b 1
)

set "url=%~1"
set "repo_name=%~n1"

if not exist libraries (
    mkdir libraries
    if errorlevel 1 (
        echo Error: Failed to create 'libraries' directory
        exit /b 1
    )
)

if exist "libraries\!repo_name!" (
    echo Note: Directory 'libraries\!repo_name!' already exists. Skipping checkout.
    exit /b 0
)

echo Checking out !repo_name!...
svn checkout !url! libraries\!repo_name!
if errorlevel 1 (
    echo Error: Failed to checkout !repo_name! repository
    exit /b 1
)

echo Successfully checked out !repo_name!
endlocal
