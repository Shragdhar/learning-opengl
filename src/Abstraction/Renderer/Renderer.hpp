#include <glad/glad.h>

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

namespace glAPI
{
    void Clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void SetViewport(GLsizei width, GLsizei height);
}
