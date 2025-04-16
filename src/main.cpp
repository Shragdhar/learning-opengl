#include "Abstraction/Window/handler.hpp"
#include "Abstraction/Shader/Shader.hpp"
#include "Abstraction/Buffers/Buffer.hpp"
#include "Abstraction/System/FileHandler.hpp"
#include "Abstraction/Window/Window.hpp"
#include "Abstraction/Input/Input.hpp"
#include "Abstraction/Renderer/Renderer.hpp"

#define UniquePtr(X) std::unique_ptr<X>

using namespace absGL;

bool running{true};
SDL_Event event;

int main()
{
    // Singletons first
    Input* Input = Input::Get_Singleton();
    Renderer* Renderer = Renderer::Get_Singleton();

    UniquePtr(Window) window =
        Window::CreateGLWindow("Weird ass title", 0, 0, 800, 800);

    std::string proj_dir = FileHandler::get_base_dir();
    std::string vertex_file = "src/shaders/vertex.vs";
    std::string fragment_file = "src/shaders/fragment.fs";

    Shader shader1(vertex_file, fragment_file, proj_dir);

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom left
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   // top right
        -0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f     // top left
    };

    unsigned int indices[] = {
        2, 3, 0,
        3, 1, 0
    };

    VertexArray VAO1;

    VertexBuffer VBO1(vertices, sizeof(vertices), GL_STATIC_DRAW);
    VBO1.attribute(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    VBO1.attribute(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

    IndexBuffer EBO(indices, sizeof(indices), GL_STATIC_DRAW);

    VBO1.unbind();
    VAO1.unbind();

    std::string variable = "sentColor";
    while (window->is_running())
    {
        window->Clear(0.2, 0.3, 0.5);

        shader1.use();

        glAPI::SetUniformValue(shader1, variable, {1.0, 0.5, 0.5} );

        VAO1.bind();
        glAPI::DrawElements(6);

        Input->Listen();

        if (window->IsWindowResized()) { window->Resize(Input->Get_WindowEvent().Width, Input->Get_WindowEvent().Height); }
        if (Input->IsKeyPressed(Input::Key::Escape)) { window->Quit(); }

        window->SwapWindow();
    }

    return 0;
}
