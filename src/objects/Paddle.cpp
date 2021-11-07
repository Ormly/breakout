#include "Paddle.h"

#include <utility>


Paddle::Paddle(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
               std::vector<GLuint> collisionBox, std::vector<GLfloat> color)
               :m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)),
               m_numberOfIndices(numberOfIndices), m_collisionBox(std::move(collisionBox)), m_color(std::move(color))
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

std::vector<GLuint> Paddle::getCollisionBox() const
{
    return m_collisionBox;
}

VertexArray *Paddle::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Paddle::getIndexBuffer() const
{
    return m_indexBuffer;
}

std::vector<GLfloat> Paddle::getColor() const
{
    return m_color;
}

