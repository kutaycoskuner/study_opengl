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

// constant variables
// -----------------------------------
constexpr unsigned int ERROR_BUFFER_SIZE = 512;


// ------------------------------------------------------------------------------------------------
// ----- Functions Definitions
// ------------------------------------------------------------------------------------------------
bool Application::Initialize(c_configType& config)
{
	// ------------------------------------------------------------------------------------------------
	//  Settings
	// ------------------------------------------------------------------------------------------------
	const unsigned int SCR_WIDTH = std::stoul(config.at("scr").at("width"));
	const unsigned int SCR_HEIGHT = std::stoul(config.at("scr").at("height"));
	const char* WNDW_NAME = config.at("scr").at("wndw_name").c_str();

	// ------------------------------------------------------------------------------------------------
	//  GLFW
	// ------------------------------------------------------------------------------------------------
	glfwInit();
	// :: first param what option we want to configure; second option is value we set.
	// :: 3 means we are explicitly using core profile. version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//

	// :: if apple
	// --------------------------
	const char* glsl_version = "#version 330";
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------------
	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WNDW_NAME, NULL, NULL);
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

	// glad: load all OpenGL function pointers
	// --------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ------------------------------------------------------------------------------------------------
	//  IMGUI Init
	// ------------------------------------------------------------------------------------------------
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

	// Our state
	this->clear_color = Vec4(
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		scaleByteToZeroOne(std::stoul(config.at("colors").at("bg"))),
		1.00f
	);
}

bool Application::Load(c_configType& config)
{
	// todo: shaders, meshdata, texture

	// load config states
	this->b_isWireframeMode = config.at("settings").at("is_wireframeMode") == "true";

	// load shaders
	//std::unordered_map<std::string, ShaderCompileDesc> shaders = loadShaders();
	//const char* vrtx_shader_src = shaders.at("vrtxShader").content.c_str();
	//const char* frag_shader_src = shaders.at("fragShader").content.c_str();

	// build and compile our shader zprogram
// ------------------------------------
	this->ourShader = new Shader("shaders/3d_vrtxShader.glsl", "shaders/3d_fragShader.glsl");
	//unsigned int vrtxShader = compileShader(vrtx_shader_src, GL_VERTEX_SHADER);
	//unsigned int fragShader = compileShader(frag_shader_src, GL_FRAGMENT_SHADER);

	// --------------------------
	//unsigned int shaderProgram = linkShaderProgram({ vrtxShader, fragShader });

	// --------------------------
	// texture
	setVerticalFlipMode(true);
	texture1 = createTexture("data/textures/container.jpg", 2);
	texture2 = createTexture("data/textures/awesomeface.png");

	// --------------------------
	//deleteCompiledShaders({ vrtxShader, fragShader });

	// create vertex array object and vertex buffer object
	// --------------------------
	glGenVertexArrays(buffer_count, VAOs);
	glGenBuffers(buffer_count, VBOs); // :: memory alani olusturuyor
	glGenBuffers(buffer_count, &EBO); // :: ebo icin memory

	// binding buffers
	// ----- texture square
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::cubeVrts), ObjToDraw::cubeVrts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ObjToDraw::squareInds), ObjToDraw::squareInds, GL_STATIC_DRAW);


	// att: pos
	unsigned int stride = 5;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// att: color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// att: texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//// ----- texture square end

	// attempt :: coordinate lines 
	//glBindVertexArray(VAOs[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::x_axis), ObjToDraw::x_axis, GL_STATIC_DRAW);
	//glBindVertexArray(VAOs[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::y_axis), ObjToDraw::y_axis, GL_STATIC_DRAW);
	//// att: pos
	//unsigned int stride = 6;
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// att: color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// linking vertex attributes
	// --------------------------       
	// 1. parameter specifies which vertex attribute we want to configure  | location of position
	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
	// 3. parameter specifies type of data gl_float
	// 4. parameter specifies if you want to data to be normalized
	// 5. known as stride space between consequtive vertex attributes
	// 6. void this is the offset where the position data begins in the buffer

	// clean up
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 1;

}

void Application::MainLoop()
{
	// uniform variables according to update frequency
	UniformsPerObject uni_obj;
	UniformsPerView uni_view;
	UniformsPerFrame uni_frame;

	// initial values for the uniforms
	uni_obj.world_matrix = mat_utils::identity4();
	uni_view.view_matrix = mat_utils::identity4();
	uni_view.projection_matrix = mat_utils::identity4();
	uni_obj.mixValue = 0.2f;

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	(*ourShader).use(); // don't forget to activate/use the shader before setting uniforms!
	ourShader->setInt("texture2", 1);

	// states
	float speed = PI / 4;
	float top = 0.5f, left = -0.5f, near = 0.1f, far = 100.0f;

	bool animate = true;

	// draw wireframe or not
	if (b_isWireframeMode) // todo: deserialize config
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glEnable(GL_DEPTH_TEST);

	// cube positions 
	Vec3 cubePositions[] = {
		Vec3(2.0f,  5.0f, -15.0f),
		Vec3(-1.5f, -2.2f, -2.5f),
		Vec3(-3.8f, -2.0f, -12.3f),
		Vec3(2.4f, -0.4f, -3.5f),
		Vec3(-1.7f,  3.0f, -7.5f),
		Vec3(1.3f, -2.0f, -2.5f),
		Vec3(1.5f,  2.0f, -2.5f),
		Vec3(1.5f,  0.2f, -1.5f),
		Vec3(-1.3f,  1.0f, -1.5f),
		Vec3(0.0f,  0.0f,  -3.0f)
	};

	// render loop 
	// --------------------------
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, uni_obj);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		float aspect_ratio = float(w) / float(h);

		// Start the Dear ImGui frame
		updateUI();

		// render clear screen
		// ------------------------------
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update the uniform color
		// ------------------------------
		float time_value;
		if (animate)
		{
			time_value = glfwGetTime();
		}
		else
		{
			time_value = 0;
		}
		float scale = (sinf(time_value) + 1.0f) / 4 + 0.5f; // 0 1 0 -1 | 1 2 1 0

		// create transformations
		uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f)) * mat_utils::rotationXYZ(time_value, Vec3(1.0f, 1.0f, 1.0f).normalized());
		uni_view.view_matrix = mat_utils::translation(Vec3(0.0f, 0.0f, -3.0f)); //*mat_utils::scale(scale);
		uni_view.projection_matrix = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);

		// set the texture mix value in the shader
		ourShader->setFloat("mixValue", uni_obj.mixValue);
		//ourShader->setMat4("world_matrix", uni_obj.world_matrix);
		ourShader->setMat4("view_matrix", uni_view.view_matrix);
		ourShader->setMat4("projection_matrix", uni_view.projection_matrix);

		// 
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		// draw scene
		ourShader->use();
		glBindVertexArray(VAOs[0]);

		// assign texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		for (unsigned int ii = 0; ii < 10; ii++)
		{
			float angle = 20.0f * ii;
			Mat4 model = mat_utils::translation(cubePositions[ii]) * mat_utils::rotationXYZ(time_value + angle, Vec3(1.0f, 1.0f, 1.0f).normalized()); //*mat_utils::scale(scale);
			ourShader->setMat4("world_matrix", model);
			//model = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		drawUI();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Unload()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	delete ourShader;
	glDeleteVertexArrays(buffer_count, VAOs);
	glDeleteBuffers(buffer_count, VBOs);
}

int Application::Exit()
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

void Application::drawScene() {}

void drawObjToScr(const unsigned int& shader, const unsigned int& vao)
{
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
#endif