#pragma once
#include <iostream>
#include <SDL2/SDL.h>

// Events
void handle_framebuffer_resize(const SDL_Event &event);
void framebuffer_size_callback(int , int );
void handle_quit_event(const SDL_Event &event, bool &running);

