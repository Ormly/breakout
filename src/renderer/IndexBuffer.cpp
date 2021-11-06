#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint* data, GLuint numberOfIndices)
:m_numberOfIndices(numberOfIndices)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numberOfIndices, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::getNumberOfIndices() const
{
    return m_numberOfIndices;
}

