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
set(config_dir_full
    "${CMAKE_SOURCE_DIR}/config/" 
) 
set(config_dir_relative
    "/config/" 
) 

set(data_dir_full
    "${CMAKE_SOURCE_DIR}/data/" 
) 
set(data_dir_relative
    "/data/" 
) 

set(shader_dir_full
    "${CMAKE_SOURCE_DIR}/shaders/" 
)
set(shader_dir_relative
    "/shader/" 
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
    "${sourceDir}/core/renderer.cpp"
    "${sourceDir}/core/ui.cpp"
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

set(dataCode
    "${sourceDir}/data/geometry.cpp"
)

set(configFiles
    "${config_dir_full}/config.yaml"
    "${config_dir_full}/yamltest.yaml"
)

set(dataMaps
    "${data_dir_full}/_maps/predef3d_namemap.cpp"
    "${data_dir_full}/_maps/texture_name-pathmap.cpp"
)

set(dataPaths
    "${data_dir_full}/_paths/model_paths.cpp"
    "${data_dir_full}/_paths/shader_paths.cpp"
)

set(dataPredefs
    "${data_dir_full}/_predefs/predef_materials.cpp"
    "${data_dir_full}/_predefs/predef_primitive_scene_nodes.cpp"
    "${data_dir_full}/_predefs/predef_scene_lights.cpp"
    "${data_dir_full}/_predefs/predef_vertex_data.cpp"
)

set(dataScenes
    "${data_dir_full}/_scenes/1.0_testscene.cpp"
    "${data_dir_full}/_scenes/2.0_multiplelights_testscene.cpp"
    "${data_dir_full}/_scenes/2.3_importmodel_testscene.cpp"
    "${data_dir_full}/_scenes/3.0_outliner_testscene.cpp"
    "${data_dir_full}/_scenes/3.10.instancing_testscene.cpp"
    "${data_dir_full}/_scenes/3.11.antialiasing_testscene.cpp"
    "${data_dir_full}/_scenes/3.2_blending_testscene.cpp"
    "${data_dir_full}/_scenes/3.3_faceculling_testscene.cpp"
    "${data_dir_full}/_scenes/3.4_framebuffers_testscene.cpp"
    "${data_dir_full}/_scenes/3.5_cubemap_testscene.cpp"
    "${data_dir_full}/_scenes/3.8_advglsl_testscene.cpp"
    "${data_dir_full}/_scenes/3.9_geoshader_testscene.cpp"
    "${data_dir_full}/_scenes/4.1.blinnphong_testscene.cpp"
    "${data_dir_full}/_scenes/4.2_gammacorrection_testscene.cpp"
    "${data_dir_full}/_scenes/4.3_shadows_testscene.cpp"
    "${data_dir_full}/_scenes/4.4_point-shadows_testscene.cpp"
    "${data_dir_full}/_scenes/4.5_normal-map_testscene.cpp"
    "${data_dir_full}/_scenes/4.6_parallax_testscene.cpp"
    "${data_dir_full}/_scenes/4.7_hdr_testscene.cpp"
    "${data_dir_full}/_scenes/4.8_bloom_testscene.cpp"
    "${data_dir_full}/_scenes/4.9_deferred-shading_testscene.cpp"
    "${data_dir_full}/_scenes/4.10_ssao_testscene.cpp"
)

set(shaderFiles
    "${shader_dir_full}/post_process/gaussian-blur_vrtx_shader.glsl"
    "${shader_dir_full}/post_process/gaussian-blur_frag_shader.glsl"
    "${shader_dir_full}/1.0.3d_frag_shader.glsl"
    "${shader_dir_full}/1.0.3d_vrtx_shader.glsl"
    "${shader_dir_full}/1.1.axis-x_frag_shader.glsl"
    "${shader_dir_full}/1.1.axis-x_vrtx_shader.glsl"
    "${shader_dir_full}/1.1.axis-z_frag_shader.glsl"
    "${shader_dir_full}/1.1.axis-z_vrtx_shader.glsl"
    "${shader_dir_full}/1.2.diffuse_frag_shader.glsl"
    "${shader_dir_full}/1.2.diffuse_vrtx_shader.glsl"
    "${shader_dir_full}/1.3.green_frag_shader.glsl"
    "${shader_dir_full}/1.3.green_vrtx_shader.glsl"
    "${shader_dir_full}/1.4.pink_frag_shader.glsl"
    "${shader_dir_full}/1.4.pink_vrtx_shader.glsl"
    "${shader_dir_full}/2.0.phong_lit_frag_shader.glsl"
    "${shader_dir_full}/2.0.phong_lit_vrtx_shader.glsl"
    "${shader_dir_full}/2.1.lightmap_lit_frag_shader.glsl"
    "${shader_dir_full}/2.1.lightmap_lit_vrtx_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-directional_lit_frag_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-directional_lit_vrtx_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-point_lit_frag_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-point_lit_vrtx_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-spot_lit_frag_shader.glsl"
    "${shader_dir_full}/2.2.lightcaster-spot_lit_vrtx_shader.glsl"
    "${shader_dir_full}/2.3.multiplelights_lit_frag_shader.glsl"
    "${shader_dir_full}/2.3.multiplelights_lit_vrtx_shader.glsl"
    "${shader_dir_full}/3.0.depthtesting_lit_frag_shader.glsl"
    "${shader_dir_full}/3.0.depthtesting_lit_vrtx_shader.glsl"
    "${shader_dir_full}/3.1.stenciltesting02_frag_shader.glsl"
    "${shader_dir_full}/3.1.stenciltesting02_vrtx_shader.glsl"
    "${shader_dir_full}/3.1.stenciltesting_frag_shader.glsl"
    "${shader_dir_full}/3.1.stenciltesting_vrtx_shader.glsl"
    "${shader_dir_full}/3.10.instance02_frag_shader.glsl"
    "${shader_dir_full}/3.10.instance02_vrtx_shader.glsl"
    "${shader_dir_full}/3.10.instance_frag_shader.glsl"
    "${shader_dir_full}/3.10.instance_vrtx_shader.glsl"
    "${shader_dir_full}/3.2.blending_frag_shader.glsl"
    "${shader_dir_full}/3.2.blending_vrtx_shader.glsl"
    "${shader_dir_full}/3.4.framebuffer_frag_shader.glsl"
    "${shader_dir_full}/3.4.framebuffer_vrtx_shader.glsl"
    "${shader_dir_full}/3.5.cubemap_frag_shader.glsl"
    "${shader_dir_full}/3.5.cubemap_vrtx_shader.glsl"
    "${shader_dir_full}/3.6.cubemaplit_frag_shader.glsl"
    "${shader_dir_full}/3.6.cubemaplit_vrtx_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-blue_frag_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-blue_vrtx_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-green_frag_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-green_vrtx_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-red_frag_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-red_vrtx_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-yellow_frag_shader.glsl"
    "${shader_dir_full}/3.8.advglsl-yellow_vrtx_shader.glsl"
    "${shader_dir_full}/3.9.axes_frag_shader.glsl"
    "${shader_dir_full}/3.9.axes_geo_shader.glsl"
    "${shader_dir_full}/3.9.axes_vrtx_shader.glsl"
    "${shader_dir_full}/3.9.explode_frag_shader.glsl"
    "${shader_dir_full}/3.9.explode_geo_shader.glsl"
    "${shader_dir_full}/3.9.explode_vrtx_shader.glsl"
    "${shader_dir_full}/3.9.geo_frag_shader.glsl"
    "${shader_dir_full}/3.9.geo_geo_shader.glsl"
    "${shader_dir_full}/3.9.geo_vrtx_shader.glsl"
    "${shader_dir_full}/3.9.normal_frag_shader.glsl"
    "${shader_dir_full}/3.9.normal_geo_shader.glsl"
    "${shader_dir_full}/3.9.normal_vrtx_shader.glsl"
    "${shader_dir_full}/4.1.blinnphong2_frag_shader.glsl"
    "${shader_dir_full}/4.1.blinnphong2_vrtx_shader.glsl"
    "${shader_dir_full}/4.1.blinnphong_frag_shader.glsl"
    "${shader_dir_full}/4.1.blinnphong_vrtx_shader.glsl"
    "${shader_dir_full}/4.2.gamma_frag_shader.glsl"
    "${shader_dir_full}/4.2.gamma_vrtx_shader.glsl"
    "${shader_dir_full}/4.3.light-shadow_frag_shader.glsl"
    "${shader_dir_full}/4.3.light-shadow_vrtx_shader.glsl"
    "${shader_dir_full}/4.3.shadowmap_frag_shader.glsl"
    "${shader_dir_full}/4.3.shadowmap_vrtx_shader.glsl"
    "${shader_dir_full}/4.4.plight-shadow_frag_shader.glsl"
    "${shader_dir_full}/4.4.plight-shadow_vrtx_shader.glsl"
    "${shader_dir_full}/4.4.shadowmap-pl_frag_shader.glsl"
    "${shader_dir_full}/4.4.shadowmap-pl_geo_shader.glsl"
    "${shader_dir_full}/4.4.shadowmap-pl_vrtx_shader.glsl"
    "${shader_dir_full}/4.5.normal01_frag_shader.glsl"
    "${shader_dir_full}/4.5.normal01_vrtx_shader.glsl"
    "${shader_dir_full}/4.6.normal02_frag_shader.glsl"
    "${shader_dir_full}/4.6.normal02_vrtx_shader.glsl"
    "${shader_dir_full}/4.7.parallax_frag_shader.glsl"
    "${shader_dir_full}/4.7.parallax_vrtx_shader.glsl"
    "${shader_dir_full}/4.8.hdr_frag_shader.glsl"
    "${shader_dir_full}/4.8.hdr_vrtx_shader.glsl"
    "${shader_dir_full}/4.9.bloom_frag_shader.glsl"
    "${shader_dir_full}/4.9.bloom_vrtx_shader.glsl"
    "${shader_dir_full}/4.10.1.deferred-geometry_frag_shader.glsl"
    "${shader_dir_full}/4.10.1.deferred-geometry_vrtx_shader.glsl"
    "${shader_dir_full}/4.10.2.deferred-lighting_frag_shader.glsl"
    "${shader_dir_full}/4.10.2.deferred-lighting_vrtx_shader.glsl"
    "${shader_dir_full}/4.11.1.ssao-geometry_frag_shader.glsl"
    "${shader_dir_full}/4.11.1.ssao-geometry_vrtx_shader.glsl"
    "${shader_dir_full}/4.11.2.ssao-draw_frag_shader.glsl"
    "${shader_dir_full}/4.11.2.ssao-draw_vrtx_shader.glsl"
    "${shader_dir_full}/4.11.3.ssao-blur_frag_shader.glsl"
    "${shader_dir_full}/4.11.4.ssao-lighting_frag_shader.glsl"
)


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
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/renderer.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/Camera.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/light.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/material.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/matrix4.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/mesh.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/model.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/queue.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/scene.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/scene_state.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/shader.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/transform.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/ui.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/uniforms.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/vector2.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/vector3.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/vector4.h"
    "${CMAKE_SOURCE_DIR}/source/headers/abstract/window_state.h"
)
    
set(coreHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/core/opengl.h"
    "${CMAKE_SOURCE_DIR}/source/headers/core/ui.h"
)
    
    set(dataHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/data/data.h"
    "${CMAKE_SOURCE_DIR}/source/headers/data/scenes.h"
    )
    # pattern wise adding all files
    file(GLOB dataHeaders "${CMAKE_SOURCE_DIR}/source/headers/data/*.h")


set(eventsHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/events/events.h"
    "${CMAKE_SOURCE_DIR}/source/headers/events/input_observer.h"
)

set(mapsHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/maps/shaders.h"
)

set(templatesHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/templates/header_template_1.0.h"
)

set(testHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/test/basic.h"
    "${CMAKE_SOURCE_DIR}/source/headers/test/integration_tests.h"
    "${CMAKE_SOURCE_DIR}/source/headers/test/unit_tests.h"
)

set(utilsHeaders
    "${CMAKE_SOURCE_DIR}/source/headers/utils/utilities.h"
    "${CMAKE_SOURCE_DIR}/source/headers/utils/light_yaml_parser.hpp"
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
#               Organize the source structure into filteres
# ----------------------------------------------------------------------------------------
source_group(TREE ${CMAKE_SOURCE_DIR}/source PREFIX "source" FILES ${sourceCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/blackboard PREFIX "source/blackboard" FILES ${blackboardCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/core PREFIX "source/core" FILES ${coreCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/event_handling PREFIX "source/event_handling" FILES ${eventHandlingCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/data PREFIX "source/data" FILES ${dataCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/libs PREFIX "source/libs" FILES ${libsCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/scene PREFIX "source/scene" FILES ${sceneCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/test PREFIX "source/tests" FILES ${testCode})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/utils PREFIX "source/utils" FILES ${utilsCode})
source_group(TREE ${config_dir_full} PREFIX "config" FILES ${configFiles})
source_group(TREE ${data_dir_full}/_maps PREFIX "data/_maps" FILES ${dataMaps})
source_group(TREE ${data_dir_full}/_paths PREFIX "data/_paths" FILES ${dataPaths})
source_group(TREE ${data_dir_full}/_predefs PREFIX "data/_predefs" FILES ${dataPredefs})
source_group(TREE ${data_dir_full}/_scenes PREFIX "data/_scenes" FILES ${dataScenes})
source_group(TREE ${shader_dir_full} PREFIX "shaders" FILES ${shaderFiles})


# ----------------------------------------------------------------------------------------
#               Organize Header Files into Folders
# ----------------------------------------------------------------------------------------
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/abstract PREFIX "source/headers/abstract" FILES ${abstractHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/core PREFIX "source/headers/core" FILES ${coreHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/data PREFIX "source/headers/data" FILES ${dataHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/events PREFIX "source/headers/events" FILES ${eventsHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/maps PREFIX "source/headers/maps" FILES ${mapsHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/templates PREFIX "source/headers/templates" FILES ${templatesHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/test PREFIX "source/headers/test" FILES ${testHeaders})
source_group(TREE ${CMAKE_SOURCE_DIR}/source/headers/utils PREFIX "source/headers/utils" FILES ${utilsHeaders})


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
    ${dataCode}
    ${testCode}
    ${utilsCode}
    ${configFiles}
    ${dataMaps}
    ${dataPaths}
    ${dataPredefs}
    ${dataScenes}
    # Adding headers here doesn't affect compilation, but makes them appear in the solution explorer
    ${shaderFiles}
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
    "${CMAKE_SOURCE_DIR}/source/headers/abstract"
    "${CMAKE_SOURCE_DIR}/source/headers/core"
    "${CMAKE_SOURCE_DIR}/source/headers/data"
    "${CMAKE_SOURCE_DIR}/source/headers/events"
    "${CMAKE_SOURCE_DIR}/source/headers/maps"
    "${CMAKE_SOURCE_DIR}/source/headers/templates"
    "${CMAKE_SOURCE_DIR}/source/headers/test"
    "${CMAKE_SOURCE_DIR}/source/headers/utils"
)

# ----------------------- glad
include_directories("${CMAKE_SOURCE_DIR}/libs/_glad-0.136/include")
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/libs/_glad-0.136/src/glad.c")
target_link_libraries(${PROJECT_NAME} PRIVATE glad)


# ----------------------- stb
include_directories("${CMAKE_SOURCE_DIR}/libs/_stb")



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
set(ASSIMP_BUILD_GLTF_IMPORTER ON)             # Enable only GLTF importer
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
add_compile_definitions(CONFIG_DIR_FULL="${config_dir_full}")
add_compile_definitions(DATA_DIR_FULL="${data_dir_full}")
add_compile_definitions(SHADER_DIR_FULL="${shader_dir_full}")

add_compile_definitions(CONFIG_DIR_RELATIVE="${config_dir_relative}")
add_compile_definitions(DATA_DIR_RELATIVE="${data_dir_relative}")
add_compile_definitions(SHADER_DIR_RELATIVE="${shader_dir_relative}")


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

