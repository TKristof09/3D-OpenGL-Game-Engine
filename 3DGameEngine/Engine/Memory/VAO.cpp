#include "VAO.h"
#include <iostream>
VAO::VAO()
{
}

void VAO::Init()
{
    glGenVertexArrays(1, &m_vao);

}
VAO::~VAO()
{
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &m_vao);
}

void VAO::AttachBuffer(const GLuint type, const size_t size, const GLuint mode, const void* data)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
	glBindBuffer(type, buffer);
    glBufferData(type, size, data, mode);
}

void VAO::Bind() const
{
    glBindVertexArray(m_vao);
}

void VAO::UnBind() const
{
    glBindVertexArray(0);
}

void VAO::AddAttributef(const GLuint index, const int size, const GLuint stride, const void* offset)
{
    glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
}

void VAO::AddAttributei(const GLuint index, const int size, const GLuint stride, const void* offset)
{
    glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, GL_INT, stride, offset);
}