// ---------------------------------------------------------------------------------------
// ----- Notes
// ---------------------------------------------------------------------------------------
/*
	I will write some stuff here someday.
	...
*/
#if 1
// ---------------------------------------------------------------------------------------
// ----- Libraries
// ---------------------------------------------------------------------------------------
// imgui
#include "../../libs/imgui-1.89.5/imgui.h"
#include "../../libs/imgui-1.89.5/imgui_impl_glfw.h"
#include "../../libs/imgui-1.89.5/imgui_impl_opengl3.h"

#include "../headers/test/basic.h"			// project start basic test
#include "../headers/utils/utilities.h"		// self written utilities
#include "../headers/data/data.h"			// data headers ex. model vertices
#include "../headers/events/events.h"		// window, mouse-, keyboard input events
#include "../headers/abstract/application.h"	
#include "../headers/abstract/camera.h"				
#include "../headers/abstract/shader.h"				
#include "../headers/abstract/material.h"				
#include "../headers/abstract/uniforms.h"	
#include "../headers/abstract/model.h"		
#include "../headers/maps/shaders.h"			
#include "../headers/core/opengl.h"			

#include "../../headers/data/scenes.h"

#include <GLFW/glfw3.h>  // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>	 // opengl hardware adaptor before glfw
#include <iostream>				
#include <string>				
#include <unordered_map>		
#include <cmath>     			

#include <memory>
#include <filesystem>

// ---------------------------------------------------------------------------------------
// self keywords
// ---------------------------------------------------------------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;

// ---------------------------------------------------------------------------------------
// global, constant variables
// ---------------------------------------------------------------------------------------
constexpr unsigned int kg_error_buffer_size = 512;
Application* gp_app;
const Vec3	Application::world_up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3	Application::world_origin = Vec3(0.0f, 0.0f, 0.0f);
bool		Application::toggle_mouselock = true;

// ---------------------------------------------------------------------------------------
// ----- Functions Definitions
// ---------------------------------------------------------------------------------------   
void Application::disableStencil()
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void Application::enableStencil()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
}

void Application::clearStencil()
{
	// return to default state
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);

	//glEnable(GL_DEPTH_TEST);
}


bool Application::initialize(k_configType& config)
{
	gp_app = this;

	const unsigned int k_scr_width = std::stoul(config.at("scr").at("width"));
	const unsigned int k_scr_height = std::stoul(config.at("scr").at("height"));
	const char* kp_wndw_name = config.at("scr").at("wndw_name").c_str();



	initWindowSystem(k_scr_width, k_scr_height, kp_wndw_name);
	const char* glsl_version = "#version 330";
	window_state.b_first_mouse = true;
	window_state.mouse_x = std::stoul(config.at("scr").at("width")) / 2.0f;
	window_state.mouse_y = std::stoul(config.at("scr").at("height")) / 2.0f;

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return bool(-1);
	}

	initUISystem(glsl_version);

	// stb image library should flip textures?
	img_utils::setVerticalFlipMode(true);

	// init asset importer
	Assimp::Importer importer;
	if (!importer.IsExtensionSupported("obj")) {
		std::cout << "Failed to load Assimp library." << std::endl;
	}

	// our state
	std::vector<unsigned int> bg_rgb = color_utils::hexToRGB(config.at("colors").at("bg"));


	this->clear_color = Vec4(
		scaleByteToZeroOne(float(bg_rgb[0])),
		scaleByteToZeroOne(float(bg_rgb[1])),
		scaleByteToZeroOne(float(bg_rgb[2])),
		1.00f
	);


	// 3.4 generate frame buffer object 
	glGenFramebuffers(1, &lit_fbo);
	// bunun yerinin dogru olup olmadigina emin degilim
	glBindFramebuffer(GL_FRAMEBUFFER, lit_fbo);
	// texture for framebuffer
	glGenTextures(1, &framebuffer_color_texture);
	glBindTexture(GL_TEXTURE_2D, framebuffer_color_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, k_scr_width, k_scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer_color_texture, 0);

	glGenRenderbuffers(1, &lit_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, lit_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, k_scr_width, k_scr_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, lit_rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	// unbind frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return 0;
}

bool Application::load(k_configType& config)
{
	loadConfig(config);

	loadSceneData(config);

	loadShaders();

	loadTextures();

	loadMeshData();

	return 1;
}

void Application::loadConfig(const k_configType& config)
{
	// load config states
	this->b_wireframe_mode = config.at("settings").at("is_wireframeMode") == "true";
}

void Application::loadSceneData(const k_configType& config)
{

	int scene_number = std::stoi(config.at("scene").at("active_scene"));

	if (scene_number == 0)			active_scene = new TestScene;
	else if (scene_number == 1)		active_scene = new MultipleLightsTestScene;
	else if (scene_number == 2)		active_scene = new ImportModelTestScene;
	else if (scene_number == 3)		active_scene = new OutlinerTestScene;
	else if (scene_number == 4)		active_scene = new BlendingTestScene;
	else if (scene_number == 5)		active_scene = new FaceCullingTestScene;
	else if (scene_number == 6)		active_scene = new FrameBufferTestScene;
	
	
	// ----- camera
	// --------------------------------------------------------------------------------------
	active_scene->cameras.push_back(Camera());
	Camera& cam = active_scene->cameras.back();

	cam.near = std::stof(config.at("default_camera").at("near"));
	cam.far = std::stof(config.at("default_camera").at("far"));
	cam.fov = std::stof(config.at("default_camera").at("fov"));
	// cam.rotation_sensitivity = std::stof(config.at("default_camera").at("rotation_sensitivity"));
	resetCamera();
	active_scene->loadData();
	SceneState& scene_state = active_scene->scene_state;

	// register listeners
	input_speaker.addListener(active_scene);

	// ui
	scene_state.b_toggleui = false;

	// animation
	scene_state.last_frame_time = std::stof(config.at("default_animation")
		.at("last_frame_time"));

	// predefined_scene_element_transforms
	Transform transform;
	scene_state.transforms.push_back(transform);

	// ----- models
	// --------------------------------------------------------------------------------------
	std::vector<const char*> model_paths = loadModelPaths();

	for (int ii = 0; ii < model_paths.size(); ii++)
	{
		Model ourModel(model_paths[ii]);
		active_scene->models.push_back(Model(ourModel));
	}
}

void Application::loadTextures()
{
	// texture
	setVerticalFlipMode(true);

	for (auto it = active_scene->texture_names.begin(); it != active_scene->texture_names.end(); ++it)
	{
		TextureSet	texture_set;
		std::string texture_name = *it;
		RelativePaths::texture_paths[texture_name].color != "" ?
			texture_set.color = createTexture(RelativePaths::texture_paths[texture_name].color)
			: texture_set.color = 0;
		
		RelativePaths::texture_paths[texture_name].roughness != "" ?
			texture_set.roughness = createTexture(RelativePaths::texture_paths[texture_name].roughness) 
			: texture_set.roughness = 0;
		
		RelativePaths::texture_paths[texture_name].normal != "" ?
			texture_set.normal = createTexture(RelativePaths::texture_paths[texture_name].normal)
			: texture_set.normal = 0;
		
		RelativePaths::texture_paths[texture_name].specular != "" ?
			texture_set.specular = createTexture(RelativePaths::texture_paths[texture_name].specular)
			: texture_set.specular = 0;
		
		RelativePaths::texture_paths[texture_name].emission != "" ?
			texture_set.emission = createTexture(RelativePaths::texture_paths[texture_name].emission)
			: texture_set.emission = 0;
		textures[texture_name] = texture_set;
	}

}

void Application::loadShaders()
{
	// build and compile our shader program
	// todo: butun shaderlari yukle daha sonra aktifi sec | bu 3d pipeline ini bozuyor
	for (const ShaderPaths& path_struct : RelativePaths::shader_paths)
	{
		const std::string vrtx = path_struct.vrtx_shader_file;
		const std::string frag = path_struct.frag_shader_file;
		// get between / and _ for key
		std::vector<std::string> path_parts = str_utils::split(vrtx, "_");
		std::string left_trimmed_key = path_parts[0];

		path_parts = str_utils::split(left_trimmed_key, ".");
		const std::string name = path_parts.back();
		shaders[name] = std::make_shared<Shader>(vrtx, frag);
	}
}

std::vector<const char*> Application::loadModelPaths()
{
	std::vector<const char*> model_paths;
	for (const std::string& path : active_scene->model_paths)
	{
		model_paths.push_back(path.c_str());
	}
	return model_paths;
}


void Application::loadMeshData()
{
	// create vertex array object and vertex buffer object
	glGenVertexArrays(buffer_count, vertex_arrays);
	glGenBuffers(buffer_count, vertex_buffers); // :: memory alani olusturuyor
	glGenBuffers(buffer_count, element_buffers); // :: ebo icin memory


	// binding buffers
	//glBindVertexArray(vertex_arrays[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Predef3D::cube_vrts__pos_uv), Predef3D::cube_vrts__pos_uv, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffers[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Predef3D::square_inds), Predef3D::square_inds, GL_STATIC_DRAW);

	// linking vertex attributes
	// --------------------------       
	// 1. parameter specifies which vertex attribute we want to configure  | location of position
	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
	// 3. parameter specifies type of data gl_float
	// 4. parameter specifies if you want to data to be normalized
	// 5. known as stride space between consequtive vertex attributes
	// 6. void this is the !! offset where the position data begins in the buffer

	// att: new_pos
	unsigned int stride = 5;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// att: color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// att: texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// lit: coord, normal, texture
	glGenVertexArrays(1, &lit_vao);
	glGenBuffers(1, &lit_vbo); // :: memory alani olusturuyor
	glBindBuffer(GL_ARRAY_BUFFER, lit_vbo);

	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	// todo: vertexbuffer class olustur
	glBindVertexArray(lit_vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Predef3D::cube_vrts__pos_norm_uv), Predef3D::cube_vrts__pos_norm_uv, GL_STATIC_DRAW);
	stride = 8;
	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// att: normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// att: texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//generateBuffer(lit_vao, lit_vbo, Predef3D::cube_vrts__pos_uv, 5, 1, 0);

	glGenBuffers(1, &lit_ebo); // :: ebo icin memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lit_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Predef3D::cube_inds__pos_norm_uv), Predef3D::cube_inds__pos_norm_uv, GL_STATIC_DRAW);


	// screen quad VAO
	glGenVertexArrays(1, &vertex_arrays[0]);
	glGenBuffers(1, &vertex_buffers[0]);
	glBindVertexArray(vertex_arrays[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Predef3D::quad_vrts__pos_tex), &Predef3D::quad_vrts__pos_tex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// clean new_up
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Application::generateBuffer(uint vrtx_arr, uint vrtx_buffer, const float obj_vrts[], const uint& stride, bool vrtx, bool tex)
{
	// light
	glGenVertexArrays(1, &vrtx_arr);
	glGenBuffers(1, &vrtx_buffer); // :: memory alani olusturuyor
	glBindBuffer(GL_ARRAY_BUFFER, vrtx_buffer);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	// todo: vertexbuffer class olustur
	glBindVertexArray(vrtx_arr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vrts), obj_vrts, GL_STATIC_DRAW);
	// att: vrtx 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	if (vrtx)
		glEnableVertexAttribArray(0);
	// att: texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	if (tex)
		glEnableVertexAttribArray(2);
}

void Application::mainLoop()
{
	// uniform variables according to update frequency
	Uniforms uni;
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;

	// initial values for the uniforms
	uni_obj.world_matrix = mat_utils::identity4();
	uni_view.view_matrix = mat_utils::identity4();
	uni_view.projection_matrix = mat_utils::identity4();
	uni_obj.mix_value = 0.2f;

	// ----- render loop 
	// --------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, uni_obj);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		Camera& cam = active_scene->cameras[0];
		cam.aspect_ratio = float(w) / float(h);

		// Start the Dear ImGui frame
		updateUI();

		updateScene();

		drawScene(uni);

		drawUI();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int Application::initWindowSystem(const unsigned int& width, const unsigned int& height, const char*& window_name)
{
	// :: GLFW
	glfwInit();
	// first param what option we want to configure; second option is value we set.
	// 3 means we are explicitly using core profile. version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//
	// if apple

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	this->window = glfwCreateWindow(width, height, window_name, NULL, NULL);
	// first two params x,y in size; 3. name; 4-5 necesssary but ignore
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// resize handle
	glfwSetFramebufferSizeCallback(window, callbackFrameBufferSize);
	glfwSetCursorPosCallback(window, callbackMouse);
	glfwSetScrollCallback(window, callbackScroll);
	return 0;
}

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

void Application::unload()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	delete active_scene;
	glDeleteVertexArrays(1, &lit_vao);
	glDeleteBuffers(1, &lit_vbo);
	glDeleteFramebuffers(1, &lit_fbo);
	glDeleteRenderbuffers(1, &lit_rbo);
	glDeleteVertexArrays(buffer_count, vertex_arrays);
	glDeleteBuffers(buffer_count, vertex_buffers);
}

int Application::exit()
{
	// glfw: purge allocated memory
	// ------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void Application::drawUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::updateUI()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// remove this retun to activate ui
	if (!active_scene->scene_state.b_toggleui)
		return;

	//2. Show a simple window that we create ourselves.We use a Begin / End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		static const char* txt_aspectRatio = "Aspect Ratio: ";

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

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

		const char* animate_button_name =
			this->active_scene->scene_state.animate ? "Stop" : "Play";
		if (ImGui::Button(animate_button_name))
			this->active_scene->scene_state.animate = !this->active_scene->scene_state.animate;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}
}

void assignBuffer(const float* objToDraw, const int sizeofObjToDraw, const unsigned int& inptLayout, const unsigned int& vrtxBuffer)
{
	glBindVertexArray(inptLayout);	// VAO note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeofObjToDraw, objToDraw, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Application::setPointLightParameters(Uniforms& uni)
{
	// point light
	const std::vector<PointLight>& point_lights = active_scene->point_lights;
	if (point_lights.empty()) { return; }
	float multiplier = 4.0f;
	for (int ii = 0; ii < 3; ii++)
	{
		std::string name = "point_lights[" + std::to_string(ii) + "].";
		active_shader->setVec3(name + "position", point_lights[ii].position);
		active_shader->setVec3(name + "ambient", point_lights[ii].ambient);
		active_shader->setVec3(name + "diffuse", point_lights[ii].diffuse);
		active_shader->setVec3(name + "specular", point_lights[ii].specular);
		active_shader->setFloat(name + "constant", point_lights[ii].constant);
		active_shader->setFloat(name + "linear", point_lights[ii].linear);
		active_shader->setFloat(name + "quadratic", point_lights[ii].quadratic);
		active_shader->setFloat(name + "brightness", point_lights[ii].brightness);
	}
}

void Application::setDirectionalLightParameters(Uniforms& uni)
{
	const std::vector<DirectionalLight>& directional_lights = active_scene->directional_lights;
	if (directional_lights.empty()) { return; }
	active_shader->setVec3("directional_light.direction", directional_lights[0].direction);
	active_shader->setVec3("directional_light.diffuse", directional_lights[0].diffuse); // darken diffuse light a bit
	active_shader->setVec3("directional_light.ambient", directional_lights[0].ambient);
	active_shader->setVec3("directional_light.specular", directional_lights[0].specular);
	active_shader->setFloat("directional_light.brightness", directional_lights[0].brightness);
}

void Application::setSpotLightParameters(Uniforms& uni)
{
	const std::vector<SpotLight>& spot_lights = active_scene->spot_lights;
	if (spot_lights.empty()) { return; }
	active_shader->setVec3("spot_light.position", spot_lights[0].position);
	active_shader->setVec3("spot_light.direction", spot_lights[0].direction);
	active_shader->setVec3("spot_light.ambient", spot_lights[0].ambient);
	active_shader->setVec3("spot_light.diffuse", spot_lights[0].diffuse);
	active_shader->setVec3("spot_light.specular", spot_lights[0].specular);
	active_shader->setFloat("spot_light.constant", spot_lights[0].constant);
	active_shader->setFloat("spot_light.linear", spot_lights[0].linear);
	active_shader->setFloat("spot_light.quadratic", spot_lights[0].quadratic);
	active_shader->setFloat("spot_light.cutoff", spot_lights[0].cutoff);
	active_shader->setFloat("spot_light.outer_cutoff", spot_lights[0].outer_cutoff);
	active_shader->setFloat("spot_light.brightness", spot_lights[0].brightness);
}

void Application::drawScene(Uniforms& uni)
{
	// draw wireframe or not
	if (b_wireframe_mode) // todo: deserialize config
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// 3.4. framebuffer
	// bind to framebuffer and draw scene as we normally would to color texture 
	glBindFramebuffer(GL_FRAMEBUFFER, lit_fbo);
	
	
	// enable this to avoid awkward whatever front rendering
	glEnable(GL_DEPTH_TEST);

	// enable stencil test
	glEnable(GL_STENCIL_TEST);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// https://learnopengl.com/Advanced-OpenGL/Stencil-testing
	// both the depth and stencil test pass, we will use the reference value
	glStencilOp(
		GL_KEEP,		// stencil action if stencil test fails 
		GL_KEEP,		// stencil action if stencil test passes but depth test fails
		GL_REPLACE		// stencil action if both pass
	);

	// render clear screen
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// get width and height
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	// draw scene
	disableStencil();

	const SceneState& scene_state = active_scene->scene_state;
	const Camera& cam = active_scene->cameras[0];

	// setting uniform names
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;
	// create transformations
	//upo.world_matrix = mat_utils::rotationX(toRadian(-45.0f))
	//	* mat_utils::rotationXYZ(scene_state.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
	//	;
	upv.view_matrix = cam.calcViewMatrix(world_up);
	upv.projection_matrix
		= mat_utils::projectPerspective(toRadian(cam.fov), cam.aspect_ratio, cam.near, cam.far);
	upv.view_proj_matrix = upv.projection_matrix * upv.view_matrix;

	// draw light placeholders
	// --------------------------------------------------------------------------
	std::vector<PointLight>& point_lights = active_scene->point_lights;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		this->active_shader = shaders.at("3d");
		(*active_shader).use();

		// assign uniforms
		active_shader->setVec3("light_color", active_scene->point_lights[ii].diffuse); // light_coloru degistirme
		active_shader->setMat4("view_matrix", uni.upv.view_matrix);
		active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
		active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

		glBindVertexArray(lit_vao);
		active_shader->setVec3("light_color", point_lights[ii].diffuse);

		Mat4 model = mat_utils::translation(point_lights[ii].position)
			* mat_utils::scale(PredefSceneElements::light_placeholder.transform.scale)
			;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	std::vector<SpotLight>& spot_lights = active_scene->spot_lights;
	for (int ii = 0; ii < spot_lights.size(); ii++)
	{
		this->active_shader = shaders.at("3d");
		(*active_shader).use();

		// assign uniforms
		active_shader->setVec3("light_color", active_scene->spot_lights[ii].diffuse); // light_coloru degistirme
		active_shader->setMat4("view_matrix", uni.upv.view_matrix);
		active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
		active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

		glBindVertexArray(lit_vao);
		active_shader->setVec3("light_color", spot_lights[ii].diffuse);

		Mat4 model = mat_utils::translation(spot_lights[ii].position)
			* mat_utils::scale(PredefSceneElements::light_placeholder.transform.scale)
			;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	// draw scene objects
	// --------------------------------------------------------------------------
	int element_count = active_scene->predefined_scene_elements.size();
	for (int i = 0; i < element_count; i++)
	{
		if (active_scene->predefined_scene_elements[i].element_bools.indexed)
		{
			// enable face culling 
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
			glFrontFace(GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		this->active_shader = shaders.at(active_scene->predefined_scene_elements[i].shader_name);
		// activate shader
		(*active_shader).use();

		// assign uniforms
		active_shader->setFloat("mix_val", upo.mix_value);
		active_shader->setVec3("view_pos", cam.position);
		active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

		// directional light
		setDirectionalLightParameters(uni);
		// point light
		setPointLightParameters(uni);
		//// spotLight
		setSpotLightParameters(uni);

		Mat4 model = mat_utils::identity4();
		active_shader->setMat4("world_matrix", model);

		// material
		//active_shader->setInt("texture1", 0);
		//active_shader->setInt("texture2", 1);
		active_shader->setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		active_shader->setInt("material.diffuse_map1", 0);
		active_shader->setInt("material.specular_map1", 1);
		active_shader->setInt("material.emission_map1", 2);
		active_shader->setFloat("material.emission_factor", active_scene->scene_state.emission_factor); // material emission factor
		active_shader->setFloat("material.shininess", active_scene->scene_state.shininess);
		float maxObjectScale = (std::max(model._11, std::max(model._22, model._33)));
		active_shader->setFloat("outline_scale", maxObjectScale);


		// assign texture
		std::string texture_name = active_scene->predefined_scene_elements[i].texture_name;

			glActiveTexture(GL_TEXTURE0);
			textures[texture_name].color != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].color)
			: glBindTexture(GL_TEXTURE_2D, 0);
		
			glActiveTexture(GL_TEXTURE1);
			textures[texture_name].specular != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].specular)
			: glBindTexture(GL_TEXTURE_2D, 0);
		
			glActiveTexture(GL_TEXTURE2);
			textures[texture_name].color != 0 ? 
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].emission) 
			: glBindTexture(GL_TEXTURE_2D, 0);


		// ----- draw element
		// -------------------------------------------------------------------------------------
		glBindVertexArray(lit_vao);
		Transform transform = active_scene->predefined_scene_elements[i].transform;
		model =
			mat_utils::translation(Vec3(transform.position.x, transform.position.y, transform.position.z))  // 0, 3, 10 * cos(ss.time)
			* mat_utils::rotateX(toRadian(transform.rotation.x))
			* mat_utils::rotateY(toRadian(transform.rotation.y))
			* mat_utils::rotateZ(toRadian(transform.rotation.z))
			* mat_utils::scale(transform.scale.x, transform.scale.y, transform.scale.z)
			;
		active_shader->setMat4("world_matrix", model);
		if (active_scene->predefined_scene_elements[i].element_bools.stencil_testing) { disableStencil(); }

		if (active_scene->predefined_scene_elements[i].element_bools.indexed)
		{
			// Bind the index buffer
			glBindBuffer(lit_vao, lit_ebo);
			glDrawElements(GL_TRIANGLES, sizeof(Predef3D::cube_inds__pos_norm_uv), GL_UNSIGNED_INT, 0);
		}
		else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
		{
			glDrawArrays(GL_TRIANGLES, 0, 36 / active_scene->scene_state.vertex_divider);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		if (active_scene->predefined_scene_elements[i].element_bools.stencil_testing) {
			enableStencil();
			this->active_shader = shaders.at("stenciltesting");
			(*active_shader).use();
			// light uniforms
			const SceneState& ss = active_scene->scene_state;
			UniformsPerObject& upo = uni.upo;
			UniformsPerView& upv = uni.upv;
			UniformsPerFrame& upf = uni.upf;

			// assign textures and uniforms
			active_shader->setVec3("view_pos", active_scene->cameras[0].position);
			active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

			active_shader->setInt("material.texture_diffuse1", 0);
			active_shader->setInt("material.texture_specular1", 1);
			active_shader->setInt("material.texture_emissive1", 2);
			active_shader->setFloat("material.emission_factor", ss.emission_factor);

			// set ligt parameters
			setDirectionalLightParameters(uni);
			setPointLightParameters(uni);
			setSpotLightParameters(uni);

			Mat4 world = model;
			active_shader->setMat4("world_matrix", world);

			float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
			active_shader->setFloat("outline_scale", maxObjectScale);
			if (active_scene->predefined_scene_elements[i].element_bools.indexed)
			{
				// Bind the index buffer
				glBindBuffer(lit_vao, lit_ebo);
				glDrawElements(GL_TRIANGLES, sizeof(Predef3D::cube_inds__pos_norm_uv), GL_UNSIGNED_INT, 0);
			}
			else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
			{
				glDrawArrays(GL_TRIANGLES, 0, 36 / active_scene->scene_state.vertex_divider);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			clearStencil();
			glClear(GL_STENCIL_BUFFER_BIT);
		}

	}

	// ---- draw models
	// -------------------------------------------------------------------------------------
	for (int i = 0; i < active_scene->models.size(); i++)
	{

		// face culling
		if (active_scene->scene_state.model_element_bools[i].indexed)
		{
			// enable face culling 
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
			glFrontFace(GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		std::string shader_name = "multiplelights";
		this->active_shader = shaders.at(shader_name);
		// activate shader
		(*active_shader).use();
		// light uniforms
		const SceneState& ss = active_scene->scene_state;
		UniformsPerObject& upo = uni.upo;
		UniformsPerView& upv = uni.upv;
		UniformsPerFrame& upf = uni.upf;

		// assign textures and uniforms
		active_shader->setVec3("view_pos", active_scene->cameras[0].position);
		active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

		active_shader->setInt("material.texture_diffuse1", 0);
		active_shader->setInt("material.texture_specular1", 1);
		active_shader->setInt("material.texture_emissive1", 2);
		active_shader->setFloat("material.emission_factor", ss.emission_factor);

		// set ligt parameters
		setDirectionalLightParameters(uni);
		setPointLightParameters(uni);
		setSpotLightParameters(uni);

		Mat4 world = mat_utils::identity4();
		active_shader->setMat4("world_matrix", world);

		float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
		active_shader->setFloat("outline_scale", maxObjectScale);

		std::vector<ElementBools> bools = active_scene->scene_state.model_element_bools;
		if (bools[i].stencil_testing) { disableStencil(); }
		active_scene->models[i].draw(*active_shader);
		if (bools[i].stencil_testing) { 
			enableStencil(); 
			this->active_shader = shaders.at("stenciltesting02");
			(*active_shader).use();
			// light uniforms
			const SceneState& ss = active_scene->scene_state;
			UniformsPerObject& upo = uni.upo;
			UniformsPerView& upv = uni.upv;
			UniformsPerFrame& upf = uni.upf;

			// assign textures and uniforms
			active_shader->setVec3("view_pos", active_scene->cameras[0].position);
			active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

			active_shader->setInt("material.texture_diffuse1", 0);
			active_shader->setInt("material.texture_specular1", 1);
			active_shader->setInt("material.texture_emissive1", 2);
			active_shader->setFloat("material.emission_factor", ss.emission_factor);

			// set ligt parameters
			setDirectionalLightParameters(uni);
			setPointLightParameters(uni);
			setSpotLightParameters(uni);

			Mat4 world = mat_utils::identity4();
			active_shader->setMat4("world_matrix", world);

			float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
			active_shader->setFloat("outline_scale", maxObjectScale);
			active_scene->models[i].draw(*active_shader);
			clearStencil();
			glClear(GL_STENCIL_BUFFER_BIT);
		}
	}

	// 3.4. framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	this->active_shader = shaders.at("framebuffer");
	(*active_shader).use();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vertex_arrays[0]);
	glBindTexture(GL_TEXTURE_2D, framebuffer_color_texture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Application::setPresetMaterial(const Material& material)
{
	active_shader->setVec3("material.specular", material.specular);
	active_shader->setVec3("material.diffuse", material.diffuse);
	active_shader->setFloat("material.shininess", material.shininess * 128.0f);
	//active_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	//active_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	//active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	//active_shader->setFloat("material.shininess", 32.0f);
}

void Application::setMaterial(const Material& material)
{
	active_shader->setVec3("material.specular", material.specular);
	active_shader->setInt("material.diffuse_map", 0);
	active_shader->setFloat("material.shininess", material.shininess);
}

void Application::updateScene()
{
	// update time
	SceneState& scene_state = active_scene->scene_state;
	scene_state.time = (float)glfwGetTime();
	scene_state.delta_time = scene_state.time - scene_state.last_frame_time;
	scene_state.last_frame_time = scene_state.time;
	// animate?
	if (!scene_state.animate)
		return;
	active_scene->update();
}

void Application::resetCamera()
{
	Camera& camera = active_scene->cameras[0];
	//camera.position = Vec3(0.0f, 0.0f, 5.0f);
	camera.position = Vec3(-12.0f, 10.0f, 12.0f);
	const Vec3 k_camera_target_point = Vec3(0.0f, 0.0f, 0.0f);
	camera.lookAtTarget(k_camera_target_point);
}

void setTriangleLightColorShiftByTime(Vec3& light_color, Vec3& light_specular, const float& time)
{
	float color_state = ((sin(time * 0.5f) + 1.0f) * 0.5f) * 6.0f;
	float r, g, b;

	if (color_state < 1.0f)
	{
		r = 1.0f;
		g = color_state;
		b = 0.0f;
	}
	else if (color_state < 2.0f)
	{
		r = 2.0f - color_state;
		g = 1.0f;
		b = 0.0f;
	}
	else if (color_state < 3.0f)
	{
		r = 0.0f;
		g = 1.0f;
		b = color_state - 2.0f;
	}
	else if (color_state < 4.0f)
	{
		r = 0.0f;
		g = 4.0f - color_state;
		b = 1.0f;
	}
	else if (color_state < 5.0f)
	{
		r = color_state - 4.0f;
		g = 0.0f;
		b = 1.0f;
	}
	else
	{
		r = 1.0f;
		g = 0.0f;
		b = 6.0f - color_state;
	}
	light_color = Vec3(r, g, b);
	light_specular = light_color * 0.5f;
}

void drawObjToScr(const unsigned int& shader, const unsigned int& vao)
{
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
#endif