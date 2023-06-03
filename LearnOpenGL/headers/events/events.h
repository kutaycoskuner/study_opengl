#pragma once
struct SceneState;
struct UniformsPerObject;
struct GLFWwindow;

void callbackFrameBufferSize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, UniformsPerObject& uni, SceneState& scene_state);
