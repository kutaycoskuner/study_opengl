# Study-LearnOpenGL-cpp
Study project for learning OpenGL

| Project Started | Last Update     | 
| :-------------- | :-------------- | 
| 19-Aug-2022     | 13-Feb-2024     |

# Table of Contents
1. [Description](#description)
2. [Installation and Usage](#installation-and-usage)
3. [Controls](#controls)
4. [Feature List](#feature-list)
5. [Display](#display)
6. [References](#references)

# Description
This is a study repository for learning graphics programming through OpenGL.

# Installation and Usage
- This section is not yet written.

# Controls
| Key          | Function |
| :------:     | :---------- | 
| `w`          | Move camera forward
| `a`          | Move camera to left
| `s`          | Move camera backwards
| `d`          | Move camera to right
| `x`          | Move camera down
| `space bar`  | Move camera up
| `q`          | Pitch towards left
| `e`          | Pitch towards right
| `r`          | Yaw towards up
| `f`          | Yaw towards down
| `z`          | Toggle mouse control on pitch and yaw (default: disabled) 
| `c`          | Reset camera position 
| `g`          | Toggle user interface 
| `shift`      | If pressed when moving speeds up the camera movement

# Feature List
- This section is not yet written.

# Display
```cpp
0.61 Framebuffers Implementation: Convolution matrix post processing edge detection
```  
![0.61 framebuffers](_display/0.61_framebuffer_2024-02-13.gif)

```cpp
0.49 Face culling
```  
![0.48 culling](_display/0.49_face-culling_2023-09-14.gif)

```cpp
0.48 Transparency through blending
```  
![0.48 blending](_display/0.48_blending_2023-08-09.gif)

```cpp
0.48 Outline per item
// Method 2.1 + Cleansing stencil buffer after each object draw
```  
![0.48 Stencil Testing 2](_display/0.48_stencil-test-outline-per-item_2023-08-03.gif)

```
0.46 Model import illuminated (diffuse, specular, emission)
```  
![0.46 model import illuminated](_display/0.46_shader-specular-fix_2023-07-21.gif)

```
0.44 Multiple lights: 1 directional- 3 point- (rgb), 1 spot light
```  
![0.44 multiple lights](_display/0.44_multiple-lights_fixed_2023-07-11.gif)

```
0.42 Light casters respectively: directional-, point-, spot light
```  
![0.42 Light casteres](_display/0.42_light-casters_2023-06-25.gif)

```
0.41 Light map and emission
```  
![0.41 Light Maps Emission](_display/0.41_lightmaps-emission_2023-06-20.gif)

```
0.39 Phong shading
```  
![0.39 Phong shading](_display/0.39_phong_shading_2023-06-12.gif)

```
0.35 Static camera rotation with changing focus by time
```  
![0.35 Static camera rotation with changing focus by time](_display/0.35_camera-rotation-focus-time_2023-06-04.gif)

```
0.31 Perspective projection
```  
![0.31 3D Perspective projection / transformation](_display/0.31_perspective-rotation_2023-05-18.gif)

```
0.21 Pixel color interpolation
```  
![0.21 Pixel color interpolation](_display/0.21_pixel-color-calculation-2_2023-04-14.png)


# References
- Learning
    - Videos
        - [Sanderson, Grant. "Essense of Linear Algebra". _Uploaded by 3Blue1Brown, Youtube_. 2016.](https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab)
        - [Gordan, Victor."Stencil Buffer & Outlining". _Uploaded by Victor Gordan, Youtube_. 2021.](https://www.youtube.com/watch?v=ngF9LWWxhd0)
        - [Will, Brian. "OpenGL - depth and stencil buffers". _Uploaded by Brian Will, Youtube_. 2019.](https://youtu.be/wVcWOghETFw)
    - Websites
        - Joey de Vries [learnopengl.com](https://learnopengl.com)
        - Jordan Santell [jsantell.com/3d-projection](https://jsantell.com/3d-projection/)
    - Supervision / Support
        - Volkan Ilbeyli [github.com/vilbeyli](https://github.com/vilbeyli)
- Dependencies
    - Libraries
        - GLFW | GLFW is a lightweight utility library for use with OpenGL. [Download](https://www.glfw.org/download.html)
        - GLAD | OpenGL hardware adjustment library. [Download](https://glad.dav1d.de/)
        - Asset-Importer-Lib | Importing 3d file formats into a shader, in-memory imediate format [Download](http://assimp.org/)
        - Dear ImGui | C++ gui library [Download](https://github.com/ocornut/imgui/releases/tag/v1.89.5)
        - stb_image.h | Image file load library. [Downlaod](https://github.com/nothings/stb/blob/master/stb_image.h)
    - Environment Setup 
        - Visual Studio (Main IDE)
        - Visual Studio Code
        - RenderDoc (Frame Debugging)
        - CMake
- Data
    - Phong shading predefined materials
        - OpenGL/VRML Materials. [http://devernay.free.fr/cours/opengl/materials.html](http://devernay.free.fr/cours/opengl/materials.html)
    - Models
        - Backpack by Berk Gedik [https://sketchfab.com/3d-models/survival-guitar-backpack-799f8c4511f84fab8c3f12887f7e6b36](https://sketchfab.com/3d-models/survival-guitar-backpack-799f8c4511f84fab8c3f12887f7e6b36)
        - Lantern by Rajil Jose Macatangay (polyhaven) [https://polyhaven.com/a/Lantern_01](https://polyhaven.com/a/Lantern_01)
        - Suzanne by Blender [https://docs.blender.org/manual/en/latest/modeling/meshes/primitives.html](https://docs.blender.org/manual/en/latest/modeling/meshes/primitives.html)
        - Test Objects by Kutay Coskuner (inspired by Robin Seibold) 