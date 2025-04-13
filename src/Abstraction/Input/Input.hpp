#include "includes/SDL_x.hpp"
#include <functional>
#include <iostream>

class Input
{
public:
    Input();
    ~Input();

    enum class Key;

    struct WindowEvent;
    std::unordered_map<SDL_Scancode, bool> keystate;

    static Input* Get_Singleton();
    WindowEvent& Get_WindowEvent();


    void Listen();
    void RegisterFunction(std::function<void()>);

    bool IsKeyPressed(Key);
    bool Quit();

    struct WindowEvent
    {
        bool  Resized = false;
        int   Width = 0;
        int   Height = 0;
    };

    enum class Key {
        A = SDL_SCANCODE_A,
        B = SDL_SCANCODE_B,
        C = SDL_SCANCODE_C,
        D = SDL_SCANCODE_D,
        E = SDL_SCANCODE_E,
        F = SDL_SCANCODE_F,
        G = SDL_SCANCODE_G,
        H = SDL_SCANCODE_H,
        I = SDL_SCANCODE_I,
        J = SDL_SCANCODE_J,
        K = SDL_SCANCODE_K,
        L = SDL_SCANCODE_L,
        M = SDL_SCANCODE_M,
        N = SDL_SCANCODE_N,
        O = SDL_SCANCODE_O,
        P = SDL_SCANCODE_P,
        Q = SDL_SCANCODE_Q,
        R = SDL_SCANCODE_R,
        S = SDL_SCANCODE_S,
        T = SDL_SCANCODE_T,
        U = SDL_SCANCODE_U,
        V = SDL_SCANCODE_V,
        W = SDL_SCANCODE_W,
        X = SDL_SCANCODE_X,
        Y = SDL_SCANCODE_Y,
        Z = SDL_SCANCODE_Z,
        Space = SDL_SCANCODE_SPACE,
        Escape = SDL_SCANCODE_ESCAPE
    };

private:
    static Input* instance;
    WindowEvent window_event;
};










