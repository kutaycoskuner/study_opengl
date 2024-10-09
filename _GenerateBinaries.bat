@echo off
:: echo off is preventing to print all lines of code 

setlocal enabledelayedexpansion

:: ---------------------------------------------------------------------------------------
::              varıables
:: ---------------------------------------------------------------------------------------


set CALL_PATH=0
set CURRENT_DIR=%cd%
set SOLUTION_DIRECTORY=build

:: Read project name from config/config.txt
::  for /f "tokens=2 delims==" %%A in (config/config.yaml) do set PROJECT_NAME=%%A

::  echo Project Name: %PROJECT_NAME%
::  exit /b 0

:: ---------------------------------------------------------------------------------------
::              parameter scan
:: ---------------------------------------------------------------------------------------
for %%i IN (%*) DO (
    set CALL_PATH=%%i
)

call :print "running _GenerateBinaries.bat"

:: TODO more parameter handling
:: if "%%i"=="-c"      call :AddBuildTask_Clean


:: ---------------------------------------------------------------------------------------
::              check if build folder and solution file exist otherwise create
:: ---------------------------------------------------------------------------------------
if !CALL_PATH! EQU 0 (
    if not exist !SOLUTION_DIRECTORY! (
        call :print "could not found solution directory"
        call ./_GenerateBuildProject.bat
        exit /b 0
    )
    if exist !SOLUTION_DIRECTORY! (
        if not exist !SOLUTION_DIRECTORY!/*.sln (
            call :print "could not found solution file"
            call ./_GenerateBuildProject.bat
            exit /b 0
        ) 
    )
)

:: ---------------------------------------------------------------------------------------
::              generate binaries
:: ---------------------------------------------------------------------------------------
if !CALL_PATH! EQU 0 (
    cd !SOLUTION_DIRECTORY!
)

:: Build the project for both configurations
for %%c in (Debug Release) do (
    cmake --build . --config %%c
    if !errorlevel! NEQ 0 (
        call :print "Encountered problem on building binaries in <%%c> configuration"
        exit /b 1
    )
    call :print "Binaries successfully generated for <%%c> configuration"
)

if CALL_PATH EQU 0 (
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
