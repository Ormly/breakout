#include <fstream>
#include "Shaders.h"
#include <iostream>

namespace
{
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    GLint result;
    int infoLogLength;
}

Shaders::Shaders(std::string vertexShaderPath, std::string fragmentShaderPath)
: m_vertexShaderPath(std::move(vertexShaderPath)),
  m_fragmentShaderPath(std::move(fragmentShaderPath))
{
    m_programID = createShaders();
}

Shaders::~Shaders()
{
    glDeleteProgram(m_programID);
}

void Shaders::bind() const
{
    glUseProgram(m_programID);
}

void Shaders::unbind() const
{
    glUseProgram(0);
}

void Shaders::setUniform4f(const std::string &name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4)
{
    glUniform4f(getUniformLocation(name), value1, value2, value3, value4);
}

void Shaders::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

GLuint Shaders::getUniformLocation(const std::string &name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLint location = glGetUniformLocation(m_programID, name.c_str());

    //Todo: proper error handling
    if(location < 0)
        std::cout <<
        "Error: Uniform " <<
        name <<
        " does not exist." <<
        std::endl;

    m_uniformLocationCache[name] = location;

    return location;
}

GLboolean Shaders::readShadersFromFile()
{
    //TODO: error handling
    std::ifstream vertexShaderStream(m_vertexShaderPath.c_str(), std::ios::in);
    std::string line;
    if(vertexShaderStream.is_open()){
        line = "";
        while(getline(vertexShaderStream, line))
            vertexShaderCode += "\n" + line;
        vertexShaderStream.close();
    }

    std::ifstream fragmentShaderStream(m_fragmentShaderPath.c_str(), std::ios::in);
    if(fragmentShaderStream.is_open()){
        line = "";
        while(getline(fragmentShaderStream, line))
            fragmentShaderCode += "\n" + line;
        fragmentShaderStream.close();
    }
}

//Todo: combine compile functions in one, something like compileShader(shader, type)
GLuint Shaders::compileVertexShader()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    printf("Compiling shader: %s\n", m_vertexShaderPath.c_str());
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer , nullptr);
    glCompileShader(vertexShaderID);

    result = GL_FALSE;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        infoLogLength = 0;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto* errorMessage = (GLchar*)alloca(infoLogLength * sizeof(GLchar));
        glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, errorMessage);
        std::cout <<
        "Vertex Shader failed to compile \n" <<
        "Error message: " <<
        errorMessage <<
        std::endl;
        glDeleteShader(vertexShaderID);

        //Todo: error handling
    }

    std::cout << "Vertex Shader successfully compiled!" << std::endl;

    return vertexShaderID;
}

GLuint Shaders::compileFragmentShader()
{
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    printf("Compiling shader: %s\n", m_fragmentShaderPath.c_str());
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , nullptr);
    glCompileShader(fragmentShaderID);

    result = GL_FALSE;
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        infoLogLength = 0;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        auto* errorMessage = (GLchar*)alloca(infoLogLength * sizeof(GLchar));
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, errorMessage);
        std::cout <<
        "Vertex Shader failed to compile \n" <<
        "Error message: " <<
        errorMessage <<
        std::endl;
        glDeleteShader(fragmentShaderID);

        //Todo: error handling
    }

    std::cout << "Fragment Shader successfully compiled!" << std::endl;

    return fragmentShaderID;
}

GLuint Shaders::createShaders()
{
    if(!readShadersFromFile())
        std::cout << "Error: Shaders could not be read!" << std::endl;
    else
        std::cout << "Shaders successfully read!" << std::endl;

    //Todo: error handling

    GLuint programID = glCreateProgram();
    GLuint vertexShaderID = compileVertexShader();
    GLuint fragmentShaderID = compileFragmentShader();

    //Todo: error handling

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);
    glValidateProgram(programID);

    result = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if(result == GL_FALSE)
    {
        infoLogLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

        auto* errorMessage = (GLchar*)alloca(infoLogLength * sizeof(GLchar));
        glGetShaderInfoLog(programID, infoLogLength, nullptr, errorMessage);

        std::cout <<
        "Program could not be linked \n" <<
        "Error message: " <<
        errorMessage <<
        std::endl;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    std::cout << "Shaders successfully created!" << std::endl;

    return programID;
}






