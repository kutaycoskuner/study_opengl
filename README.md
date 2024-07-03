# Study-LearnOpenGL-cpp
Study project for learning OpenGL

| Project Started | Last Update     | 
| :-------------- | :-------------- | 
| 19-Aug-2022     | 03-Jul-2024     |

# Table of Contents
1. [Description](#description)
2. [Installation and Usage](#installation-and-usage)
3. [Controls](#controls)
4. [Feature List](#feature-list)
5. [Display](#display)
6. [References](#references)

# Description
- Last built on `Visual Studio Community 2022 v17.9.2 Debug Mode`

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
- [x] Vertex defined shape drawing
- [x] Texture importing
- [x] 3D Perspective projection (own 4x4 Matrix and 2D/3D Vector Library)
- [x] Moveable camera
- [x] UI Movement controls 
- [x] Phong illumination
- [x] Directional, Point, Spot lighting
- [x] Light maps, emission
- [x] Model importing (.obj)
- [x] Outline Shader (Depth-, Stencil test method)
- [x] Transparency through blending
- [x] Face culling
- [x] Frame buffers
- [x] Uniform buffer object implementation
- [x] Cubemapped Skybox 
- [x] GPU instancing
- [x] Anti Aliasing (MSAA)
- [x] UI Scene changer
- [x] Automated frame based scene testing

# Display
```cpp
0.66 Instancing, optimization
- method 1: No instance
    - 5000 draw | 27 ms | 35 fps
- method 2: multiple draw call (amount/predetermined cache) + loop transform assignment
    - 5000 draw | 12 ms | 80 fps
- method 3: multiple draw call (amount/predetermined cache) + uniform buffer memory link
    - 5000 draw | 7.5ms | 134 fps
- method 4: single draw call + uniform buffer memory link
    - 5000 draw | 7.5ms | 134 fps
- method 5: mesh count * draw call + data as vbo
    - 5000 draw | 7.0ms | 140 fps
(gif is optimized for web preview)
```  
![0.66 instancing](_display/0.66_instancing_2024-04-01.gif)

```cpp
0.64 Geometry shaders - Normal display, Explode model
```  
![0.64 geometry shaders](_display/0.64_geometry-shaders_2024-03-18.gif)

```cpp
0.62 Cubemap: Skybox implementation
```  
![0.62 cubemaps](_display/0.62_skybox_2024-02-18.gif)

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
        - stb_image_write.h | Image file write library. | [download](https://github.com/nothings/stb/blob/master/stb_image_write.h)
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
        - Kokorec by Berk Gedik [https://sketchfab.com/3d-models/street-food-vendor-challenge-kokorec-141db37d07fc4ccba84ab5f38a8181b5](https://sketchfab.com/3d-models/street-food-vendor-challenge-kokorec-141db37d07fc4ccba84ab5f38a8181b5)
        - Lantern by Rajil Jose Macatangay (polyhaven) [https://polyhaven.com/a/Lantern_01](https://polyhaven.com/a/Lantern_01)
        - Suzanne by Blender [https://docs.blender.org/manual/en/latest/modeling/meshes/primitives.html](https://docs.blender.org/manual/en/latest/modeling/meshes/primitives.html)
        - Test Objects by Kutay Coskuner (inspired by Robin Seibold) 
        - Jupiter by murilo.kleine in Sketchfab [https://sketchfab.com/3d-models/jupiter-free-downloadable-model-61671f29ca0a4fa39dc9653290282418](https://sketchfab.com/3d-models/jupiter-free-downloadable-model-61671f29ca0a4fa39dc9653290282418)