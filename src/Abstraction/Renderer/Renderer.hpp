#include "Abstraction/Shader/Shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <unordered_map>

class Renderer
{
public:

    static Renderer* Get_Singleton();

    void ClearWindow(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0, GLfloat alpha = 1);

private:
    static Renderer* singleton;
    Renderer(){}
    ~Renderer() { delete singleton; }
};

typedef struct Color 
{
    GLfloat red     = 0.0;
    GLfloat green   = 0.0;
    GLfloat blue    = 0.0;
    GLfloat alpha   = 0.0;
    bool has_alpha;

    Color() = default;
    Color(GLfloat r) : red(r), has_alpha(false) {}
    Color(GLfloat r, GLfloat g) : red(r), green(g), has_alpha(false) {}
    Color(GLfloat r, GLfloat g, GLfloat b) : red(r), green(g), blue(b), has_alpha(false) {}
    Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : red(r), green(g), blue(b), alpha(a), has_alpha(true) {}

} Color;

namespace glAPI
{

    // Window related
    void Clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void SetViewport(GLsizei width, GLsizei height);

    // Buffers related
    void DrawArrays(GLsizei count);
    void DrawElements(GLsizei count);

    // Shader related
    void SetUniformValue(Shader& shader, const std::string& variable, Color);
    GLint GetUniformLocation(Shader& shader, const std::string& variable);
}
