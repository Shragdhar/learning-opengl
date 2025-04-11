#pragma once
#include <iostream>
#include <glad/glad.h>

class Shader 
{
public:
    Shader(std::string vertex_path, std::string fragment_path, std::string base_dir = "");
    void use();
    GLuint get_id();

private:
    GLuint shader_program_index;

};
