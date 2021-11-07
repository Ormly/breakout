#ifndef BREAKOUT_FRAME_H
#define BREAKOUT_FRAME_H

#include "GL/glew.h"
#include <vector>

class Frame
{
private:
    void* m_data;
    GLuint m_dataSize;
    void* m_indices;
    GLuint m_numberOfIndices;
    std::vector<std::vector<GLuint>> m_collisionBoxes;
    std::vector<GLfloat> m_color;
public:
    Frame(void* data, GLuint dataSize, void* indices, GLuint numberOfIndices, std::vector<std::vector<GLuint>> collisionBoxes, std::vector<GLfloat> color);
    void* getData() const;
    GLuint getDataSize() const;
    void* getIndices() const;
    GLuint getNumberOfIndices() const;
    std::vector<std::vector<GLuint>> getCollisionBoxes() const;
    std::vector<GLfloat> getColor() const;
};


#endif //BREAKOUT_FRAME_H
