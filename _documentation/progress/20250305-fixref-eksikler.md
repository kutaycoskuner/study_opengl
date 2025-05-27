# eksikler

- WHERE I WAS
    - switch between render mode on ui

- [x] scenes
    - [x] blending sahnesi blend objeleri gorunmuyor
        - fixed by reactivating sort algorythm
    - [x] blin phong sahnesi gecmiyor
        - fix blinn phong, shaderlarda specular gecmedigi icin 0 atiyor. o da isiklandirmayi bozmuyordu
    - [x] geometry shader sahnesi kokorecci yamuk
        - fixed in previous commit by adding rotation
    - [x] outliner sahnesi frustum outlnielaanmiyor
        - fixed primitive scene objects icin stencil testing bool u falsemis

- duzeltmeler
    - [x] dosya ismi duzeltmeleri (shaders)
    - [wip] degisken ve fonksiyon ismi duzeltmeleri
        check_naming_conventions.py
        it will take two paramters 
        scope folder
        output file as full path
        it will iterate over folders and children files to find files with certain extensions such as .cpp and .h
        it will ignore files in libs/ lib/
        then it will extract names of functions and variables.
        it will write a line for each on output file
        valid or not (x or v)
        type fun or var
        name of the function or variable
        path of where to be found
        rules:
        all variables should be snake case except constants constants are uppercase
        private variables should have _ front
        all functions should also follow snake case

        - get unfiting variable and function names on cpp files by script
    - setting up consistent and stable naming convention

- bugs
    - [x] perspective bug (warp drive)
        - camera rotation fix next time
    - [x] resizing bug
    - [x] geometry scene bug
    - [x] blinn phong (dark aura of light)
        - light direction and diff fix
    - camera squish
    - on scene change ssao scene is not appearing
    - packaging

- degisiklikler
    - [x] shadername yerine enum kullanarak switchleme
    - ui camera rotation show deg instead of rad

- eklemeler
    - [x] keybinding tab on ui
        - tab degistirmeyi buylamadim gecici coum olarak menu bara keybindings yerine options koydum

    - [wip] rendering different render targets  from ui
        - [x] created enum for defining what to render renderviewmode
        - [x] created renderviewmode bool to detect what to render
        - set logic to switch between things on ui  
            - now I can switch, but when changed scenes its stuck on the previous. I need to implement a logic that only shows available textures dependent on used shader
            - shaderin id olarak enum, shader paths ve renerview mode seti kullanacagim
            - renderviewmode hangisine ait olmali problemi bogdu yapip gececegim.
                - [x] shaderpath regex editing
                - \n\s{1,}\. -> new line one or more space characters. and . at the end
                - added refactoring
            - [x] implement new shader shader struct to logic -> select by enum -> send options to ui
                - [x] split data to prevent circular dependency


        - created bools for effects plshadows, dlshadows, slshadows, ssao 
    
    - automated python scene check 
    
    - object selection from frame (id method?)

- implementation 
    - profiling pix