# Log
- [todo](#todo)
- [nomenclature](#nomenclature)
- [comment discipline](#comment-discipline)
- [logging actions](#logging-actions)
- [log](#log)


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


# Todo
- [x] 05-Apr-2023 24-Aug-2022 utility yi ayir
- [x] 30-Mar-2023 04-Sep-2022 draw 2 triangles next to each other 
- [x] 30-Mar-2023 04-Sep-2022 create same 2 triangles using two different VAO and VBO 
- [x] 30-Mar-2023 04-Sep-2022 create two shader programs where the second program uses different fragment shader that outputs different color and draw tri with diff shad.
- [x] 07-Apr-2023 05-Apr-2023 arch: datayi ayir
- [x] 21-Apr-2023 07-Apr-2023 add: data class icine alan refacting
- [x] 03-May-2023 02-May-2023 add: struct Vec4
- [x] 03-May-2023 05-May-2023 add: Matrix utilities
- [x] 17-May-2023 17-May-2023 todo 6 parameter projectPerspective function
- [d] 05-Apr-2023 fix: split fonksiyonunu duzelt
- [x] 18-May-2023 17-May-2023 todo 4 parameter projectPerspective function
- [x] 18-May-2023 16-May-2023 fix: find reason of perspective distortion 
- [x] 30-May-2023 18-May-2023 arch: refactoring after v0.31
- [x] 30-May-2023 16-May-2023 add: Imgui draw ui encapsulate in self function   
- [x] 31-May-2023 30-May-2023 add: refactor load shader, mesh, texture functions
- [x] 04-Jun-2023 04-Jun-2023 add: display: Camera rotation
- [x] 12-Jun-2023 11-Jun-2023 arch: mat4 transformasyonlari alt alta yaz
- [x] 12-Jun-2023 11-Jun-2023 add: phong shading
- [x] 12-Jun-2023 12-Jun-2023 fix: naming inconsistency on shaders
- [x] 12-Jun-2023 06-Jun-2023 add: refactor after 0.36: file / folder renaming
- [x] 13-Jun-2023 12-Jun-2023 add: basic ligtging exercises
- [x] 20-Jun-2023 02-Jun-2023 add: consistent naming on file structure
- [x] 25-Jun-2023 24-Jun-2023 add: light casters display scene
- [x] 25-Jun-2023 24-Jun-2023 add: ui toggle button
- [x] 25-Jun-2023 24-Jun-2023 add: light brightness, light color 
- [x] 25-Jun-2023 06-Jun-2023 add: Camera class / struct
- [x] 25-Jun-2023 02-Jun-2023 add: Code standard: openGL.h / d_objToDraw / 3d_fragShader / unitTest_Vector4 cases ekle
    - opengl.h | objto_draw | 3d_frag_shader | utest_vector4 |
- [x] 03-Jul-2023 01-Jul-2023 add: new scene for multiple lights, scene state multiple light positions
- [x] 11-Jul-2023 11-Jul-2023 add: kutuphanelerin static pathlerini duzelt
- [x] 11-Jul-2023 08-Jul-2023 fix: assimp import olayini coz
- [x] 20-Jul-2023 20-Jul-2023 fix: textures are not mapped correctly
    - fix through texture flipping on y axis
- [x] 20-Jul-2023 fix: specular texture not working
    - forgot to assign textures to send shader
- [x] 21-Jul-2023 20-Jul-2023 add: load self model
- 12-Apr-2023 add: deserialize config or config struct
- 02-May-2023 add: struct VecN
- 28-May-2023 add: Edge detection / outlines
- 04-Jun-2023 arch: Comment standard
- 06-Jun-2023 add: application singleton
- 20-Jun-2023 add: obje verisi soyutlama | https://vilbeyli.github.io/C++-Conditional-Compiling-using-constexpr/
- 24-Jun-2023 add: ui camera, direction, light direction controls
- 25-Jun-2023 add: documentation: keys, ui controls
- 11-Jul-2023 add: pitch distortion

# Push procedure checklist 1.4
- add log
- check todo
- change readme version and date
- change time log
- push

# Log
                                                                               |
- [0.47] add: Stencil testing
    - 29-Jul-2023
        - add: documentation camera controls
        - add: display stencil test 2
        - add: display stencil test 1
    - 28-Jul-2023
        - add: set scene state model from single variable to vector
        - add: test objects created separately
        - add: display stencil scale outlining normalized thickess
    - 27-Jul-2023
        - wip: outline thickness problem
        - add: outlining object through stencil testing
        - wip: stencil testing

- [0.46] add: Depth testing
    - 21-Jul-2023
        - add: depth testing
        - add: new scene for depth testing chapter
    - 21-Jul-2023
        - add: display fixed specular
        - fix: weird speculars on bottom parts solved through adding view dir uniform, reflection calculation
        - fix: readme references

- [0.45] add: asset importer library
    - 21-Jul-2023
        - add: display model import
        - fix: specular texture problem
    - 20-Jul-2023
        - add: model references
        - arch: draw / update separation on set light parameter functions
        - add: Test models creation and import
        - add: workshop file on gitignore
        - add: assimp model loader
        - fix: model load texture problem (flip texture on y axis)
    - 13-Jul-2023
        - wip: assimp model import implementation
        - add: mesh class

- [0.44] arch: Camera rework ...
    - 11-Jul-2023
        - add: display multiple lights fixeds
        - fix: fixed some of the warnings
        - add: assimp library loaded
        - add: libraries relative path 
        - add: toggle mouse lock with z key
        - fix: Camera getRight, getUp
        - add: Camera reset function
        - add: Camera speed multiplier with shift
        - add: Q E keys to move up and down
        - fix: Camera class
    - 08-Jul-2023 add: Mesh abstraction
        - wip: fix: assimp import, 
        - wip: model abstraction 
    - 07-Jul-2023
        - add: Vector2 class derived from vector4
        - arch: light parametrization
    - 06-Jul-2023 wip: light parametrization, technical debt
    - 05-Jul-2023
        - fix: specular reflection problem
        - arch: refactor shader 2.3 
        - add: assimp library as static library .lib

- [0.43] add: Multiple lights
    - 03-Jul-2023
        - add: display: multiple lights
        - add: multiple lights scene
        - add: self made ground texture, emission, specular
    - 01-Jul-2023 
        - add: multiple lights shader | directional, point, spot light functions
        - arch: version name on shader file names
    - 30-Jun-2023 
        - arch: shader paths separated into its own file as data
        - arch: each scene split to its own file
    - 25-Jun-2023
        - arch: object world positions moved to data
        - arch: renaming test files: integrationTest to itest, unitTest to utest, basic test to btest
        - arch: ar, near, far, fov variables moved in camera struct
        - arch: split camera functions on its own .cpp file

- [0.42] add: Lightcasters: directional, point, spot
    - 25-Jun-2023 
        - add: light brightness
        - add: ui toggle button (x)
        - add: display: lightcasters
    - 24-Jun-2023
        - wip:  lightcaster display scenes
        - arch: scene state light variables removed and included within light object
    - 23-Jun-2023 
        - add: light casters directional, point, spot light
    - 22-Jun-2023
        - wip: light casters scene, shaders
    - 20-Jun-2023
        - arch: file naming consistency

- [0.41] add: Light map and emission
    - 19-Jun-2023  
        - add: display: light map and emission
        - add: emission texture
        - add: lightmap use on texture
        - 21.12-21.40   wip: Sampling texture   
        - 16.26-17.00   add: light map scene
        - 15.53-16.26   arch: scenes in their own file 
    - 18-Jun-2023   add: red to green, green to blue, blue to red color shift function
    - 18-Jun-2023   fix: light rotation formula 2 to 2.0f

- [0.40] add: Material, Light structs
    - 18-Jun-2023   add: display 0.40 phong shading and materials
    - 18-Jun-2023   fix: Light going black time calculatino fix sin + 1 / 2
    - 17-Jun-2023   add: Material, Light parametrization in shader
    - 13-Jun-2023   wip: Material props use in shader
    - 13-Jun-2023   add: Material struct, Materials class set functions
    - 12-Jun-2023   arch: file folder renaming
    - 12-Jun-2023   add: Orbit light on basic lightning scene
    - 12-Jun-2023   fix: Shader variables naming inconsistency

- [0.38] wip: Diffuse light
    - 11-Jun-2023   add: diffuse light on shading from static light source
    - 11-Jun-2023   add: Learnopengl scene imitation
    - 11-Jun-2023   add: Mat4 *= function
    - 09-Jun-2023   add: New scene for lighting 1 light 1 texture object
    - 09-Jun-2023   fix: b_animate / time dependency broken by adding anim_time
    - 09-Jun-2023   add: Draw scene with different objecs and diff. shaders

- [0.37] wip: Light, Load all shaders at once
    - 09-Jun-2023   add: Load all shaders at once loadShaders()
    - 07-Jun-2023   wip: lighting
    - 06-Jun-2023   arch: split calcViewMatrix split 2 functions lookAt, rotate
    - 06-Jun-2023   add: display: 0.36 camera movement

- [0.36] add: Camera movement, zoom
    - 06-Jun-2023   add: Camera zoom
    - 06-Jun-2023   add: Camera mouse rotation
    - 06-Jun-2023   wip: Camera mouse rotation through pitch yaw
    - 05-Jun-2023   add: deltaTime to camera speed
    - 04-Jun-2023   fix: Readme typo

- [0.35] wip: Camera static rotation / planar movement
    - 04-Jun-2023   add: display: Camera static rotation
    - 04-Jun-2023   add: Vec3 += -= * override functions
    - 04-Jun-2023   add: Camera key movement
    - 03-Jun-2023   wip: Camera lookAt with 3 parameters: position, target, up
    - 03-Jun-2023   wip: Camera variables, lookAt no parameters

- [0.34] add: Cohesion refactor: drawScene, updateScene
    - 02-Jun-2023   arch: Refactor: drawScene, updateScene
    - 31-May-2023   arch: Naming refactor
    - 31-May-2023   chg: element buffer array idsini array olarak tanimla
    - 31-May-2023   arch: Refactor: init- windowsystem, uisystem functions
    - 31-May-2023   arch: Refactor: load- shader, texture, mesh functions

- [0.33] add: Application abstraction
    - 30-Mar-2023   arch: application class initilaize, load, mainloop, unload, exit (first level abstraction)
    - 29-Mar-2023   wip: refactor application class
    - 29-Mar-2023   add: 0.32 display multiple cubes 94 frame
    - 29-May-2023   learn: git stash
    - 28-May-2023   wip: Refactor

- [0.32] add: Multiple cube render
    - 18-May-2023   add: Multiple cube renders
    - 18-May-2023   fix: Readme typo fix

- [0.31] add: 4 Parameter project perspective ...
    - 18-May-2023   add: display: Rotating cube
    - 18-May-2023   fix: RotationXYZ math
    - 18-May-2023   add: 4 Parameter project perspective
    - 17-May-2023   add: clear color through config file
    - 17-May-2023   fun: math utility: Degree to radian converter 
    - 17-May-2023   add: 6 Parameter frustrum initial values


- [0.30] add: Dear Imgui, glm, Transformation pipeline matrices
    - 17-May-2023   add: Install glm library
    - 16-May-2023   wip: projectPerspective with aspect ratio
    - 11-May-2023   add: Imgui basic implementation
    - 10-May-2023   wip: projectPerspective 
    - 09-May-2023   add: Transformation pipeline matrices: world, view, projection 

- [0.29] add: Matrix utils, transformation integration
    - 05-May-2023   add: Last display content
    - 04-May-2023   add: OpenGL realtime uniform change / render scale, rotation
    - 04-May-2023   add: Shader class Mat4 uniform insertion class
    - 04-May-2023   add: Mat4 Vec4 product
    - 04-May-2023   add: Vec4 Vec3 constructor
    - 04-May-2023   add: Matrix utilities, integration test 1

- [0.28] add: Vec4, Mat4, unitTests
    - 03-May-2023   add: Vec4 and Vec4 unit tests
    - 01-May-2023   add: Matrix-Matrix product & unit test
    - 01-May-2023   add: Mat4 aritmetics unit test
    - 30-Apr-2023   add: References update on readme | documentation?

- [0.27] add: Mat4 struct
    - 02-May-2023   add: Struct Vec4, wip: Vec4 unit test
    - 30-Apr-2023   add: Unit_test Mat4: default constructor, parametr constructor, copy constructor
    - 30-Apr-2023   add: Matrix4 struct, constructors, override operators
    - 30-Apr-2023   add: x,y coordinates as data

- [0.26] learn: Vector math
    - 27-Apr-2023   add: Vector dot products
    - 27-Apr-2023   add: Vector/scalar add/sub
    - 27-Apr-2023   add: Vector math: plus, length

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