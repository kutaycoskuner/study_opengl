#pragma once
#include "../headers/abstract/uniforms.h"			// shader objesi olusturmaya dair veritipi
#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi

void callbackFrameBufferSize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, MyUniforms& uni);
