#ifndef VAO_H
#define VAO_H
#include <GL/glew.h>
class VAO
{
public:
    enum BufferType : int 
    {
        ARRAY = GL_ARRAY_BUFFER,
        ELEMENT = GL_ELEMENT_ARRAY_BUFFER
    };
    enum DrawMode : int 
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };

    VAO();
    void Init();
    ~VAO();
    void Delete();
    void AttachBuffer(const GLuint type, const size_t size, const GLuint mode, const void* data);
    void Bind() const;
    void UnBind() const;
    // TODO maybe make it track the index and not take it as an argument
    void AddAttributef(const GLuint index, const int size, const GLuint stride, const void* offset);
    void AddAttributei(const GLuint index, const int size, const GLuint stride, const void* offset);

private:
    GLuint m_vao{0};
};

#endif // DEBUG