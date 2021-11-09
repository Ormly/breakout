#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include "GL/glew.h"
#include <vector>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include "glm/glm.hpp"

class Paddle
{
private:
    std::vector<GLfloat> m_data;
    GLuint m_dataSize;
    std::vector<GLuint> m_indices;
    GLuint m_numberOfIndices;
    std::vector<GLfloat> m_color;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    GLfloat m_paddleWidth;
    GLfloat m_paddleHeight;
    glm::vec2 m_center;
    GLfloat m_offset;
    std::vector<GLfloat> m_origin;
public:
    Paddle(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices, std::vector<GLfloat> color, GLfloat paddleWidth, GLfloat paddleHeight, glm::vec2 center);
    std::vector<GLfloat> getCollisionBox() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    void addToOffset(GLfloat addition);
    GLfloat getOffset() const;
    GLfloat getWidth() const;
    GLfloat getHeight() const;
    void resetPaddleBuffer();
    //void translate(GLfloat offset);
};


#endif //BREAKOUT_PADDLE_H
