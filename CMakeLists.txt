# Set required CMake version
cmake_minimum_required(VERSION 3.24)

# Set the project name
project(project_test)

# multiprocessor compile
add_compile_options(/MP)

# ----------------------------------------------------------------------------------------
#               Standards and Configurations
# ----------------------------------------------------------------------------------------

# Optional: Define the C++ standard you want to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the architecture
set(InstructionSetArchitecture x64)
set(CMAKE_GENERATOR_PLATFORM ${InstructionSetArchitecture})

# Set startup project to project other than CMake builds (for Visual Studio)
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}
)

# use folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set default build type if not specified (optional)
# if(NOT CMAKE_BUILD_TYPE)
#     message(STATUS "CMAKE_BUILD_TYPE not specified. Setting default to 'Release'.")
#     set(CMAKE_BUILD_TYPE "Release")
# endif()

# ----------------------------------------------------------------------------------------
#               Main Directories
# ----------------------------------------------------------------------------------------
set(configDir
    "${CMAKE_SOURCE_DIR}/config/" 
) 

set(dataDir
    "${CMAKE_SOURCE_DIR}/data/" 
) 

set(shaderDir
    "${CMAKE_SOURCE_DIR}/shaders/" 
) 

set(sourceDir
    "source"
)

# Define the output directory based on system name, architecture, and build type
set(outputDir 
    "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${InstructionSetArchitecture}/${CMAKE_BUILD_TYPE}"    
)


# ----------------------------------------------------------------------------------------
#               Main Files
# ----------------------------------------------------------------------------------------
set(sourceCode
    "${sourceDir}/main.cpp"

    "${sourceDir}/blackboard/blackboard.cpp"
    
    "${sourceDir}/core/application.cpp"
    
    "${sourceDir}/event_handling/input_speaker.cpp"
    "${sourceDir}/event_handling/ui_events.cpp"
    "${sourceDir}/event_handling/window_events.cpp"
    
    "${sourceDir}/libs/asset_import.cpp"
    
    "${sourceDir}/scene/camera.cpp"
    "${sourceDir}/scene/scene.cpp"

    "${sourceDir}/test/btest_hello_world.cpp"
    "${sourceDir}/test/btest_test.cpp"
    "${sourceDir}/test/itest_transformations.cpp"
    "${sourceDir}/test/utest_matrix4.cpp"
    "${sourceDir}/test/utest_queue.cpp"
    "${sourceDir}/test/utest_transform.cpp"
    "${sourceDir}/test/utest_vector3.cpp"
    "${sourceDir}/test/utest_vector4.cpp"

    "${sourceDir}/utils/common_utils.cpp"
    "${sourceDir}/utils/image_utils.cpp"
    "${sourceDir}/utils/matrix_utils.cpp"
    "${sourceDir}/utils/self_utils.cpp"
    "${sourceDir}/utils/shader_utils.cpp"
    "${sourceDir}/utils/vector_utils.cpp"

    "${configDir}/config.yaml"

    "${dataDir}/_maps/predef3d_namemap.cpp"
    "${dataDir}/_maps/texture_name-pathmap.cpp"

    "${dataDir}/_paths/model_paths.cpp"
    "${dataDir}/_paths/shader_paths.cpp"

    "${dataDir}/_predefs/predef_materials.cpp"
    "${dataDir}/_predefs/predef_primitive_scene_nodes.cpp"
    "${dataDir}/_predefs/predef_scene_lights.cpp"
    "${dataDir}/_predefs/predef_vertex_data.cpp"

    "${dataDir}/_scenes/1.0_testscene.cpp"
    "${dataDir}/_scenes/2.0_multiplelights_testscene.cpp"
    "${dataDir}/_scenes/2.3_importmodel_testscene.cpp"
    "${dataDir}/_scenes/3.0_outliner_testscene.cpp"
    "${dataDir}/_scenes/3.10.instancing_testscene.cpp"
    "${dataDir}/_scenes/3.11.antialiasing_testscene.cpp"
    "${dataDir}/_scenes/3.2_blending_testscene.cpp"
    "${dataDir}/_scenes/3.3_faceculling_testscene.cpp"
    "${dataDir}/_scenes/3.4_framebuffers_testscene.cpp"
    "${dataDir}/_scenes/3.5_cubemap_testscene.cpp"
    "${dataDir}/_scenes/3.8_advglsl_testscene.cpp"
    "${dataDir}/_scenes/3.9_geoshader_testscene.cpp"
    "${dataDir}/_scenes/4.1.blinnphong_testscene.cpp"
    "${dataDir}/_scenes/4.2_gammacorrection_testscene.cpp"


)


# set(dataFiles
#     "${dataDir}/test.stl"
# )


# ----------------------------------------------------------------------------------------
#               CMake Environment Variables
# ----------------------------------------------------------------------------------------
# Specify where to output archive (static libs), libraries, and executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${outputDir}/static_libs"
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${outputDir}"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${outputDir}"
)


# ----------------------------------------------------------------------------------------
#               Adding Required Packages (OpenGL, GLFW, GLEW, etc.)
# ----------------------------------------------------------------------------------------
# Find OpenGL
find_package(OpenGL REQUIRED)

# Optional: Find other libraries (GLFW, GLEW, etc.)
# For example, to add GLFW, you can use:
# find_package(GLFW3 REQUIRED)

# ----------------------------------------------------------------------------------------
#               Include Directories and Executable
# ----------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${sourceCode})

# ----------------------------------------------------------------------------------------
#               Adding Libraries
# ----------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# ----------------------- includes
# Add the headers directory so the compiler can find header files
include_directories(
    # "${CMAKE_SOURCE_DIR}/headers"
    "${CMAKE_SOURCE_DIR}/headers/abstract"
    "${CMAKE_SOURCE_DIR}/headers/core"
    "${CMAKE_SOURCE_DIR}/headers/data"
    "${CMAKE_SOURCE_DIR}/headers/events"
    "${CMAKE_SOURCE_DIR}/headers/maps"
    "${CMAKE_SOURCE_DIR}/headers/templates"
    "${CMAKE_SOURCE_DIR}/headers/test"
    "${CMAKE_SOURCE_DIR}/headers/utils"
    )

# ----------------------- glad
include_directories("${CMAKE_SOURCE_DIR}/libs/glad-0.136/include")
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/libs/glad-0.136/src/glad.c")
target_link_libraries(${PROJECT_NAME} PRIVATE glad)


# ----------------------- stb
include_directories("${CMAKE_SOURCE_DIR}/libs/stb")



# include_directories("${CMAKE_SOURCE_DIR}/libs/header_hello_1.0.0")
# add_library( # MODULE, STATIC, SHARED (DYNAMIC)
#     "hello" STATIC
#     "libs/header_hello_1.0.0/hello.cpp"
# )
# target_link_libraries(${PROJECT_NAME} PRIVATE hello)

# submodules

# ----------------------- glfw
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/glfw") 
include_directories("${CMAKE_SOURCE_DIR}/libs/glfw/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# ----------------------- assimp
# Disable building all importers and exporters by default
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
# Enable only the importers you need (e.g., OBJ)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)  
# Disable specific features or tests that you don't need
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)  # Disable tools like assimp_cmd

add_subdirectory("${CMAKE_SOURCE_DIR}/libs/assimp") 
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/assimp/include)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)

# ----------------------- imgui
include_directories("${CMAKE_SOURCE_DIR}/libs/imgui")
add_library( # MODULE, STATIC, SHARED (DYNAMIC)
    "imgui" STATIC
    "libs/imgui/imgui.cpp"
    "libs/imgui/imgui_demo.cpp"
    "libs/imgui/imgui_draw.cpp"
    "libs/imgui/imgui_tables.cpp"
    "libs/imgui/imgui_widgets.cpp"
    "libs/imgui/backends/imgui_impl_glfw.cpp"
    "libs/imgui/backends/imgui_impl_opengl3.cpp"

)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

# Add the executable, linking the project name with the source files

# this definition could be used in code
add_compile_definitions(CONFIG_DIR="${configDir}")
add_compile_definitions(DATA_DIR="${dataDir}")
add_compile_definitions(SHADER_DIR="${shaderDir}")


# ----------------------------------------------------------------------------------------
#               Set Folders
# ----------------------------------------------------------------------------------------
set_property(TARGET glad PROPERTY FOLDER "Libs/glad")

set_property(TARGET assimp PROPERTY FOLDER "Libs/assimp")
set_property(TARGET zlibstatic PROPERTY FOLDER "Libs/assimp")
set_property(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTY FOLDER "Libs/assimp")

set_property(TARGET glfw PROPERTY FOLDER "Libs/glfw")
set_property(TARGET uninstall PROPERTY FOLDER "Libs/glfw")
set_property(TARGET update_mappings PROPERTY FOLDER "Libs/glfw")


set_property(TARGET imgui PROPERTY FOLDER "Libs/imgui")


# "${sourceDir}/shaders/1.0.3d_frag_shader.glsl"
# "${sourceDir}/shaders/1.0.3d_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.1.axis-x_frag_shader.glsl"
# "${sourceDir}/shaders/1.1.axis-x_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.1.axis-z_frag_shader.glsl"
# "${sourceDir}/shaders/1.1.axis-z_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.1.axis-z_frag_shader.glsl"
# "${sourceDir}/shaders/1.2.diffuse_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.2.diffuse_frag_shader.glsl"
# "${sourceDir}/shaders/1.3.green_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.3.green_frag_shader.glsl"
# "${sourceDir}/shaders/1.4.pink_vrtx_shader.glsl"
# "${sourceDir}/shaders/1.4.pink_frag_shader.glsl"
# "${sourceDir}/shaders/2.0.phong_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.0.phong_lit_frag_shader.glsl"
# "${sourceDir}/shaders/2.1.lightmap_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.1.lightmap_lit_frag_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-directional_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-directional_lit_frag_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-point_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-point_lit_frag_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-spot_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.2.lightcaster-spot_lit_frag_shader.glsl"
# "${sourceDir}/shaders/2.3.multiplelights_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/2.3.multiplelights_lit_frag_shader.glsl"
# "${sourceDir}/shaders/3.0.depthtesting_lit_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.0.depthtesting_lit_frag_shader.glsl"
# "${sourceDir}/shaders/3.1.stenciltesting_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.1.stenciltesting_frag_shader.glsl"
# "${sourceDir}/shaders/3.1.stenciltesting02_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.1.stenciltesting02_frag_shader.glsl"
# "${sourceDir}/shaders/3.2.blending_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.2.blending_frag_shader.glsl"
# "${sourceDir}/shaders/3.4.framebuffer_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.4.framebuffer_frag_shader.glsl"
# "${sourceDir}/shaders/3.5.cubemap_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.5.cubemap_frag_shader.glsl"
# "${sourceDir}/shaders/3.6.cubemaplit_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.6.cubemaplit_frag_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-blue_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-blue_frag_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-green_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-green_frag_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-red_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-red_frag_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-yellow_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.8.advglsl-yellow_frag_shader.glsl"
# "${sourceDir}/shaders/3.9.axes_frag_shader.glsl"
# "${sourceDir}/shaders/3.9.axes_geo_shader.glsl"
# "${sourceDir}/shaders/3.9.axes_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.9.explode_frag_shader.glsl"
# "${sourceDir}/shaders/3.9.explode_geo_shader.glsl"
# "${sourceDir}/shaders/3.9.explode_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.9.geo_frag_shader.glsl"
# "${sourceDir}/shaders/3.9.geo_geo_shader.glsl"
# "${sourceDir}/shaders/3.9.geo_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.9.normal_frag_shader.glsl"
# "${sourceDir}/shaders/3.9.normal_geo_shader.glsl"
# "${sourceDir}/shaders/3.9.normal_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.10.instance_frag_shader.glsl"
# "${sourceDir}/shaders/3.10.instance_vrtx_shader.glsl"
# "${sourceDir}/shaders/3.10.instance02_frag_shader.glsl"
# "${sourceDir}/shaders/3.10.instance02_vrtx_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong_frag_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong_vrtx_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong_frag_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong_vrtx_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong2_frag_shader.glsl"
# "${sourceDir}/shaders/4.1.blinnphong2_vrtx_shader.glsl"
# "${sourceDir}/shaders/4.2.gamma_frag_shader.glsl"
# "${sourceDir}/shaders/4.2.gamma_vrtx_shader.glsl"

