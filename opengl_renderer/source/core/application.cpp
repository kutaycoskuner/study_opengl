// ------------------------------------------------------------------------------------------------
// ----- Notes
// ------------------------------------------------------------------------------------------------
/*
	I will write some stuff here someday.
	...
*/
#if 1
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
// imgui
#include "../../libs/imgui-1.89.5/imgui.h"
#include "../../libs/imgui-1.89.5/imgui_impl_glfw.h"
#include "../../libs/imgui-1.89.5/imgui_impl_opengl3.h"

#include "../headers/test/basic.h"					// project start basic test
#include "../headers/utils/utilities.h"				// self written utilities
#include "../headers/data/data.h"					// data headers ex. model vertices
#include "../headers/events/events.h"				// window, mouse-, keyboard input events
#include "../headers/abstract/application.h"	
#include "../headers/abstract/camera.h"				
#include "../headers/abstract/shader.h"				
#include "../headers/abstract/material.h"				
#include "../headers/abstract/uniforms.h"	
#include "../headers/abstract/model.h"		
#include "../headers/maps/shaders.h"			
#include "../headers/core/opengl.h"					

#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>			// opengl hardware adaptor before glfw
#include <iostream>				
#include <string>				
#include <unordered_map>		
#include <cmath>     			

#include <memory>
#include <filesystem>

// ------------------------------------------------------------------------------------------------
// self keywords
// ------------------------------------------------------------------------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;
// -----------------------------------
// global, constant variables
// -----------------------------------
constexpr unsigned int kg_error_buffer_size = 512;
Application* gp_app;
const Vec3	Application::world_up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3	Application::world_origin = Vec3(0.0f, 0.0f, 0.0f);
bool		Application::toggle_mouselock = true;

// ------------------------------------------------------------------------------------------------
// ----- Functions Definitions
// ------------------------------------------------------------------------------------------------
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
	SceneState& ss = scene_state;

	// ----- scene object transforms init
	// --------------------------------------------------------------------------------------
	ss.obj_rotation_angle_y = 0.0f;

	// ----- camera
	// --------------------------------------------------------------------------------------
	Camera& cam = ss.camera;

	ss.camera.near = 1.0f;
	ss.camera.far = 100.0f;
	ss.camera.fov = 45.0f;
	
	ss.camera.rotation_sensitivity = 0.02f;

	resetCamera(ss.camera);

	// ----- lights
	// --------------------------------------------------------------------------------------
	// directional
	int num_dlights = 1;
	int num_plights = 3;
	int num_slights = 1;
	for (int ii = 0; ii < num_dlights; ii++)
	{
		ss.directional_lights.emplace_back();
		//ss.directional_lights[ii].direction	= Vec3(-1.0f, -0.5f, -1.0f);
		ss.directional_lights[ii].direction = Vec3(-1.0f, -0.8f, -0.2f);
		ss.directional_lights[ii].diffuse = Vec3(0.8f, 0.8f, 0.8f);
		ss.directional_lights[ii].ambient = Vec3(0.08f, .08f, 0.08f);
		ss.directional_lights[ii].specular = Vec3(1.0f, 1.0f, 1.0f);
	}
	// point
	for (int ii = 0; ii < num_plights; ii++)
	{
		ss.point_lights.emplace_back();
		ss.point_lights[ii].position = Vec3(0.0f, 0.0f, 0.0f);
		ss.point_lights[ii].ambient = Vec3(0.05f, 0.05f, 0.05f);
		ss.point_lights[ii].diffuse = Vec3(0.8f, 0.8f, 0.8f);
		ss.point_lights[ii].specular = Vec3(1.0f, 1.0f, 1.0f);
		ss.point_lights[ii].constant = 1.0f;
		ss.point_lights[ii].linear = 0.09f;
		ss.point_lights[ii].quadratic = 0.032f;
	}
	// spot
	for (int ii = 0; ii < num_slights; ii++)
	{
		ss.spot_lights.emplace_back();
		ss.spot_lights[ii].position = Vec3(0.0f, 15.0f, 0.0f);
		ss.spot_lights[ii].direction = Vec3(0.0f, -1.0f, 0.0f);
		ss.spot_lights[ii].ambient = Vec3(0.02f, 0.02f, 0.02f);
		ss.spot_lights[ii].diffuse = Vec3(0.8f, 0.8f, 0.0f);
		ss.spot_lights[ii].specular = Vec3(1.0f, 1.0f, 1.0f);
		ss.spot_lights[ii].constant = 1.0f;
		ss.spot_lights[ii].linear = 0.09f;
		ss.spot_lights[ii].quadratic = 0.032f;
		ss.spot_lights[ii].cutoff = cos(radian(27.5f));
		ss.spot_lights[ii].outer_cutoff = cos(radian(30.0f));
	}

	// animation
	ss.animate = false;
	ss.angle_multiplier = 0.0f;
	ss.last_frame_time = 0.0f;
	ss.emission_factor = 0.0f;

	// ui
	ss.b_toggleui = false;

	// ----- models
	std::vector<const char*> model_paths = {
		"data/models/testobject0_frustum/testobject.obj",
		"data/models/testobject1_dodecahedron/testobject.obj",
		"data/models/testobject2_sphere/testobject.obj",
		"data/models/testobject3_cube0/testobject.obj",
		"data/models/testobject4_cube1/testobject.obj",
		"data/models/testobject5_cube2/testobject.obj",
		"data/models/testobject6_cube3/testobject.obj",
		"data/models/testobject7_torus/testobject.obj",
		"data/models/testobject8_mine/testobject.obj",
		"data/models/testobject9_cylinder/testobject.obj",
		"data/models/testobject10_suzanne/testobject.obj",
		"data/models/testobject11_cone/testobject.obj"
		//"data/models/testobjects_by_kutaycoskuner/testobjects.obj"
	};

	//for (int ii = 0; ii < model_paths.size(); ii++)
	//{
	//	Model ourModel(model_paths[ii]);
	//	ss.models.push_back(Model(ourModel));
	//}


	// cube positions 
	ss.obj_positions = ObjWorldPositions::obj_world_positions;
}

void Application::loadTextures()
{
	// texture
	setVerticalFlipMode(true);
	
	//texture1 = createTexture("data/textures/container.jpg", 2);
	//texture2 = createTexture("data/textures/awesomeface.png");
	
	vec_texture_diffuse.push_back(createTexture("data/textures/2k_test_diffuse_mid.jpg"));	// 0
	vec_texture_specular.push_back(createTexture("data/textures/2k_test_specular.jpg"));
	vec_texture_emission.push_back(createTexture("data/textures/2k_test_emission.jpg"));

	vec_texture_diffuse.push_back(createTexture("data/textures/container.jpg"));	// 1

	
	texture_diffuse = createTexture("data/textures/2k_test_diffuse_mid.jpg");
	texture_specular = createTexture("data/textures/2k_test_specular.jpg");
	texture_emission = createTexture("data/textures/2k_test_emission.jpg");


	
	//textures_diffuse[0] = createTexture("data/textures/2k_test_diffuse_mid.jpg");
	//textures_diffuse[1] = createTexture("data/textures/blending_transparent_window_blue.png");
	//vec_texture_diffuse.push_back(createTexture("data/textures/container2_diffuse.png"));
	//vec_texture_specular.push_back(createTexture("data/textures/container2_specular.png"));

	texture_ground_diffuse = createTexture("data/textures/800_blackchecker.png");
	texture_ground_specular = createTexture("data/textures/800_checker_specular_regions.png");
	texture_ground_emission = createTexture("data/textures/800_checker_emission_regions.png");
}

void Application::loadShaders()
{
	// build and compile our shader program
	// todo: butun shaderlari yukle daha sonra aktifi sec | bu 3d pipeline ini bozuyor
	const std::vector<std::vector<std::string>> shader_paths = ShaderPaths::shader_paths;

	for (const std::vector<std::string>& path_pair : shader_paths)
	{
		const std::string vrtx = path_pair[0];
		const std::string frag = path_pair[1];
		// get between / and _ for key
		std::vector<std::string> path_parts = str_utils::split(vrtx, "_");
		std::string left_trimmed_key = path_parts[0];
		//path_parts = str_utils::split(left_trimmed_key, "/");
		path_parts = str_utils::split(left_trimmed_key, ".");
		const std::string name = path_parts.back();
		//
		shaders[name] = std::make_shared<Shader>(vrtx, frag);
	}

}

void Application::loadMeshData()
{
	// create vertex array object and vertex buffer object
	glGenVertexArrays(buffer_count, vaos);
	glGenBuffers(buffer_count, vbos); // :: memory alani olusturuyor
	glGenBuffers(buffer_count, ebos); // :: ebo icin memory


	// binding buffers
	glBindVertexArray(vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::cube_vrts__pos_uv), ObjToDraw::cube_vrts__pos_uv, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ObjToDraw::square_inds), ObjToDraw::square_inds, GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::cube_vrts__pos_norm_uv), ObjToDraw::cube_vrts__pos_norm_uv, GL_STATIC_DRAW);
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
	//generateBuffer(lit_vao, lit_vbo, ObjToDraw::cube_vrts__pos_uv, 5, 1, 0);

	glGenBuffers(1, &lit_ebo); // :: ebo icin memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lit_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ObjToDraw::cube_inds__pos_norm_uv), ObjToDraw::cube_inds__pos_norm_uv, GL_STATIC_DRAW);


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

	// render loop 
	// --------------------------



	while (!glfwWindowShouldClose(window))
	{
		processInput(window, uni_obj, scene_state);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		SceneState& ss = scene_state;
		ss.camera.aspect_ratio = float(w) / float(h);

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	glDeleteVertexArrays(buffer_count, vaos);
	glDeleteBuffers(buffer_count, vbos);
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
	if (!scene_state.b_toggleui)
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

		ImGui::SliderFloat("Camera Pos X", &this->scene_state.camera.position.x, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pos Y", &this->scene_state.camera.position.y, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pos Z", &this->scene_state.camera.position.z, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Yaw  ", &this->scene_state.camera.yaw_rad	, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("Camera Pitch", &this->scene_state.camera.pitch_rad	, -10.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		const char* animate_button_name =
				this->scene_state.animate ? "Stop" : "Play";
		if (ImGui::Button(animate_button_name))                    
			this->scene_state.animate = !this->scene_state.animate;
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

void Application::drawScene(Uniforms& uni)
{
	// draw wireframe or not
	if (b_wireframe_mode) // todo: deserialize config
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// enable this to avoid awkward whatever front rendering
	glEnable(GL_DEPTH_TEST);
	
	// enable stencil test
	glEnable(GL_STENCIL_TEST);
	
	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// enable face culling 
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

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
	//multipleLightsScene(uni);
	//importModelScene(uni);
	//testObjectsScene(uni);
	//faceCullingTestScene(uni);
	frameBuffersTestScene(uni);
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
	SceneState& ss = scene_state;
	scene_state.time = (float)glfwGetTime();
	scene_state.delta_time = scene_state.time - scene_state.last_frame_time;
	scene_state.last_frame_time = scene_state.time;

	// animate?
	if (!scene_state.animate)
		return;

	//// animation
	//if (scene_state.b_animate)
	//{
	//	scene_state.animation_time = scene_state.time;
	//}
	//else
	//{
	//	scene_state.animation_time = 0.0f;
	//}

	// camera position
	// --------------------------------------------------------------------------------------
	//float camera_multiplier = 16.0f;
	//ss.camera.position.x = -camera_multiplier * sin(ss.time);
	//ss.camera.position.z =  camera_multiplier  * cos(ss.time);
	//ss.camera.lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));

	// rotate obj
	// --------------------------------------------------------------------------------------
	ss.obj_rotation_angle_y = fmod(ss.time * 50.0f, 360.0f);

	// shifting lights
	// --------------------------------------------------------------------------------------
	float distance_multiplier = 3.0f;
	for (int ii = 0; ii < ss.point_lights.size(); ii++)
	{
		// change light position
		ss.point_lights[ii].position = Vec3(
			distance_multiplier * cos(ss.time + 2 * PI / 3.0f * ii),
			4.0f,
			distance_multiplier * sin(ss.time + 2 * PI / 3.0f * ii))
			;

		// change light color
		float change_key = ss.time + ii;
		setTriangleLightColorShiftByTime(ss.point_lights[ii].diffuse, ss.point_lights[ii].specular, change_key);
	}

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	ss.emission_factor = (sin(ss.time) + 1) * 0.5;

	// ui changes
	// --------------------------------------------------------------------------------------
	//ss.light.direction = ui_state.spotlight_dir;

}

void Application::resetCamera(Camera& camera)
{
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