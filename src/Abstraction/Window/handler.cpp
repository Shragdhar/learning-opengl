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
        event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
    {
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

