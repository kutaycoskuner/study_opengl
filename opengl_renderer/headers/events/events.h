#pragma once
struct SceneState;
struct UniformsPerObject;
struct GLFWwindow;

void callbackFrameBufferSize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, UniformsPerObject& uni, SceneState& scene_state);
void callbackMouse(GLFWwindow* window, double xpos, double ypos);
void callbackScroll(GLFWwindow* window, double xoffset, double yoffset);

