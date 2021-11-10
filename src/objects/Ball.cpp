#include "Ball.h"

#include <utility>

Ball::Ball(std::vector<GLfloat> positions,std::vector<GLuint> indices, std::vector<GLfloat> color, glm::vec2 initialVelocity, glm::vec2 initialCenter, GLfloat initialSpeed, GLfloat sideLength)
:m_positions(std::move(positions)), m_indices(std::move(indices)), m_color(std::move(color)), m_center(initialCenter), m_speed(initialSpeed), m_sideLength(sideLength)
{
    m_velocity.x = initialVelocity.x + initialSpeed;
    m_velocity.y = initialVelocity.y + initialSpeed;
    m_offset.x = 0;
    m_offset.y = 0;

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

std::vector<GLfloat> Ball::getCollisionBox() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_center.x - m_sideLength / 2);
    collisionBox.push_back(m_center.y - m_sideLength / 2);
    collisionBox.push_back(m_center.x + m_sideLength / 2);
    collisionBox.push_back(m_center.y - m_sideLength / 2);
    collisionBox.push_back(m_center.x + m_sideLength / 2);
    collisionBox.push_back(m_center.y + m_sideLength / 2);
    collisionBox.push_back(m_center.x - m_sideLength / 2);
    collisionBox.push_back(m_center.y + m_sideLength / 2);

    return collisionBox;
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
    m_velocity.x = velocity.x;
    m_velocity.y = velocity.y;
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

void Ball::addToOffset(GLfloat additionX, GLfloat additionY)
{
    m_offset.x += additionX;
    m_offset.y += additionY;

    m_center.x += additionX;
    m_center.y += additionY;
}

glm::vec2 Ball::getOffset() const
{
    return m_offset;
}

glm::vec2 Ball::getCenter() const
{
    return m_center;
}

GLfloat Ball::getSideLength() const
{
    return m_sideLength;
}

void Ball::addToSpeed(GLfloat addition)
{
    m_speed += addition;
    m_velocity.x += addition;
    m_velocity.y += addition;
}
