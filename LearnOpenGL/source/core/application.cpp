// ------------------------------------------------------------------------------------------------
// ----- Notes
// ------------------------------------------------------------------------------------------------
/*
Version: 0.32
https://learnopengl.com/Getting-started/Coordinate-Systems
Coordinate system end.
Continue: Camera

*/
#if 1
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/test/basic.h"					// kendi test header dosyam
#include "../headers/utils/utilities.h"				// config dosyasi okuma ve cekmeye dair kendi kutuphanem
#include "../headers/data/data.h"					// opengl in cizecegi verilerin tutuldugu dosyalar
#include "../headers/events/events.h"				// opengl in cizecegi verilerin tutuldugu dosyalar
#include "../headers/abstract/application.h"		
#include "../headers/abstract/Camera.h"	
#include "../headers/abstract/shader.h"				// shader objesi olusturmaya dair veritipi
#include "../headers/abstract/uniforms.h"			// shader objesi olusturmaya dair veritipi
#include "../headers/maps/shaders.h"				// shaderlarin isimleri ve dosya konumlarinin mapleri
#include "../headers/core/openGL.h"					// ana calisma dosyasi

#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>			// opengl hardware adaptor !glfw den once
#include <iostream>				// cout / cin icin lazim
#include <string>				// standart string kutuphanesi
#include <unordered_map>		// dictionary / map kutuphanesi
#include <cmath>     			//

// imgui
#include "../../libs/imgui-1.89.5/imgui.h"
#include "../../libs/imgui-1.89.5/imgui_impl_glfw.h"
#include "../../libs/imgui-1.89.5/imgui_impl_opengl3.h"

// glm
#include <glm/vec3.hpp>						// glm::vec3
#include <glm/vec4.hpp>						// glm::vec4
#include <glm/mat4x4.hpp>					// glm::mat4
#include <glm/ext/matrix_transform.hpp>		// glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp>	// glm::perspective
#include <glm/ext/scalar_constants.hpp>		// glm::pi


// self keywords
// -----------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;

// global, constant variables
// -----------------------------------
constexpr unsigned int kg_error_buffer_size = 512;
Application* gp_app;

// ------------------------------------------------------------------------------------------------
// ----- Functions Definitions
// ------------------------------------------------------------------------------------------------

Mat4 Camera::calcViewMatrix(const Vec3& new_pos, const Vec3& new_tar, const Vec3& world_up)
{
	position = new_pos;
	up = world_up;
	direction = (new_pos - new_tar).normalized();
	right = cross3d(world_up, direction).normalized();
	up = cross3d(direction, right).normalized();
	float rx = right.x;
	float ry = right.y;
	float rz = right.z;
	float ux = world_up.x;
	float uy = world_up.y;
	float uz = world_up.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;
	float px = position.x;
	float py = position.y;
	float pz = position.z;
	return Mat4(
		rx, ry, rz, 0,
		ux, uy, uz, 0,
		dx, dy, dz, 0,
		0, 0, 0, 1
	) *
		Mat4(
			1, 0, 0, -px,
			0, 1, 0, -py,
			0, 0, 1, -pz,
			0, 0, 0, 1
		);
}

Mat4 Camera::calcViewMatrix()
{
	float rx = right.x;
	float ry = right.y;
	float rz = right.z;
	float ux = up.x;
	float uy = up.y;
	float uz = up.z;
	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;
	float px = position.x;
	float py = position.y;
	float pz = position.z;
	return Mat4(
		rx, ry, rz, 0,
		ux, uy, uz, 0,
		dx, dy, dz, 0,
		0, 0, 0, 1
	) *
		Mat4(
			1, 0, 0, -px,
			0, 1, 0, -py,
			0, 0, 1, -pz,
			0, 0, 0, 1
		);
}

void Application::handleMouseEvent(GLFWwindow* window, double xpos, double ypos)
{
	WindowState& ws = window_state;
	if (ws.b_first_mouse)
	{
		ws.mouse_x = xpos;
		ws.mouse_y = ypos;
		ws.b_first_mouse = false;
	}

	float xoffset = xpos - ws.mouse_x;
	float yoffset = ypos - ws.mouse_y; // reversed since y-coordinates range from bottom to top
	ws.mouse_x = xpos;
	ws.mouse_y = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Camera& cam = scene_state.camera;
	cam.pitch += yoffset;
	cam.yaw += xoffset;

	// limiter
	if (cam.pitch > 89.0f)
		cam.pitch = 89.0f;
	if (cam.pitch < -89.0f)
		cam.pitch = -89.0f;

	cam.calcAxes(cam.pitch, cam.yaw, world_up);
	
}

void Application::handleScrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{
	float& fov = scene_state.fov;
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}

void Camera::calcAxes(const float& pitch, const float& yaw, const Vec3& world_up)
{
	Vec3 new_dir;
	new_dir.x = cos(radian(yaw)) * cos(radian(pitch));
	new_dir.y = sin(radian(pitch));
	new_dir.z = sin(radian(yaw)) * cos(radian(pitch));
	direction = new_dir.normalized();
	right = cross3d(world_up, direction).normalized();
	up = cross3d(direction, right).normalized();
}

bool Application::initialize(k_configType& config)
{
	gp_app = this;
	const unsigned int k_scr_width = std::stoul(config.at("scr").at("width"));
	const unsigned int k_scr_height = std::stoul(config.at("scr").at("height"));
	const char* kp_wndw_name = config.at("scr").at("wndw_name").c_str();

	world_up = Vec3(0.0f, 1.0f, 0.0f);

	initWindowSystem(k_scr_width, k_scr_height, kp_wndw_name);
	const char* glsl_version = "#version 330";

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	initUISystem(glsl_version);

	// Our state
	this->clear_color = Vec4(
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		1.00f
	);
}

bool Application::load(k_configType& config)
{
	loadConfig(config);

	loadSceneData(config);

	loadShaders();

	loadTextures();

	loadMeshData();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, callbackMouse); // todo initialize
	glfwSetScrollCallback(window, callbackScroll);
	window_state.b_first_mouse = true;
	window_state.mouse_x = std::stoul(config.at("scr").at("width")) / 2.0f;
	window_state.mouse_y = std::stoul(config.at("scr").at("height")) / 2.0f;

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
	ss.near = 1.0f;
	ss.far = 100.0f;
	ss.fov = 45.0f;
	ss.last_frame_time = 0.0f;

	Camera& cam = ss.camera;
	cam.pitch	= 0.0f;
	cam.yaw		= 90.0f;

	// animation
	scene_state.b_animate = true;

	// cube positions 
	scene_state.obj_positions = {
		Vec3(2.0f,  5.0f, -15.0f),
		Vec3(-1.5f, -2.2f, -2.5f),
		Vec3(-3.8f, -2.0f, -12.3f),
		Vec3(2.4f, -0.4f, -3.5f),
		Vec3(-1.7f,  3.0f, -7.5f),
		Vec3(1.3f, -2.0f, -2.5f),
		Vec3(1.5f,  2.0f, -2.5f),
		Vec3(1.5f,  0.2f, -1.5f),
		Vec3(-1.3f,  1.0f, -1.5f),
		Vec3(0.0f,  0.0f,  0.0f)
	};

	// init camera wuth default values
	const Vec3 k_position = Vec3(0.0f, 0.0f, 5.0f);
	const Vec3 k_target_point = Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 k_world_up = world_up;
	scene_state.camera.calcViewMatrix(k_position, k_target_point, k_world_up);
}

void Application::loadTextures()
{
	// texture
	setVerticalFlipMode(true);
	texture1 = createTexture("data/textures/container.jpg", 2);
	texture2 = createTexture("data/textures/awesomeface.png");
}

void Application::loadShaders()
{
	// build and compile our shader program
	this->active_shader = new Shader("shaders/3d_vrtxShader.glsl", "shaders/3d_fragShader.glsl");
}

void Application::loadMeshData()
{
	// create vertex array object and vertex buffer object
	glGenVertexArrays(buffer_count, VAOs);
	glGenBuffers(buffer_count, VBOs); // :: memory alani olusturuyor
	glGenBuffers(buffer_count, EBOs); // :: ebo icin memory

	// binding buffers
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::cubeVrts), ObjToDraw::cubeVrts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ObjToDraw::squareInds), ObjToDraw::squareInds, GL_STATIC_DRAW);


	// linking vertex attributes
	// --------------------------       
	// 1. parameter specifies which vertex attribute we want to configure  | location of position
	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
	// 3. parameter specifies type of data gl_float
	// 4. parameter specifies if you want to data to be normalized
	// 5. known as stride space between consequtive vertex attributes
	// 6. void this is the offset where the position data begins in the buffer

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
	// clean new_up
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
	uni_obj.mixValue = 0.2f;

	// render loop 
	// --------------------------
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, uni_obj, scene_state);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		scene_state.aspect_ratio = float(w) / float(h);

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
	delete active_shader;
	glDeleteVertexArrays(buffer_count, VAOs);
	glDeleteBuffers(buffer_count, VBOs);
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
	//// 2. Show a simple window that we create ourselves.We use a Begin / End pair to create a named window.
	//{
	//	static float f = 0.0f;
	//	static int counter = 0;
	//	static const char* txt_aspectRatio = "Aspect Ratio: ";

	//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text(txt_aspectRatio);               // Display some text (you can use a format strings too)
	//	ImGui::Checkbox("Animate Y", &this->ui_state.animate);      // Edit bools storing our window open/close state
	//	//ImGui::Checkbox("Another Window", &show_another_window);

	//	ImGui::SliderInt("Width", &this->ui_state.width, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::SliderInt("Height", &this->ui_state.height, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::SliderFloat("Near", &this->ui_state.near, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::SliderFloat("Far", &this->ui_state.far, 0.0f, 1000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::SliderFloat("Top/Bottom", &this->ui_state.top, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::SliderFloat("Left/Right", &this->ui_state.left, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::ColorEdit3("clear color", (this->ui_state.clear_color.toFloatPointer()));		// Edit 3 floats representing a color

	//	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//	//	counter++;
	//	//ImGui::SameLine();
	//	//ImGui::Text("counter = %d", counter);

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	//	ImGui::End();
	//}
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
	// todo: draw parameters structa topla | 
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	(*active_shader).use(); // don't forget to activate/use the shader before setting uniforms!
	active_shader->setInt("texture2", 1);

	// draw wireframe or not
	if (b_wireframe_mode) // todo: deserialize config
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glEnable(GL_DEPTH_TEST);
	// render clear screen
	// ------------------------------
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// create transformations
	SceneState& ss = scene_state;
	uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f)) * mat_utils::rotationXYZ(ss.time, Vec3(1.0f, 1.0f, 1.0f).normalized());
	uni_view.view_matrix = scene_state.camera.calcViewMatrix();
	uni_view.projection_matrix = mat_utils::projectPerspective(radian(ss.fov), ss.aspect_ratio, ss.near, ss.far);

	// set the texture mix value in the shader
	active_shader->setFloat("mixValue", uni_obj.mixValue);
	//ourShader->setMat4("world_matrix", uni_obj.world_matrix);
	active_shader->setMat4("view_matrix", uni_view.view_matrix);
	active_shader->setMat4("projection_matrix", uni_view.projection_matrix);

	// 
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	// draw scene
	active_shader->use();
	glBindVertexArray(VAOs[0]);

	// assign texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	for (unsigned int ii = 0; ii < 10; ii++)
	{
		float angle = 20.0f * ii;
		Mat4 model = mat_utils::translation(scene_state.obj_positions[ii]) * mat_utils::rotationXYZ(scene_state.time + angle, Vec3(1.0f, 1.0f, 1.0f).normalized()); //*mat_utils::scale(scale);
		active_shader->setMat4("world_matrix", model);
		//model = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Application::updateScene()
{
	// update time
	if (scene_state.b_animate)
	{
		scene_state.time = (float)glfwGetTime();
	}
	else
	{
		scene_state.time = 0;
	}
	scene_state.delta_time = scene_state.time - scene_state.last_frame_time;
	scene_state.last_frame_time = scene_state.time;

	// camera position
	//const float radius = 10.0f;
	//scene_state.camera.position.x = sin(scene_state.time) * radius;
	//scene_state.camera.position.z = cos(scene_state.time) * radius;
	//int num_obj = scene_state.obj_positions.size();

	////scene_state.camera.target = scene_state.obj_positions[(int)(scene_state.time) % num_obj];
	//scene_state.camera.new_dir = (scene_state.camera.position - scene_state.camera.target).normalized();
	//Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
	//scene_state.camera.right = cross3d(up, scene_state.camera.new_dir);
	//scene_state.camera.up = cross3d(scene_state.camera.new_dir, scene_state.camera.right);
}

void drawObjToScr(const unsigned int& shader, const unsigned int& vao)
{
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
#endif