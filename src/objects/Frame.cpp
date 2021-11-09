#include "Frame.h"

#include <utility>

Frame::Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
             std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color,
             std::vector<GLfloat> widths, std::vector<GLfloat> heights, std::vector<glm::vec2> centers)
             : m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)), m_numberOfIndices(numberOfIndices),
             m_collisionBoxes(std::move(collisionBoxes)), m_color(std::move(color)), m_widths(std::move(widths)), m_heights(std::move(heights)), m_centers(std::move(centers))
{
    m_leftHeight = m_heights.at(0);
    m_rightHeight = m_heights.at(1);
    m_topHeight = m_heights.at(2);

    m_leftWidth = m_widths.at(0);
    m_rightWidth = m_widths.at(1);
    m_topWidth = m_widths.at(2);

    m_leftCenter.x = m_centers.at(0).x;
    m_leftCenter.y = m_centers.at(0).y;
    m_rightCenter.x = m_centers.at(1).x;
    m_rightCenter.y = m_centers.at(1).y;
    m_topCenter.x = m_centers.at(2).x;
    m_topCenter.y = m_centers.at(2).y;

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_data.data(), m_dataSize);
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_numberOfIndices);
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

std::vector<GLfloat> Frame::getColor() const
{
    return m_color;
}

VertexArray *Frame::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Frame::getIndexBuffer() const
{
    return m_indexBuffer;
}

std::vector<GLfloat> Frame::getCollisionBoxLeft() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_leftCenter.x - m_leftWidth / 2);
    collisionBox.push_back(m_leftCenter.y - m_leftHeight / 2);
    collisionBox.push_back(m_leftCenter.x + m_leftWidth / 2);
    collisionBox.push_back(m_leftCenter.y - m_leftHeight / 2);
    collisionBox.push_back(m_leftCenter.x + m_leftWidth / 2);
    collisionBox.push_back(m_leftCenter.y + m_leftHeight / 2);
    collisionBox.push_back(m_leftCenter.x - m_leftWidth / 2);
    collisionBox.push_back(m_leftCenter.y + m_leftHeight / 2);

    return collisionBox;
}

std::vector<GLfloat> Frame::getCollisionBoxRight() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_rightCenter.x - m_rightWidth / 2);
    collisionBox.push_back(m_rightCenter.y - m_rightHeight / 2);
    collisionBox.push_back(m_rightCenter.x + m_rightWidth / 2);
    collisionBox.push_back(m_rightCenter.y - m_rightHeight / 2);
    collisionBox.push_back(m_rightCenter.x + m_rightWidth / 2);
    collisionBox.push_back(m_rightCenter.y + m_rightHeight / 2);
    collisionBox.push_back(m_rightCenter.x - m_rightWidth / 2);
    collisionBox.push_back(m_rightCenter.y + m_rightHeight / 2);

    return collisionBox;
}

std::vector<GLfloat> Frame::getCollisionBoxTop() const
{
    std::vector<GLfloat> collisionBox;
    collisionBox.push_back(m_topCenter.x - m_topWidth / 2);
    collisionBox.push_back(m_topCenter.y - m_topHeight / 2);
    collisionBox.push_back(m_topCenter.x + m_topWidth / 2);
    collisionBox.push_back(m_topCenter.y - m_topHeight / 2);
    collisionBox.push_back(m_topCenter.x + m_topWidth / 2);
    collisionBox.push_back(m_topCenter.y + m_topHeight / 2);
    collisionBox.push_back(m_topCenter.x - m_topWidth / 2);
    collisionBox.push_back(m_topCenter.y + m_topHeight / 2);

    return collisionBox;
}

GLfloat Frame::getLeftWidth() const
{
    return m_widths.at(0);
}

GLfloat Frame::getLeftHeight() const
{
    return m_heights.at(0);
}

GLfloat Frame::getRightWidth() const
{
    return m_widths.at(1);
}

GLfloat Frame::getRightHeight() const
{
    return m_heights.at(1);
}

GLfloat Frame::getTopWidth() const
{
    return m_widths.at(2);
}

GLfloat Frame::getTopHeight() const
{
    return m_heights.at(2);
}
