#ifndef BREAKOUT_FRAME_H
#define BREAKOUT_FRAME_H

#include "GL/glew.h"
#include <vector>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include "glm/glm.hpp"

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

    GLfloat m_leftWidth;
    GLfloat m_leftHeight;
    glm::vec2 m_leftCenter;

    GLfloat m_rightWidth;
    GLfloat m_rightHeight;
    glm::vec2 m_rightCenter;

    GLfloat m_topWidth;
    GLfloat m_topHeight;
    glm::vec2 m_topCenter;

    std::vector<GLfloat> m_widths;
    std::vector<GLfloat> m_heights;
    std::vector<glm::vec2> m_centers;
public:
    Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices,
          GLuint numberOfIndices, std::vector<std::vector<GLuint>> collisionBoxes,
          std::vector<GLfloat> color, std::vector<GLfloat> widths, std::vector<GLfloat> heights, std::vector<glm::vec2> centers);
    std::vector<GLfloat> getCollisionBoxLeft() const;
    std::vector<GLfloat> getCollisionBoxRight() const;
    std::vector<GLfloat> getCollisionBoxTop() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    GLfloat getLeftWidth() const;
    GLfloat getLeftHeight() const;
    GLfloat getRightWidth() const;
    GLfloat getRightHeight() const;
    GLfloat getTopWidth() const;
    GLfloat getTopHeight() const;
};


#endif //BREAKOUT_FRAME_H
