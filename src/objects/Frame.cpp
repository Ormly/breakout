#include "Frame.h"

#include <utility>

Frame::Frame(void *data, GLuint dataSize, void *indices, GLuint numberOfIndices,
             std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color)
             : m_data(data), m_dataSize(dataSize), m_indices(indices), m_numberOfIndices(numberOfIndices),
             m_collisionBoxes(std::move(collisionBoxes)), m_color(std::move(color))
{

}

std::vector<std::vector<GLuint>> Frame::getCollisionBoxes() const
{
    return m_collisionBoxes;
}

void *Frame::getData() const
{
    return m_data;
}

GLuint Frame::getDataSize() const
{
    return m_dataSize;
}

void *Frame::getIndices() const
{
    return m_indices;
}

GLuint Frame::getNumberOfIndices() const
{
    return m_numberOfIndices;
}

std::vector<GLfloat> Frame::getColor() const
{
    return m_color;
}
