#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/glad.h>

class Shader{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void checkCompileErrors(unsigned int, std::string);
};

#endif
