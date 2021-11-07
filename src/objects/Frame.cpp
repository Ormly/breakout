#include "Frame.h"

#include <utility>

Frame::Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
             std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color)
             : m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)), m_numberOfIndices(numberOfIndices),
             m_collisionBoxes(std::move(collisionBoxes)), m_color(std::move(color))
{

}

std::vector<std::vector<GLuint>> Frame::getCollisionBoxes() const
{
    return m_collisionBoxes;
}

std::vector<GLfloat> Frame::getData() const
{
    return m_data;
}

GLuint Frame::getDataSize() const
{
    return m_dataSize;
}

std::vector<GLuint> Frame::getIndices() const
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
