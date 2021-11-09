#ifndef BREAKOUT_BRICKGROUP_H
#define BREAKOUT_BRICKGROUP_H

#include "GL/glew.h"
#include <vector>
#include "Brick.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"

class BrickGroup
{
private:
    std::vector<GLfloat> m_data;
    std::vector<GLuint> m_indices;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    std::vector<Brick> m_bricks;
    std::vector<GLfloat> m_color;
    GLboolean m_penetrated;
    //std::vector<GLuint> m_brickLayout;
public:
    BrickGroup(std::vector<Brick> bricks, std::vector<GLuint> brickLayout, std::vector<GLfloat> color);
    void kill(GLuint id);
    std::vector<Brick> getBricks() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    GLboolean isPenetrated() const;
    void resetBuffer();
};


#endif //BREAKOUT_BRICKGROUP_H
