#ifndef BREAKOUT_FRAME_H
#define BREAKOUT_FRAME_H

#include "GL/glew.h"
#include <vector>

class Frame
{
private:
    std::vector<GLfloat> m_positions;
    std::vector<GLfloat> m_color;
public:
    Frame(std::vector<GLfloat> positions, std::vector<GLfloat> color);
    std::vector<GLfloat> getPositions() const;
    std::vector<GLfloat> getColor() const;
};


#endif //BREAKOUT_FRAME_H
