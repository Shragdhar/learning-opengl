#include "Buffer.hpp"

using namespace absGL;
// ------------------ Vertex Buffer Object ------------------------

VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size, GLenum usage)
{
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER,
                 size,
                 data,
                 usage);
}

void VertexBuffer::attribute(GLuint index, GLuint size, GLenum type,
                    GLboolean normalized, GLsizei stride,
                    const void *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

GLuint VertexBuffer::get_id()
{
    return vertex_buffer_object;
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// -------------- Vertex Array Object ------------------------

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void VertexArray::add_buffer(VertexBuffer& vbo)
{
    bind();
    vbo.bind();
}

GLuint VertexArray::get_id()
{
    return vertex_array_object;
}

void VertexArray::bind()
{
    glBindVertexArray(vertex_array_object);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
