#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader 
{
public:
    Shader(std::string vertex_path, std::string fragment_path, std::string base_dir = "");
    void use();

    inline GLuint   get_id()    const { return shader_program_index; };
           void     set        (const std::string &name, bool value) const;
           void     set        (const std::string &name, int value) const;
           void     set        (const std::string &name, float value) const;
           void     set        (const std::string &name, const glm::mat4& value) const;

private:
    GLuint shader_program_index;

};
