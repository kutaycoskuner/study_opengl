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
- Notes
    - texture coordinates range from 0 to 1 in the x and y axis. Retrievving the texture color using texture coordinates is called sampling.
    - learn blob, cache: zaman kazanmak icin kullandigin memory bolgesi

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
    - big five ctors
    - const correctness
    - serialization
        - serialization is the process of converting an object or data structure into a format that can be easily transmitted or stored.
    - deserialization


- git sub module
    - baska bir repoyu nasil sub module olarak kullanirim

- 3rd party kutuphane
    1. kutuphane source u indir
    2. cmake ile build i yarat
    3. vs uzerinde acip debug/release buildleri yap
    4. 1. sub module
    4. 2. statik kirli yol
        1. project properties > linker > general > add additional library directories
        2. project properties > linker > input   > add additional library file name
        3. project properties > vc++ directories > add library include folder | convention

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
- <naming conventions>
    - Rules
        1. Favor 3-4 char names if readable
            - vertex    : vrtx
            - fragment  : frag
            - color     : col
            - lahmacun  : lah
    - class, struct
        - MyClass
    - file names
        - folder names
            - all_small_characters
            - split with _ whitespace
            - well known names shorted to 3-4 characters: libraries -> libs
            - 
        - file naming keys
            - s: self           (self files main work files)
            - b: blueprint      (structs / classes)
            - d: data           (models, scenes, vertices, materials input in gerneral)
            - m: mapping        (how to associate data / mappings ex. shader with file names)
            - c: core           (main file)
            - u: utililities    (self written library functions, parsers / calculators etc.)
            - x: testing        (test files)
    - variables: variable
        - global: g_variable
        - bools: b_isVariable
    - function names
        - rules
            - starts with a verb
            - clearly describes what function does
            - only one task
        - doSomeStuff()
    - config file
        - ex: test_name         (configuration files default settings for program to start)

- <visual studio: linking library>
    - right click on project name on solution explorer > properties
    - configuration > vc++ directories > 
    - click expand arrow then <edit>
    - library directories > <library>/build/src/debug         | .lib files
    - include directories > <library>/include                 | include folder
    - linking
        - linker > input > additional dependencies
        - add glfw3.lib;opengl32.lib

# Shortcuts
- f5                                debugger
- shift + f5                        calisan debug i kapatiyor
- ctrl + shift + f5                 debug i yeniden calistiriyor