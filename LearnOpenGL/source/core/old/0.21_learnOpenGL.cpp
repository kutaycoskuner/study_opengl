//// ------------------------------------------------------------------------------------------------
//// ----- Libraries
//// ------------------------------------------------------------------------------------------------
///*
//Version 0.21
//https://learnopengl.com/Getting-started/Shaders
//Shaders has ended.
//
//*/
//
//// ------------------------------------------------------------------------------------------------
//// ----- Libraries
//// ------------------------------------------------------------------------------------------------
//#include "../headers/test/basic.h"      // kendi test header dosyam
//#include "../headers/utils/utilities.h"      // kendi test header dosyam
//#include "../headers/data/data.h"    
//#include "../headers/abstract/shader.h"     
//#include "../headers/maps/shaders.h"     
//#include "../headers/core/openGL.h"     
//
//#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
//#include <glad/glad.h>  // opengl hardware adaptor !glfw den once
//#include <iostream>     // cout / cin icin lazim
//#include <string>
//#include<unordered_map>
//
//using uint = unsigned int;
//
//constexpr unsigned int kg_error_buffer_size = 512;
//
//// ------------------------------------------------------------------------------------------------
//// ----- Functions Definitions
//// ------------------------------------------------------------------------------------------------
//int learnOpenGL(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& config)
//{
//	// ------------------------------------------------------------------------------------------------
//	// ==== Settings
//	// ------------------------------------------------------------------------------------------------
//	const unsigned int SCR_WIDTH = std::stoul(config["scr"]["width"]);
//	const unsigned int SCR_HEIGHT = std::stoul(config["scr"]["height"]);
//	const char* WNDW_NAME = config["scr"]["wndw_name"].c_str();
//
//	// :: load shaders
//	// --------------------------
//	std::unordered_map<std::string, ShaderData> shaders = loadShaders();
//	const char* vrtxShaderSrc = shaders.at("vrtxShader").content.c_str();
//	const char* fragShaderSrc = shaders.at("fragShader").content.c_str();
//	const char* fragShaderSrc1 = shaders.at("fragShader_1").content.c_str();
//	const char* fragShaderSrc2 = shaders.at("fragShader_2").content.c_str();
//
//
//
//	// :: glfw init
//	// --------------------------
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
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// glad: load all OpenGL function pointers
//	// --------------------------
//	// adapt OpenGL load through GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	unsigned int vrtxShader = compileShader(vrtxShaderSrc, GL_VERTEX_SHADER);
//	unsigned int fragShader = compileShader(fragShaderSrc, GL_FRAGMENT_SHADER);
//
//	unsigned int fragShaderBlue = compileShader(fragShaderSrc1, GL_FRAGMENT_SHADER);
//	unsigned int fragShaderViol = compileShader(fragShaderSrc2, GL_FRAGMENT_SHADER);
//
//	// --------------------------
//	unsigned int shaderProgram = linkShaderProgram({ vrtxShader, fragShader });
//	unsigned int shaderProgramBlue = linkShaderProgram({ vrtxShader, fragShaderBlue });
//	unsigned int shaderProgramViol = linkShaderProgram({ fragShaderViol, vrtxShader });
//
//	deleteCompiledShaders({ vrtxShader, fragShader, fragShaderBlue, fragShaderViol });
//
//	// create vertex array object and vertex buffer object
//	// --------------------------
//	const unsigned int bufferSize = 1;
//	unsigned int VBO, VAO, EBO;
//	unsigned int VBOs[bufferSize], VAOs[bufferSize];
//	glGenVertexArrays(bufferSize, VAOs);
//	glGenBuffers(bufferSize, VBOs); // :: memory alani olusturuyor
//	//glGenBuffers(bufferSize, &EBO); // :: ebo icin memory
//
//
//	// binding buffers
//	glBindVertexArray(VAOs[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//
//
//	// :: exercise 1
//	// --------------------------
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
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
//	// triangle setup
//// ---------------------
//	//assignBuffer(vertices, sizeof(vertices), VAOs[0], VBOs[0]);
//	//assignBuffer(triangle1, sizeof(triangle1), VAOs[1], VBOs[1]);
//	//assignBuffer(triangle2, sizeof(triangle2), VAOs[2], VBOs[2]);
//
//	
//	// draw wireframe or not
//	if (config["settings"]["is_wireframeMode"] == "true") // todo: deserialize config
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//
//	// draw the object
//	// --------------------------
//	//someOpenGLFunctionThatDrawsTriangle();
//
//	// render loop 
//	// --------------------------
//	while (!glfwWindowShouldClose(window))
//	{
//		// input
//		// ------------------------------
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
//		//glBindVertexArray(VAO);
//		// GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		//glDrawArrays(GL_TRIANGLES, 0, 6); // exercise 1 de 6 nokta oldugu icin
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		// update the uniform color
//		// ------------------------------
//		float timeValue = glfwGetTime();
//		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//		glUniform4f(vertexColorLocation, scaleByteToZeroOne(18), greenValue, scaleByteToZeroOne(18), 1.0f);
//		
//		// :: draw triangle
//		glBindVertexArray(VAOs[0]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//		// :: exercise 2
//		// draw first triangle using the data from the first VAO
//		//glUseProgram(shaderProgramBlue);
//
//
//		// :: exercise 3
//		//drawObjToScr(shaderProgram, VAOs[0]);
//		//drawObjToScr(shaderProgramViol, VAOs[1]);
//		// then we draw the second triangle using the data from the second VAO
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
//	//glDeleteVertexArrays(1, &VAO);
//	//glDeleteBuffers(1, &VBO);
//	//glDeleteBuffers(1, &EBO);
//	//glDeleteProgram(shaderProgram);
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(bufferSize, VAOs);
//	glDeleteBuffers(bufferSize, VBOs);
//	glDeleteProgram(shaderProgram);
//
//	// glfw: purge allocated memory
//	// ------------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
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
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}