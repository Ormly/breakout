#include "Paddle.h"

#include <utility>

Paddle::Paddle(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color, GLfloat initialSpeed) : RenderableRectangle(center, width, height, std::move(color)),
                                                                                                                    m_offset(0.0f), m_speed(initialSpeed)
{

}

void Paddle::addToOffset(GLfloat addition)
{
    m_offset += addition;
    m_center.x += addition;

    m_vertices.at(0) += addition;
    m_vertices.at(2) += addition;
    m_vertices.at(4) += addition;
    m_vertices.at(6) += addition;

    if(m_vertices.at(0) < 20.0f)
    {
        m_vertices.at(0) = 20.0f;
        m_vertices.at(2) = 20.0f + m_width;
        m_vertices.at(4) = 20.0f + m_width;
        m_vertices.at(6) = 20.0f;

        m_offset = 0.0f;

        resetBuffer();
    }

    if(m_vertices.at(2) > 748.0f)
    {
        m_vertices.at(0) = 748.0f - m_width;
        m_vertices.at(2) = 748.0f;
        m_vertices.at(4) = 748.0f;
        m_vertices.at(6) = 748.0f - m_width;

        m_offset = 0.0f;

        resetBuffer();
    }
}

GLfloat Paddle::getOffset() const
{
    return m_offset;
}

std::vector<GLfloat> Paddle::getCollisionBox() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_vertices.at(0));
    collisionBox.push_back(m_center.y);
    collisionBox.push_back(m_vertices.at(2));
    collisionBox.push_back(m_center.y);
    collisionBox.push_back(m_vertices.at(4));
    collisionBox.push_back(m_vertices.at(5));
    collisionBox.push_back(m_vertices.at(6));
    collisionBox.push_back(m_vertices.at(7));

    return collisionBox;
}

GLfloat Paddle::getSpeed() const
{
    return m_speed;
}

void Paddle::setSpeed(GLfloat speed)
{
    m_speed = speed;
}
