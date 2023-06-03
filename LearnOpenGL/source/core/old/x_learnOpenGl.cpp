//// ------------------------------------------------------------------------------------------------
//// ----- Notes
//// ------------------------------------------------------------------------------------------------
///*
//Version: 0.21
//https://learnopengl.com/Getting-started/Shaders
//Shaders has ended.
//
//*/
//#if 0
//// ------------------------------------------------------------------------------------------------
//// ----- Libraries
//// ------------------------------------------------------------------------------------------------
//#include "../headers/test/basic.h"					// kendi test header dosyam
//#include "../headers/utils/utilities.h"			// config dosyasi okuma ve cekmeye dair kendi kutuphanem
//#include "../headers/data/data.h"					// opengl in cizecegi verilerin tutuldugu dosyalar
//#include "../headers/abstract/shader.h"			// shader objesi olusturmaya dair veritipi
//#include "../headers/maps/shaders.h"			// shaderlarin isimleri ve dosya konumlarinin mapleri
//#include "../headers/core/openGL.h"					// ana calisma dosyasi
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "../libs/stb_image.h"
//
//#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
//#include <glad/glad.h>			// opengl hardware adaptor !glfw den once
//#include <iostream>				// cout / cin icin lazim
//#include <string>				// standart string kutuphanesi
//#include<unordered_map>			// dictionary / map kutuphanesi
//
//// self keywords
//// -----------------------------------
//using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
//
//// constant variables
//// -----------------------------------
//constexpr unsigned int ERROR_BUFFER_SIZE = 512;
//
//// ------------------------------------------------------------------------------------------------
//// ----- Functions Definitions
//// ------------------------------------------------------------------------------------------------
//int learnOpenGL(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& config)
//{
//	// ------------------------------------------------------------------------------------------------
//	//  Settings
//	// ------------------------------------------------------------------------------------------------
//	const unsigned int SCR_WIDTH = std::stoul(config["scr"]["width"]);
//	const unsigned int SCR_HEIGHT = std::stoul(config["scr"]["height"]);
//	const char* WNDW_NAME = config["scr"]["wndw_name"].c_str();
//
//	// load shaders
//	std::unordered_map<std::string, ShaderCompileDesc> shaders = loadShaders();
//	const char* vrtx_shader_src = shaders.at("vrtxShader").content.c_str();
//	const char* frag_shader_src = shaders.at("fragShader").content.c_str();
//	const char* frag_shader_src1 = shaders.at("fragShader_1").content.c_str();
//	const char* frag_shader_src2 = shaders.at("fragShader_2").content.c_str();
//
//	// glfw init
//	glfwInit();
//	// :: first param what option we want to configure; second option is value we set.
//	// :: 3 means we are explicitly using core profile. version 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//
//
//	// :: if apple
//	// --------------------------
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WNDW_NAME, NULL, NULL);
//	// first two params x,y in size; 3. name; 4-5 necesssary but ignore
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// resize handle
//	glfwSetFramebufferSizeCallback(window, callbackFrameBufferSize);
//
//	// glad: load all OpenGL function pointers
//	// --------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// build and compile our shader zprogram
//	// ------------------------------------
//	Shader ourShader("shaders/vrtxShader.glsl", "shaders/fragShader.glsl");
//
//	unsigned int vrtxShader = compileShader(vrtx_shader_src, GL_VERTEX_SHADER);
//	unsigned int fragShader = compileShader(frag_shader_src, GL_FRAGMENT_SHADER);
//
//	unsigned int fragShaderBlue = compileShader(frag_shader_src1, GL_FRAGMENT_SHADER);
//	unsigned int fragShaderViol = compileShader(frag_shader_src2, GL_FRAGMENT_SHADER);
//
//	// --------------------------
//	unsigned int shaderProgram = linkShaderProgram({ vrtxShader, fragShader });
//	unsigned int shaderProgramBlue = linkShaderProgram({ vrtxShader, fragShaderBlue });
//	unsigned int shaderProgramViol = linkShaderProgram({ fragShaderViol, vrtxShader });
//
//
//	// --------------------------
//	// texture
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned int texture1 = createTexture("data/textures/container.jpg");
//	unsigned int texture2 = createTexture("data/textures/awesomeface.png");
//
//	// --------------------------
//	deleteCompiledShaders({ vrtxShader, fragShader, fragShaderBlue, fragShaderViol });
//
//	// create vertex array object and vertex buffer object
//	// --------------------------
//	const unsigned int buffer_count = 1;
//	unsigned int VBO, VAO, EBO;
//	unsigned int VBOs[buffer_count], VAOs[buffer_count];
//	glGenVertexArrays(buffer_count, VAOs);
//	glGenBuffers(buffer_count, VBOs); // :: memory alani olusturuyor
//	glGenBuffers(buffer_count, &EBO); // :: ebo icin memory
//
//	// binding buffers
//	glBindVertexArray(VAOs[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjToDraw::squareVrts), ObjToDraw::squareVrts, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ObjToDraw::squareInds), ObjToDraw::squareInds, GL_STATIC_DRAW);
//
//	// att: pos
//	unsigned int stride = 8;
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// att: color
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// att: texture
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	// linking vertex attributes
//	// --------------------------       
//	// 1. parameter specifies which vertex attribute we want to configure  | location of position
//	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
//	// 3. parameter specifies type of data gl_float
//	// 4. parameter specifies if you want to data to be normalized
//	// 5. known as stride space between consequtive vertex attributes
//	// 6. void this is the offset where the position data begins in the buffer
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//
//
//
//	// draw wireframe or not
//	if (config["settings"]["is_wireframeMode"] == "true") // todo: deserialize config
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//
//	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//	// -------------------------------------------------------------------------------------------
//	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
//	// either set it manually like so:
//	glUniform1i(glGetUniformLocation(shaderProgram, "ktexture1"), 0);
//	// or set it via the texture class
//	ourShader.setInt("texture2", 1);
//
//	// render loop 
//	// --------------------------
//	while (!glfwWindowShouldClose(window))
//	{
//		processInput(window);
//
//		// render clear screen
//		// ------------------------------
//		glClearColor(scaleByteToZeroOne(18), scaleByteToZeroOne(18), scaleByteToZeroOne(18), 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// draw the object
//		// ------------------------------
//		glUseProgram(shaderProgram);
//
//		// update the uniform color
//		// ------------------------------
//		//float timeValue = glfwGetTime();
//		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//		//glUniform4f(vertexColorLocation, scaleByteToZeroOne(18), greenValue, scaleByteToZeroOne(18), 1.0f);
//
//		// :: draw triangle
//		ourShader.use();
//		glBindVertexArray(VAOs[0]);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//
//		// check and call events and swap the buffers
//		// ------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(buffer_count, VAOs);
//	glDeleteBuffers(buffer_count, VBOs);
//	glDeleteProgram(shaderProgram);
//
//	// glfw: purge allocated memory
//	// ------------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//unsigned int createTexture(const std::string& path)
//{
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	//// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// we want to repeat the awesomeface pattern so we kept it at GL_REPEAT
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	//// set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		if (nrChannels == 3)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		}
//		else if (nrChannels == 4)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		}
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture: " << path << std::endl;
//	}
//	glBindTexture(GL_TEXTURE_2D, 0);
//	stbi_image_free(data);
//	return texture;
//}
//
//void assignBuffer(const float* objToDraw, const int sizeofObjToDraw, const unsigned int& inptLayout, const unsigned int& vrtxBuffer)
//{
//	glBindVertexArray(inptLayout);	// VAO note that we bind to a different VAO now
//	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);	// and a different VBO
//	glBufferData(GL_ARRAY_BUFFER, sizeofObjToDraw, objToDraw, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//}
//
//void drawObjToScr(const unsigned int& shader, const unsigned int& vao)
//{
//	glUseProgram(shader);
//	glBindVertexArray(vao);
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//}
//
//void callbackFrameBufferSize(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//#endif