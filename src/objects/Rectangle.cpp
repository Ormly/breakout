#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 center, GLfloat width, GLfloat height):
m_center(center), m_width(width), m_height(height)
{
    updateVertices();
}

void Rectangle::updateVertices()
{
    m_vertices.clear();
    m_vertices.push_back(m_center.x - m_width / 2);
    m_vertices.push_back(m_center.y - m_height / 2);
    m_vertices.push_back(m_center.x + m_width / 2);
    m_vertices.push_back(m_center.y - m_height / 2);
    m_vertices.push_back(m_center.x + m_width / 2);
    m_vertices.push_back(m_center.y + m_height / 2);
    m_vertices.push_back(m_center.x - m_width / 2);
    m_vertices.push_back(m_center.y + m_height / 2);
}

glm::vec2 Rectangle::getCenter() const
{
    return m_center;
}

GLfloat Rectangle::getWidth() const
{
    return m_width;
}

GLfloat Rectangle::getHeight() const
{
    return m_height;
}

std::vector<GLfloat> Rectangle::getVertices() const
{
    return m_vertices;
}

std::vector<GLuint> Rectangle::getIndices() const
{
    return m_indices;
}

std::vector<GLfloat> Rectangle::getCollisionBox() const
{
    return m_vertices;
}
