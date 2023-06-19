#pragma once
#ifndef S_OPENGL
#define S_OPENGL

#include "../abstract/vector3.h" // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <string>
#include<unordered_map>
#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi


struct ShaderCompileDesc;

// shader util
unsigned int compileShader(const char* src, int glShaderStage);
unsigned int linkShaderProgram(const std::vector<unsigned int>& shader_ids);
void deleteCompiledShaders(const std::vector<unsigned int>& shader_ids);
std::unordered_map<std::string, ShaderCompileDesc> loadShaders();

//
void drawObjToScr(const unsigned int& shader, const unsigned int& vao);
void assignBuffer(const float* objToDraw, const int sizeofObjToDraw, const unsigned int& inptLayout, const unsigned int& vrtxBuffer);

// animation
Vec3 setTriangleLightColorShiftByTime(const float& time);

#endif