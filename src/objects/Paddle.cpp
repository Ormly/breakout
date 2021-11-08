#include "Paddle.h"
#include <iostream>

Paddle::Paddle(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
               std::vector<GLuint> collisionBoxIndices, std::vector<GLfloat> color, GLuint paddleSize)
               :m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)),
               m_numberOfIndices(numberOfIndices), m_color(std::move(color)),
               m_paddleSize(paddleSize), m_offset(0.0f)
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

    m_collisionBox = m_data;
}

std::vector<GLfloat> Paddle::getCollisionBox() const
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

GLfloat Paddle::getOffset() const
{
    return m_offset;
}

void Paddle::addToOffset(GLfloat addition)
{
    m_offset += addition;

    m_collisionBox.at(0) += addition;
    m_collisionBox.at(2) += addition;
    m_collisionBox.at(4) += addition;
    m_collisionBox.at(6) += addition;

    if(m_collisionBox.at(0) < 20.0f)
    {
        m_collisionBox.at(0) = 20.0f;
        m_collisionBox.at(2) = 20.0f + m_paddleSize;
        m_collisionBox.at(4) = 20.0f + m_paddleSize;
        m_collisionBox.at(6) = 20.0f;

        m_offset = 0.0f;

        resetPaddleBuffer();
    }

    if(m_collisionBox.at(2) > 748.0f)
    {
        m_collisionBox.at(0) = 748.0f - m_paddleSize;
        m_collisionBox.at(2) = 748.0f;
        m_collisionBox.at(4) = 748.0f;
        m_collisionBox.at(6) = 748.0f - m_paddleSize;

        m_offset = 0.0f;

        resetPaddleBuffer();
    }

    /*
    std::cout <<
    "Offset: " <<
    m_offset <<
    "\n" <<
    "Left X: " <<
    m_collisionBox.at(0) <<
    "\n" <<
    "Right X: " <<
    m_collisionBox.at(2) <<
    std::endl;
     */
}

void Paddle::resetPaddleBuffer()
{
    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_collisionBox.data(), m_collisionBox.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

