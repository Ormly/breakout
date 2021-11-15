#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "RenderableRectangle.h"

class Ball : public RenderableRectangle
{
private:
    glm::vec2 m_velocity;
    glm::vec2 m_offset;
    GLfloat m_speed;
public:
    Ball(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color, glm::vec2 initialVelocity, GLfloat initialSpeed);
    void setSpeed(GLfloat speed);
    GLfloat getSpeed() const;
    void setVelocity(glm::vec2 velocity);
    glm::vec2 getVelocity() const;
    void addToOffset(GLfloat additionX, GLfloat additionY);
    glm::vec2 getOffset() const;
    void addToSpeed(GLfloat addition);
};


#endif //BREAKOUT_BALL_H
