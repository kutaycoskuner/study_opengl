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
#include "application.h"	
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/backends/imgui_impl_glfw.h"
#include "../../libs/imgui/backends/imgui_impl_opengl3.h"
// test

// ---------------------------------------------------------------------------------------
//				Forward Declarations
// ---------------------------------------------------------------------------------------
void drawKeybindingsTab();
void drawGraphicsTab();
void drawParametersTab(const Application& app);

// ---------------------------------------------------------------------------------------
//				Functions
// ---------------------------------------------------------------------------------------

void Application::initUISystem(const char*& glsl_version)
{
	//  :: IMGUI Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Application::drawUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::updateUI()
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
		//if (ImGui::BeginMenu("File"))
		//{
		//	//ImGui::ShowExampleMenuFile();
		//	if (ImGui::MenuItem("Select Scene", "Shortcut")) {}
		//	ImGui::EndMenu();
		//}
		if (ImGui::BeginMenu("Select Scene"))
		{
			//if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			//if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Multiple Lights", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 1 });
			}
			if (ImGui::MenuItem("Import Model", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 2 });
			}
			if (ImGui::MenuItem("Outliner", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 3 });
			}
			if (ImGui::MenuItem("Blending", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 4 });
			}
			if (ImGui::MenuItem("Face Culling", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 5 });
			}
			if (ImGui::MenuItem("Frame Buffer", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 6 });
			}
			if (ImGui::MenuItem("Cube Map", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 7 });
			}
			if (ImGui::MenuItem("Advanced GLSL", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 8 });
			}
			if (ImGui::MenuItem("Geometry Shader", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 9 });
			}
			if (ImGui::MenuItem("Instancing", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 10 });
			}
			if (ImGui::MenuItem("Anti Aliasing", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 11 });
			}
			if (ImGui::MenuItem("Blinn-Phong / Phong", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 12 });
			}
			if (ImGui::MenuItem("Gamma Correction", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 13 });
			}
			if (ImGui::MenuItem("Directional Light Shadows", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 14 });
			}
			if (ImGui::MenuItem("Point Light Shadows", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 15 });
			}
			if (ImGui::MenuItem("Normal Map", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 16 });
			}
			if (ImGui::MenuItem("Parallax Mapping", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 17 });
			}
			if (ImGui::MenuItem("High Dynamic Range", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 18 });
			}
			if (ImGui::MenuItem("Bloom", "")) {
				input_speaker.notifyUIEvent(UIEvent::SelectScene, { 19 });
			}
                        if (ImGui::MenuItem("Deferred Shading", ""))
                        {
                            input_speaker.notifyUIEvent(UIEvent::SelectScene, {20});
                        }

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}



	// remove this retun to activate ui
	if (!active_scene->scene_state.b_toggleui)
		return;

	//				floating window
	// --------------------------------------------------------------------------------------
	//2. Show a simple window that we create ourselves.We use a Begin / End pair to create a named window.
	{
		ImGui::Begin("Scene Controls"); // Create a window called "Scene Controls"

		if (ImGui::BeginTabBar("Tabs")) // Start the tab bar
		{
			// Parameters Tab
			if (ImGui::BeginTabItem("Parameters"))
			{
				ImGui::Text("Camera Controls");
				ImGui::SliderFloat("Camera Pos X", &this->active_scene->cameras[0].position.x, -10.0f, 10.0f);
				ImGui::SliderFloat("Camera Pos Y", &this->active_scene->cameras[0].position.y, -10.0f, 10.0f);
				ImGui::SliderFloat("Camera Pos Z", &this->active_scene->cameras[0].position.z, -10.0f, 10.0f);
				ImGui::SliderFloat("Camera Yaw  ", &this->active_scene->cameras[0].yaw_rad, -10.0f, 10.0f);
				ImGui::SliderFloat("Camera Pitch", &this->active_scene->cameras[0].pitch_rad, -10.0f, 10.0f);

				ImGui::Text("Point Light Controls");
				ImGui::SliderFloat("p light 01 x", &this->active_scene->point_lights[0].position.x, -10.0f, 10.0f);
				ImGui::SliderFloat("p light 01 y", &this->active_scene->point_lights[0].position.y, -10.0f, 10.0f);
				ImGui::SliderFloat("p light 01 z", &this->active_scene->point_lights[0].position.z, -10.0f, 10.0f);

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

void drawParametersTab(const Application& app) {

}

void drawGraphicsTab() {
	if (ImGui::BeginTabItem("Graphics"))
	{
		ImGui::Text("Graphics Settings");
		static float gamma_correction = 2.2f;
		static float bloom_threshold = 1.0f;
		static int shadow_quality = 3; // 1: Low, 2: Medium, 3: High

		ImGui::SliderFloat("Gamma Correction", &gamma_correction, 1.0f, 3.0f);
		ImGui::SliderFloat("Bloom Threshold", &bloom_threshold, 0.0f, 2.0f);
		ImGui::Combo("Shadow Quality", &shadow_quality, "Low\0Medium\0High\0");

		ImGui::EndTabItem();
	}
}

void drawKeybindingsTab() {
	if (ImGui::BeginTabItem("Keybinds"))
	{
		ImGui::Text("Keybindings");

		// Define the keybinding pairs
		static const char* keybinds[][2] = {
			{"W", "Move camera forward"},
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

void Application::toggleScreenshotMode() {
	screenshot_mode = !screenshot_mode;
}