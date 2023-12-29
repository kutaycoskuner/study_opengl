// ----- Libraries
// ---------------------------------------------------------------------------------------
#include "../headers/abstract/uniforms.h"			// shader objesi olusturmaya dair veritipi
#include "../headers/abstract/application.h"			// shader objesi olusturmaya dair veritipi
#include "../headers/abstract/scene_state.h"			// shader objesi olusturmaya dair veritipi
#include "../headers/abstract/window_state.h"		
#include <GLFW/glfw3.h>			// opengl i daha rahat kullanabilmek icin fonksion kutuphanesi


// ----- variables
// ---------------------------------------------------------------------------------------
extern Application* gp_app;


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

void processInput(GLFWwindow* window, UniformsPerObject& uni, SceneState& scene_state)
{

	static bool keyPressed = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

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

	// camera
	SceneState& ss = scene_state;
	Vec3& cam_pos = scene_state.camera.position;
	
	const Vec3& cam_dir = scene_state.camera.getDirection();
	const Vec3& cam_up = scene_state.camera.getUp(Application::world_up);
	const Vec3& cam_right = scene_state.camera.getRight(Application::world_up);
	
	float cam_speed = 2.5f * scene_state.delta_time; // adjust accordingly
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) cam_speed *= 3.0f;


	// ----- move camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		cam_pos += + cam_speed * cam_dir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		cam_pos += - cam_speed * cam_dir;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		cam_pos += + cam_speed * cam_right;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		cam_pos += - cam_speed * cam_right;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)	cam_pos += + cam_speed * cam_up;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)		cam_pos += - cam_speed * cam_up;
	
	// ----- keypress rotations
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		ss.camera.rotate(+ss.camera.rotation_sensitivity, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		ss.camera.rotate(-ss.camera.rotation_sensitivity, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		ss.camera.rotate(0.0f, +ss.camera.rotation_sensitivity);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ss.camera.rotate(0.0f, -ss.camera.rotation_sensitivity);



	// ----- reset camera
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		Application::resetCamera(ss.camera);
	}

	// Check if the key is X and if it was pressed
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		keyPressed = true;
	}

	// toggle ui
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE && keyPressed)
	{
		ss.b_toggleui = !ss.b_toggleui;
		keyPressed = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		Application::toggle_mouselock = !Application::toggle_mouselock;
}


void callbackMouse(GLFWwindow* window, double xpos, double ypos)
{
	gp_app->handleMouseEvent(window, xpos, ypos);
}

void callbackScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	gp_app->handleScrollEvent(window, xoffset, yoffset);
}


void Application::handleMouseEvent(GLFWwindow* window, double xpos, double ypos)
{
	if (toggle_mouselock) return;

	WindowState& ws = window_state;
	SceneState& ss = scene_state;
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

	ss.camera.rotate(-xoffset, yoffset);
}

void Application::handleScrollEvent(GLFWwindow* window, double xoffset, double yoffset)
{
	float& fov = scene_state.camera.fov;
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}