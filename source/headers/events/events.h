#pragma once
#include <opengl.h>


struct SceneState;
struct UniformsPerObject;
struct GLFWwindow;

void callbackFrameBufferSize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, UniformsPerObject& uni);
void callbackMouse(GLFWwindow* window, double xpos, double ypos);
void callbackScroll(GLFWwindow* window, double xoffset, double yoffset);

enum class EventType {
	KeyPress,
	Click,
	UIEvent
};

enum class InputType {
	KeyPress,
	KeyRelease,
	MouseMove
};

struct InputEventKey {
	InputType	    type;
	int				key;
	float			xpos;
	float			ypos;
};

enum class UIEvent {
	SelectScene,
	SetRenderView,
	OpenUISegment,
	ToggleGraphicEnhancer
};

enum class InputEvent {
	MoveForward,
	MoveBackward,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
	MoveSpeedIncrease,
	RotateRight,
	RotateLeft,
	RotateUp,
	RotateDown,
	ToggleUI,
	ToggleMouseLock,
	ResetCamera,
	ZoomIn,
	ZoomOut,
	Undefined
};

const std::unordered_map<int, InputEvent> keyboard = {
	{ GLFW_KEY_LEFT_SHIFT,	InputEvent::MoveSpeedIncrease},
	{ GLFW_KEY_W,			InputEvent::MoveForward },
	{ GLFW_KEY_S,			InputEvent::MoveBackward },
	{ GLFW_KEY_D,			InputEvent::MoveRight },
	{ GLFW_KEY_A,			InputEvent::MoveLeft },
	{ GLFW_KEY_SPACE,		InputEvent::MoveUp },
	{ GLFW_KEY_X,			InputEvent::MoveDown },
	{ GLFW_KEY_E,			InputEvent::RotateRight },
	{ GLFW_KEY_Q,			InputEvent::RotateLeft },
	{ GLFW_KEY_G,			InputEvent::ToggleUI },
	{ GLFW_KEY_R,			InputEvent::RotateUp },
	{ GLFW_KEY_F,			InputEvent::RotateDown },
	{ GLFW_KEY_C,			InputEvent::ResetCamera }
};