# Set required CMake version
cmake_minimum_required(VERSION 3.24)

# Set the project name
project(opengl_renderer)

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
#               Adding Required Packages (OpenGL, GLFW, GLEW, etc.)
# ----------------------------------------------------------------------------------------
# Find OpenGL
find_package(OpenGL REQUIRED)


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
)

set(blackboardCode
    "${sourceDir}/blackboard/blackboard.cpp"
)

set(coreCode
    "${sourceDir}/core/application.cpp"
)

set(eventHandlingCode
    "${sourceDir}/event_handling/input_speaker.cpp"
    "${sourceDir}/event_handling/ui_events.cpp"
    "${sourceDir}/event_handling/window_events.cpp"
)

set(libsCode
    "${sourceDir}/libs/asset_import.cpp"
)

set(sceneCode
    "${sourceDir}/scene/camera.cpp"
    "${sourceDir}/scene/scene.cpp"
)

set(testCode
    "${sourceDir}/test/btest_hello_world.cpp"
    "${sourceDir}/test/btest_test.cpp"
    "${sourceDir}/test/itest_transformations.cpp"
    "${sourceDir}/test/utest_matrix4.cpp"
    "${sourceDir}/test/utest_queue.cpp"
    "${sourceDir}/test/utest_transform.cpp"
    "${sourceDir}/test/utest_vector3.cpp"
    "${sourceDir}/test/utest_vector4.cpp"
)

set(utilsCode
    "${sourceDir}/utils/common_utils.cpp"
    "${sourceDir}/utils/image_utils.cpp"
    "${sourceDir}/utils/matrix_utils.cpp"
    "${sourceDir}/utils/self_utils.cpp"
    "${sourceDir}/utils/shader_utils.cpp"
    "${sourceDir}/utils/vector_utils.cpp"
)

set(configFiles
    "${configDir}/config.yaml"
)

set(dataMaps
    "${dataDir}/_maps/predef3d_namemap.cpp"
    "${dataDir}/_maps/texture_name-pathmap.cpp"
)

set(dataPaths
    "${dataDir}/_paths/model_paths.cpp"
    "${dataDir}/_paths/shader_paths.cpp"
)

set(dataPredefs
    "${dataDir}/_predefs/predef_materials.cpp"
    "${dataDir}/_predefs/predef_primitive_scene_nodes.cpp"
    "${dataDir}/_predefs/predef_scene_lights.cpp"
    "${dataDir}/_predefs/predef_vertex_data.cpp"
)

set(dataScenes
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
#               Header Files
# ----------------------------------------------------------------------------------------
set(abstractHeaders
    "${CMAKE_SOURCE_DIR}/headers/abstract/application.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/Camera.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/light.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/material.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/matrix4.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/mesh.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/model.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/queue.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/scene.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/scene_state.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/shader.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/transform.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/ui.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/uniforms.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/vector2.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/vector3.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/vector4.h"
    "${CMAKE_SOURCE_DIR}/headers/abstract/window_state.h"
)

set(coreHeaders
    "${CMAKE_SOURCE_DIR}/headers/core/opengl.h"
    "${CMAKE_SOURCE_DIR}/headers/core/ui.h"
)

set(dataHeaders
    "${CMAKE_SOURCE_DIR}/headers/data/data.h"
    "${CMAKE_SOURCE_DIR}/headers/data/scenes.h"
)

set(eventsHeaders
    "${CMAKE_SOURCE_DIR}/headers/events/events.h"
    "${CMAKE_SOURCE_DIR}/headers/events/input_observer.h"
)

set(mapsHeaders
    "${CMAKE_SOURCE_DIR}/headers/maps/shaders.h"
)

set(templatesHeaders
    "${CMAKE_SOURCE_DIR}/headers/templates/header_template_1.0.h"
)

set(testHeaders
    "${CMAKE_SOURCE_DIR}/headers/test/basic.h"
    "${CMAKE_SOURCE_DIR}/headers/test/integration_tests.h"
    "${CMAKE_SOURCE_DIR}/headers/test/unit_tests.h"
)

set(utilsHeaders
    "${CMAKE_SOURCE_DIR}/headers/utils/utilities.h"
)

# ----------------------------------------------------------------------------------------
#               All Header Files
# ----------------------------------------------------------------------------------------

set(allHeaderFiles
    ${abstractHeaders}
    ${coreHeaders}
    ${dataHeaders}
    ${eventsHeaders}
    ${mapsHeaders}
    ${templatesHeaders}
    ${testHeaders}
    ${utilsHeaders}
    
)

# ----------------------------------------------------------------------------------------
#               Organize the source structure into folders
# ----------------------------------------------------------------------------------------
source_group(TREE ${CMAKE_SOURCE_DIR}/source PREFIX "source" FILES ${sourceCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/blackboard PREFIX "source/blackboard" FILES ${blackboardCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/core PREFIX "source/core" FILES ${coreCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/event_handling PREFIX "source/event_handling" FILES ${eventHandlingCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/libs PREFIX "source/libs" FILES ${libsCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/scene PREFIX "source/scene" FILES ${sceneCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/test PREFIX "source/tests" FILES ${testCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/utils PREFIX "source/utils" FILES ${utilsCode})
source_group(TREE ${configDir} PREFIX "config" FILES ${configFiles})
source_group(TREE ${dataDir}/_maps PREFIX "data/_maps" FILES ${dataMaps})
source_group(TREE ${dataDir}/_paths PREFIX "data/_paths" FILES ${dataPaths})
source_group(TREE ${dataDir}/_predefs PREFIX "data/_predefs" FILES ${dataPredefs})
source_group(TREE ${dataDir}/_scenes PREFIX "data/_scenes" FILES ${dataScenes})

# ----------------------------------------------------------------------------------------
#               Organize Header Files into Folders
# ----------------------------------------------------------------------------------------

source_group(TREE ${CMAKE_SOURCE_DIR}/headers/abstract PREFIX "headers/abstract" FILES ${abstractHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/core PREFIX "headers/core" FILES ${coreHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/data PREFIX "headers/data" FILES ${dataHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/events PREFIX "headers/events" FILES ${eventsHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/maps PREFIX "headers/maps" FILES ${mapsHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/templates PREFIX "headers/templates" FILES ${templatesHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/test PREFIX "headers/test" FILES ${testHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/headers/utils PREFIX "headers/utils" FILES ${utilsHeaders})


# ----------------------------------------------------------------------------------------
#               Include Directories and Executable
# ----------------------------------------------------------------------------------------
add_executable(
    ${PROJECT_NAME}
    ${sourceCode}
    ${blackboardCode}
    ${coreCode}
    ${eventHandlingCode}
    ${libsCode}
    ${sceneCode}
    ${testCode}
    ${utilsCode}
    ${configFiles}
    ${dataMaps}
    ${dataPaths}
    ${dataPredefs}
    ${dataScenes}
    # Adding headers here doesn't affect compilation, but makes them appear in the solution explorer
    ${abstractHeaders}
    ${coreHeaders}
    ${dataHeaders}
    ${eventsHeaders}
    ${mapsHeaders}
    ${templatesHeaders}
    ${testHeaders}
    ${utilsHeaders}
)

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

