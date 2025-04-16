#include "Renderer.hpp"
#include "Abstraction/Shader/Shader.hpp"

Renderer* Renderer::singleton = nullptr;

Renderer* Renderer::Get_Singleton()
{
    if (singleton == nullptr) {
        singleton = new Renderer();
    }
    return singleton;
}

void Renderer::ClearWindow(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glAPI::Clear(red, green, blue, alpha);
}

//-------------------------------------------------------------------------------------------
//                                      glAPI                                                |
//-------------------------------------------------------------------------------------------
namespace glAPI
{
std::unordered_map<std::string, GLint> uniform_cache;


void Clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SetViewport(GLsizei width, GLsizei height)
{
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void DrawArrays(GLsizei count) {
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void DrawElements(GLsizei count) {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

// Unifrom overloads ------------
void SetUniformValue(Shader& shader, const std::string& variable, Color Color)
{
    int uniform_location = GetUniformLocation(shader, variable);
    glUseProgram(shader.get_id());

    if (Color.has_alpha) {
        glUniform4f(uniform_location, Color.red, Color.green, Color.blue, Color.alpha);
    } else {
        glUniform3f(uniform_location, Color.red, Color.green, Color.blue);
    }
}

GLint GetUniformLocation(Shader& shader, const std::string& variable)
{
    if (uniform_cache.find(variable) != uniform_cache.end()) return uniform_cache[variable];
    GLint loc = glGetUniformLocation(shader.get_id(), variable.c_str());
    uniform_cache[variable] = loc;
    return loc;
}

}
