#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H
#include "GL/glew.h"
#include <vector>

class Brick
{
private:
    std::vector<GLfloat> m_positions;
    GLuint m_id;
    GLboolean m_alive;
public:
    Brick(std::vector<GLfloat> positions, GLuint id);
    const std::vector<GLfloat> &getPositions() const;
    GLboolean getID() const;
    GLboolean isAlive() const;
    void kill();
};


#endif //BREAKOUT_BRICK_H
