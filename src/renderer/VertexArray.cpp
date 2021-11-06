#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_arrayID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_arrayID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &vertexBufferLayout)
{
    bind();
    vertexBuffer.bind();

    std::vector<LayoutElement> elements = vertexBufferLayout.getLayoutElements();
    GLuint offset = 0;
    for(GLuint i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              element.numberOfElements,
                              element.type,
                              element.normalized,
                              vertexBufferLayout.getStride(),
                              (const void*) offset);

        offset += element.numberOfElements * LayoutElement::getSizeOfType(element.type);
    }
}
