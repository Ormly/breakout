#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H
#include "GL/glew.h"
#include <vector>
#include "glm/glm.hpp"

class Brick
{
private:
    std::vector<GLfloat> m_positions;
    GLuint m_id;
    GLboolean m_alive;
    GLfloat m_height;
    GLfloat m_width;
    glm::vec2 m_center;
public:
    Brick(std::vector<GLfloat> positions, GLuint id, GLfloat height, GLfloat width, glm::vec2 center);
    const std::vector<GLfloat> &getPositions() const;
    GLboolean getID() const;
    GLboolean isAlive() const;
    void kill();
    std::vector<GLfloat> getCollisionBox() const;
    GLfloat getWidth() const;
    GLfloat getHeight() const;
};


#endif //BREAKOUT_BRICK_H
