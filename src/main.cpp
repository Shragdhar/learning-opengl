#include "Abstraction/Shader/Shader.hpp"
#include "Abstraction/Buffers/Buffer.hpp"
#include "Abstraction/System/Utils.hpp"
#include "Abstraction/Window/Window.hpp"
#include "Abstraction/Input/Input.hpp"
#include "Abstraction/Renderer/Renderer.hpp"
#include "Abstraction/System/Texture.hpp"
#include <glm/glm.hpp>

#define UniquePtr(X) std::unique_ptr<X>

using namespace absGL;

bool running{true};
SDL_Event event;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

int main()
{
    // Singletons first
    Input* Input = Input::Get_Singleton();
    Renderer* Renderer = Renderer::Get_Singleton();

    UniquePtr(Window) window =
        Window::CreateGLWindow("Weird ass title", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);

    std::string proj_dir = FileHandler::get_base_dir();
    std::string vertex_file = "src/shaders/vertex.vs";
    std::string fragment_file = "src/shaders/fragment.fs";

    std::string variable = "sentColor";
    std::string model_var = "model";

    Color cozy = {242, 227, 168};

    Image image1(proj_dir + "Images/cozy_room.jpg");
    Image image2(proj_dir + "Images/rainworld1.jpg");
    Texture texture1(image1);
    Texture texture2(image2);
    image1.free_memory();
    image2.free_memory();

    float aspect_ratio1 = image1.get_width() / (float)image1.get_height();
    float aspect_ratio2 = image2.get_width() / (float)image2.get_height();

    Shader shader1(vertex_file, fragment_file, proj_dir);

    float vertices[] = {
        // positions         // colors            // texture
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // bottom left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // top right
        -0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 0.0f     // top left
    };

    unsigned int indices[] = {
        0, 2, 3,
        3, 1, 0
    };

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(aspect_ratio1, 1.0f, 1.0f));

    VertexArray VAO1;
    VertexBuffer VBO1(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer EBO(indices, sizeof(indices), GL_STATIC_DRAW);

    VBO1.attribute(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    VBO1.attribute(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    VBO1.attribute(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

    VBO1.unbind();
    VAO1.unbind();

    while (window->is_running())
    {
        window->Clear(cozy);

        shader1.use();

        shader1.set(model_var, model);
        shader1.set("texture1", 0);
        shader1.set("texture2", 1);

        texture1.bind();
        texture2.bind();
        VAO1.bind();

        glAPI::DrawElements(6);

        Input->Listen();

        if (window->IsWindowResized()) { window->Resize(Input->Get_WindowEvent().Width, Input->Get_WindowEvent().Height); }
        if (Input->IsKeyPressed(Input::Key::Escape)) { window->Quit(); }

        window->SwapWindow();
    }

    return 0;
}
