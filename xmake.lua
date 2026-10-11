-- ----------------------------------------------------------------------------------------
--               Project (root scope: applies to every target)
-- ----------------------------------------------------------------------------------------
-- CMake: project(opengl_renderer)
set_project("opengl_renderer")

-- CMake: set(CMAKE_CXX_STANDARD 20) + CMAKE_CXX_STANDARD_REQUIRED ON
set_languages("c++20")

-- CMake: CMAKE_BUILD_TYPE Debug/Release; pick one with: xmake f -m debug|release
add_rules("mode.debug", "mode.release")
-- writes compile_commands.json for qt creator / clangd on every build
add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})


-- CMake: add_subdirectory(libs/glfw) -- now an xmake package, downloaded and cached
add_requires("glfw", "assimp")


-- ----------------------------------------------------------------------------------------
--               Main program
-- ----------------------------------------------------------------------------------------
-- CMake: add_library(glad STATIC ...) + include_directories(libs/_glad-0.136/include)
target("glad")
    set_kind("static")
    add_files("libs/_glad-0.136/src/glad.c")
    add_includedirs("libs/_glad-0.136/include", {public = true})


-- CMake: add_library(imgui STATIC ...) + include_directories(libs/imgui)
target("imgui")
    set_kind("static")
    add_files("libs/imgui/*.cpp")
    add_files("libs/imgui/backends/imgui_impl_glfw.cpp",
              "libs/imgui/backends/imgui_impl_opengl3.cpp")
    add_includedirs("libs/imgui", {public = true})
    add_packages("glfw")    -- imgui_impl_glfw.cpp includes GLFW/glfw3.h


-- CMake: add_executable(${PROJECT_NAME} ...)
target("opengl_renderer")
    set_kind("binary")

    -- CMake: sourceCode, blackboardCode, coreCode, eventHandlingCode, libsCode,
    -- sceneCode, dataCode, testCode, utilsCode (every .cpp under source/)
    add_files("source/**.cpp")

    -- CMake: dataMaps, dataPaths, dataPredefs, dataScenes
    add_files("data/_maps/*.cpp", "data/_paths/*.cpp",
              "data/_predefs/*.cpp", "data/_scenes/*.cpp")

    -- CMake: include_directories(source/headers/...)
    add_includedirs("source/headers/abstract", "source/headers/core",
                    "source/headers/data", "source/headers/events",
                    "source/headers/maps", "source/headers/templates",
                    "source/headers/test", "source/headers/utils")


    -- CMake: target_link_libraries(... glad)
    add_deps("glad", 'imgui')
    add_packages('glfw', "assimp")

    -- CMake: include_directories(libs/_stb) -- header-only, nothing to compile
    add_includedirs("libs/_stb")

    
    -- CMake: add_compile_definitions(CONFIG_DIR_FULL=...) etc.
    -- forward slashes: a backslash path inside a C++ string would be read as escapes
    local root = os.projectdir():gsub("\\", "/")
    add_defines('CONFIG_DIR_FULL="' .. root .. '/config/"',
                'DATA_DIR_FULL="'   .. root .. '/data/"',
                'SHADER_DIR_FULL="' .. root .. '/shaders/"')

