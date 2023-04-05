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
- 24-Aug-2022 utility yi ayir
- [x] 30-Mar-2023 04-Sep-2022 draw 2 triangles next to each other 
- [x] 30-Mar-2023 04-Sep-2022 create same 2 triangles using two different VAO and VBO 
- [x] 30-Mar-2023 04-Sep-2022 create two shader programs where the second program uses different fragment shader that outputs different color and draw tri with diffent shader


# LOG
- [0.19] arch: File organization prototype
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