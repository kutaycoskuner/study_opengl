// ------------------------------------------------
// ==== Libraries
// ------------------------------------------------
#include <iostream>     // cout / cin icin lazim
#include "basic.h"      // kendi test header dosyam
#include <glad/glad.h>  // opengl hardware adaptor !glfw den once
#include <GLFW/glfw3.h> // opengl kutuphaesi

// ------------------------------------------------
// ==== Function Declerations
// ------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float byteToOneScale(unsigned int byte);

// ------------------------------------------------
// ==== Settings
// ------------------------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WNDW_NAME = "Potatoland";


// ------------------------------------------------
// ==== Shaders
// ------------------------------------------------
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.02f, 0.7f, 0.72f, 1.0f);\n"
"}\0";

// ------------------------------------------------
// ==== Data
// ------------------------------------------------
float vertices[] = {
    -0.5f, -0.5f, 0.0f,     // left
     0.5f, -0.5f, 0.0f,     // right
     0.0f,  0.5f, 0.0f      // top
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


// ------------------------------------------------
// ==== Main
// ------------------------------------------------
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
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // control fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
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
    glGenVertexArrays(1, &VAO);
    // :: memory alani olusturuyor
    glGenBuffers(1, &VBO);
    // binding vetex array object
    glBindVertexArray(VAO);
    // :: ebo icin memory
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // :: bind etme baglama
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // :: buffer a vertex verisini aktar | bu memory adresinden bu kadar byte kopyala, verinin kendisi
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_reduced), vertices_reduced, GL_STATIC_DRAW);
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

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // draw the object
    // --------------------------
    //someOpenGLFunctionThatDrawsTriangle();

    // render loop 
    // --------------------------
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands
        // orthblue: 6, 180, 186
        // #202020: 32,32,32
        glClearColor(byteToOneScale(32), byteToOneScale(32), byteToOneScale(32), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
float byteToOneScale(unsigned int byte)
{
    return (float(byte) / 255.0f);
}