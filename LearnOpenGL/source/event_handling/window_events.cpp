// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/uniforms.h"			// shader objesi olusturmaya dair veritipi
#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi



// ------------------------------------------------------------------------------------------------
// ----- Functions
// ------------------------------------------------------------------------------------------------

void callbackFrameBufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, MyUniforms& uni)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		uni.mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (uni.mixValue >= 1.0f)
			uni.mixValue = 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		uni.mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (uni.mixValue <= 0.0f)
			uni.mixValue = 0.0f;
	}
}