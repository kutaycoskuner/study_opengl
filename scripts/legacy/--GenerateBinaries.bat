@echo off
:: echo off is preventing printing all lines of code 

setlocal enabledelayedexpansion

:: ---------------------------------------------------------------------------------------
::              variables
:: ---------------------------------------------------------------------------------------

set CALL_PATH=0
set CURRENT_DIR=%cd%
set SOLUTION_DIRECTORY=build

:: Read project name from config/config.txt (disabled for now)
:: for /f "tokens=2 delims==" %%A in (config/config.yaml) do set PROJECT_NAME=%%A

:: echo Project Name: %PROJECT_NAME%
:: exit /b 0

:: ---------------------------------------------------------------------------------------
::              parameter scan
:: ---------------------------------------------------------------------------------------
for %%i IN (%*) DO (
    set CALL_PATH=%%i
)

call :print "Running --GenerateBinaries.bat"

:: TODO: More parameter handling
:: if "%%i"=="-c" call :AddBuildTask_Clean


:: ---------------------------------------------------------------------------------------
::              check if build folder and solution file exist otherwise create
:: ---------------------------------------------------------------------------------------
if !CALL_PATH! EQU 0 (
    if not exist "!SOLUTION_DIRECTORY!" (
        call :print "Could not find solution directory. Attempting to create solution..."
        call ./--GenerateBuildProject.bat
        if !errorlevel! NEQ 0 (
            call :print "ERROR: Failed to generate build project. Exiting..."
            exit /b 1
        )
    )

    if exist "!SOLUTION_DIRECTORY!" (
        if not exist "!SOLUTION_DIRECTORY!\*.sln" (
            call :print "Could not find solution file. Running build project generation..."
            call ./--GenerateBuildProject.bat
            if !errorlevel! NEQ 0 (
                call :print "ERROR: Failed to generate solution file. Exiting..."
                exit /b 1
            )
        )
    )
)

:: ---------------------------------------------------------------------------------------
::              generate binaries
:: ---------------------------------------------------------------------------------------
if !CALL_PATH! EQU 0 (
    cd "!SOLUTION_DIRECTORY!"
)

:: Build the project for both Debug and Release configurations
for %%c in (Debug Release) do (
    call :print "Building binaries for <%%c> configuration..."
    cmake --build . --config %%c
    if !errorlevel! NEQ 0 (
        call :print "ERROR: Encountered problem building binaries in <%%c> configuration"
        exit /b 1
    )
    call :print "Binaries successfully generated for <%%c> configuration"
)

if !CALL_PATH! EQU 0 (
    cd ..
)

exit /b 0


:: ---------------------------------------------------------------------------------------
::              functions
:: ---------------------------------------------------------------------------------------
:print
echo.
echo %*
exit /b
