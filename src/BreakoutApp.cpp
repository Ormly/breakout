#include "BreakoutApp.h"

#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer/Shaders.h"
#include "renderer/Renderer.h"



static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
}

int main()
{
    windowWidth = 768.0f;
    windowHeight = 1024.0f;

    glfwSetErrorCallback(error_callback);

    if(!initializeWindow())
        exit(EXIT_FAILURE);


    initializeGameObjects();

    //glm::mat4 transform(glm::translate());
    Shaders shaders("../res/shaders/VertexShader.vertexshader",
                    "../res/shaders/FragmentShader.fragmentshader");
    shaders.bind();
    glm::mat4 projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
    glm::mat4 identity(1.0f);
    shaders.setUniformMat4f("u_projection", projection);
    //shaders.setUniformMat4f("u_transform", identity);

    Renderer renderer;
    shaders.unbind();
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();
        //draw Frame
        shaders.setUniform4f("u_color", frame->getColor().at(0), frame->getColor().at(1), frame->getColor().at(2), frame->getColor().at(3));
        renderer.draw(*frameVertexArray,*frameIndexBuffer, shaders);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLboolean initializeWindow()
{
    if (!glfwInit())
    {
        std::cout <<
        "GLFW Error: Library could not be initialized!" <<
        std::endl;

        return GL_FALSE;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "breakout", nullptr, nullptr);
    if (!window)
    {
        std::cout <<
        "GLFW Error: Window context could not be initialized!" <<
        std::endl;

        return GL_FALSE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout <<
                  "GLEW Error: Could not be initialized!";

        return GL_FALSE;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}

GLboolean initializeGameObjects()
{
    //Initialize Frame
    std::vector<GLfloat> frameData = {
            0.0f,0.0f,
            20.0f,0.0f,
            748.0f,0.0f,
            768.0f,0.0f,
            768.0f,1004.0f,
            768.0f,1024.0f,
            748.0f,1024.0f,
            20.0f,1024.0f,
            0.0f,1024.0f,
            0.0f,1004.0f
    };

    std::vector<GLuint> frameIndices = {
            0, 1, 7,
            7, 8, 0,
            2, 3, 5,
            5, 6, 2,
            4, 5, 8,
            8, 9, 4
    };

    //Todo: Make this not be stupid as hell
    std::vector<GLuint> frameCollisionBoxFirst({0,1,7,7,8,0});
    std::vector<GLuint> frameCollisionBoxSecond({2,3,5,5,6,2});
    std::vector<GLuint> frameCollisionBoxThird({4,5,8,8,9,4});
    std::vector<std::vector<GLuint>> frameCollisionBoxes;
    frameCollisionBoxes.push_back(frameCollisionBoxFirst);
    frameCollisionBoxes.push_back(frameCollisionBoxSecond);
    frameCollisionBoxes.push_back(frameCollisionBoxThird);

    std::vector<GLfloat> frameColor({0.823f,0.823f,0.823f,1.0f});

    frame = new Frame(frameData, frameData.size() * sizeof(GLfloat), frameIndices, frameIndices.size(), frameCollisionBoxes, frameColor);

    frameVertexArray = new VertexArray();
    frameVertexBuffer = new VertexBuffer(frame->getData().data(), frame->getDataSize());
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(2);
    frameVertexArray->addBuffer(*frameVertexBuffer, frameVertexBufferLayout);
    frameIndexBuffer = new IndexBuffer(frame->getIndices().data(), frame->getNumberOfIndices());
    frameVertexBuffer->unbind();
    frameVertexArray->unbind();
    frameIndexBuffer->unbind();

    return GL_TRUE;
}
