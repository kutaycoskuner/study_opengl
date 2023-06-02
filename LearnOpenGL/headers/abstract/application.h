#pragma once
// ------------------------------------------------------------------------------------------------
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector4.h"
#include "../abstract/ui.h"
#include "../abstract/scene_state.h"
#include <unordered_map>
#include <string>


// ------------------------------------------------------------------------------------------------
// ----- abstract declarations
// ------------------------------------------------------------------------------------------------
struct GLFWwindow;
class Shader;
struct Uniforms;

// ------------------------------------------------------------------------------------------------
// ----- function declerations
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
class Application
{
public:
    using k_configType = const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

    Application() : window(nullptr), active_shader(nullptr) {}
    // Program ilk basladiginda izlenen prosedurleri icerir.
    // 
    // - isletim sisteminden bellek isteme
    // - cesitli sistemleri hazirlama
    bool initialize(k_configType& config);

    // Program bellegi hazirlandiktan sonra motorun kullanacagi built-in
    // kaynaklari yuklemek icin izlenen prosedurleri icerir.
    // 
    // - built-in shader compilation
    // - built-in texture loading
    // - built-in asset loading
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

private:
    // initialize
    int initWindowSystem(const unsigned int& width, const unsigned int& height, const char*& window_name);
    void initUISystem(const char*& glsl_version);
    // load
    void loadConfig(const k_configType& config);
    void loadSceneData(const k_configType& config);
    void loadTextures();
    void loadShaders();
    void loadMeshData();
    // ui
    void drawUI();
    void updateUI();
    // scene
    void drawScene(Uniforms& uni);
    void updateScene();

private:
    const static unsigned int buffer_count = 1;
    // Uygulama veri ve state tanimlari
    GLFWwindow* window;
    Shader*      active_shader;
    unsigned int texture1;
    unsigned int texture2;
    unsigned int VAOs[buffer_count];
    unsigned int VBOs[buffer_count];
    unsigned int EBOs[buffer_count];

    SceneState scene_state;

    // config
    bool        b_wireframe_mode;
    Vec4        clear_color;
    UIState     ui_state;
};
