#include "Window.hpp"
#include "Abstraction/Input/Input.hpp"
#include "Abstraction/Shader/Shader.hpp"
#include "Abstraction/Renderer/Renderer.hpp"

// Factory function to create window instance and return it
std::unique_ptr<Window> Window::CreateGLWindow(const std::string& title, int posX, int posY, uint32_t height, uint32_t width, Uint32 flags)
{
    std::unique_ptr<Window> instance = std::unique_ptr<Window>(new Window(title, posX, posY, height, width));

    if (!init_SDL()) {return nullptr;}

    instance->SDL_window = SDL_CreateWindow(title.c_str(), posX, posY, width, height,flags);
    if (!instance->SDL_window) {
        std::cout << "Failed to create SDL window: " << SDL_GetError();
    }

    instance->running = true;

    SDL_GLContext glContext = SDL_GL_CreateContext(instance->SDL_window);
    if (!glContext) {
        std::cout << "Failed to create glContext: " << SDL_GetError();
    }

    if (!init_GLAD()) {return nullptr;}

    glAPI::SetViewport(width, height);

    return instance;
}

bool Window::IsWindowResized() { return Input::Get_Singleton()->Get_WindowEvent().Resized; }

void Window::Clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    Renderer::Get_Singleton()->ClearWindow(red, green, blue, alpha);
}

void Window::Clear(Color color) {
    Renderer::Get_Singleton()->ClearWindow(color.red, color.green, color.blue, color.alpha);
}

void Window::Resize(GLfloat width, GLfloat height)
{
    glAPI::SetViewport(width, height);
}

void Window::SwapWindow()
{
    SDL_GL_SwapWindow(GetSDLWindow());
}

void Window::Quit() { running = false; }

// ---------------- PRIVATE FUNCTIONS ------------------------
//
bool Window::init_SDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    return true;
}

bool Window::init_GLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
