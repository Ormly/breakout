#include "Brick.h"

#include <utility>

Brick::Brick(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color):
RenderableRectangle(center, width, height, std::move(color)), m_alive(GL_TRUE)
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
