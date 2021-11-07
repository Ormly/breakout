#ifndef BREAKOUT_FRAME_H
#define BREAKOUT_FRAME_H

#include "GL/glew.h"
#include <vector>

class Frame
{
private:
    std::vector<GLfloat> m_data;
    GLuint m_dataSize;
    std::vector<GLuint> m_indices;
    GLuint m_numberOfIndices;
    std::vector<std::vector<GLuint>> m_collisionBoxes;
    std::vector<GLfloat> m_color;
public:
    Frame(std::vector<GLfloat> data, GLuint dataSize, std::vector<GLuint> indices, GLuint numberOfIndices, std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color);
    std::vector<GLfloat> getData() const;
    GLuint getDataSize() const;
    std::vector<GLuint> getIndices() const;
    GLuint getNumberOfIndices() const;
    std::vector<std::vector<GLuint>> getCollisionBoxes() const;
    std::vector<GLfloat> getColor() const;
};


#endif //BREAKOUT_FRAME_H
