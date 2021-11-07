#include "Frame.h"

Frame::Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
             std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color)
             : m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)), m_numberOfIndices(numberOfIndices),
             m_collisionBoxes(std::move(collisionBoxes)), m_color(std::move(color))
{
    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_data.data(), m_dataSize);
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_numberOfIndices);
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

std::vector<std::vector<GLuint>> Frame::getCollisionBoxes() const
{
    return m_collisionBoxes;
}

std::vector<GLfloat> Frame::getColor() const
{
    return m_color;
}

VertexArray *Frame::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Frame::getIndexBuffer() const
{
    return m_indexBuffer;
}
