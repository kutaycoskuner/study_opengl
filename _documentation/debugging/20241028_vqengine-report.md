Issue: GenerateProjectFiles.bat Assumes Execution from /build Directory

**Description**  
The GenerateProjectFiles.bat script currently assumes that it is executed from within the build directory, leading to errors if the script is run from the root project directory. This causes issues when following the README instructions directly, as it doesn’t specify to navigate to /build before executing the script.

**Steps to Reproduce**  
1. clone repository from github:
```
git clone https://github.com/vilbeyli/VQEngine.git
```

2. navigate to the root project directory:
```
cd VQEngine
```

3. Attempt to build project as indicated in the readme:
```
./build/GenerateProjectFiles.bat
```

**Expected Behavior**  
The script should run successfully from the root project directory, without needing to navigate to /build.

**Actual Behavior**  
When running `GenerateProjectFiles.bat` from the root directory, it results in the following errors:
```
fatal: not a git repository (or any of the parent directories): .git
```

**Cause**  
The issue is that the script is attempting to execute commands that rely on the assumption it’s running from the /build directory. Running it from the root directory causes relative path issues.

**Workaround**  
The issue can be temporarily resolved by navigating to the build directory before executing the script:
```
cd build
.\GenerateProjectFiles.bat
```

**Suggested Solution**  
Modify the GenerateProjectFiles.bat script to make it independent of the current working directory. Adding a command to change to the script’s directory at the start can help resolve this:

Add the following at the beginning of GenerateProjectFiles.bat:
```bat
@echo off
cd /d "%~dp0"
```

This will ensure the script runs from its own directory regardless of where it is called from, allowing users to follow the README instructions without modification.

**Additional Information**  

Operating System: &nbsp;&nbsp; Windows 10 (Version 22H2 Os Build 19045.5011)  
Git Version: &emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp; 2.37.1.windows.1
