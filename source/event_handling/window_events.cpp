// ----- Libraries
// ---------------------------------------------------------------------------------------
#include "uniforms.h"			// shader objesi olusturmaya dair veritipi
#include "renderer.h"			// shader objesi olusturmaya dair veritipi
#include "scene_state.h"			// shader objesi olusturmaya dair veritipi
#include "window_state.h"		
#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi


// ----- variables
// ---------------------------------------------------------------------------------------
extern Renderer* gp_app;


// ----- Functions
// ---------------------------------------------------------------------------------------

void callbackFrameBufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Vec3 operator*(const float& scalar, const Vec3& vector)
{
	return vector * scalar;
}

void processInput(GLFWwindow* window, UniformsPerObject& uni)
{
	static std::map<int, bool> key_state;

	// quit application
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// blending factor between two textures
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		uni.mix_value += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (uni.mix_value >= 1.0f)
			uni.mix_value = 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		uni.mix_value -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (uni.mix_value <= 0.0f)
			uni.mix_value = 0.0f;
	}

	// ----- move camera
	std::vector<int> active_keys;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)	active_keys.push_back(GLFW_KEY_LEFT_SHIFT);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_W);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_S);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_D);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_A);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)		active_keys.push_back(GLFW_KEY_SPACE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_X);
	// ----- rotate camera											
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_Q);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_E);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_R);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)			active_keys.push_back(GLFW_KEY_F);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)			gp_app->resetCamera();

	// ----- toggle ui 
	// prevent fast switching on bool state
	// only activates after key release
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) key_state[GLFW_KEY_G] = true;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE && key_state[GLFW_KEY_G]) {
		active_keys.push_back(GLFW_KEY_G);
		key_state[GLFW_KEY_G] = false;
	}
	
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) key_state[GLFW_KEY_O] = true;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE && key_state[GLFW_KEY_O])
    {
        active_keys.push_back(GLFW_KEY_O);
        key_state[GLFW_KEY_O] = false;
        gp_app->toggleAO();
    }


	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) key_state[GLFW_KEY_T] = true;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE && key_state[GLFW_KEY_T]) {
		active_keys.push_back(GLFW_KEY_T);
		key_state[GLFW_KEY_T] = false;
		gp_app->toggleScreenshotMode();
	}


	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) key_state[GLFW_KEY_Z] = true;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE && key_state[GLFW_KEY_Z]) {
		Renderer::toggle_mouselock = !Renderer::toggle_mouselock;
		key_state[GLFW_KEY_Z] = false;
	}
	if (active_keys.size() > 0)
		gp_app->input_speaker.notifyMultipleKeyPress(active_keys);
}


void callbackMouse(GLFWwindow* window, double xpos, double ypos)
{
	gp_app->handleMouseEvent(window, xpos, ypos);
}

void callbackScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	gp_app->handleScrollEvent(window, xoffset, yoffset);
}


void Renderer::handleMouseEvent(GLFWwindow* window, double xpos, double ypos)
{
	if (toggle_mouselock)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	WindowState& ws = window_state;
	const SceneState& ss = active_scene->scene_state;
	if (ws.b_first_mouse)
	{
		ws.mouse_x = float(xpos);
		ws.mouse_y = float(ypos);
		ws.b_first_mouse = false;
	}

	float xoffset = float(xpos) - ws.mouse_x;
	float yoffset = float(ypos) - ws.mouse_y; // reversed since y-coordinates range from bottom to top
	ws.mouse_x = float(xpos);
	ws.mouse_y = float(ypos);

	//float sensitivity = ss.camera.rotation_sensitivity;
	float sensitivity = 0.005f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	active_scene->cameras[0].rotate(-xoffset, yoffset);
}

void Renderer::handleScrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{
	float& fov = active_scene->cameras[0].fov;
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}