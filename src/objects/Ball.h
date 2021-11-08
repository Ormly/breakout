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
    GLfloat m_speed;
    std::vector<GLuint> m_collisionBox;
    std::vector<GLfloat> m_color;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
public:
    Ball(std::vector<GLfloat> positions, std::vector<GLuint> indices, std::vector<GLuint> collisionBox, std::vector<GLfloat> color);
    std::vector<GLfloat> getPositions() const;
    void setSpeed(GLfloat speed);
    GLfloat getSpeed() const;
    void setVelocity(glm::vec2 velocity);
    glm::vec2 getVelocity() const;
    std::vector<GLuint> getCollisionBox() const;
    std::vector<GLfloat> getColor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
};


#endif //BREAKOUT_BALL_H
