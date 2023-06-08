# Notebook
- [Links](#links)
- [Structure](#structure)
- [Dependencies](#dependencies)
- [Abbreviations](#abbreviations)
- [Notes](#notes)
- [Documentation](#documentation)
- [How to?](#how-to)
- [Shortcuts](#shortcuts)

# Links
- learnOpenGL
    - https://learnopengl.com/Getting-started/Creating-a-window
- GLFW 
    - https://www.glfw.org/download.html

- google ccp style guide
    - https://google.github.io/styleguide/cppguide.html

- google filament
    - https://github.com/google

- perspective projection matrix calculation article
    - http://www.songho.ca/opengl/gl_projectionmatrix.html

- perspective projection jsantell
    - https://jsantell.com/3d-projection/

- styling guide

- vsc keyboard shortcuts
    - https://visualstudio.microsoft.com/keyboard-shortcuts.pdf

- cast operator
    - https://en.cppreference.com/w/cpp/language/cast_operator

- scratchpixel
    - https://scratchapixel.com/

- gfx journal by jendrick illner
    - https://www.jendrikillner.com/tags/weekly/

# Structure
- project
    + config                : degiskenlerin tutuldugu yer
    + data                  : cizim icin kullanilan verinin geldigi yer
    + headers               : include files function declerations
    + libs                  : outer code
    + shaders               : shader files
    + source                : every logic and data that I wrote
        - utilities
        - main
        - test
        - entry

# Formats
- settings: .ini, .yaml, .xml, .json
- scene material: 
- model: .obj

# Dependencies
- GLAD                  | OpenGL versiyonunu hardware e gore ayarlayan kutuphane
    - https://glad.dav1d.de/

- CMake                 | CMake is a tool that can generate project/solution files of the user's choice (e.g. Visual Studio, Code::Blocks, Eclipse) from a collection of source code files using pre-defined CMake scripts.
    - https://cmake.org/download/

- GLFW                  | library specificfically targeted OpenGL, allows context define window parameters and handle user inputs
    - download https://www.glfw.org/download.html
    - 64 bit precompiled binaries

- Visual Studio
    - Create new project choose c++ Empty project
    - glsl linker

# Abbreviations
- fov
    - field of view: how large the view space is

- NDC
    - Normalized device coordinates: coordinates scaled between -1,1 range

- VBO
    - Vertex buffer objects: store large number of vertices in the GPU s memory.    | vertex buffer
    - vbo datanin kendisi   

- VAO                                                                               | input layout
    - Vertex array object, just like a vertex buffer objct and any subsequent vertex attribute calls from that point on will be stored inside vao
    - vertex bufferi nasil interpret ettigin

- EBO                                                                               | index buffer
    - element buffer object. Indicating overlapping vertices, to avoid redundant work.
    - vertex bufferi hangi sirayala okudugu

- GLSL  
    - OpenGL shading language


# Blackboard
- unordered map
    - [] hem okuyup hem yaziyor yoks yaziyor
    - yoksa patlamasi icin .at("")

- pointer tipleri
    - shared pointer, unique pointer
    - raw pointer, smart pointer
    - bu objeyi refer eden 

- module ne demek
    - .exe, ya da .dll

- coordinate systems
    - https://learnopengl.com/Getting-started/Coordinate-Systems
    - local space (or object space) : are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.
    - world space                   : coordinates relative to global origin of the world
    - view space (or eye space)     : camera view
    - clip space                    : -1 to 1 removes anything outer than this range
    - screen space                  : clip coordinates to monitor screen coordinates    

    - model_matrix         : local -> world
    - view_matrix          : world -> view
    - projection_matrix    : view  -> clip

- vector math
    - vector negation
    - scalar vector operations | + - * /
    - vector vector operations 
        - addition and subtraction
    - length
    - normalizing vector
    - dot product: boylari carpi aralarindaki acinin cosinusu : iki vektorun paralelligine bakiyor 
    - cross product: 

- testing
    - unit test
    - integration test

- nomenclature, naming
    - uniforms short
    - events

- uniform
    - update olma sikligi
        - per frame
        - per view
        - per object

- Notes
    - texture coordinates range from 0 to 1 in the x and y axis. Retrievving the texture color using texture coordinates is called sampling.
    - learn blob, cache: zaman kazanmak icin kullandigin memory bolgesi
    - pointer and -> dereferencing
    - c style api | c like 
    - conversionlari goz ardi etme

- framedebugging
    - renderdoc
    - tools > settings > dark mode
    - 

- colors
    - black bg
        - #202020
        - #090909
        - #121212

- magic number
    - guzel degisken isimlendirmesi ile saglamak lazim

- self naming dictionary
    - vrtx: vertex
    - frag: fragment
    - col: color

- concepts
    - array of structs, struct of arrays
    - spherical harmonics
    - smart pointer
    - deferred initialization
    - big five ctors
    - const correctness
    - serialization
        - serialization is the process of converting an object or data structure into a format that can be easily transmitted or stored.
    - deserialization
    - forward decleration: decleration yapip erteletebilirsin | eger * ve &
    - const correctness | bulundugu obeyi degistirip degistirmiyor mu hangisi objeyi mutate ediyor state degitiriyor
    - template meta programming
    - static fonksiyon o cpp dosyasina ozel fonksiyon demek

- git sub module
    - baska bir repoyu nasil sub module olarak kullanirim


- glsl shaders
    - c like language
    - always begin with veresion declaration
    - types: int, float, double, uint, bool
    - vectors:
        - vecn: default vector of n floats
        - bvecn: vector of n booleans
        - ivecn: vector of n integers
        - uvecn: vector of n unsigned integers
        - dvecn: vector of n double components


- opengl
    - A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

- cpp
    - constexpr
    - &: adress
    - array pointer decay | array in boyu ve kendisini ayri ayri ver
    - compile time / run time constant | constexpr
    - static kullandigin yere gore anlami degisiyor | variable qualifier -> o dosyaya ozel scope management

- state machine
    - a collection of variables that deefine how opengl should currently operate


- graphic pipeline
    vertex shader > shape assembly > geometry shader > rasterization > fragment shader > test and blending

- fragment
    - in OpenGL is all the data required for OpenGL to render a single pixel.

- buffer
    - batch of memory saved for a task | set of vertices coordinates 


- shader


- vector
    - size of 4
    - x y z defines dimensions; w describes depth in perspective division

- data formats
    - yaml
    - csv
    - json
    - xml
    - protocol buffers
    - messagepack

# Documentation
- created project
- added git
- did basic cpp test
- download cmake, glfw
    - build glfw with cmake
- added include and .lib files to project
- downloaded GLAD included file to project
- added glad.c file to project


# How to
- <git>
    - git status
    - git stash
    - git stash pop
    - git stash list
    - git log

- <how to forward decleration>
    - ne oldugunu bilmene gerek yok
    - struct GLFWwindow;

- <ne zaman state>
    - bir fonksiyonda yaratip diger fonksiyonda kullanacaksan state

- <disardan dosya ekleme>
    - ekledigin cpp dosyasina sag tiklayip include in project de

- <fonksiyona toplama>
    - global
    - fonksiyon parametresi
    - parametrelerin hepsini structta topla
    - fonksiyon 3-4 parametreden fazla almasa iyi olur
    - application class icine gomup fonksiyonlari member a cevir


- <casting>
    - static cast
    - dynamic cast  derived type i base type a cast etmede
    - reinterpret cast ne yaptigini biliyorsun

- <disardan dosya ekleme>
    - ekledigin cpp dosyasina sag tiklayip include in project de

- <integrate 3rd party third party libraries>
    - compiled library
        - kutuphane source u indir 
        - cmake ile build i yarat
        - vs uzerinde acip debug/release buildleri yap
        - sub module
        - statik kirli yol
            - project properties > linker > general > add additional library directories
            - project properties > linker > input   > add additional library file name
            - project properties > vc++ directories > add library include folder | convention

    - c style | built in library (ex: stb_image.h)
        - .h dosyasini proje dosyasinin icine indir
        - include et

    - header only | non-compiled kutuphane
        - indir, proje hiyerarsisinde kutuphanelerin icine koy 
        - project properies > c/c++ > additional include folders 
            - $(SolutionDir)/FolderName


- <farkli seyler cizdirme | draw different things>
    1. find how many objects are going to be drawn: set buffer_count
    2. buffer dataya cizilecek objeyi ver / her bir obje icin yeni bir vao ve vbo
    3. glVertexAttribPointer, glEnableVertexAttribArray uzerinde stride ve ilgili verinin boyunu goster
    4. glDraw elements uzerinde cizim tipi, stride ve int

- <visual studio: linking library>
    - right click on project name on solution explorer > properties
    - configuration > vc++ directories > 
    - click expand arrow then <edit>
    - library directories > <library>/build/src/debug         | .lib files
    - include directories > <library>/include                 | include folder
    - linking
        - linker > input > additional dependencies
        - add glfw3.lib;opengl32.lib

- <linker error>
    - case 1:
        - birden fazla tanim oldugunda oluyor
        - baska bir sekilde de olabiliyor
    - case 2: 
        - .h nin icine tanim koyarsak | birden fazla kopya oluyor

- <const char to string | string to const char>
    - const char* ex = str.c_string()
    - static_cast<const char*>(str.c_str());

- <read access violation>
    - exp: extern keyword unden kaynakli oldu
    - senin olmayan pointeri dereference

- <vs: alti yesil dalgali cizgi>
    - tanim yok declaration var

- <parametre koyamadigin callback fonksiyonu>
    - seceenekler
        - global degisken
        - glfw window user pointer
        - manually handle every frame

- <kod kalitesi>
    - naming
    - responsiibility, ownership dagilimlari
    - const refler

# Shortcuts
- f5                                debugger
- shift + f5                        calisan debug i kapatiyor
- ctrl + shift + f5                 debug i yeniden calistiriyor
- chrl + shift + h                  find and replace
- ctrl + m > o                      collapse
- ctrl + m > p                      expand
- ctrl + m > i                      local expand
- ctrl + shift + f9                 remove all breakpoints
- ctrl + shift + b                  compile
- shift + alt up/down               multi line edit
- ctrl + alt + l                    solution explorer
- ctrl + -                          bir onceki satira atla
- ctrl + m, s                       collapse
- ctrl + m, i                       expand