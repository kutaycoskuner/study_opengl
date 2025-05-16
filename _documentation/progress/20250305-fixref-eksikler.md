# eksikler

- scenes
    - [x] blending sahnesi blend objeleri gorunmuyor
        - fixed by reactivating sort algorythm
    - [x] blin phong sahnesi gecmiyor
        - fix blinn phong, shaderlarda specular gecmedigi icin 0 atiyor. o da isiklandirmayi bozmuyordu
    - [x] geometry shader sahnesi kokorecci yamuk
        - fixed in previous commit by adding rotation
    - [x] outliner sahnesi frustum outlnielaanmiyor
        - fixed primitive scene objects icin stencil testing bool u falsemis

- duzeltmeler
    - dosya ismi duzeltmeleri
    - degisken ve fonksiyon ismi duzeltmeleri
    - setting up consistent and stable naming convention

- bugs
    - perspective bug (warp drive)
    - blinn phong (dark aura of light)
    - resizing bug


- degisiklikler
    - shadername yerine enum kullanarak switchleme

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