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

    -- xmake install -o <dir>: a flat, standalone copy (replaces the copy part of --PackProgram.bat)
    -- the exe sits next to config/, data/, shaders/, so main.cpp switches to its relative path mode
    on_install(function (target)
        import("lib.detect.find_file")
        local outdir = target:installdir()
        os.mkdir(outdir)
        os.cp(target:targetfile(), outdir)
        for _, dir in ipairs({"config", "data", "shaders"}) do
            os.cp(path.join(os.projectdir(), dir), outdir)
        end

        -- msys2 clang64 runtime dlls the exe imports; without them it only starts from a clang64 shell
        for _, dll in ipairs({"libc++.dll", "zlib1.dll"}) do
            local src = find_file(dll, {"$(env PATH)"})
            if src then
                os.cp(src, outdir)
            else
                cprint("${yellow}warning: %s not found on PATH, the packed exe will not start outside a clang64 shell", dll)
            end
        end
        cprint("${green}installed into %s", outdir)
    end)
target_end()


-- ----------------------------------------------------------------------------------------
--               Tasks (replace the old --*.bat scripts, now in scripts/legacy/)
-- ----------------------------------------------------------------------------------------
-- each step runs as its own xmake process (like typing the command): a build started inside
-- this process would still use the mode loaded at startup, not the one just configured
-- xmake binaries: build debug and release (replaces --GenerateBinaries.bat)
task("binaries")
    set_menu({usage = "xmake binaries", description = "Build debug and release, then return to the current mode.", options = {}})
    on_run(function ()
        import("core.project.config")
        config.load()
        local current = {plat = config.get("plat"), arch = config.get("arch"),
                         toolchain = config.get("toolchain"), mode = config.get("mode")}
        local xmake = os.programfile()
        local function configure(mode)
            local args = {"f", "-p", current.plat, "-a", current.arch, "-m", mode}
            if current.toolchain then table.insert(args, "--toolchain=" .. current.toolchain) end
            os.execv(xmake, args)
        end

        for _, mode in ipairs({"debug", "release"}) do
            cprint("${bright}building %s ...", mode)
            configure(mode)
            os.execv(xmake, {"-y"})
        end
        configure(current.mode)
        cprint("${green}binaries ready in build/%s/%s/{debug,release}, back in %s mode", current.plat, current.arch, current.mode)
    end)
task_end()

-- xmake pack: release build copied into a clean artifacts/ (replaces --PackProgram.bat)
task("pack")
    set_menu({usage = "xmake pack", description = "Build release and copy a standalone, runnable program into artifacts/.", options = {}})
    on_run(function ()
        import("core.project.config")
        config.load()
        local current = {plat = config.get("plat"), arch = config.get("arch"),
                         toolchain = config.get("toolchain"), mode = config.get("mode")}
        local xmake = os.programfile()
        local function configure(mode)
            local args = {"f", "-p", current.plat, "-a", current.arch, "-m", mode}
            if current.toolchain then table.insert(args, "--toolchain=" .. current.toolchain) end
            os.execv(xmake, args)
        end
        local outdir = path.join(os.projectdir(), "artifacts")

        configure("release")
        os.execv(xmake, {"-y"})
        os.tryrm(outdir)    -- clean pack, like the old script
        os.execv(xmake, {"install", "-o", outdir})
        configure(current.mode)
        cprint("${green}packed into %s, back in %s mode", outdir, current.mode)
    end)
task_end()
