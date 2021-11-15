#ifndef BREAKOUT_RENDERABLERECTANGLE_H
#define BREAKOUT_RENDERABLERECTANGLE_H

#include "Rectangle.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"

class RenderableRectangle : public Rectangle
{
private:
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    std::vector<GLfloat> m_color;
protected:
    virtual void resetBuffer();
public:
    RenderableRectangle(glm::vec2 center, GLfloat width, GLfloat height, std::vector<GLfloat> color);
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    std::vector<GLfloat> getColor() const;
};


#endif //BREAKOUT_RENDERABLERECTANGLE_H
