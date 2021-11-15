#ifndef BREAKOUT_ENDSCREEN_H
#define BREAKOUT_ENDSCREEN_H

#include "RenderableRectangle.h"

class EndScreen
{
private:
    std::vector<RenderableRectangle*> m_rectangles;
public:
    EndScreen(std::vector<RenderableRectangle*> &rectangles);
    std::vector<RenderableRectangle*> getRectangles() const;
    std::vector<GLfloat> getColor() const;
};


#endif //BREAKOUT_ENDSCREEN_H
