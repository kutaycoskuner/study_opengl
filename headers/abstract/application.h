#pragma once
//              libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/vector4.h"
#include "../abstract/ui.h"
#include "../abstract/scene.h"
#include "../abstract/queue.h"
#include "../abstract/scene_state.h"
#include "../abstract/window_state.h"
#include "../abstract/camera.h"
#include "../abstract/queue.h"
#include "../events/input_observer.h"
#include "../data/data.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <random>


//              forward declarations
// ------------------------------------------------------------------------------------------------
struct GLFWwindow;
struct Uniforms;
struct Material;
class Shader;
using uint = unsigned int;


//              function declerations
// ------------------------------------------------------------------------------------------------

//              abstract
// ------------------------------------------------------------------------------------------------
class Application : public InputListener
{
public:
    using ConfigData = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

    // state
    bool reload                     = true;

       // Define the enum for path mode
    enum class PathMode {
        RELATIVE,
        FULL
    };
    PathMode path_mode              = Application::PathMode::RELATIVE;

    std::string data_dir_path       = "";
    std::string config_dir_path     = "";
    std::string shader_dir_path     = "";
    
    // testing
    bool save_frame                 = false;
    bool create_test_scene_frames   = false;
    unsigned int active_test_scene  = 0;

    // standards
    static const Vec3 world_up;
    static const Vec3 world_origin;

    static bool toggle_mouselock;

    void resetCamera();
    void toggleScreenshotMode();
    void toggleAO();

    void setPathType(std::string path_mode);

    // handlers
    InputSpeaker input_speaker;

    Application() : window(nullptr), active_shader(nullptr), active_scene(nullptr) 
        ,vertex_arrays{ 0 }, element_buffers{ 0 }
    {}
    // - ask memory from operating system
    // - preapre libraries
    bool initialize(const ConfigData& config);

    // Program bellegi hazirlandiktan sonra motorun kullanacagi built-in
    // kaynaklari yuklemek icin izlenen prosedurleri icerir.
    // 
    // - built-in shader compilation
    // - built-in texture loading
    // - built-in asset lfoading
    bool load(const ConfigData& config);
 
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
    void mainLoop(ConfigData& config);

    // handle
    void handleMouseEvent(GLFWwindow* window, double xpos, double ypos);
    void handleScrollEvent(GLFWwindow* window, double xoffset, double yoffset);

private:
    // initialize
    int initWindowSystem(const unsigned int& width, const unsigned int& height, const char*& window_name);
    void initUISystem(const char*& glsl_version);
    
    // load
    void loadConfig(const ConfigData& config);
    void loadSceneData(const ConfigData& config);
    void loadTextures();
    void loadShaders();
    std::vector<const char*> loadModelPaths();
    void loadMeshData();

    void generateShadowFBO();
    void generateBuffer(uint vrtx_arr, uint vrtx_buffer, const float obj_vrts[], const uint& stride, bool vrtx, bool tex);

    // ui
    void drawUI();
    void updateUI();

    // hooks
    //void onMultipleKeyPress(std::vector<int> keys);
    void onUIEvent(const UIEvent& event, const std::vector<int>& params);


    // draw  sub / short / convention functions
    void setActiveShader(const std::string& name);

    // draw scene
    void drawScene(Uniforms& uni);

        void setUniforms(const Uniforms& uni);
        
        void drawHelper_axes(Uniforms& uni);
        void drawHelper_lightPlaceholders(Uniforms& uni);

        void drawSceneNode_primitive_shadows_dl(const Mat4& model_mat);
        void drawSceneNode_primitive_shadows_pl(const float far_plane);

        void drawSceneNodes_primitive(Uniforms& uni);
        void drawSceneNodes_models(Uniforms& uni);

        void drawScene_skybox(Uniforms& uni);


        void drawShadowMap();
        void drawShadowCubemap();

        void drawDeferredLightingPass();

        void drawBackbuffer(int display_w, int display_h);
        void drawQuad();

        void compute_QuadVrtxTangents();

    void updateScene();
    void setMaterial(const Material& material);
    void setPresetMaterial(const Material& material);

    // stencil
    void disableStencil();
    void enableStencil();
    void clearStencil();

    // custom functions
    void setPointLightParameters(const Uniforms& uni);
    void setSpotLightParameters(const Uniforms& uni);
    void setDirectionalLightParameters(const Uniforms& uni);

    // 

    const unsigned int  SSAO_KERNEL_SIZE = 64;
    unsigned int        fbo_ssao;
    unsigned int        tex_ssao;
    unsigned int        fbo_ssao_blur;
    unsigned int        tex_ssao_blur;
    std::vector<Vec3>   ssao_kernel;
    //std::vector<Vec3> ssao_noise;
    unsigned int        ssao_noise_texture;
    void createSSAOSampleKernel();
    void createSSAONoiseTexture();
    void drawSSAOPass(const Uniforms& uni);
    void drawSSAOLightingPass(const Uniforms& uni);
    void ppSSAOBlur(); // pp stans for post process

    // reset


private:
    const static unsigned int buffer_count  = 10;
    const float reduction_128f              = 0.0078125f;
    const unsigned int INVALID_ID           = 0;

    // Uygulama veri ve state tanimlari
    GLFWwindow* window;
    bool screenshot_mode = false;


    // event
    Queue<std::map<UIEvent, std::vector<int>>> ui_events;

    // skybox
    unsigned int cubemap_texture;
    
    unsigned int lit_ebo; // element buffer object  || index buffer
    unsigned int instanced_buffer;
    
    unsigned int computed_vertex_array_obj = 0;
    unsigned int computed_vertex_buffer;
    unsigned int vertex_arrays[buffer_count];
    unsigned int vertex_buffers[buffer_count];
    unsigned int element_buffers[buffer_count];

    //unsigned int frame_buffers[buffer_count];
    //unsigned int render_buffers[buffer_count];

    std::map<std::string, unsigned int> named_arrays;

    unsigned int ubo_matrices;
   
    // anti-aliasing
    unsigned int sample_count = 1;
    unsigned int fbo_illumination_msaa;
    unsigned int rbo_illumination_msaa;
    unsigned int tex_illumination_msaa_color;

    // deferred shading
    unsigned int g_buffer;
    unsigned int g_position;
    unsigned int g_normal;
    unsigned int g_color_specular;
        
    // high dynamic range
    GLuint  fbo_illumination_hdr;
    GLuint  tex_illumination_hdr[2];

    // pp: post process
    GLuint fbo_bloom[2];
    GLuint tex_bloom[2];

    // final frame buffer (low dynamic range output)
    unsigned int fbo_backbuffer;       // frame buffer object    || frame buffer
    unsigned int rbo_backbuffer_depth; // render buffer object   || render buffer
    unsigned int fbo_backbuffer_color;

    // shadow buffers
    std::vector<unsigned int> fbo_shadow;
    std::vector<unsigned int> tex_shadow_maps;

    // shadow cubemaps
    std::vector<unsigned int> fbo_shadow_cube;
    std::vector<unsigned int> tex_shadow_cubemaps;
    
    // shadow matrices
    std::vector<GLfloat*>     ptr_mat_light_space;
    std::vector<Mat4>         mat_light_space;
    std::array<Mat4, 6>       mat_light_space_cubemaps;


    std::shared_ptr<Shader> active_shader;
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, TextureSet> textures;
    
    // Scene scene;
    Scene*      active_scene;
    WindowState window_state;
    UIState     ui_state;

    // config
    bool        b_wireframe_mode = false;
    Vec4        clear_color;

    // temporary
    int             display_width           = 800;
    int             display_height          = 600;

    int             shadowmap_resolution_x  = 1024;
    int             shadowmap_resolution_y  = 1024;
    float           shadowmap_aspect_ratio;
  
    float           camera_aspect_ratio;
    float           shadow_far_plane;
    Vec3            ui_vector;


    float dimension = 10.0f;

};
