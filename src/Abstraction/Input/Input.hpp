#include "includes/SDL_x.hpp"
#include <functional>
#include <iostream>

class Input
{
public:
    enum class Key;
    struct WindowEvent;

    static std::unordered_map<SDL_Scancode, bool> keystate;

    static void Listen();
    static void RegisterFunction(std::function<void()>);

    static bool IsKeyPressed(Key);
    static bool Quit();

    struct WindowEvent
    {
        static inline bool Resized = false;
        static inline int Width = 0;
        static inline int Height = 0;

        static inline bool CloseRequested = false;
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
    static std::vector<std::function<void()>> registered_functions;
};










