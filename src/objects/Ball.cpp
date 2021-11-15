#include "Ball.h"

Ball::Ball(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color, glm::vec2 initialVelocity,GLfloat initialSpeed):
RenderableRectangle(center, width, height, std::move(color))
{
    m_velocity.x = initialVelocity.x + initialSpeed;
    m_velocity.y = initialVelocity.y + initialSpeed;
    m_offset.x = 0;
    m_offset.y = 0;
}

void Ball::setSpeed(GLfloat speed)
{
    m_speed = speed;
}

GLfloat Ball::getSpeed() const
{
    return m_speed;
}

void Ball::setVelocity(glm::vec2 velocity)
{
    m_velocity.x = velocity.x;
    m_velocity.y = velocity.y;
}

glm::vec2 Ball::getVelocity() const
{
    return m_velocity;
}

void Ball::addToOffset(GLfloat additionX, GLfloat additionY)
{
    m_offset.x += additionX;
    m_offset.y += additionY;

    m_center.x += additionX;
    m_center.y += additionY;

    updateVertices();
}

glm::vec2 Ball::getOffset() const
{
    return m_offset;
}

void Ball::addToSpeed(GLfloat addition)
{
    m_speed += addition;
    m_velocity.x += addition;
    m_velocity.y += addition;
}
