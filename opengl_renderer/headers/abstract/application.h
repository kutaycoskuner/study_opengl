#pragma once
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector4.h"
#include "../abstract/ui.h"
#include "../abstract/scene_state.h"
#include "../abstract/camera.h"
#include "../abstract/window_state.h"
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

    static void resetCamera(Camera& camera);

    Application() : window(nullptr), active_shader(nullptr) {}
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
    std::vector<const char*> loadModels();
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

    // draw objects
    void drawAxis(int vao, const char* shader_name, Uniforms& uni);
    void drawLightPlaceholder(int vao, const char* shader_name, Uniforms& uni);
    //void drawGroundPlane(int vao, const char* shader_name, Uniforms& uni);
    void drawPredefElementsCube(int vao, const char* shader_name, Uniforms& uni);
    void drawGroundPlane(int vao, const char* shader_name, Uniforms& uni);
    void drawSingleCube(int vao, const char* shader_name, Uniforms& uni);
    void drawTwoCubes(int vao, const char* shader_name, Uniforms& uni);
    void drawModel(Model model, int vao, const char* shader_name, Uniforms& uni);
    void drawOverlappingCubes(int vao, const char* shader_name, Uniforms& uni);

    // specific scenes
    void phongScene(Uniforms& uni);
    void lightMapScene(Uniforms& uni);
    void lightCasterScene(Uniforms& uni);
    void multipleLightsScene(Uniforms& uni);
    void importModelScene(Uniforms& uni);
    void testObjectsScene(Uniforms& uni);
    void blendingTestScene(Uniforms& uni);
    void faceCullingTestScene(Uniforms& uni);
    void frameBuffersTestScene(Uniforms& uni);

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
    
    unsigned int texture1;
    unsigned int texture2;

    unsigned int texture_diffuse;
    unsigned int texture_specular;
    unsigned int texture_emission;
    
    unsigned int texture_ground_diffuse;
    unsigned int texture_ground_specular;
    unsigned int texture_ground_emission;
    
    unsigned int lit_vao;
    unsigned int lit_vbo;
    unsigned int lit_ebo;
    
    unsigned int textures_diffuse[buffer_count];
    unsigned int textures_specular[buffer_count];
    unsigned int textures_emission[buffer_count];
    
    std::vector<unsigned int> vec_texture_diffuse;
    std::vector<unsigned int> vec_texture_specular;
    std::vector<unsigned int> vec_texture_emission;
    
    unsigned int vaos[buffer_count];
    unsigned int vbos[buffer_count];
    unsigned int ebos[buffer_count];

    SceneState  scene_state;
    WindowState window_state;
    UIState     ui_state;

    // config
    bool        b_wireframe_mode = false;
    Vec4        clear_color;
};
