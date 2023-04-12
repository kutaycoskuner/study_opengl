#pragma once
#ifndef S_OPENGL
#define S_OPENGL

#include <string>
#include<unordered_map>
#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi


struct ShaderData;

std::unordered_map<std::string, ShaderData> loadShaders();

unsigned int compileShader(const char* src, int glShaderStage);
unsigned int linkShaderProgram(const std::vector<unsigned int>& shader_ids);
void deleteCompiledShaders(const std::vector<unsigned int>& shader_ids);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int learnOpenGL(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& config);
#endif