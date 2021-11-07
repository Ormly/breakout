#include "Paddle.h"


Paddle::Paddle(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices,
               std::vector<GLuint> collisionBox, std::vector<GLfloat> color)
               :m_data(std::move(data)), m_dataSize(dataSize), m_indices(std::move(indices)),
               m_numberOfIndices(numberOfIndices), m_collisionBox(std::move(collisionBox)), m_color(std::move(color)),
               m_paddleSize(100)
{
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

std::vector<GLuint> Paddle::getCollisionBox() const
{
    return m_collisionBox;
}

VertexArray *Paddle::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Paddle::getIndexBuffer() const
{
    return m_indexBuffer;
}

std::vector<GLfloat> Paddle::getColor() const
{
    return m_color;
}

void Paddle::translate(GLfloat offset)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(i % 2 == 0)
        {
            m_data.at(i) += offset;
            GLfloat currentX = m_data.at(i);

            if(currentX < 20.0f)
            {
                m_data.at(0) = 20.0f;
                m_data.at(2) = 20.0f + m_paddleSize;
                m_data.at(4) = 20.0f + m_paddleSize;
                m_data.at(6) = 20.0f;

                break;
            }

            if(currentX > 748.0f)
            {
                m_data.at(0) = 748.0f - m_paddleSize;
                m_data.at(2) = 748.0f;
                m_data.at(4) = 748.0f;
                m_data.at(6) = 748.0f - m_paddleSize;

                break;
            }
        }
    }

    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_data.data(), m_dataSize);
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

/*
GLfloat Paddle::getOffset() const
{
    return m_offset;
}

void Paddle::addToOffset(GLfloat addition)
{
    m_offset += addition;
}
 */

