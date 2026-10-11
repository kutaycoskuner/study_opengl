# Legacy scripts

Superseded build scripts, kept for reference only. They are not run, maintained or referenced by the build; they need CMake and Visual Studio and may no longer work.

| File | What it was | Superseded | Replaced by | Not carried over |
| :--- | :--- | :--- | :--- | :--- |
| `--GenerateBuildProject.bat` | Checked CMake, initialized missing submodules, deleted `build/`, generated the Visual Studio 2022 solution, then called `--GenerateBinaries.bat` | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake f -p mingw --toolchain=clang` once, then `xmake binaries` | Visual Studio solution generation; CMake presence check; automatic submodule init (now `git submodule update --init --recursive` by hand); wiping `build/` first (now `xmake c`) |
| `--GenerateBinaries.bat` | Ran `cmake --build` for Debug and Release in `build/` | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake binaries` task in `xmake.lua` | Output in `bin/Windows/x64/<Config>/` (xmake builds into `build/mingw/x86_64/<mode>/`) |
| `--PackProgram.bat` | Built Release if missing, wiped `artifacts/`, copied the exe plus `config/`, `data/`, `shaders/` into it | 11-Oct-2026, xmake migration (after `aa58f69`) | `xmake pack` task + `on_install` of `opengl_renderer` in `xmake.lua` | Nothing; the new pack also copies the MSYS2 runtime DLLs (`libc++.dll`, `zlib1.dll`) |

## Changes
- 20261011 — added `--GenerateBuildProject.bat`, `--GenerateBinaries.bat`, `--PackProgram.bat` (moved from the repository root)
