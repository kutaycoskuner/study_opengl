git submodule add https://github.com/glfw/glfw.git libs/glfw
git submodule add https://github.com/assimp/assimp.git libs/assimp
git submodule add https://github.com/ocornut/imgui.git libs/imgui
git submodule add https://github.com/kutaycoskuner/yurt.git data/yurt



Remove-Item -Path "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\artifacts" -Recurse -Force
    - removing artifacts directory

Remove-Item -Path "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\bin" -Recurse -Force
    - removing bin directory

Remove-Item -Path "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build" -Recurse -Force
    - removing build directory

./--GenerateBuildProject.bat
    - run genrate build project script

./--GenerateBinaries.bat
    - run generate binaries

./--PackProgram.bat

Get-ChildItem -Recurse ./ -Filter *.cpp -Name
    - dosyadaki .cpp ile biten dosyalarin isimlerini cikariyor

Get-ChildItem -Recurse ./ -Directory -Name
    - 

$Files = Get-Childitem -Recurse ./ -Filter *.cpp -Name
    - files degiskeni olusturuyor

./build/project_test.sln

./bin/Windows/x64/Release/opengl_renderer.exe

tree ./ 
    - tree view

tree ./source/ /f
    - tree view all source files 

./artifacts/opengl_renderer.exe