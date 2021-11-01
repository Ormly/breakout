#ifndef BREAKOUT_SHADERS_H
#define BREAKOUT_SHADERS_H

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "glm/glm.hpp"

class Shaders
{
private:
    GLuint m_programID;
    std::string m_vertexShaderPath;
    std::string m_fragmentShaderPath;
    std::unordered_map<std::string, GLint> m_uniformLocationCache;
public:
    Shaders(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shaders();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    GLboolean readShadersFromFile();
    GLuint compileVertexShader();
    GLuint compileFragmentShader();
    GLuint createShaders();
    GLuint getUniformLocation(const std::string& name);
};


#endif //BREAKOUT_SHADERS_H
