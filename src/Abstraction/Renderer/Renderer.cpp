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

namespace glAPI
{
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
}
