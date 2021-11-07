#include <iostream>
#include "Renderer.h"

void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

GLboolean glLogCall(const char *function, const char *file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout <<
        "[OpenGL Error] (" <<
        error <<
        "): " <<
        function <<
        " " <<
        file <<
        ":" <<
        line <<
        std::endl;

        return GL_FALSE;
    }

    return GL_TRUE;
}

void Renderer::draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shaders &shaders) const
{
    vertexArray.bind();
    shaders.bind();
    indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, indexBuffer.getNumberOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
