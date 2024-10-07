@echo off
:: echo off is preventing to print all lines of code 

setlocal enabledelayedexpansion
:: What is Delayed Expansion?
:: In a batch file, by default, variables are evaluated at the time a line of code is parsed, not when the code is executed. This can cause issues in loops or conditionals where the value of a variable may change during execution, but the batch interpreter doesn't recognize the updated value because it uses the initial value from the time the line was parsed.

:: ---------------------------------------------------------------------------------------
::              variables
:: ---------------------------------------------------------------------------------------
set LAUNCH_VS=1
set SOLUTION_DIRECTORY=build
set PROJECT_NAME=test_opengl

:: TODO Parameter scan



:: ---------------------------------------------------------------------------------------
::              check if cmake is installed
:: ---------------------------------------------------------------------------------------
echo.
:: echo. -> new line
echo Checking program prerequisites...


:: check if cmake is installed
cmake --version > nul 2>&1
if !errorlevel! NEQ 0 (
    echo [!PROJECT_NAME!] cannot find path to cmake. Please install cmake.
    exit /b -1
) else (
    echo [!PROJECT_NAME!]   CMake            - Ready.
)

:: Check if submodule is initialized to avoid CMake file not found errors
call :CheckAndInitializeSubmodules


:: ---------------------------------------------------------------------------------------
::              clean install if if build already exists
:: ---------------------------------------------------------------------------------------
echo.
echo clean setup initialization
if exist !SOLUTION_DIRECTORY! (
    rmdir /s /q !SOLUTION_DIRECTORY!
    echo .
    echo removed existing build directory 
)

:: Generate build directory
if not exist !SOLUTION_DIRECTORY! (
    echo [!PROJECT_NAME!] Creating directory !SOLUTION_DIRECTORY!...
    mkdir !SOLUTION_DIRECTORY!
)

:: TODO Run cmake
cd !SOLUTION_DIRECTORY!



:: ---------------------------------------------------------------------------------------
::              generate solution folders in build/
:: ---------------------------------------------------------------------------------------
echo.
echo generataing solution files.

cmake ..


::if !LAUNCH_VS! EQU 1 (
::    start %SOLUTION_FILE%
::)

if !errorlevel! EQU 0 (
    echo [!PROJECT_NAME!] Success!
) else (
    echo.
    echo [!PROJECT_NAME!] Error with CMake. No solution files generated.
    echo. 
    exit /b -1
)

:: ---------------------------------------------------------------------------------------
::              generate binaries
:: ---------------------------------------------------------------------------------------
call ../_GenerateBinaries.bat !SOLUTION_DIRECTORY!
if !errorlevel! EQU 0 (
    echo.
    echo Solution file and binaries are ready. You can try to start solution:
    echo ./build/!PROJECT_NAME!.sln
    echo. 
    echo or directly call the executable:
    echo ./bin/Windows/x64/Release/!PROJECT_NAME!.exe
) else (
    echo.
    echo encountered problem on building binaries
    exit /b -1
)


cd ..

exit /b 0

:: ---------------------------------------------------------------------------------------
::              functions
:: ---------------------------------------------------------------------------------------
:CheckAndInitializeSubModules
:: TODO write this function if necessary
echo.
echo checking and initializing submodules.
exit /b 0
