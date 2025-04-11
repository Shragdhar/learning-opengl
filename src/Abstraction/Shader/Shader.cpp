#include "Abstraction/Window/handler.hpp"
#include "Shader.hpp"

Shader::Shader(std::string vertex_path, std::string fragment_path, std::string base_dir)
{
    if (base_dir.empty()) {
        std::cout << "Empty path provided, using default one";
        base_dir = FileHandler::get_base_dir();
    }

    std::string vertex_code = FileHandler::read("src/shaders/vertex.vs", base_dir);
    const char* gl_vertex_code = vertex_code.c_str(); // because OpenGL expects lvalue pointer

    std::string fragment_code = FileHandler::read("src/shaders/fragment.fs", base_dir);
    const char* gl_fragment_code = fragment_code.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &gl_vertex_code, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &gl_fragment_code, NULL);
    glCompileShader(fragmentShader);

    shader_program_index = glCreateProgram();
    glAttachShader(shader_program_index, vertexShader);
    glAttachShader(shader_program_index, fragmentShader);
    glLinkProgram(shader_program_index);
}

void Shader::use()
{
    glUseProgram(shader_program_index);
}

GLuint Shader::get_id()
{
    return shader_program_index;
}
