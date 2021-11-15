#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include "RenderableRectangle.h"

class Paddle : public RenderableRectangle
{
private:
    GLfloat m_offset;
public:
    Paddle(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color);
    void addToOffset(GLfloat addition);
    GLfloat getOffset() const;
    std::vector<GLfloat> getCollisionBox() const override;
};


#endif //BREAKOUT_PADDLE_H
