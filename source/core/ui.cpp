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

	// ----- test ---------------------------------------------------------------------------

	if (ImGui::BeginMainMenuBar())
	{
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

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	// ----- test  end ----------------------------------------------------------------------


	// remove this retun to activate ui
	if (!active_scene->scene_state.b_toggleui)
		return;

	//2. Show a simple window that we create ourselves.We use a Begin / End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		static const char* txt_aspectRatio = "Aspect Ratio: ";

		ImGui::Begin("Hello world");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text(txt_aspectRatio);               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Animate Y", &this->ui_state.animate);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("Light Dir X", &this->scene_state.light.direction.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SliderFloat("Light Dir Y", &this->scene_state.light.direction.y, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SliderFloat("Light Dir Z", &this->scene_state.light.direction.z, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SliderFloat("Light Pos Z", &this->scene_state.light.position.z, -5.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("", (this->ui_state.clear_color.toFloatPointer()));		// Edit 3 floats representing a color

		ImGui::SliderFloat("Camera Pos X", &this->active_scene->cameras[0].position.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pos Y", &this->active_scene->cameras[0].position.y, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pos Z", &this->active_scene->cameras[0].position.z, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Yaw  ", &this->active_scene->cameras[0].yaw_rad, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pitch", &this->active_scene->cameras[0].pitch_rad, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


		ImGui::SliderFloat("p light 01 x", &this->active_scene->point_lights[0].position.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("p light 01 y", &this->active_scene->point_lights[0].position.y, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("p light 01 z", &this->active_scene->point_lights[0].position.z, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		// Debug
		//ImGui::SliderFloat("Dimension",    &this->dimension, -30.0f, 50.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::SliderFloat("Osman", &this->active_scene->directional_lights[0].position.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


		const char* animate_button_name =
			this->active_scene->scene_state.animate ? "Stop" : "Play";
		if (ImGui::Button(animate_button_name))
			this->active_scene->scene_state.animate = !this->active_scene->scene_state.animate;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		//ImGui::Text("vertices: %u | tringles: %u", active_scene->scene_state.stats_vrts, active_scene->scene_state.stats_tris);
		ImGui::End();
	}
}