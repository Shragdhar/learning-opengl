#pragma once
#include <glad/glad.h>

namespace absGL
{
class VertexBuffer
{
public:
    VertexBuffer(const void *data,
                 GLsizeiptr size,
                 GLenum usage);

    void attribute(GLuint index, GLuint size, GLenum type,
                    GLboolean normalized, GLsizei stride,
                    const void *pointer);

    GLuint get_id();
    void bind();
    void unbind();

private:
    GLuint vertex_buffer_object;
};

class VertexArray
{
public:
    VertexArray();
    void add_buffer(VertexBuffer& vbo);
    GLuint get_id();
    void bind();
    void unbind();

private:
    GLuint vertex_array_object;
};
}
