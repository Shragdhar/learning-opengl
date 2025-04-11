#include <glad/glad.h>
#include <filesystem>
#include <fstream>
#include "handler.hpp"

void handle_quit_event(const SDL_Event &event, bool &running)
{
    if (event.type == SDL_KEYDOWN && ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ||
                                       event.key.keysym.scancode == SDL_SCANCODE_Q))

    { running = false; }
}
void handle_framebuffer_resize(const SDL_Event &event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
        event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        
        int newWidth = event.window.data1;
        int newHeight = event.window.data2;
        framebuffer_size_callback(newWidth, newHeight);
    }
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(int width, int height)
{
    glViewport(0, 0, width, height);
}

bool init_SDL() 
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

bool init_GLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

//
// FILE HANDLER
//
namespace FileHandler
{
    std::string get_base_dir()
    {
        std::string current_path = std::filesystem::current_path();
        std::string proj_dir = std::string(current_path)+ "/../";
        return proj_dir;
    }

    std::string read(std::string path, std::string base_dir)
    {
        if (base_dir.empty()) {
            std::cout << "Empty path provided, using default one";
            base_dir = FileHandler::get_base_dir();
        }

        std::filesystem::path checked_path = path;
        std::string absolute_path;

        if (checked_path.is_relative()) {
            absolute_path = base_dir + path;
        }
        else if (checked_path.is_absolute()) {
            absolute_path = path;
        }

        std::fstream file(absolute_path);
        if (!file) { std::cout << "Couldn't read file: " << std::endl; return ""; }

        std::string file_content((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

        file.close();

        return file_content;
    }

    void write(std::string path, std::string content, std::string base_dir)
    {
        if (base_dir.empty()) {
            std::cout << "Empty path provided, using default one";
            base_dir = FileHandler::get_base_dir();
        }

        std::filesystem::path checked_path = path;
        std::string absolute_path;

        if (checked_path.is_relative()) {
            absolute_path = base_dir + path;
        }
        else if (checked_path.is_absolute()) {
            absolute_path = path;
        }

        std::fstream file;

        file.open(absolute_path, std::ios_base::out);
        if (!file) { 
            std::cout << "File failed to create: " << SDL_GetError();
            return;
        }

        file << content;
        file.close();

    }
}














