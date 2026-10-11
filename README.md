<h1 align="center">
    OpenGL Renderer
</h1>

<p align="center">
    A study project to learn computer graphics and software design principles/patterns through the OpenGL API.
</p>

<p align="center">
    <img alt="OpenGL" src="https://img.shields.io/badge/OpenGL-3.3-blue?logo=opengl&logoColor=white" />
    <img alt="Project Version" src="https://img.shields.io/badge/Project_Version-0.98.1-blue" />
    <img alt="Start Date" src="https://img.shields.io/badge/project_start-19_Aug_2022-blue" />
    <img alt="Last Update" src="https://img.shields.io/github/last-commit/kutaycoskuner/study-opengl" />
    <img alt="main" src="https://img.shields.io/github/actions/workflow/status/kutaycoskuner/study-opengl/cmake-platform-windows.yml?branch=main&label=main" />
    <img alt="dev" src="https://img.shields.io/github/actions/workflow/status/kutaycoskuner/study-opengl/cmake-platform-windows.yml?branch=dev&label=dev" />
</p>

<p align="center">
    <img src="_display/0.96.0-ssao-20250326.gif" />
    <br>
    <sub><i>0.96.0 Screen space ambient occlusion</i></sub>
</p>

------------------------------------------------------------------------------------------

## Folders

```bash
study-opengl/
├── _display/                   # Screenshots and GIFs of each rendering milestone
├── config/                     # config.yaml: window, camera and scene settings
├── data/                       # Models, textures, cubemaps and scene definitions
│   ├── _predefs/               # Predefined materials and objects
│   └── _scenes/                # One test scene per chapter (e.g. 4.3_shadows_testscene.cpp)
├── libs/                       # Third-party libraries (GLFW, GLAD, Assimp, ImGui, stb)
├── scripts/                    # Python helpers: naming convention checks, bulk renaming
├── shaders/                    # GLSL shaders, named <chapter>-<name>-<vrtx|frag|geom>.glsl
├── source/                     # Renderer source code (core, scene, events, utils, tests)
├── CMakeLists.txt
├── --GenerateBuildProject.bat  # Configures the solution and builds Debug + Release
├── --GenerateBinaries.bat      # Rebuilds Debug + Release from an existing build/
└── --PackProgram.bat           # Copies a standalone, runnable build into artifacts/
```

------------------------------------------------------------------------------------------

## Installation and Usage

### Prerequisites
- **Windows 10/11** with an OpenGL 3.3 capable graphics driver
- **Git**: [Install Git](https://git-scm.com/downloads)
- **CMake 3.24+**: [Install CMake](https://cmake.org/download/)
- **Visual Studio 2022** with the "Desktop development with C++" workload: [Install Visual Studio](https://visualstudio.microsoft.com/vs/)
- **Windows 10 SDK 10.0.19041.0+**: [Install Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/)

### Installation

```bash
# 1. Clone the repository with its submodules
git clone --recursive https://github.com/kutaycoskuner/study-opengl.git
cd study-opengl

# 2. Generate the Visual Studio solution and build Debug + Release
#   Automated (also initializes missing submodules):
./--GenerateBuildProject.bat
#   Manual:
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
cd ..

# 3. Run the program
./bin/Windows/x64/Release/opengl_renderer.exe

# Optional: open the solution in Visual Studio
./build/opengl_renderer.sln

# Optional: create a standalone copy in artifacts/ that can be moved anywhere
./--PackProgram.bat
```

> If CMake fails with `CMAKE_C_COMPILER not set`, another CMake/MinGW installation (e.g. Strawberry Perl) is
> first in your `PATH`. Keep the `-G "Visual Studio 17 2022"` generator so CMake uses MSVC.

------------------------------------------------------------------------------------------

## Controls

| Key            | Function                                              |
| :------------: | :---------------------------------------------------- |
| `w` `a` `s` `d`| Move camera forward / left / backward / right         |
| `space` / `x`  | Move camera up / down                                 |
| `q` / `e`      | Rotate camera left / right                            |
| `r` / `f`      | Tilt camera up / down                                 |
| `shift`        | Increase movement speed while pressed                 |
| `z`            | Toggle mouse control for rotation (default: disabled) |
| `c`            | Reset camera position                                 |
| `g`            | Toggle user interface                                 |
| `o`            | Toggle ambient occlusion (SSAO)                       |
| `t`            | Toggle screenshot mode                                |
| `↑` / `↓`      | Change texture blend factor                           |
| `esc`          | Quit                                                  |

------------------------------------------------------------------------------------------

## Feature List

- [x] Vertex-defined shape drawing
- [x] Texture importing
- [x] 3D perspective projection (custom 4x4 matrix and 2D/3D vector library)
- [x] Moveable camera and UI movement controls
- [x] Phong and Blinn-Phong illumination
- [x] Directional, point and spot lighting
- [x] Light maps and emission maps
- [x] Model importing (.obj)
- [x] Outline shader (depth and stencil test method)
- [x] Transparency through blending
- [x] Face culling
- [x] Frame buffers
- [x] Uniform buffer objects (UBO)
- [x] Cubemapped skybox
- [x] GPU instancing
- [x] Anti-aliasing (MSAA)
- [x] UI scene changer
- [x] Automated frame-based scene testing
- [x] Shadow mapping (point light / directional light)
- [x] Normal mapping
- [x] Parallax mapping
- [x] High dynamic range lighting (HDR)
- [x] Post process effect: bloom
- [x] Deferred shading
- [x] Screen space ambient occlusion (SSAO)
- [ ] Physically based rendering (PBR)

------------------------------------------------------------------------------------------

## Display

A selection of milestones. More are in the [`_display`](_display/) folder.

<p align="center">
    <img src="_display/0.95.0_deferred-shading_20250305.png" />
    <br>
    <sub><i>0.95.0 Deferred shading</i></sub>
</p>

<p align="center">
    <img src="_display/0.94.6_pshadows-gloom_20250120.gif" />
    <br>
    <sub><i>0.94.6 Dynamic point light shadows with bloom post processing</i></sub>
</p>

<p align="center">
    <img src="_display/0.92_parallax-mapping_20241217.gif" />
    <br>
    <sub><i>0.92 Parallax occlusion mapping</i></sub>
</p>

<p align="center">
    <img src="_display/0.90.3_dynamic-directional-light_20241107.gif" />
    <br>
    <sub><i>0.90.3 Dynamic directional light shadows (shadow mapping)</i></sub>
</p>

<p align="center">
    <img src="_display/0.66_instancing_2024-04-01.gif" />
    <br>
    <sub><i>0.66 GPU instancing</i></sub>
</p>

<p align="center">
    <img src="_display/0.48_stencil-test-outline-per-item_2023-08-03.gif" />
    <br>
    <sub><i>0.48 Stencil testing and outlining per item</i></sub>
</p>

------------------------------------------------------------------------------------------

## References

- **Learning**
    - [Sanderson, Grant. "Essence of Linear Algebra". _3Blue1Brown, YouTube_. 2016.](https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab)
    - [Gordan, Victor. "Stencil Buffer & Outlining". _YouTube_. 2021.](https://www.youtube.com/watch?v=ngF9LWWxhd0)
    - [Will, Brian. "OpenGL - Depth and Stencil Buffers". _YouTube_. 2019.](https://youtu.be/wVcWOghETFw)
    - Joey de Vries, [learnopengl.com](https://learnopengl.com)
    - Jordan Santell, [jsantell.com/3d-projection](https://jsantell.com/3d-projection/)
    - Supervision / support: Volkan Ilbeyli, [github.com/vilbeyli](https://github.com/vilbeyli)
- **Dependencies**
    - Libraries: GLFW, GLAD, Assimp (Open Asset Import Library), Dear ImGui, stb_image, stb_image_write
    - Tools: Visual Studio, Visual Studio Code, RenderDoc (frame debugging), CMake
- **Data**
    - Phong predefined materials: [OpenGL/VRML Materials](http://devernay.free.fr/cours/opengl/materials.html)
    - Backpack by Berk Gedik, [Sketchfab](https://sketchfab.com/3d-models/survival-guitar-backpack-799f8c4511f84fab8c3f12887f7e6b36)
    - Kokorec by Berk Gedik, [Sketchfab](https://sketchfab.com/models/141db37d07fc4ccba84ab5f38a8181b5/embed?autostart=1&internal=1&tracking=0&ui_ar=0&ui_infos=0&ui_snapshots=1&ui_stop=0&ui_theatre=1&ui_watermark=0)
    - Lantern by Rajil Jose Macatangay, [Poly Haven](https://polyhaven.com/a/Lantern_01)
    - Suzanne by Blender, [Documentation](https://docs.blender.org/manual/en/latest/modeling/meshes/primitives.html)
    - Jupiter by murilo.kleine, [Sketchfab](https://sketchfab.com/3d-models/jupiter-free-downloadable-model-61671f29ca0a4fa39dc9653290282418)
