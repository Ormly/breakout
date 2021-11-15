#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include "RenderableRectangle.h"

class Paddle : public RenderableRectangle
{
private:
    GLfloat m_offset;
    GLfloat m_speed;
public:
    Paddle(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color, GLfloat initialSpeed);
    void addToOffset(GLfloat addition);
    GLfloat getOffset() const;
    std::vector<GLfloat> getCollisionBox() const override;
    void setSpeed(GLfloat speed);
    GLfloat getSpeed() const;
};


#endif //BREAKOUT_PADDLE_H
