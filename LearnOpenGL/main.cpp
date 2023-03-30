// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include <iostream>     // cout / cin icin lazim
#include "basic.h"      // kendi test header dosyam
#include <glad/glad.h>  // opengl hardware adaptor !glfw den once
#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi

// ------------------------------------------------------------------------------------------------
// ==== Function Declerations
// ------------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float scaleByteToZeroOne(unsigned int byte);

// ------------------------------------------------------------------------------------------------
// ==== Settings
// ------------------------------------------------------------------------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WNDW_NAME = "Potatoland";


// ------------------------------------------------------------------------------------------------
// ==== Shaders
// ------------------------------------------------------------------------------------------------
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.02f, 0.7f, 0.72f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.85f, 0.09f, 0.56f, 1.0f);\n"
"}\n\0";


// ------------------------------------------------------------------------------------------------
// ==== Data
// ------------------------------------------------------------------------------------------------
//float vertices[] = {
//    -0.5f, -0.5f, 0.0f,     // left
//     0.5f, -0.5f, 0.0f,     // right
//     0.0f,  0.5f, 0.0f      // top
//};

float vertices[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	// second triangle
	 0.0f, -0.5f, 0.0f,  // left
	 0.9f, -0.5f, 0.0f,  // right
	 0.45f, 0.5f, 0.0f   // top 
};

float triangle1[] = {
	// first triangle
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top  
};


float triangle2[] = {
	// second triangle
  0.0f, -0.5f, 0.0f,  // left
  0.9f, -0.5f, 0.0f,  // right
  0.45f, 0.5f, 0.0f   // top  
};

float vertices_2tri[] = {
	// first triangle
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f,  0.5f, 0.0f,  // top left 
	// second triangle
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
};

float vertices_reduced[] = {
	// first triangle
	0.5f,  0.5f, 0.0f,   // top right
	0.5f, -0.5f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
};

// to speciicy overlapping vertices | used with Element Buffer object
unsigned int indices[] = {
	0, 1, 3,    // first triangle
	1, 2, 3     // second triangle
};

// ------------------------------------------------------------------------------------------------
// ==== Main
// ------------------------------------------------------------------------------------------------
int main()
{
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

	// vertex shader
	// --------------------------
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// control shader
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	// --------------------------
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader);
	// control fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// color frag shader
	// --------------------------
	unsigned int fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShaderViolet = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgramBlue = glCreateProgram();
	unsigned int shaderProgramViolet = glCreateProgram();
	glShaderSource(fragmentShaderBlue, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShaderBlue);
	glShaderSource(fragmentShaderViolet, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShaderViolet);

	glAttachShader(shaderProgramBlue, vertexShader);
	glAttachShader(shaderProgramBlue, fragmentShaderBlue);
	glLinkProgram(shaderProgramBlue);
	glAttachShader(shaderProgramViolet, vertexShader);
	glAttachShader(shaderProgramViolet, fragmentShaderViolet);
	glLinkProgram(shaderProgramViolet);


	// shader program
	// --------------------------
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// control shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	// delete shaders after linking | shader objelerine linkten sonra ihtiyac kalmiyor.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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
		glUseProgram(shaderProgramViolet);
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

// ------------------------------------------------
// ==== Function Definitions
// ------------------------------------------------
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
// utility functions
// --------------------------
