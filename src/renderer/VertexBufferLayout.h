#ifndef BREAKOUT_VERTEXBUFFERLAYOUT_H
#define BREAKOUT_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <string>
#include "GL/glew.h"

struct LayoutElement
{
    GLuint type;
    GLuint numberOfElements;
    GLchar normalized;

    static GLuint getSizeOfType(GLuint type)
    {
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }

        //TODO: check for nonexistent type
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<LayoutElement> m_layoutElements;
    GLuint m_stride;
public:
    VertexBufferLayout();

    template<typename T>
    void push(GLuint numberOfElements){}

    std::vector<LayoutElement> getLayoutElements() const;
    GLuint getStride() const;
};

template<> inline void VertexBufferLayout::push<GLfloat>(GLuint numberOfElements)
{
    m_layoutElements.push_back({GL_FLOAT, numberOfElements, GL_FALSE});
    m_stride += LayoutElement::getSizeOfType(GL_FLOAT) * numberOfElements;
}

template<> inline void VertexBufferLayout::push<GLuint>(GLuint numberOfElements)
{
    m_layoutElements.push_back({GL_UNSIGNED_INT, numberOfElements, GL_FALSE});
    m_stride += LayoutElement::getSizeOfType(GL_UNSIGNED_INT) * numberOfElements;
}

template<> inline void VertexBufferLayout::push<GLchar>(GLuint numberOfElements)
{
    m_layoutElements.push_back({GL_UNSIGNED_BYTE, numberOfElements, GL_TRUE});
    m_stride += LayoutElement::getSizeOfType(GL_UNSIGNED_BYTE) * numberOfElements;
}


#endif //BREAKOUT_VERTEXBUFFERLAYOUT_H
