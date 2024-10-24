#pragma once
#ifndef S_SHADER
#define S_SHADER
// ------------------------------------------------------------------------------------------------
// ----- libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/matrix4.h"
#include "../abstract/vector2.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// ------------------------------------------------------------------------------------------------
// ----- function declerations
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ----- abstract
// ------------------------------------------------------------------------------------------------
struct ShaderCompileDesc
{
	// variables
	// -----------------------------------
	const std::string name;
	const std::string path;
	const std::string content;

	// constructors
	// -----------------------------------	
	// Default constructor
	ShaderCompileDesc() : name(""), path(""), content("") {}

	// Parameter constructor
	ShaderCompileDesc(const std::string& name, const std::string& path, const std::string& content) 
		: name(name), path(path), content(content) {}

	// Copy constructor
	ShaderCompileDesc(const ShaderCompileDesc& other) : name(other.name), path(other.path), content(other.content) {}

	// todo move constructor

	// todo destructor
};

// this shader class is suggested in learnopengl
class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            if (geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (const std::ifstream::failure& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n"
                << "File: " << __FILE__ << "\n"
                << "Line: " << __LINE__ << "\n"
                << "Exception Message: " << e.what() << "\n"
                << "Shader File Path: " << (geometryPath ? geometryPath : (vShaderFile.is_open() ? vertexPath : fragmentPath)) << "\n" 
                << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shader
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (geometryPath != nullptr)
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
        {
            glAttachShader(ID, geometry);
        }
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shader as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr) glDeleteShader(geometry);
    }
    Shader(const std::string& vertexPath, const std::string& fragPath): 
        Shader(vertexPath.c_str(), fragPath.c_str())
    {}
    Shader(const std::string& vertexPath, const std::string& fragPath, const std::string& geoPath) :
        Shader(vertexPath.c_str(), fragPath.c_str(), geoPath.c_str())
    {}
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const Mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &value.m[0][0]);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const Vec2& value) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const float& vx, const float& vy) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), vx, vy);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const Vec3& value) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const float& vx, const float& vy, const float& vz) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), vx, vy, vz);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif
