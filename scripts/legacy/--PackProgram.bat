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
    echo Build directory does not exist. Running ./--GenerateBuildProject.bat...
    call ./--GenerateBuildProject.bat
    if !errorlevel! NEQ 0 (
        echo ERROR: Build project generation failed. Stopping packaging process.
        exit /b -1
    )
)

:: Step 2: Control if bin/Windows/x64/Release/*.exe exists
if not exist "%BINARIES_PATH%\%EXECUTABLE_PATTERN%" (
    echo Executables not found in %BINARIES_PATH%. Running ./--GenerateBinaries.bat...
    call ./--GenerateBinaries.bat
    if !errorlevel! NEQ 0 (
        echo ERROR: Binary generation failed. Stopping packaging process.
        exit /b -1
    )
)

:: Step 3: Control if artifacts directory exists
if exist "%PACKAGE_DIRECTORY%" (
    echo Artifacts directory exists. Deleting for a clear build...
    rmdir /S /Q "%PACKAGE_DIRECTORY%"
)

:: Step 4: Create artifacts directory
echo Creating directory %PACKAGE_DIRECTORY%...
mkdir "%PACKAGE_DIRECTORY%"
if !errorlevel! NEQ 0 (
    echo ERROR: Failed to create artifacts directory. Stopping packaging process.
    exit /b -1
)

:: Step 5: Copy executables to artifacts
echo Copying executables to artifacts...
xcopy "%BINARIES_PATH%\%EXECUTABLE_PATTERN%" "%PACKAGE_DIRECTORY%" /Y
if !errorlevel! NEQ 0 (
    echo ERROR: Failed to copy executables. Stopping packaging process.
    exit /b -1
)

:: Step 6: Copy config, data, shaders directories to artifacts
echo Copying %CONFIG_DIRECTORY%, %DATA_DIRECTORY%, and %SHADERS_DIRECTORY% to artifacts...
xcopy "%CONFIG_DIRECTORY%" "%PACKAGE_DIRECTORY%\%CONFIG_DIRECTORY%" /S /I /Y
if !errorlevel! NEQ 0 (
    echo ERROR: Failed to copy config directory. Stopping packaging process.
    exit /b -1
)

:: Ensure all files in data directory are copied, including .obj files
xcopy "%DATA_DIRECTORY%\*" "%PACKAGE_DIRECTORY%\%DATA_DIRECTORY%" /S /I /Y
if !errorlevel! NEQ 0 (
    echo ERROR: Failed to copy data directory. Stopping packaging process.
    exit /b -1
)

xcopy "%SHADERS_DIRECTORY%" "%PACKAGE_DIRECTORY%\%SHADERS_DIRECTORY%" /S /I /Y
if !errorlevel! NEQ 0 (
    echo ERROR: Failed to copy shaders directory. Stopping packaging process.
    exit /b -1
)

:: Step 7: Print completion message
call :print "Packaging complete in the artifacts directory."

exit /b 0


:: ---------------------------------------------------------------------------------------
::              functions
:: ---------------------------------------------------------------------------------------
:print
echo.
echo %*
exit /b
