# Log
- [todo](#todo)
- [nomenclature](#nomenclature)
- [comment discipline](#comment-discipline)
- [logging actions](#logging-actions)
- [log](#log)


# Nomenclature
- 1.1
    - Conventions
        1. all lower case with underscore: table_name 
            - underscore yoksa - : table-names
            - ikisi de yoksa:    : TableName
        2. mixed case                     : TableName
        3. 
    - common variable names: 1
        - ex. table_items
    - class data members: 1
    - global constants has `k` in front of the mixed
        - ex. k_table
    - pointer degisken isimleri `p` ile baslasin
        - ex. p_table
        - birden fazla front tag varsa birlestir
        - kp_table 
    - function names: 2
        - DoSometing()

# Comment Discipline 
- 1.6
    comment             :        | "#888888"
    xx                  :   .    | "#dbdbdb"
    title               :   ==== | "#00c8ff" 
    sub-title           :   ==   | "#128EC4"
    description         :   ::   | "#06b4ba" 
    problem             :   !!   | "#FF2D00"
    query               :   ??   | "#33ffff" 
    todo                :   >>   | "#da1991"
    test                :   test | "#ffa100"
    separator line      :   --   | "#99ff33"
    ----------------------------------------
    highlight           :   **   | "#8fab21"  
    disabledProperty    :  none


# Logging Actions
- 1.6
    - org: organization, decisions, notebook changes
    - arch: architectural, framework change, tryout

    - com: installation, compatibility update
    - add: add, insert, data content

    - del: deleted
    - fix: fix a bug or problem
    - upg: update, upgraded, progressed, optimize
    - chg: stylistic change, typo

    - std: study, learn, test
    - wip: work in progress
    - mix: multiple additions

    + versiyon sonunda ! varsa repository push yok

# Push procedure checklist 1.4
- check todo
- add log
- change readme version and date
- change time log
- push


# Todo
- [x] 05-Apr-202324-Aug-2022 utility yi ayir
- [x] 30-Mar-2023 04-Sep-2022 draw 2 triangles next to each other 
- [x] 30-Mar-2023 04-Sep-2022 create same 2 triangles using two different VAO and VBO 
- [x] 30-Mar-2023 04-Sep-2022 create two shader programs where the second program uses different fragment shader that outputs different color and draw tri with diff shad.
- [x] 07-Apr-2023 05-Apr-2023 arch: datayi ayir
- [x] 21-Apr-2023 07-Apr-2023 add: data class icine alan refacting
- 05-Apr-2023 fix: split fonksiyonunu duzelt
- 12-Apr-2023 add: deserialize config or config struct


# Log
- [x]
    - todo transformation
    - todo gui

- [0.25] add: Namespace utilities
    - 26-Apr-2023   wip: Vector class, transformations
    - 26-Apr-2023   add: Create vector struct, unit test
    - 26-Apr-2023   add: namespace utilities
    - 26-Apr-2023   arch: Refactor image_utils, test, events

- [0.24] add: Texture exercises
    - 26-Apr-2023   add: Textures exercise 4
    - 25-Apr-2023   add: Texture wrapping parameters on createTexture function 
    - 25-Apr-2023   std: Textures exercise 1,2 

- [0.23] add: Textures ... 
    - 21-Apr-2023   add: createTexture functions
    - 21-Apr-2023   learn: practice stb_image.h library
    - 21-Apr-2023   del: commented out code
    - 21-Apr-2023   arch: Shader class 
    - 18-Apr-2023   wip: opengl textures

- [0.221] arch: Refactor ObjToDraw as class static
    - 18-Apr-2023   arch: refactor data obj as static class obj 
    - 16-Apr-2023   arch: main remove duplicate return

- [0.21] arch: Shader utilities
    - 16-Apr-2023   arch: shader utilities functions are separated
    - 16-Apr-2023   add: learnopengl shader class (not in use)
    - 14-Apr-2023   learn: color triangle
    - 14-Apr-2023   learn: altering colors through uniforms
    - 12-Apr-2023   arch: assignBuffer, drawObjToScr

- [0.20] arch: Shader, data decoupling
    - 12-Apr-2023   arch: Shader compile, linker, delete functions
    - 11-Apr-2023   name: rename shadersource names
    - 11-Apr-2023   arch: load shader fonksiyonunu ayir
    - 07-Apr-2023   arch: shader read separation
    - 07-Apr-2023   arch: data separation
    - 06-Apr-2023   study: study on data formats

- [0.19] arch: Organization prototype
    - 05-Apr-2023   arch: configuration file separation
        - folders added: config (.xml, .json, .yaml, .ini) data (textures, points, lines, .obj)
    - 04-Apr-2023   learn: 3rd party library ekleme
    - 04-Apr-2023   arch: test function, testi yaz statik test degiskeni ekle, shaderlari dosyadan oku 
    - 31-Mar-2023   arch: separating main function 
    - 30-Mar-2023   arch: categorizing files
        - folders: shaders (.glsl), headers (.h), source (.cpp), libs (glad)
    - starting shaders

- [0.18] add: Hello triangle exercises
    - 30-Mar-2023   hello triangle exercices
        - exercise 1: draw 2 triangle
        - exercise 2: draw 2 triangle with different voa and vbos
        - exercise 3: use different fragment shaders for each triangle
    - 29-Mar-2023   repeat previous

- [old]
- 04-Sep-2022 0.17      add: Hello triangle
- 24-Aug-2022 0.16!     wip: Hello triangle
- 23-Aug-2022 0.15!     org: Nomenclature, Comment Discipline, Logging Actions
- 23-Aug-2022 0.14      add: Hello window
- 22-Aug-2022 0.13!     add: installing and including libraries GLAD, GLFW
- 22-Aug-2022 0.12!     add: Basic cpp practice
- 19-Aug-2022 0.11      add: Visual Studio Project Files and gitignore expansion
- 19-Aug-2022 0.10      Project git folder created