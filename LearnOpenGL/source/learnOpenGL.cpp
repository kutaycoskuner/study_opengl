
// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/test/basic.h"      // kendi test header dosyam
#include "../headers/utilities/utilities.h"      // kendi test header dosyam
#include "../headers/data/data.h"    
#include "../headers/blueprint/shader.h"     
#include "../headers/mappings/shaders.h"     
#include "../headers/core/openGL.h"     

#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>  // opengl hardware adaptor !glfw den once
#include <iostream>     // cout / cin icin lazim
#include <string>
#include<unordered_map>

using uint = unsigned int;

constexpr unsigned int ERROR_BUFFER_SIZE = 512;

// ------------------------------------------------------------------------------------------------
// ----- Functions Definitions
// ------------------------------------------------------------------------------------------------
int learnOpenGL(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& config)
{
	// ------------------------------------------------------------------------------------------------
	// ==== Settings
	// ------------------------------------------------------------------------------------------------
	const unsigned int SCR_WIDTH = std::stoul(config["scr"]["width"]);
	const unsigned int SCR_HEIGHT = std::stoul(config["scr"]["height"]);
	const char* WNDW_NAME = config["scr"]["wndw_name"].c_str();

	// :: load shaders
	// --------------------------
	std::unordered_map<std::string, ShaderData> shaders = loadShaders();
	const char* vrtxShaderSrc = shaders.at("vrtxShader").content.c_str();
	const char* fragShaderSrc1 = shaders.at("fragShader_1").content.c_str();
	const char* fragShaderSrc2 = shaders.at("fragShader_2").content.c_str();

	// :: glfw init
	// --------------------------
	glfwInit();
	// :: first param what option we want to configure; second option is value we set.
	// :: 3 means we are explicitly using core profile. version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//

	// :: if apple
	// --------------------------
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WNDW_NAME, NULL, NULL);
	// first two params x,y in size; 3. name; 4-5 necesssary but ignore
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// resize handle
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// --------------------------
	// adapt OpenGL load through GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vrtxShader = compileShader(vrtxShaderSrc, GL_VERTEX_SHADER);
	unsigned int fragShader = compileShader(fragShaderSrc1, GL_FRAGMENT_SHADER);

	unsigned int fragShaderBlue = compileShader(fragShaderSrc1, GL_FRAGMENT_SHADER);
	unsigned int fragShaderViol = compileShader(fragShaderSrc2, GL_FRAGMENT_SHADER);

	// --------------------------
	unsigned int shaderProgram = linkShaderProgram({ vrtxShader, fragShader });
	unsigned int shaderProgramBlue = linkShaderProgram({ vrtxShader, fragShaderBlue });
	unsigned int shaderProgramViol = linkShaderProgram({ fragShaderViol, vrtxShader });

	deleteCompiledShaders({ vrtxShader, fragShader, fragShaderBlue, fragShaderViol });

	// create vertex array object and vertex buffer object
	// --------------------------
	unsigned int VBO, VAO, EBO;
	unsigned int VBOs[2], VAOs[2];
	//glGenVertexArrays(1, &VAO);
	glGenVertexArrays(2, VAOs);
	// :: memory alani olusturuyor
	//glGenBuffers(1, &VBO);
	glGenBuffers(2, VBOs);
	// binding vetex array object
	//glBindVertexArray(VAO);
	glBindVertexArray(VAOs[0]);
	// :: ebo icin memory
	glGenBuffers(1, &EBO);

	// :: bind etme baglama
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	// :: buffer a vertex verisini aktar | bu memory adresinden bu kadar byte kopyala, verinin kendisi
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_reduced), vertices_reduced, GL_STATIC_DRAW);

	// :: exercise 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	// --------------------------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// linking vertex attributes
	// --------------------------       
	// 1. parameter specifies which vertex attribute we want to configure  | location of position
	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
	// 3. parameter specifies type of data gl_float
	// 4. parameter specifies if you want to data to be normalized
	// 5. known as stride space between consequtive vertex attributes
	// 6. void this is the offset where the position data begins in the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// second triangle setup
// ---------------------
	glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	// glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// draw the object
	// --------------------------
	//someOpenGLFunctionThatDrawsTriangle();

	// render loop 
	// --------------------------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// ------
		processInput(window);

		// rendering commands
		// ------
		// #202020: 32,32,32
		// #090909: 9, 9, 9
		// #121212: 18, 18, 18
		glClearColor(scaleByteToZeroOne(18), scaleByteToZeroOne(18), scaleByteToZeroOne(18), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw the object
		// ------
		glUseProgram(shaderProgram);
		glUseProgram(shaderProgramBlue);
		//glBindVertexArray(VAO);
		// GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 0, 6); // exercise 1 de 6 nokta oldugu icin
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// :: exercise 2
		// draw first triangle using the data from the first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// then we draw the second triangle using the data from the second VAO
		glUseProgram(shaderProgramViol);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);

	// glfw: purge allocated memory
	// --------------------------
	glfwTerminate();
	return 0;
}


unsigned int compileShader(const char* src, int glShaderStage)
{
	unsigned int shader_id = glCreateShader(glShaderStage);
	unsigned int shaderProgram = glCreateProgram();
	glShaderSource(shader_id, 1, &src, NULL);
	glCompileShader(shader_id);
	int success;
	char infoLog[ERROR_BUFFER_SIZE];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, ERROR_BUFFER_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader_id;
}

unsigned int linkShaderProgram(const std::vector<unsigned int>& shader_ids)
{
	int success;
	char infoLog[ERROR_BUFFER_SIZE];
	unsigned int shaderProgram_id = glCreateProgram();
	// for
	for (unsigned int shader_id : shader_ids)
	{
		glAttachShader(shaderProgram_id, shader_id);
	}
	glLinkProgram(shaderProgram_id);
	// control shader program
	glGetProgramiv(shaderProgram_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	return shaderProgram_id;
}

void deleteCompiledShaders(const std::vector<unsigned int>& shader_ids)
{
	for (unsigned int shader_id : shader_ids)
	{
		glDeleteShader(shader_id);
	}
}

std::unordered_map<std::string, ShaderData> loadShaders()
{
	std::unordered_map<std::string, ShaderData> shaders;
	for (auto it = shader_mapping.begin(); it != shader_mapping.end(); ++it) {
		const std::string& name = it->first;
		const std::string& path = it->second;

		shaders.emplace(name, ShaderData(name, path, readFileContents(path)));
	}
	return shaders;
}

// glfw: resize adjustment callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// process all input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}