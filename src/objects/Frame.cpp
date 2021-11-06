#include "Frame.h"

#include <utility>

std::vector<GLfloat> Frame::getPositions() const
{
    return m_positions;
}

Frame::Frame(std::vector<GLfloat> positions, std::vector<GLfloat> color)
:m_positions(std::move(positions)),
m_color(std::move(color))
{

}

std::vector<GLfloat> Frame::getColor() const
{
    return m_color;
}
