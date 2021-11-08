#include "Ball.h"

#include <utility>

Ball::Ball(std::vector<GLfloat> positions,std::vector<GLuint> indices, std::vector<GLuint> collisionBox, std::vector<GLfloat> color)
:m_positions(std::move(positions)), m_indices(std::move(indices)),m_collisionBox(std::move(collisionBox)), m_color(std::move(color))
{
    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_positions.data(), m_positions.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_indices.size() * sizeof(GLuint));
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

glm::vec2 Ball::getVelocity() const
{
    return m_velocity;
}

std::vector<GLuint> Ball::getCollisionBox() const
{
    return m_collisionBox;
}

std::vector<GLfloat> Ball::getColor() const
{
    return m_color;
}

std::vector<GLfloat> Ball::getPositions() const
{
    return m_positions;
}

void Ball::setVelocity(glm::vec2 velocity)
{
    m_velocity = velocity;
}

VertexArray *Ball::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Ball::getIndexBuffer() const
{
    return m_indexBuffer;
}

GLfloat Ball::getSpeed() const
{
    return m_speed;
}

void Ball::setSpeed(GLfloat speed)
{
    m_speed = speed;
}
