#include "EndScreen.h"

EndScreen::EndScreen(std::vector<RenderableRectangle *> &rectangles): m_rectangles(rectangles)
{

}

std::vector<RenderableRectangle *> EndScreen::getRectangles() const
{
    return m_rectangles;
}

std::vector<GLfloat> EndScreen::getColor() const
{
    return m_rectangles.at(0)->getColor();
}
