#include "BreakoutApp.h"

#include <iostream>
#include <windows.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shaders.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/Renderer.h"

GLFWwindow* window;

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
    glfwSetErrorCallback(error_callback);

    if(!initializeWindow())
        exit(EXIT_FAILURE);

    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    if(!initializeGlew())
        exit(EXIT_FAILURE);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    window = glfwCreateWindow(768, 1024, "breakout", nullptr, nullptr);
    if (!window)
    {
        std::cout <<
        "GLFW Error: Window context could not be initialized!" <<
        std::endl;

        return GL_FALSE;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return GL_TRUE;
}

GLboolean initializeGlew()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout <<
        "GLEW Error: Could not be initialized!";

        return GL_FALSE;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //wglMakeCurrent();

    return GL_TRUE;
}
