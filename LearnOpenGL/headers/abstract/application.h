#pragma once
// ------------------------------------------------------------------------------------------------
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector4.h"
#include "../abstract/ui.h"
#include <unordered_map>
#include <string>


// ------------------------------------------------------------------------------------------------
// ----- abstract declarations
// ------------------------------------------------------------------------------------------------
struct GLFWwindow;
class Shader;
// ------------------------------------------------------------------------------------------------
// ----- function declerations
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
class Application
{
public:
    using c_configType = const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

    Application() : window(nullptr), ourShader(nullptr) {}
    // Program ilk basladiginda izlenen prosedurleri icerir.
    // 
    // - isletim sisteminden bellek isteme
    // - cesitli sistemleri hazirlama
    bool Initialize(c_configType& config);

    // Program bellegi hazirlandiktan sonra motorun kullanacagi built-in
    // kaynaklari yuklemek icin izlenen prosedurleri icerir.
    // 
    // - built-in shader compilation
    // - built-in texture loading
    // - built-in asset loading
    bool Load(c_configType& config);
 
    // Program kapanirken izlenen prosedurleri icerir.
    //
    // - isletim sistemine kullanilan bellegi iade etme
    // - cesitli sistemleri kapatma
    int Exit();


    // Motorun kullandigi built-in ve diger kaynaklari isletim sistemine
    // iade etmek icin izlenen prosedurleri icerir.
    // 
    // - texture, shader, asset belleklerini isletim sistemine iade etme
    void Unload();


    // Bir frame'i cizmek icin gereken tum mantik ve aritmetik islemlerini icerir.
    // 
    // - kullanicidan gelen input'u isleme
    // - simulasyon dunyasini guncelleme (update/tick)
    // - cizim icin gerekli datayi toplama
    // - cizim icin komutlari grafik islemcisine gonderme
    // - uygulama penceresine son resmi aktarma
    void MainLoop();

private:
    void drawScene();

    void updateUI();
    void drawUI();
    // todo
    void updateScene();
    void loadTextures();
    void loadShaders();
    void loadMesh();

private:
    const static unsigned int buffer_count = 1;
    // Uygulama veri ve state tanimlari
    GLFWwindow* window;
    Shader*      ourShader;
    unsigned int texture1;
    unsigned int texture2;
    unsigned int VAOs[buffer_count];
    unsigned int VBOs[buffer_count];
    unsigned int EBO;
    // config
    bool b_isWireframeMode;
    Vec4 clear_color;
    UIState     ui_state;

};
