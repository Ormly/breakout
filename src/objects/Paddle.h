#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include "GL/glew.h"
#include <vector>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"

class Paddle
{
private:
    std::vector<GLfloat> m_data;
    GLuint m_dataSize;
    std::vector<GLuint> m_indices;
    GLuint m_numberOfIndices;
    std::vector<GLfloat> m_collisionBox;
    std::vector<GLfloat> m_color;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    GLuint m_paddleSize;
    GLfloat m_offset;
public:
    Paddle(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices, std::vector<GLuint> collisionBoxIndices, std::vector<GLfloat> color);
    std::vector<GLfloat> getCollisionBox() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    void addToOffset(GLfloat addition);
    GLfloat getOffset() const;
    void resetPaddleBuffer();
    //void translate(GLfloat offset);
};


#endif //BREAKOUT_PADDLE_H
