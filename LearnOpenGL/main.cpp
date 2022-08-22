// ------------------------------------------------
// ==== Libraries
// ------------------------------------------------
#include <iostream>     // we need iostream here too since we use it in this file as well
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

    // render loop 
    // --------------------------
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands
        glClearColor(byteToOneScale(6), byteToOneScale(180), byteToOneScale(186), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

float byteToOneScale(unsigned int byte)
{
    return (float(byte) / 255.0f);
}