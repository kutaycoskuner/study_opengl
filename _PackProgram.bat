@echo off
setlocal enabledelayedexpansion

:: ---------------------------------------------------------------------------------------
::              variables
:: ---------------------------------------------------------------------------------------
set PACKAGE_DIRECTORY=artifacts
set BUILD_DIRECTORY=build
set BINARIES_PATH=bin/Windows/x64/Release
set EXECUTABLE_PATTERN=*.exe
set CONFIG_DIRECTORY=config
set DATA_DIRECTORY=data
set SHADERS_DIRECTORY=shaders


:: ---------------------------------------------------------------------------------------
::              main process
:: ---------------------------------------------------------------------------------------
call :print "Packaging started.."

:: Step 1: Control if build folder exists
if not exist "%BUILD_DIRECTORY%" (
    echo Build directory does not exist. Running ./_GenerateBuildProject.bat...
    call ./_GenerateBuildProject.bat
)

:: Step 2: Control if bin/Windows/x64/Release/*.exe exists
if not exist "%BINARIES_PATH%\%EXECUTABLE_PATTERN%" (
    echo Executables not found in %BINARIES_PATH%. Running ./_GenerateBinaries.bat...
    call ./_GenerateBinaries.bat
)

:: Step 3: Control if artifacts directory exists
if exist "%PACKAGE_DIRECTORY%" (
    echo Artifacts directory exists. Deleting for a clear build...
    rmdir /S /Q "%PACKAGE_DIRECTORY%"
)

:: Step 4: Create artifacts directory
echo Creating directory %PACKAGE_DIRECTORY%...
mkdir "%PACKAGE_DIRECTORY%"

:: Step 5: Copy executables to artifacts
echo Copying executables to artifacts...
xcopy "%BINARIES_PATH%\%EXECUTABLE_PATTERN%" "%PACKAGE_DIRECTORY%" /Y

:: Step 6: Copy config, data, shaders directories to artifacts
echo Copying %CONFIG_DIRECTORY%, %DATA_DIRECTORY%, and %SHADERS_DIRECTORY% to artifacts...
xcopy "%CONFIG_DIRECTORY%" "%PACKAGE_DIRECTORY%\%CONFIG_DIRECTORY%" /S /I /Y
xcopy "%DATA_DIRECTORY%" "%PACKAGE_DIRECTORY%\%DATA_DIRECTORY%" /S /I /Y
xcopy "%SHADERS_DIRECTORY%" "%PACKAGE_DIRECTORY%\%SHADERS_DIRECTORY%" /S /I /Y

:: Step 7: Print completion message
call :print "Packaging complete on artifacts directory."

exit /b 0


:: ---------------------------------------------------------------------------------------
::              functions
:: ---------------------------------------------------------------------------------------
:print
echo.
echo %*
exit /b
