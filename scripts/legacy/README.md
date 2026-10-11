# Legacy build

The old CMake / Visual Studio build (`CMakeLists.txt` and the `.bat` scripts that drove it), superseded by `xmake.lua` and kept for reference only. Nothing here is run, maintained or referenced by the build; it needs CMake and Visual Studio, and `CMakeLists.txt` expects to sit in the repository root, so it no longer works from this folder.

| File | What it was | Superseded | Replaced by | Not carried over |
| :--- | :--- | :--- | :--- | :--- |
| `CMakeLists.txt` | The CMake build: C++20, all sources and headers listed by hand, glad/imgui static libraries, glfw and assimp from submodules (`add_subdirectory`), `*_DIR_FULL` / `*_DIR_RELATIVE` defines, Visual Studio folder filters | 11-Oct-2026, xmake migration (after `191257e`) | `xmake.lua` (its `CMake:` comments point back to the matching lines here) | Visual Studio solution with folder filters (`source_group`, `FOLDER` properties, startup project); assimp limited to the OBJ, FBX and GLTF importers (the xmake package builds all importers); output in `bin/<system>/x64/<config>/` (now `build/mingw/x86_64/<mode>/`); the unused `*_DIR_RELATIVE` defines. The glfw and assimp submodules it builds from were removed; to use it again, restore them from git history |
| `--GenerateBuildProject.bat` | Checked CMake, initialized missing submodules, deleted `build/`, generated the Visual Studio 2022 solution, then called `--GenerateBinaries.bat` | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake f -p mingw --toolchain=clang` once, then `xmake binaries` | Visual Studio solution generation; CMake presence check; automatic submodule init (now `git submodule update --init --recursive` by hand); wiping `build/` first (now `xmake c`) |
| `--GenerateBinaries.bat` | Ran `cmake --build` for Debug and Release in `build/` | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake binaries` task in `xmake.lua` | Output in `bin/Windows/x64/<Config>/` (xmake builds into `build/mingw/x86_64/<mode>/`) |
| `--PackProgram.bat` | Built Release if missing, wiped `artifacts/`, copied the exe plus `config/`, `data/`, `shaders/` into it | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake pack` task + `on_install` of `opengl_renderer` in `xmake.lua` | Nothing; the new pack also copies the MSYS2 runtime DLLs (`libc++.dll`, `zlib1.dll`) |

## Changes
- 20261011 — added `--GenerateBuildProject.bat`, `--GenerateBinaries.bat`, `--PackProgram.bat` (moved from the repository root)
- 20261011 — added `CMakeLists.txt` (moved from the repository root)
- 20261011 — glfw and assimp submodules removed from `libs/`; `CMakeLists.txt` needs them restored from git history to build again
