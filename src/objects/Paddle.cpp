#include "Paddle.h"
#include <iostream>
#include <utility>

Paddle::Paddle(std::vector<GLfloat> data, GLuint dataSize,std::vector<GLuint> indices, GLuint numberOfIndices,
               std::vector<GLfloat> color, GLfloat paddleWidth, GLfloat paddleHeight, glm::vec2 center)
               : m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)),
                 m_numberOfIndices(numberOfIndices), m_color(std::move(color)),
                 m_paddleWidth(paddleWidth), m_offset(0.0f), m_paddleHeight(paddleHeight), m_center(center)
{
    m_origin = m_data;
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

std::vector<GLfloat> Paddle::getCollisionBox() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_center.x - m_paddleWidth / 2);
    collisionBox.push_back(m_center.y);
    collisionBox.push_back(m_center.x + m_paddleWidth / 2);
    collisionBox.push_back(m_center.y);
    collisionBox.push_back(m_center.x + m_paddleWidth / 2);
    collisionBox.push_back(m_center.y + m_paddleHeight / 2);
    collisionBox.push_back(m_center.x - m_paddleWidth / 2);
    collisionBox.push_back(m_center.y + m_paddleHeight / 2);

    return collisionBox;
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
    m_center.x += addition;

    m_origin.at(0) += addition;
    m_origin.at(2) += addition;
    m_origin.at(4) += addition;
    m_origin.at(6) += addition;

    if(m_origin.at(0) < 20.0f)
    {
        m_origin.at(0) = 20.0f;
        m_origin.at(2) = 20.0f + m_paddleWidth;
        m_origin.at(4) = 20.0f + m_paddleWidth;
        m_origin.at(6) = 20.0f;

        m_offset = 0.0f;

        resetPaddleBuffer();
    }

    if(m_origin.at(2) > 748.0f)
    {
        m_origin.at(0) = 748.0f - m_paddleWidth;
        m_origin.at(2) = 748.0f;
        m_origin.at(4) = 748.0f;
        m_origin.at(6) = 748.0f - m_paddleWidth;

        m_offset = 0.0f;

        resetPaddleBuffer();
    }
}

void Paddle::resetPaddleBuffer()
{
    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_origin.data(), m_origin.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

GLfloat Paddle::getWidth() const
{
    return m_paddleWidth;
}

GLfloat Paddle::getHeight() const
{
    return m_paddleHeight;
}

