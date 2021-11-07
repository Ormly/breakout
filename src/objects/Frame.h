#ifndef BREAKOUT_FRAME_H
#define BREAKOUT_FRAME_H

#include "GL/glew.h"
#include <vector>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"

class Frame
{
private:
    std::vector<GLfloat> m_data;
    GLuint m_dataSize;
    std::vector<GLuint> m_indices;
    GLuint m_numberOfIndices;
    std::vector<std::vector<GLuint>> m_collisionBoxes;
    std::vector<GLfloat> m_color;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
public:
    Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices, std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color);
    std::vector<std::vector<GLuint>> getCollisionBoxes() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
};


#endif //BREAKOUT_FRAME_H
