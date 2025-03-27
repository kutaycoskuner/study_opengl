# eksikler

- eksikler
    - [x] blending sahnesi blend objeleri gorunmuyor
        - fixed by reactivating sort algorythm
    - [x] blin phong sahnesi gecmiyor
        - fix blinn phong, shaderlarda specular gecmedigi icin 0 atiyor. o da isiklandirmayi bozmuyordu
    - [x] geometry shader sahnesi kokorecci yamuk
        - fixed in previous commit by adding rotation
    - [x] outliner sahnesi frustum outlnielaanmiyor
        - fixed primitive scene objects icin stencil testing bool u falsemis

- duzeltmeler
    - setting up consistent and stable naming convention


- eklemeler
    - [x] keybinding tab on ui
        - tab degistirmeyi buylamadim gecici coum olarak menu bara keybindings yerine options koydum
    - rendering different render targets  from ui
        - created enum for defining what to render renderviewmode
        - created bools for effects plshadows, dlshadows, slshadows, ssao 
    - automated python scene check
    - object selection from frame (id method?)