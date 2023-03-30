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

# Structure

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

# Abbreviations
- NDC
    - Normalized device coordinates: coordinates scaled between -1,1 range

- VBO
    - Vertex buffer objects: store large number of vertices in the GPU s memory.    | 
    - vbo datanin kendisi

- VAO 
    - Vertex array object, just like a vertex buffer objct and any subsequent vertex attribute calls from that point on will be stored inside vao
    - vertex bufferi nasil interpret ettigin

- EBO
    - element buffer object. Indicating overlapping vertices, to avoid redundant work.
    - vertex bufferi hangi sirayala okudugu

- GLSL  
    - OpenGL shading language


# Notes
- opengl
    - A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

- cpp
    - &: adress
    - array pointer decay

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