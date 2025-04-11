#include "handler.hpp"
#include "Shader.hpp"
#include "Abstraction/Buffer.hpp"

using namespace absGL;

bool running{true};
SDL_Event event;

int main()
{
    if (!init_SDL()) {return 1;};

    SDL_Window* window = SDL_CreateWindow("weird title", 0, 0, 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    std::string proj_dir = FileHandler::get_base_dir();

    if (!init_GLAD()) {return 1;};

    // --------------------------- OpenGL functions only to be used after this line --------------------------------

    Shader shader1("src/shaders/vertex.vs", "src/shaders/fragment.fs", proj_dir);

    glViewport(0,0,800,800);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader1.use();
        VAO1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        while (SDL_PollEvent(&event)) 
        {
            handle_framebuffer_resize(event);
            handle_quit_event(event, running);
        }
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
