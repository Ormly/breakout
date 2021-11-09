#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "GL/glew.h"
#include <vector>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include "glm/glm.hpp"

class Ball
{
private:
    std::vector<GLfloat> m_positions;
    std::vector<GLuint> m_indices;
    glm::vec2 m_velocity;
    glm::vec2 m_offset;
    glm::vec2 m_center;
    GLfloat m_speed;
    std::vector<GLfloat> m_color;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    GLfloat m_sideLength;
public:
    Ball(std::vector<GLfloat> positions, std::vector<GLuint> indices, std::vector<GLfloat> color, glm::vec2 initialVelocity, glm::vec2 initialCenter, GLfloat initialSpeed, GLfloat sideLength);
    std::vector<GLfloat> getPositions() const;
    void setSpeed(GLfloat speed);
    GLfloat getSpeed() const;
    void setVelocity(glm::vec2 velocity);
    glm::vec2 getVelocity() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    void addToOffset(GLfloat additionX, GLfloat additionY);
    glm::vec2 getOffset() const;
    glm::vec2 getCenter() const;
    GLfloat getSideLength() const;
    std::vector<GLfloat> getCollisionBox() const;
};


#endif //BREAKOUT_BALL_H
