#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "RenderableRectangle.h"

class Brick : public RenderableRectangle
{
private:
    GLboolean m_alive;
public:
    Brick(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color);
    GLboolean isAlive() const;
    void kill();
};


#endif //BREAKOUT_BRICK_H
