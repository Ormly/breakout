#include "Brick.h"

#include <utility>

Brick::Brick(std::vector<GLfloat> positions, GLuint id,
             GLfloat height, GLfloat width, glm::vec2 center)
:m_positions(std::move(positions)), m_id(id), m_alive(GL_TRUE),
m_width(width), m_height(height), m_center(center)
{

}

GLboolean Brick::isAlive() const
{
    return m_alive;
}

void Brick::kill()
{
    m_alive = GL_FALSE;
}

GLboolean Brick::getID() const
{
    return m_id;
}

const std::vector<GLfloat> &Brick::getPositions() const
{
    return m_positions;
}

std::vector<GLfloat> Brick::getCollisionBox() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_center.x - m_width / 2);
    collisionBox.push_back(m_center.y - m_height / 2);
    collisionBox.push_back(m_center.x + m_width / 2);
    collisionBox.push_back(m_center.y - m_height / 2);
    collisionBox.push_back(m_center.x + m_width / 2);
    collisionBox.push_back(m_center.y + m_height / 2);
    collisionBox.push_back(m_center.x - m_width / 2);
    collisionBox.push_back(m_center.y + m_height / 2);

    return collisionBox;
}

GLfloat Brick::getWidth() const
{
    return m_width;
}

GLfloat Brick::getHeight() const
{
    return m_height;
}

