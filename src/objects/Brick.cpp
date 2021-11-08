#include "Brick.h"

#include <utility>

Brick::Brick(std::vector<GLfloat> positions, GLuint id)
:m_positions(std::move(positions)), m_id(id), m_alive(GL_TRUE)
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

