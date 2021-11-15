#include "RenderableRectangle.h"

#include <utility>

RenderableRectangle::RenderableRectangle(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color):
Rectangle(center, width, height), m_color(std::move(color))
{
    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_indices.size());
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

void RenderableRectangle::resetBuffer()
{
    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

VertexArray *RenderableRectangle::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *RenderableRectangle::getIndexBuffer() const
{
    return m_indexBuffer;
}

std::vector<GLfloat> RenderableRectangle::getColor() const
{
    return m_color;
}
