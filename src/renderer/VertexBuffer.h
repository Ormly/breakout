#ifndef BREAKOUT_VERTEXBUFFER_H
#define BREAKOUT_VERTEXBUFFER_H

#include "GL/glew.h"

class VertexBuffer
{
private:
    GLuint m_bufferID;
public:
    VertexBuffer(const void* data, const GLuint size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif //BREAKOUT_VERTEXBUFFER_H

