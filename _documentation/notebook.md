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
- models
    - metadata
        - author
        - source 
        - format
        - upload date
        - licence
        - modifications
    - stanford bunny
        - https://graphics.stanford.edu/data/3Dscanrep/
    - sponza
        - crytek sponza
        - intel sponza
        - san miguel
        - bistro
        - junk shop
        - the bathroom
        - interrogation room
        - abandoned warehouse
        
    - san miguel scene
    - utah teapot
        - https://de.wikipedia.org/wiki/Utah_teapot
    - khronos sample models 
        - https://github.com/KhronosGroup/glTF-Sample-Models
    - nvidia bistro
        - https://developer.nvidia.com/orca/amazon-lumberyard-bistro
    - suzanne_blender
    - blender scenes
        - https://www.blender.org/download/demo-files/#cycles
    - self
        - textures
            - clayman
            - parallax-test
            - grids
    - substance
        - jade toad
        - meet mat
        - preview sphere
        - tiling material

- john chapmanns cgraphics tutorials
    - https://john-chapman-graphics.blogspot.com/2013/01/ssao-tutorial.html

- engine example
    - https://github.com/KTStephano/StratusGFX

- polyhaven standards
    - https://docs.polyhaven.com/en/technical-standards/models

- icosahedron based geodesic sphere
    - https://web.archive.org/web/20180808214504/http://donhavey.com:80/blog/tutorials/tutorial-3-the-icosahedron-sphere/

- hdr lgihting by john hable
    - https://www.slideshare.net/slideshow/lighting-shading-by-john-hable/12026883

- tangent space
    - https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/

- opengl cubemap docs
    - https://www.khronos.org/opengl/wiki/Cubemap_Texture

- assembly instruction tables
    - https://www.agner.org/optimize/instruction_tables.pdf

- graphtoy graphviz tool
    - https://graphtoy.com/

- tut: ci/cd github actions / workflow / events
    - https://www.youtube.com/watch?v=R8_veQiYBjI&list=PLy7NrYWoggjzSIlwxeBbcgfAdYoxCIrM2

- texture sources
    - https://wiki.thedarkmod.com/index.php?title=Texture_Sources

- mindmap
    - https://miro.com/app/board/uXjVN7R_r_E=/

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

- material properties
    - http://devernay.free.fr/cours/opengl/materials.html

- outline render webgl
    - https://omar-shehata.medium.com/how-to-render-outlines-in-webgl-8253c14724f9

- snells law (refraction physics)
    - https://en.wikipedia.org/wiki/Snell%27s_law

- hermite interpolation
    - https://en.wikipedia.org/wiki/Hermite_interpolation

# Structure
- root/
    - _display/
    - _documentation/
    - config/
    - data/
    - headers/
    - libs/
    - source/
    - _generate_binaries.bat
    - _generate_build.bat
    - .gitattributes
    - .gitignore
    - readme.md

+ root
    + config                : variables for program
    + data                  : data entry for program. coordinates, textures, models, scenes etc.
        + paths            (t0) : data path info for data files
            - shader_paths
            - model_paths
        + scenes           (t2) : scene info
        + models           (t2) : imported models with their own textures and definitions imported through assimp
    + headers               : include files function declerations
        + abstract          : base classes
    + libs                  : outer code
    + source                : every logic core logic
        + blackboard        : testing new things 
        + core              : 
        + event_handling    :
        + shaders           :
        + test              :
        + utils             :
        - main.cpp          : entry point of the program
- CMakeLists.txt        : cmake build instructions

# Self classes
- SceneNode | GameObject            : Base container object for scene that holds transform?
- SceneElements                     : 
- Predef_3D                         : 


- if data is set of similar things  : ex. only coordinates                 - t0: raw
    - textures, paths, vertex coordinates
- if data is set of multiple things : coords + position + rotation + scale - t1: basic
    - game object with world coords takes coords + paths + textuers
- if data is set of multiple t1     : scene lights, cameras, objects etc   - t2: complex
    - models, scenes

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


# 
- memory
    - stack
    - heap
    - string fonksiyonu referans olarak gonderilmediginde c_str() lokal degiskenin adresini tuttugu icin yenisini yazdginida patliyor. veya scope bittiginde


- arch
    - polling
    - event based
    - load unload -> window size dependent resources load / unload

- effects
    - dithering
    - outline
    - pixelation
    - cel shading
    - goosh shading

- attenuation (sonumlenme) for light
    - F = 1 / (Kc + Kl * d + Kq * d * d)
    - d = distance from the fragment to light source
    - kc = constant, kl = linear, kq = quadratic

- light casters light source
    - directional
    - point
    - spot light

- process peed
    - code edit hizlandirma
    - dosya navigasyonu
    - acik dosyalari degistirme

- normalde scale
    - inverse transpose 3 3 aliyoruz
    - scale i inverse transpose yaptigimizda sadece invert oluyor.
    - pure rotasyon martrislerinin inverse transpose una esit.
    - scale i cikarmak invert etmek

- lighting models
    - phong lighting model
        - ambient, diffuse, specular lighting

- unordered map
    - [] hem okuyup hem yaziyor yoks yaziyor
    - yoksa patlamasi icin .at("")

- pointer tipleri
    - shared pointer, unique pointer
    - raw pointer, smart pointer
    - bu objeyi refer eden 

- module ne demek
    - .exe, ya da .dll

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

- nomenclature, 
    - normal variables this_is_variable
    - normal functions thisIsFunction()
    - shaderlarda  raw girdi in_ / vertex ciktisi v_ / fragment ciktisi f_ premarker
    - uniforms short uni
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
    - violet
        - #da1991
    - red
        - #ff0048               1, 0, .282
        - #ff3352   -> blender
    - green
        - #91ff01   ->          .569, 1, .004
        - #8bdc00   -> blender
    - blue
        - #06b4ba               .024, .706, .729
        - #2890ff   -> blender   
    - selection (orange / overlay)
                    -> blender  1.0, 0.62, 0.16

- <engine setup>
    - msaa > intermediate hdr > bloom > ldr 

- <graphics pipeline>

- <space transformations>
- keyword: change of basis

    - coordinate systems
        0. tangent space
            : normale tam karsidan texture koordinatlari x/y olacak sekilde baktigimiz uzay
        - https://learnopengl.com/Getting-started/Coordinate-Systems
        1. local space (object space / model space) 
            : are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.
        2. world space                   
            : coordinates relative to global origin of the world
        3. view space (or eye space)     
            : camera view
        4. projection space              
            : camera view i 2d gorsele ceviren projection
            : Projection space is an intermediate space after applying the projection matrix but before the perspective divide.
            : This means the coordinates have a W component (e.g., (𝑥,𝑦,𝑧,𝑤) (x,y,z,w)).
        5. clip space                    
            : -1 to 1 removes anything outer than this range
        - (homogeneous) screen space     
            : clip coordinates to monitor screen coordinates    

        - model_matrix         : local -> world
        - view_matrix          : world -> view
        - projection_matrix    : view  -> clip

- magic number
    - guzel degisken isimlendirmesi ile saglamak lazim

- self naming dictionary
    - vrtx: vertex
    - frag: fragment
    - col: color

- memory
    - bit  : 0 1
    - byte : 8 bit 2**8 = 256
    - 4 byte : 32 bit

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
    - void pointer: type in onemli olmadigi fakat adress in onemli oldugu yerde kullaniyor (memory boyutu) 
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

- standard defaults
    - winding order :   counter clockwise
    - axis          :   right hand rule
    - camera        :   

# Documentation
- created project
- added git
- did basic cpp test
- download cmake, glfw
    - build glfw with cmake
- added include and .lib files to project
- downloaded GLAD included file to project
- added glad.c file to project



# Blackboard
- <color spaces>
    - rgb  = linear space
    - srgb = gamma space li color space

- <blit>
    - bir bufferi otekine kopyalamak

- <shields badges>
    - badges / shields
        - https://shields.io/badges/static-badge
        - https://simpleicons.org/?q=discord
        - https://github.com/simple-icons/simple-icons/blob/master/slugs.md

- <git commitlemeden kaydetme>
    - git status
    - git add source    | staged changes
    - git clean -f      | temizle track etmek istemediklerini
    - git stash
    - git stash list
    - git stash pop
    - git checkout <sha>
    - git clean -fdfx ./

- <windows sdk>
    - vs installer > version > search sdk

- <what is CI/CD>
    continous integration and continuous deployment
    is the practice of regularly merging code changes into a shared repository, typically several times a day, and then automatically testing these changes to detect errors early.

- <what is cmake>
    CMake is an open-source, cross-platform build system and tool designed to control the software build process using simple platform-independent configuration files. It generates native build scripts (such as Makefiles, Visual Studio project files, or Xcode project files) for a variety of operating systems and development environments, allowing developers to write build instructions once and compile their project on different platforms without needing to modify the build configuration for each one.
    
- <visual studio vs>
    - ctrl + shift + t -> accurate search filtreleme

- <instance>
    - uniform gonderme
    - buffer olarak gonderme
    - bining batching birden fazla draw call cagirma


- <pix>
    - https://devblogs.microsoft.com/pix/download/
    - https://devblogs.microsoft.com/pix/winpixeventruntime/ | marker
    - low level profiling tool
    - frame debugger
    - nsight nvidia nin

- <dll file>
    - oldugu gibi kopyala,
    - directory ise vcc > include release mi debug mi kontrol et degistir
    - 

- <cubemaps skybox>
    - how to get uv coordinates for sphere cylindrical projection (equirectangular projection)
        - http://paulbourke.net/miscellaneous/cubemaps/
https://gamedev.stackexchange.com/questions/114412/how-to-get-uv-coordinates-for-sphere-cylindrical-projection
    - converting from cubemaps to fisheye
        - https://web.archive.org/web/20200226035745/https://paulbourke.net/miscellaneous/cubemaps/
    - eve renderdocs
        - https://forums.eveonline.com/t/launching-logging-into-eve-from-renderdoc/70680
    - where eve online skybox images located
        - https://www.reddit.com/r/Eve/comments/2apv5m/where_are_the_eve_skybox_images_located/
    - eve online cube maps tut
        - https://forum.kerbalspaceprogram.com/topic/138036-tutorial-setting-up-eve-cube-maps-24mb-dds-4-texture-maps/
    - ue4 space scene
        - https://www.youtube.com/watch?v=euFtUIVEr4A
    - hdri cubemap converter
        - https://matheowis.github.io/HDRI-to-CubeMap/

- <scene neleri barindirmali>
    - scene nasil update edilecek
    - hangi objeler cizilecek
        - transformlari
    - modeller 
    - materyaller
    - isiklar
    - kameralar
    - game objects
    - settings: cull var mi, outliner var mi


# Problem definitions prompt
- <arch: scene class>
    - I want application to call scene to get which models, textures and shaders to load
    - then it loads the data 
    - Scene also has two functions those are draw and update. These functions going to be implemented by specific scenes
    - For instance outliner scene will have specific draw and update function as well as its own model and data set.
    - could you give me an example class and architecture for this?

# How to

- <programi hangi gpu calistiriyor>
    - ctrl + shift + esc = task manaager
    - ctrl + tab -> performaance
        - 

- <git branch>
    - git checkout <bname>

- <packaging>
    - son kullanicinin tiklayip acacagi paket
    - exeyi kopyalayarak problemleri giderene kadar kopyalama islemine devam et
    - son pakette her sey erisilebilir olmali

- <debugger>
    - f11
        - step into: fonksiyon cagrisi varsa icine giriyor. 
        - fonksiyon cogrisi yoksa satiri calistirip gecyior
    - f10
        - step over: o satirda olacak butun fonksiyonlari calistirip bir sonrkai satira gecyior

- <github submodule>
    - gith submodule add <liknk>
        - git submodule add https://github.com/glfw/glfw.git
        - warning: in the working copy of '.gitmodules', LF will be replaced by CRLF the next time Git 
        - readonly yapiyor git init
        touches it
    - to add submodules with your git pull
        - git config submodule.recurse true
        - git submodule update --init
    - updating submodule
        - baska branch e checkout yapip commitliyorsun.
        - root commit e donup update ediyorsun.
    - how to change submodule folder name
        - rename folder ren old new
        - go to .gitmodules change name and path
        
- <find cpp standard>
    - windows:
    g++ -dM -E -x c++ nul | findstr __cplusplus
    - #define __cplusplus 201402L 2014 standard

- <testing frames>
    - header > create_test_scene_frames   = true;
    - produce frames
    - go to toolkit open pixel_matcher and run the tests
    - if all true make create_test_scene_frames   = false

- <adding key to ui / observer>
    - window_events ccp > ekle
    - application a private degisken ve o degiskeni kontrol edecek public function ekle

- <adding new vertex data object>
    - kompleks geometriyse vertexleri hespalayacak formulu bul
    - blackboardda print ile yazdir
    - vertexdata static icine at
    - named maps e isimli olarak koy
    - primitiv scene node tanimla

- <adding new scene yeni sahne ekleme>
    - headers/data/scenes.h uzerinde yeni sahneyi ekle
    - data/scenes/<scene>.cpp uzerinde yeni sahneyi yarat [vsc]
    - application da loadscenedata fonksiyonuna scene i numarasiyla ekle
    - ui a da ekle (Application::updateUI())
    - cmake icine de adresi ekle

- <adding new shader>
    - shaders/<new>.glsl yeni shader ekle [vsc]
    - data/paths/shader_paths.cpp -> shader pathleri ekle 
    - cmake add shaders
    - change shader naame in-shader code notes

- <adding new submodule>

- <aadding new vertex data>
    - yarattiktan sonra buffer object size i buyut 

- <adding new buffer>
    - yarattiktan sonra yok et

- <adding new texture>
    - add textures to data/textures
    - add paths to maps > texture_name-pathmap.cpp
    - add scene texture names

- <cc0>
    - san miguel
    - sponza

- <unordered map>
    - at kullandginda %100 emin olman gerekiyor.
    - eger yoksa find -> iterator donduruyor -> dereference daha safe

- <problem: release not included>
    - vs den include exclude etmeye calistim olmadi
    - vsc den hata satirini arattim. vsxproj dosyasinda include edildigi yeri bulup xml de manual olarak exclude ettim

- <vs: release linker error>
    - release in linkerlarini duzelt
    - linker > input  release / debug kopyala

- <vs: multithreaded compile>
    - projeye sag tik props
    - c++ > general > multiprocessor compiling

- <vs: release>
    - projeye sag tikla properties'
    - sol ustten release debug degistirerek degisiklikleri esitle
    - vc++ include and library directories

- <vs: gorunmeyen dosyayi ekleme>
    - dosya olustur sag tikla
    - add
    - existing file, sec

- <vs: imleci lineardan kare yap karakter degistiriyor>
    - num lock > insert (0 on laptop)

- <vs: linking library>
    - right click on project name on solution explorer > properties
    - configuration > vc++ directories > 
    - click expand arrow then <edit>
    - library directories > <library>/build/src/         | .lib files
    - include directories > <library>/include                 | include folder
    - linking
        - linker > input > additional dependencies
        - add glfw3.lib;opengl32.lib

- <cpp: maps>
    - okuyacagin zaman .at()
    - yazacagin zaman []
    - okuma zamaninda [] kullanirsan yoksa yaratir

- <debugging: >
    - powershell data visualization 
    - c# 
    - time series, x y visualization

- <debugging theory>
    - problemi cozmeden varsayimla ilerleme

- <debugging: tools>
    - difference checker
        - https://www.diffchecker.com/

- <debugging: renderdocs>
    - C:/Users/kutay/OneDrive/Documents/GitHub/study_opengl/opengl_renderer
    - C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\opengl_renderer\x64\Debug\opengl_renderer.exe


- <knowledge: glsl built in variables>
    - gl_PointSize
    - gl_VertexID
    - gl_FragCoord
    - gl_FrontFacing

- <knowledge: opengl draw methods>
    - glDrawArrays
    - glDrawElements
    - glDrawArraysInstanced
    - glDrawElementsInstanced

- <optimization>
    - clear 0, 1 

- <theory: global illumination>
    - yuzey sadece gelen isigi dikkate aliyor
    - gercekte isik sekip yayilmaya devam ediyor
    - her sey isik kaynagi | isik kac defa sekecek
    - ambient lighting approximate ediyor

- <theory: tonemapping>
    - high dynamic range
        - pixel degerleriyle alakali
        - 1 i gecenler bembeyaz, low dynamic range
        - high dynamic range > render / display
        - 0, 1 

- <procedure: yeni shader ekleme>
    - ilgili shader dosya isimlerini olsutur
    - ilgili shader dosya isimleri shader mapping e ekle
    - shaderlari yarat
    - naming conventionaa adapte et

- <procedure: new 3d, yeni sahne elemani ekleme>
    - array i sec veya olustur
    - array i name map e isim verecek sekilde ekle
    - predef scene element e once header sonra dosyada ekle ilgili shader ve transformlari olustur

- <procedure: yeni class olusturma>
    - once headeri olustur. Arayuzu ve memberlari belirle
    - .cpp dosyasini olusturup memberlari yazmay basla

- <procedure: loop gif uretme>
    - sharex ile loop olusturacak gifi kaydet
        - tam loop olduguna isiklarin dogru olduguna emin ol
    - ezgif > split > cut
    - frames 6, 100
    - download, yeniden yukle, optimizer
        - 2mb altina dusur

- <linear algebra: transformation application order>
    - ilk scale,
    - sonra rotate
    - sonra transform

- <cpp: string to const char*>
    .c_str()

- <cpp: function wrapper>
    -   // Create a std::function wrapper for the 'add' function
        std::function<int(int, int)> addFunction = add;
        // Use the wrapper as if it were a regular function
        int result = addFunction(3, 4);
        std::cout << "Result: " << result << std::endl;

- <cpp: lambda function>
    - A lambda function, also known as an anonymous function or a lambda expression, is a concise way to define small, unnamed functions in programming languages. Lambda functions are particularly common in languages that support functional programming paradigms, and C++ is one such language.
    In C++, a lambda function is defined using the following syntax:
    [capture](parameters) -> return_type {
    // function body
    }

- <test basic>
    - activate on main blackboard -> use blackboard.css as blank page on source/blackboard

- <test unit>
    - test/test.h uzerinde yeni unit test dosyasinin ana fonksiyonunu yaz
    - uTest_ClassName.cpp (example: transform)
    - constructor ve fonksiyonlar icin teker teker test yaz
    - her test icin parametreleri degistir
    - calistigini kontrol etmek icin bir kere fail, bir kere pass yaptir

- <change file an folder name of project>
    - change folder name
    - change .sln, .user, .vcxproj, .filters files name
    - open .sln file change name and .vcxproj name
    - open .vcxproj change rootnamespace, projectname
    - test if working
    - change github folder 

- <common bugs>
    - floating point precision
    - null pointer dereference
    - unhandled exception
    - buffer overflow 
    - link error

- <git dosya gormeme>
    - obj dosyayi gormuyor bu durumda hem dosya adi hem de icerigini ayri ayri git ignore a eklemek gerekiyor
    - bkz. gitignore

- <multiple render target debugging>
    - 

- <shading>
    - sadece color without lighting istediginde diffuse map i frag vectore gonder.
    

- <class icinde static mi degil mi>
    - application geneline mi ozel instance ina mi

- <cpp and header file structure>
    1. notes
    2. libraries
    3. self keywords
    4. global variables
    5. function declarations
    6. abstract
    7. function definitions
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

- <integrate 3rd party third party libraries | self compile library>
    - compiled library
        - kutuphane source u indir 
        - cmake ile build i yarat
            - https://learnopengl.com/Getting-started/Creating-a-window
            - download
            - create build folder in the same folder
            - open cmake
                - where is the source code:     folder
                - where to build the binaries:  folder/build
                - configure
                - check values in red click configure again
                - generate
        - vs uzerinde acip debug/release buildleri yap
            - top menu > build > build solution
        - sub module
        - statik kirli yol (.lib NOT .dll)
            - project properties > vc++ directories > add library directiories > lib folder | conventio
            - project properties > vc++ directories > add library directiories > include folder 
            - project properties > linker > input   > additional dependencies > ex. glfw3.lib;opengl32.lib | buraya .dll degil .lib geliyor
            - project properties > linker > general > add additional library directories

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

- <problems>
    - float modulus
        - fmod(x, y)
    - texture is reversed, upside down
        - try stbi -> image flip

- <exceptions>
    - Exception thrown at 0x00007FF870AFCF19 in opengl_renderer.exe: Microsoft C++ exception: std::ios_base::failure at memory location 0x000000ECD359D5C0.

- <shader problems>
- Block "VS_OUT" mismatch between shader stages

- <vocab>
    - polling 
        - periyodik araliklarla check etmek
        - callback

- <errors>
    - error C7560: 'displacement': designators must appear in member declaration order of class 'TexturePaths'
        - siralamanin tutmasi gerekiyormus

    - Exception thrown at 0x00007FFC8AB3D6AB (nvoglv64.dll) in opengl_renderer.exe: 0xC0000005: Access violation reading location 0x0000000000000010.

    - error C2259: 'Application': cannot instantiate abstract class
        - The error message "error C2259: 'Application': cannot instantiate abstract class" typically occurs when you try to create an instance of a class that has one or more pure virtual functions but has not provided implementations for those functions. In your case, the Application class inherits from InputListener, which is an abstract class due to the presence of pure virtual functions.

    - error C3861: 'stbi_flip_vertically_on_write': identifier not found
        - include un ustune 
        - #define STB_IMAGE_WRITE_IMPEMENTATION eklemezsen calismiyor

    - error C4996: 'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead
        - #define _CRT_SECURE_NO_WARNINGS
        - alternatif: properties > c/c++ > 

    - the code xecution cannot proceed because assimp-vc143-mt.dll was not found. Reinstalling the program may fix this problem.

    - error c2243: exists, but is inaccessible
        - derived class private : classname to : public classname
    
    - error e0349: no operator "[]" matches these operand
        - unordered map e erisme seklin probemli map[key] degil map.at(key)
    
    - error C2664: 'void Application::drawModel(Model &,int &,const char *,Uniforms &)': cannot convert argument 2 from     'unsigned int' to 'int &'
        - signature tutmuyor
    
    - LNK2019: unresolved external symbol "private: void __cdecl Application::drawModel(class Model &,unsigned int &,char const *,struct Uniforms &)" (?drawModel@Application@@AEAAXAEAVModel@@AEAIPEBDAEAUUniforms@@@Z) referenced in function "private: void __cdecl Application::drawScene(struct Uniforms &)" (?drawScene@Application@@AEAAXAEAUUniforms@@@Z)
    1>C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\opengl_renderer\x64\Debug\opengl_renderer.exe
    
    - error LNK2001: unresolved external symbol "public: static float * Predef3D::quad_vrts__pos_tex" (?quad_vrts__pos_tex@Predef3D@@2PAMA)
    1>C:\Users\kutay\OneDrive\Documents\GitHub\study_opengl\opengl_renderer\x64\Debug\opengl_renderer.exe : fatal error 
        - not resolved function / virtual fonksiyonlarda cikti. Adi geciyor ama fonksiyon tanimi yok
        - This error typically occurs when you declare a static member variable in a class but fail to define it outside the class. In C++, static member variables need to be defined outside the class declaration.

    - error LNK1120: 1 unresolved externals
    1>Done building project "opengl_renderer.vcxproj" -- FAILED.
        - cant find definition
        - PredefNameMaps:: unutmusum
    
    - Unhandled exception at 0x00007FF870AFCF19
        - callstack e bak
            - at cagiriyorsan iceride oldugundan emin olman lazim .at("")

- <warnings>
    - conversation from 'size_t' to 'int' possible loss of data
        static_cast<int>();
    - unreferenced local variable
        - not used in program just delete

    - warning C4715: 'Application::initialize': not all control paths return a value
        - return donmesi gereken bir fonksiyon donmuyor?
    - warning STL4038: The contents of <variant> are available only with C++17 or later.
        - project > properties > c/c++ > langugae > c++ langugae standard ayarla
    - warning C4267: 'argument': conversion from 'size_t' to 'GLsizei', possible loss of data
    - warning C5105: macro expansion producing 'defined' has undefined behavior
    - Warning	C4312	'type cast': conversion from 'GLsizei' to 'void *' of greater size

- <depth testing>
    - keep z value of index to determine what is front what is back to avoid unnecessary calculation
    - glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  | clear previous depth as well as color to draw new
    - glDepthMask(GL_FALSE);  read only depth buffer?
    - fdepth = (z-near) / (far-near)
    - fdepth = (1/z - 1/near) / ( 1/far - 1/near) -> gives greater precision when the objects are near

- <renderdocs>
    - uniform aktarma knotrolu
        - ilk vs uzerinden uniformlarin dogru shadera gonderilip gonderilmedigini kontrol et

# Shortcuts
- f5                                debugger
- shift + f5                        calisan debug i kapatiyor
- ctrl + shift + f5                 debug i yeniden calistiriyor
- chrl + shift + h                  find and replace
- ctrl + m > i                      local expand
- ctrl + shift + f9                 remove all breakpoints
- ctrl + shift + b                  compile
- shift + alt up/down               multi line edit
- ctrl + alt + l                    solution explorer
- ctrl + -                          bir onceki satira atla
- ctrl + m > o                      collapse
- ctrl + m > p                      expand
- ctrl + m, s                       collapse
- ctrl + m, i                       expand