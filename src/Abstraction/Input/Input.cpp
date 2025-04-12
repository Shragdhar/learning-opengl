#include "Input.hpp"
#include <SDL_events.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

std::unordered_map<SDL_Scancode, bool> Input::keystate;

void Input::Listen()
{
    WindowEvent::Resized = false;

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
                    WindowEvent::Resized = true;
                    WindowEvent::Width = event.window.data1;
                    WindowEvent::Height = event.window.data2;
                }
                break;
        }
    }
}

bool Input::IsKeyPressed(Key key)
{
    return keystate[static_cast<SDL_Scancode>(key)];
}
