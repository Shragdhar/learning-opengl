#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);
    
        
    if (!fragmentFile)
    {
        std::cerr << "Failed to open file" << std::endl;
    }

    if (!vertexFile)
    {
        std::cerr << "Failed to open file" << std::endl;
    }
    
    std::string fragmentCode;
    std::string vertexCode;
    std::stringstream vertexCodeBuffer;
    std::stringstream fragmentCodeBuffer;
    
    vertexCodeBuffer << vertexFile.rdbuf();
    fragmentCodeBuffer << fragmentFile.rdbuf();

    vertexCode = vertexCodeBuffer.str();
    fragmentCode = fragmentCodeBuffer.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex{0}, fragment{0};

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
    //std::cout << glGetError() << std::endl;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        // Check shader compilation errors
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        // Check program linking errors
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
