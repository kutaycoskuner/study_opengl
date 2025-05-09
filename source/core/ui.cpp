// ---------------------------------------------------------------------------------------
//				Notes
// ---------------------------------------------------------------------------------------
/*
        I will write some stuff here someday.
        ...
*/

// ---------------------------------------------------------------------------------------
//				Libraries
// ---------------------------------------------------------------------------------------
#include "../../libs/imgui/backends/imgui_impl_glfw.h"
#include "../../libs/imgui/backends/imgui_impl_opengl3.h"
#include "../../libs/imgui/imgui.h"
#include "renderer.h"
// test

// ---------------------------------------------------------------------------------------
//				Forward Declarations
// ---------------------------------------------------------------------------------------
void drawKeybindingsTab();
void drawGraphicsTab();
void drawParametersTab(const Renderer& app);

// ---------------------------------------------------------------------------------------
//				Variables
// ---------------------------------------------------------------------------------------
enum class UITabs
{
    SceneDataControl,
    Keybindings
};

UITabs selected_tab = UITabs::SceneDataControl;  // Default tab

// ---------------------------------------------------------------------------------------
//				Functions
// ---------------------------------------------------------------------------------------

void Renderer::initUISystem(const char*& glsl_version)
{
    //  :: IMGUI Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Renderer::drawUI()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::updateUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (screenshot_mode) return;

    //				main menu bar
    // --------------------------------------------------------------------------------------
    if (ImGui::BeginMainMenuBar())
    {
        // this is an example code do not delete
        // if (ImGui::BeginMenu("File"))
        //{
        //	//ImGui::ShowExampleMenuFile();
        //	if (ImGui::MenuItem("Select Scene", "Shortcut")) {}
        //	ImGui::EndMenu();
        //}
        if (ImGui::BeginMenu("Select Scene"))
        {
            // if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            // if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Multiple Lights", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {1});
            }
            if (ImGui::MenuItem("Import Model", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {2});
            }
            if (ImGui::MenuItem("Outliner", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {3});
            }
            if (ImGui::MenuItem("Blending", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {4});
            }
            if (ImGui::MenuItem("Face Culling", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {5});
            }
            if (ImGui::MenuItem("Frame Buffer", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {6});
            }
            if (ImGui::MenuItem("Cube Map", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {7});
            }
            if (ImGui::MenuItem("Advanced GLSL", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {8});
            }
            if (ImGui::MenuItem("Geometry Shader", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {9});
            }
            if (ImGui::MenuItem("Instancing", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {10});
            }
            if (ImGui::MenuItem("Anti Aliasing", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {11});
            }
            if (ImGui::MenuItem("Blinn-Phong / Phong", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {12});
            }
            if (ImGui::MenuItem("Gamma Correction", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {13});
            }
            if (ImGui::MenuItem("Directional Light Shadows", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {14});
            }
            if (ImGui::MenuItem("Point Light Shadows", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {15});
            }
            if (ImGui::MenuItem("Normal Map", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {16});
            }
            if (ImGui::MenuItem("Parallax Mapping", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {17});
            }
            if (ImGui::MenuItem("High Dynamic Range", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {18});
            }
            if (ImGui::MenuItem("Bloom", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {19});
            }
            if (ImGui::MenuItem("Deferred Shading", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {20});
            }
            if (ImGui::MenuItem("Screen Space Ambient Occlusion", ""))
            {
                input_speaker.notifyUIEvent(UIEvent::SelectScene, {21});
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Options (G)", ""))
        {
            active_scene->scene_state.toggle_ui = !active_scene->scene_state.toggle_ui;
            //input_speaker.notifyUIEvent(UIEvent::OpenUISegment, {});
        }

        ImGui::EndMainMenuBar();
    }

    // remove this retun to activate ui
    if (!active_scene->scene_state.toggle_ui) return;

    //				floating window
    // --------------------------------------------------------------------------------------
    // 2. Show a simple window that we create ourselves.We use a Begin / End pair to create a named window.
    {
        ImGui::Begin("Options");  // Create a window called "Scene Controls"

        if (ImGui::BeginTabBar("Tabs"))  // Start the tab bar
        {
            // Parameters Tab
            if (ImGui::BeginTabItem("Scene Data"))
            {
                // Render View Mode Dropdown
                ImGui::Text("Render View Mode");

                static RenderViewMode selected_mode = RenderViewMode::ILLUMINATION;
                const char*           mode_names[]  = {"Illumination", "SSAO"};

                if (ImGui::BeginCombo("Render Mode", mode_names[static_cast<int>(selected_mode)]))
                {
                    for (int i = 0; i < IM_ARRAYSIZE(mode_names); ++i)
                    {
                        bool is_selected = (static_cast<int>(selected_mode) == i);
                        if (ImGui::Selectable(mode_names[i], is_selected))
                        {
                            selected_mode = static_cast<RenderViewMode>(i); 
                            input_speaker.notifyUIEvent(UIEvent::SetRenderView, {i});
                        }
                        if (is_selected) ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                ImGui::Text("Camera Controls");
                static int               selected_camera = 0;
                std::vector<std::string> camera_names;
                for (size_t i = 0; i < this->active_scene->cameras.size(); ++i)
                {
                    camera_names.push_back("Camera " + std::to_string(i + 1));
                }

                const char* current_camera = camera_names[selected_camera].c_str();
                if (ImGui::BeginCombo("Select Camera", current_camera))
                {
                    for (size_t i = 0; i < camera_names.size(); ++i)
                    {
                        bool is_selected = (selected_camera == i);
                        if (ImGui::Selectable(camera_names[i].c_str(), is_selected))
                        {
                            selected_camera = i;
                        }
                        if (is_selected) ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                ImGui::SliderFloat("Camera Position X", &this->active_scene->cameras[selected_camera].position.x, -10.0f,
                                   10.0f);
                ImGui::SliderFloat("Camera Position Y", &this->active_scene->cameras[selected_camera].position.y, -10.0f,
                                   10.0f);
                ImGui::SliderFloat("Camera Position Z", &this->active_scene->cameras[selected_camera].position.z, -10.0f,
                                   10.0f);
                ImGui::SliderFloat("Yaw", &this->active_scene->cameras[selected_camera].yaw_rad, -3.14f, 3.14f);
                ImGui::SliderFloat("Pitch", &this->active_scene->cameras[selected_camera].pitch_rad, -3.14f, 3.14f);

                if (!this->active_scene->point_lights.empty())
                {
                    ImGui::Text("Point Light Controls");
                    // Dropdown to select which light to control
                    static int               selected_light = 0;
                    std::vector<std::string> light_names;
                    for (size_t i = 0; i < this->active_scene->point_lights.size(); ++i)
                    {
                        light_names.push_back("Point Light " + std::to_string(i + 1));
                    }

                    const char* current_item = light_names[selected_light].c_str();
                    if (ImGui::BeginCombo("Select Light", current_item))
                    {
                        for (size_t i = 0; i < light_names.size(); ++i)
                        {
                            bool is_selected = (selected_light == i);
                            if (ImGui::Selectable(light_names[i].c_str(), is_selected))
                            {
                                selected_light = i;
                            }
                            if (is_selected) ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }

                    // Controls for the selected point light
                    ImGui::SliderFloat("Point Light Position X", &this->active_scene->point_lights[selected_light].position.x,
                                       -10.0f, 10.0f);
                    ImGui::SliderFloat("Point Light Position Y", &this->active_scene->point_lights[selected_light].position.y,
                                       -10.0f, 10.0f);
                    ImGui::SliderFloat("Point Light Position Z", &this->active_scene->point_lights[selected_light].position.z,
                                       -10.0f, 10.0f);
                    // Light Intensity (Brightness)
                    ImGui::SliderFloat("Brightness", &this->active_scene->point_lights[selected_light].brightness, 0.0f,
                                       10.0f);

                    // Light Color Picker (RGB)
                    ImGui::ColorEdit3("Light Color", &this->active_scene->point_lights[selected_light].diffuse.x);
                }

                ImGui::Checkbox("Toggle Screen Space Ambient Occlusion", &this->active_scene->scene_state.toggle_ssao);

                ImGui::EndTabItem();
            }

            drawKeybindingsTab();

            ImGui::EndTabBar();
        }

        // Show FPS and performance stats
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    //				docked panel
    // --------------------------------------------------------------------------------------
}

void drawParametersTab(const Renderer& app) {}

void drawGraphicsTab()
{
    if (ImGui::BeginTabItem("Graphics"))
    {
        ImGui::Text("Graphics Settings");
        static float gamma_correction = 2.2f;
        static float bloom_threshold  = 1.0f;
        static int   shadow_quality   = 3;  // 1: Low, 2: Medium, 3: High

        ImGui::SliderFloat("Gamma Correction", &gamma_correction, 1.0f, 3.0f);
        ImGui::SliderFloat("Bloom Threshold", &bloom_threshold, 0.0f, 2.0f);
        ImGui::Combo("Shadow Quality", &shadow_quality, "Low\0Medium\0High\0");

        ImGui::EndTabItem();
    }
}

void drawKeybindingsTab()
{
    if (ImGui::BeginTabItem("Keybinds"))
    {
        ImGui::Text("Keybindings");

        // Define the keybinding pairs
        static const char* keybinds[][2] = {{"W", "Move camera forward"},
                                            {"A", "Move camera left"},
                                            {"S", "Move camera backward"},
                                            {"D", "Move camera right"},
                                            {"X", "Move camera down"},
                                            {"Space Bar", "Move camera up"},
                                            {"Q", "Rotate camera left"},
                                            {"E", "Rotate camera right"},
                                            {"R", "Tilt camera up"},
                                            {"F", "Tilt camera down"},
                                            {"Z", "Toggle mouse control for rotation (default: disabled)"},
                                            {"C", "Reset camera position"},
                                            {"G", "Toggle user interface"},
                                            {"T", "Toggle Screenshot mode"},
                                            {"O", "Toggle Ambient Occlusion"},
                                            {"Shift", "Increases movement speed while pressed"}

        };

        // Render the table
        if (ImGui::BeginTable("KeybindTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Key", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            for (const auto& keybind : keybinds)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", keybind[0]);
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", keybind[1]);
            }

            ImGui::EndTable();
        }

        ImGui::EndTabItem();
    }
}

void Renderer::toggleScreenshotMode() { screenshot_mode = !screenshot_mode; }

void Renderer::toggleAO() { active_scene->scene_state.toggle_ssao = !active_scene->scene_state.toggle_ssao; }