// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/abstract/uniforms.h"			// shader objesi olusturmaya dair veritipi
#include "../headers/abstract/scene_state.h"			// shader objesi olusturmaya dair veritipi
#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi



// ------------------------------------------------------------------------------------------------
// ----- Functions
// ------------------------------------------------------------------------------------------------

void callbackFrameBufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Vec3 operator*(const float& scalar, const Vec3& vector)
{
	return vector * scalar;
}


void processInput(GLFWwindow* window, UniformsPerObject& uni, SceneState& scene_state)
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

	// camera
	const float cam_speed = 0.05f; // adjust accordingly
	Vec3& cam_pos = scene_state.camera.position;
	const Vec3& cam_dir = scene_state.camera.direction;
	const Vec3& cam_up = scene_state.camera.up;
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam_pos -= cam_speed * cam_dir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam_pos += cam_dir * cam_speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam_pos += math_utils::cross3d(cam_dir, cam_up).normalized() * cam_speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam_pos -= math_utils::cross3d(cam_dir, cam_up).normalized() * cam_speed;
}