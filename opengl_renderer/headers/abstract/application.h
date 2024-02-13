#pragma once
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector4.h"
#include "../abstract/ui.h"
#include "../abstract/scene.h"
#include "../abstract/scene_state.h"
#include "../abstract/window_state.h"
#include "../abstract/camera.h"
#include "../events/input_observer.h"
#include "../data/data.h"
#include <unordered_map>
#include <string>
#include <memory>


// ----- forward declarations
// ------------------------------------------------------------------------------------------------
struct GLFWwindow;
struct Uniforms;
struct Material;
class Shader;
using uint = unsigned int;


// ----- function declerations
// ------------------------------------------------------------------------------------------------

// ----- abstract
// ------------------------------------------------------------------------------------------------
class Application
{
public:
    using k_configType = const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

    // standards
    static const Vec3 world_up;
    static const Vec3 world_origin;

    static bool toggle_mouselock;

    void resetCamera();

    // handlers
    InputSpeaker input_speaker;

    Application() : window(nullptr), active_shader(nullptr), active_scene(nullptr) {}
    // - ask memory from operating system
    // - preapre libraries
    bool initialize(k_configType& config);

    // Program bellegi hazirlandiktan sonra motorun kullanacagi built-in
    // kaynaklari yuklemek icin izlenen prosedurleri icerir.
    // 
    // - built-in shader compilation
    // - built-in texture loading
    // - built-in asset lfoading
    bool load(k_configType& config);
 
    // Program kapanirken izlenen prosedurleri icerir.
    //
    // - isletim sistemine kullanilan bellegi iade etme
    // - cesitli sistemleri kapatma
    int exit();


    // Motorun kullandigi built-in ve diger kaynaklari isletim sistemine
    // iade etmek icin izlenen prosedurleri icerir.
    // 
    // - texture, shader, asset belleklerini isletim sistemine iade etme
    void unload();


    // Bir frame'i cizmek icin gereken tum mantik ve aritmetik islemlerini icerir.
    // 
    // - kullanicidan gelen input'u isleme
    // - simulasyon dunyasini guncelleme (update/tick)
    // - cizim icin gerekli datayi toplama
    // - cizim icin komutlari grafik islemcisine gonderme
    // - uygulama penceresine son resmi aktarma
    void mainLoop();

    // handle
    void handleMouseEvent(GLFWwindow* window, double xpos, double ypos);
    void handleScrollEvent(GLFWwindow* window, double xoffset, double yoffset);

private:
    // initialize
    int initWindowSystem(const unsigned int& width, const unsigned int& height, const char*& window_name);
    void initUISystem(const char*& glsl_version);
    
    // load
    void loadConfig(const k_configType& config);
    void loadSceneData(const k_configType& config);
    void loadTextures();
    void loadShaders();
    std::vector<const char*> loadModelPaths();
    void loadMeshData();
    void generateBuffer(uint vrtx_arr, uint vrtx_buffer, const float obj_vrts[], const uint& stride, bool vrtx, bool tex);
    
    // ui
    void drawUI();
    void updateUI();

    // draw scene
    void drawScene(Uniforms& uni);
    void updateScene();
    void setMaterial(const Material& material);
    void setPresetMaterial(const Material& material);

    // stencil
    void disableStencil();
    void enableStencil();
    void clearStencil();

    // custom functions
    void setPointLightParameters(Uniforms& uni);
    void setSpotLightParameters(Uniforms& uni);
    void setDirectionalLightParameters(Uniforms& uni);

    // reset


private:
    const static unsigned int buffer_count = 2;
    const float reduction_128f = 0.0078125f;

    // Uygulama veri ve state tanimlari
    GLFWwindow* window;
    std::shared_ptr<Shader> active_shader;
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    
    unsigned int lit_vao; // vertex array object    || input layout
    unsigned int lit_vbo; // vertex buffer object   || vertex buffer
    unsigned int lit_ebo; // element buffer object  || index buffer

    unsigned int lit_fbo; // frame buffer object    || frame buffer
    unsigned int lit_rbo; // render buffer object   || render buffer
    
    unsigned int vertex_arrays[buffer_count];
    unsigned int vertex_buffers[buffer_count];
    unsigned int element_buffers[buffer_count];
    unsigned int frame_buffers[buffer_count];
    unsigned int render_buffers[buffer_count];

    // 
    unsigned int framebuffer_color_texture;
    
    std::unordered_map<std::string, TextureSet> textures;
    
    // Scene scene;
    Scene*      active_scene;
    WindowState window_state;
    UIState     ui_state;

    // config
    bool        b_wireframe_mode = false;
    Vec4        clear_color;

};
