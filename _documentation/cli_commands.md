cd libs
git submodule add https://github.com/glfw/glfw.git
git submodule add https://github.com/assimp/assimp.git
git submodule add https://github.com/ocornut/imgui.git


Remove-Item -Path "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\bin" -Recurse -Force
    - removing bin directory

Remove-Item -Path "C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\build" -Recurse -Force
    - removing build directory

./_GenerateBuildProject.bat
    - run genrate build project script

./_GenerateBinaries.bat
    - run generate binaries

Get-ChildItem -Recurse ./ -Filter *.cpp -Name
    - dosyadaki .cpp ile biten dosyalarin isimlerini cikariyor

Get-ChildItem -Recurse ./ -Directory -Name
    - 

$Files = Get-Childitem -Recurse ./ -Filter *.cpp -Name
    - files degiskeni olusturuyor

./build/project_test.sln

tree ./ 
    - tree view

tree ./source/ /f