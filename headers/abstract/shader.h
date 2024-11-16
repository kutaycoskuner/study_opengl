#pragma once
#ifndef S_SHADER
#define S_SHADER
// ------------------------------------------------------------------------------------------------
//                  libraries
// ------------------------------------------------------------------------------------------------
#include "../abstract/matrix4.h"
#include "../abstract/vector2.h"

#include <glad/glad.h>

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// ------------------------------------------------------------------------------------------------
//                  function declerations
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
//                  abstract
// ------------------------------------------------------------------------------------------------
struct ShaderCompileDesc
{
    // Variables
    // -----------------------------------
    std::string name;
    std::string vrtx_path;
    std::string frag_path;
    std::string geom_path;

    // Constructors
    // -----------------------------------    
    // Default constructor
    ShaderCompileDesc()
        : name(""), vrtx_path(""), frag_path(""), geom_path("") {}

    // Parameterized constructor
    ShaderCompileDesc(const std::string& name, const std::string& vrtx_path, const std::string& frag_path, const std::string& geom_path)
        : name(name), vrtx_path(vrtx_path), frag_path(frag_path), geom_path(geom_path) {}

    // Copy constructor
    ShaderCompileDesc(const ShaderCompileDesc& other)
        : name(other.name), vrtx_path(other.vrtx_path), frag_path(other.frag_path), geom_path(other.geom_path) {}

    // Move constructor
    ShaderCompileDesc(ShaderCompileDesc&& other) noexcept
        : name(std::move(other.name)), vrtx_path(std::move(other.vrtx_path)), frag_path(std::move(other.frag_path)),
        geom_path(std::move(other.geom_path)) {}

    // Destructor (default is sufficient)
    ~ShaderCompileDesc() = default;
};

// this shader class is suggested in learnopengl
class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
        // Constructor generates the shader from ShaderCompileDesc
    // ------------------------------------------------------------------------
// Constructor that generates the shader program
    Shader(const ShaderCompileDesc& shader_compile_desc)
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        // Ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            // Open files
            vShaderFile.open(shader_compile_desc.vrtx_path);
            fShaderFile.open(shader_compile_desc.frag_path);

            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // Close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert streams into strings
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            // If a geometry shader is provided, load it
            if (!shader_compile_desc.geom_path.empty()) {
                gShaderFile.open(shader_compile_desc.geom_path);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (const std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n"
                << "File: " << __FILE__ << "\n"
                << "Line: " << __LINE__ << "\n"
                << "Exception Message: " << e.what() << "\n"
                << "Shader File Path: " << (shader_compile_desc.geom_path.empty() ?
                    (shader_compile_desc.vrtx_path) : shader_compile_desc.geom_path) << "\n"
                << std::endl;
        }

        // Compile shaders
        unsigned int vertex, fragment, geometry;
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        const char* gShaderCode = geometryCode.c_str();

        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(shader_compile_desc, vertex, "VERTEX");

        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(shader_compile_desc, fragment, "FRAGMENT");

        // If a geometry shader is provided, compile it
        if (!shader_compile_desc.geom_path.empty()) {
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(shader_compile_desc, geometry, "GEOMETRY");
        }

        // Create the shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (!shader_compile_desc.geom_path.empty()) {
            glAttachShader(ID, geometry);
        }

        glLinkProgram(ID);
        checkCompileErrors(shader_compile_desc, ID, "PROGRAM");

        // Delete shaders after they are linked
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (!shader_compile_desc.geom_path.empty()) {
            glDeleteShader(geometry);
        }
    }
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
        GLuint loc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_TRUE, &value.m[0][0]);
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
    void checkCompileErrors(const ShaderCompileDesc& scd, unsigned int shader, const std::string& type)
    {
        int success;
        char infoLog[1024];

        // Check the type of error (shader or program)
        if (type != "PROGRAM") {
            // Shader compilation errors
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << "File Path: " << scd.vrtx_path << " (Vertex Shader)\n"
                    << "Error Message: " << infoLog << "\n"
                    << "-- --------------------------------------------------- --\n";
            }
        }
        else {
            // Program linking errors
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << "File Paths: \n"
                    << "Vertex Shader: " << scd.vrtx_path << "\n"
                    << "Fragment Shader: " << scd.frag_path << "\n";
                if (!scd.geom_path.empty()) {
                    std::cerr << "Geometry Shader: " << scd.geom_path << "\n";
                }
                std::cerr << "Error Message: " << infoLog << "\n"
                    << "-- --------------------------------------------------- --\n";
            }
        }
    }
};

#endif
