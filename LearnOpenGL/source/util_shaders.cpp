// ------------------------------------------------------------------------------------------------
// ----- Notes
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ----- Libraries
// ------------------------------------------------------------------------------------------------
#include "../headers/utilities/utilities.h"      // kendi test header dosyam
#include "../headers/core/openGL.h"     
#include "../headers/blueprint/shader.h"     
#include "../headers/mappings/shaders.h"     


#include <GLFW/glfw3.h> // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>  // opengl hardware adaptor !glfw den once
#include <iostream>     // cout / cin icin lazim

// ------------------------------------------------------------------------------------------------
// ----- Variables
// ------------------------------------------------------------------------------------------------
constexpr unsigned int ERROR_BUFFER_SIZE = 512;

// ------------------------------------------------------------------------------------------------
// ----- Functions
// ------------------------------------------------------------------------------------------------
unsigned int compileShader(const char* src, int glShaderStage)
{
	unsigned int shader_id = glCreateShader(glShaderStage);
	unsigned int shaderProgram = glCreateProgram();
	glShaderSource(shader_id, 1, &src, NULL);
	glCompileShader(shader_id);
	int success;
	char infoLog[ERROR_BUFFER_SIZE];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, ERROR_BUFFER_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader_id;
}

unsigned int linkShaderProgram(const std::vector<unsigned int>& shader_ids)
{
	int success;
	char infoLog[ERROR_BUFFER_SIZE];
	unsigned int shaderProgram_id = glCreateProgram();
	// for
	for (unsigned int shader_id : shader_ids)
	{
		glAttachShader(shaderProgram_id, shader_id);
	}
	glLinkProgram(shaderProgram_id);
	// control shader program
	glGetProgramiv(shaderProgram_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	return shaderProgram_id;
}

void deleteCompiledShaders(const std::vector<unsigned int>& shader_ids)
{
	for (unsigned int shader_id : shader_ids)
	{
		glDeleteShader(shader_id);
	}
}

std::unordered_map<std::string, ShaderCompileDesc> loadShaders() // todo: path as parameter to avoid include
{
	std::unordered_map<std::string, ShaderCompileDesc> shaders;
	for (auto it = shader_mapping.begin(); it != shader_mapping.end(); ++it) {
		const std::string& name = it->first;
		const std::string& path = it->second;

		shaders.emplace(name, ShaderCompileDesc(name, path, readFileContents(path)));
	}
	return shaders;
}