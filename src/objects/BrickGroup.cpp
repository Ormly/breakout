#include "BrickGroup.h"

#include <utility>

BrickGroup::BrickGroup(std::vector<Brick*> &bricks): m_bricks(bricks)
{

}

GLboolean BrickGroup::isPenetrated() const
{
    for(int i = 0; i < m_bricks.size() / 2; ++i)
        if(!(m_bricks.at(i)->isAlive()) && !(m_bricks.at(i + (m_bricks.size() / 2))->isAlive()))
            return GL_TRUE;

    return GL_FALSE;
}

GLboolean BrickGroup::wasCleared() const
{
    GLboolean wasCleared = GL_TRUE;
    for(Brick* brick : m_bricks)
        if(brick->isAlive())
            wasCleared = GL_FALSE;

    return wasCleared;
}

std::vector<Brick *> BrickGroup::getBricks() const
{
    return m_bricks;
}
