#include "BrickGroup.h"

#include <utility>

BrickGroup::BrickGroup(std::vector<Brick*> bricks, std::vector<GLuint> brickLayout, std::vector<GLfloat> color)
:m_bricks(std::move(bricks)), m_indices(std::move(brickLayout)), m_color(std::move(color)), m_penetrated(GL_FALSE)
{
    for(const Brick *brick : m_bricks)
        m_data.insert(m_data.end(), brick->getPositions().begin(), brick->getPositions().end());

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_data.data(), m_data.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_indices.size());
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

void BrickGroup::kill(GLuint id)
{
    for(Brick* brick : m_bricks)
    {
        if(brick->getID() == id && brick->isAlive())
        {
            brick->kill();
        }
    }

    resetBuffer();
}

void BrickGroup::resetBuffer()
{
    m_data.clear();
    for(const Brick* brick : m_bricks)
    {
        if(brick->isAlive())
            m_data.insert(m_data.end(), brick->getPositions().begin(), brick->getPositions().end());
    }

    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_data.data(), m_data.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

std::vector<Brick*> BrickGroup::getBricks() const
{
    return m_bricks;
}

std::vector<GLfloat> BrickGroup::getColor() const
{
    return m_color;
}

VertexArray *BrickGroup::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *BrickGroup::getIndexBuffer() const
{
    return m_indexBuffer;
}

GLboolean BrickGroup::isPenetrated() const
{
    return m_penetrated;
}
