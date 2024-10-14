@echo off
:: echo off is preventing printing all lines of code 

setlocal enabledelayedexpansion
:: What is Delayed Expansion?
:: In a batch file, by default, variables are evaluated at the time a line of code is parsed, not when the code is executed. This can cause issues in loops or conditionals where the value of a variable may change during execution, but the batch interpreter doesn't recognize the updated value because it uses the initial value from the time the line was parsed.

:: ---------------------------------------------------------------------------------------
::              variables
:: ---------------------------------------------------------------------------------------
set LAUNCH_VS=1
set SOLUTION_DIRECTORY=build
set PROJECT_NAME=opengl_renderer

:: ---------------------------------------------------------------------------------------
::              check if cmake is installed
:: ---------------------------------------------------------------------------------------
echo.
echo Checking program prerequisites...

:: Check if cmake is installed
cmake --version > nul 2>&1
if !errorlevel! NEQ 0 (
    echo [!PROJECT_NAME!] cannot find path to cmake. Please install cmake.
    exit /b -1
) else (
    echo [!PROJECT_NAME!]   CMake            - Ready.
)

:: ---------------------------------------------------------------------------------------
::              Check if submodules are initialized
:: ---------------------------------------------------------------------------------------
call :CheckAndInitializeSubmodules
if !errorlevel! NEQ 0 (
    echo [!PROJECT_NAME!] Failed to initialize or update submodules.
    exit /b -1
)

:: ---------------------------------------------------------------------------------------
::              clean install if build already exists
:: ---------------------------------------------------------------------------------------
echo.
echo Clean setup initialization...
if exist "!SOLUTION_DIRECTORY!" (
    rmdir /s /q "!SOLUTION_DIRECTORY!"
    if !errorlevel! NEQ 0 (
        echo [!PROJECT_NAME!] Error: Could not remove existing build directory.
        exit /b -1
    )
    echo Removed existing build directory.
)

:: Generate build directory
if not exist "!SOLUTION_DIRECTORY!" (
    echo [!PROJECT_NAME!] Creating directory "!SOLUTION_DIRECTORY!"...
    mkdir "!SOLUTION_DIRECTORY!"
    if !errorlevel! NEQ 0 (
        echo [!PROJECT_NAME!] Error: Could not create build directory.
        exit /b -1
    )
)

:: ---------------------------------------------------------------------------------------
::              generate solution folders in build/
:: ---------------------------------------------------------------------------------------
echo.
echo Generating solution files...

cd "!SOLUTION_DIRECTORY!"
cmake ..
if !errorlevel! NEQ 0 (
    echo [!PROJECT_NAME!] Error with CMake. No solution files generated.
    cd ..
    exit /b -1
)
echo [!PROJECT_NAME!] Solution files successfully generated.

:: ---------------------------------------------------------------------------------------
::              generate binaries
:: ---------------------------------------------------------------------------------------
call ../_GenerateBinaries.bat "!SOLUTION_DIRECTORY!"
if !errorlevel! NEQ 0 (
    echo.
    echo [!PROJECT_NAME!] Error: Encountered problem building binaries.
    cd ..
    exit /b -1
)
echo.
echo Solution file and binaries are ready. You can try to start the solution:
echo ./build/!PROJECT_NAME!.sln
echo. 
echo Or directly call the executable:
echo ./bin/Windows/x64/Release/!PROJECT_NAME!.exe
echo.

cd ..

exit /b 0

:: ---------------------------------------------------------------------------------------
::              functions
:: ---------------------------------------------------------------------------------------
:CheckAndInitializeSubModules
echo.
echo Checking and initializing submodules...

git submodule status > nul 2>&1
if !errorlevel! NEQ 0 (
    echo Git is not installed or this is not a git repository. Skipping submodule check.
    exit /b 0
)

:: Check if submodules are initialized by looking for a "-" in the status output
for /f "tokens=1" %%a in ('git submodule status') do (
    set "line=%%a"
    set "prefix=!line:~0,1!" 
    :: first character of each git status message
    if "!prefix!"=="-" (
        echo Submodules are missing or uninitialized. Initializing submodules...
        git submodule update --init --recursive
        if !errorlevel! NEQ 0 (
            echo Failed to initialize submodules. Please check your repository setup.
            exit /b -1
        )
        echo Submodules initialized successfully.
        exit /b 0
    )
)
echo.
echo All submodules are initialized.

::  :: Ensure submodules are up to date
::  echo Updating submodules...
::  git submodule update --recursive --remote
::  if !errorlevel! NEQ 0 (
::      echo Failed to update submodules. Please check your repository setup.
::      exit /b -1
::  )
::  echo Submodules are up to date.

exit /b 0
