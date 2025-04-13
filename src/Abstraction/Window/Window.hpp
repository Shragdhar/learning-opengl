#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <memory>
#include <glad/glad.h>
#include <iostream>

class Window
{
public:
    static std::unique_ptr<Window> CreateGLWindow(const std::string& title,
                                                  int posX, int posY,
                                                  uint32_t height, uint32_t width,
                                                  Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    inline SDL_Window*  GetSDLWindow() { return SDL_window; }
    inline int          get_posX()     { return posX; }
    inline int          get_posY()     { return posY; }
    inline uint32_t     get_height()   { return height; }
    inline uint32_t     get_width()    { return width; }
    inline std::string  get_title()    { return title; }
    inline bool         is_running()   { return running; }

    bool IsWindowResized();

    void Clear(GLfloat = 0, GLfloat=0, GLfloat=0, GLfloat=1);
    void Resize(GLfloat, GLfloat);
    void SwapWindow();
    void Quit();

private:
    Window(const std::string& title, int x, int y, uint32_t h, uint32_t w)
        : title(title), posX(x), posY(y), width(w), height(h) {}

    int         posX, posY;
    uint32_t    height, width;
    std::string title;
    bool        running{true};

    SDL_Window* SDL_window;

    static bool init_SDL();
    static bool init_GLAD();

};
