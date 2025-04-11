#include "Abstraction/Window/handler.hpp"
#include "Abstraction/Shader/Shader.hpp"
#include "Abstraction/Buffers/Buffer.hpp"
#include "Abstraction/System/FileHandler.hpp"
#include "Abstraction/Window/Window.hpp"

#define UniquePtr(X) std::unique_ptr<X>

using namespace absGL;

bool running{true};
SDL_Event event;

int main()
{
    UniquePtr(Window) window =
        Window::CreateGLWindow("Weird ass title", 0, 0, 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    std::string proj_dir = FileHandler::get_base_dir();
    std::string vertex_file = "src/shaders/vertex.vs";
    std::string fragment_file = "src/shaders/fragment.fs";

    Shader shader1(vertex_file, fragment_file, proj_dir);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    VertexArray VAO1;

    VertexBuffer VBO1(vertices, sizeof(vertices), GL_STATIC_DRAW);
    VBO1.attribute(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    VBO1.unbind();
    VAO1.unbind();

    while (running)
    {
        window->Clear(0.2, 0.3, 0.5);

        shader1.use();
        VAO1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        while (SDL_PollEvent(&event)) 
        {
            handle_framebuffer_resize(event);
            handle_quit_event(event, running);
        }
        SDL_GL_SwapWindow(window->GetSDLWindow());
    }

    return 0;
}
