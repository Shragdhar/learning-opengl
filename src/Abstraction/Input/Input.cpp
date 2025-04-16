#include "Input.hpp"
#include <SDL_events.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

Input* Input::instance = nullptr;

Input::Input()
{
    WindowEvent window_event;
}

Input::~Input()
{
    delete instance;
}

Input* Input::Get_Singleton()
{
    if (instance == nullptr) {
        instance = new Input();
    }
    return instance;
}

Input::WindowEvent& Input::Get_WindowEvent()
{
    return window_event;
}

void Input::Listen()
{
    window_event.Resized = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {

            case SDL_KEYDOWN:
                keystate[event.key.keysym.scancode] = true;
                break;

            case SDL_KEYUP:
                keystate[event.key.keysym.scancode] = false;
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    window_event.Resized = true;
                    window_event.Width = event.window.data1;
                    window_event.Height = event.window.data2;
                }
                break;
        }
    }
}

bool Input::IsKeyPressed(Key key)
{
    return keystate[static_cast<SDL_Scancode>(key)];
}
