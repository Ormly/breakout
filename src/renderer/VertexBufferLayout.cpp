#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
:m_stride(0)
{

}

GLuint VertexBufferLayout::getStride() const
{
    return m_stride;
}

std::vector<LayoutElement> VertexBufferLayout::getLayoutElements() const
{
    return m_layoutElements;
}
