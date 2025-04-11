#pragma once
#include <iostream>
#include <SDL2/SDL.h>

namespace FileHandler
{
// File Handling
    std::string get_base_dir();
    std::string read(std::string path, std::string base_dir = "");
    void        write(std::string path, std::string content, std::string base_dir = "");
}

// Inits
bool init_SDL();
bool init_GLAD();

// Events
void error_callback();
void handle_framebuffer_resize(const SDL_Event &event);
void framebuffer_size_callback(int , int );
void handle_quit_event(const SDL_Event &event, bool &running);

