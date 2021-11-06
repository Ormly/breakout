#include "BreakoutApp.h"

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shaders.h"
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
    windowWidth = 768.0f;
    windowHeight = 1024.0f;

    glfwSetErrorCallback(error_callback);

    if(!initializeWindow())
        exit(EXIT_FAILURE);

    /*
    glm::mat4 projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
    glm::mat4 identity(1.0f);
    glm::mat4 transform(projection * identity);
     */

    /*
    GLfloat positions[] = {
            0.0f,0.0f,0.0f,
            50.0f,0.0f,0.0f,
            718.0f,0.0f,0.0f,
            768.0f,0.0f,0.0f,
            768.0f,974.0f,0.0f,
            768.0f,1024.0f,0.0f,
            718.0f,1024.0f,0.0f,
            50.0f,1024.0f,0.0f,
            0.0f,1024.0f,0.0f,
            0.0f,974.0f,0.0f
    };

    GLuint indices[] = {
            0,1,7,
            0,7,8,
            2,5,6,
            2,3,5,
            4,5,8,
            4,8,9
    };
     */

    /*
    GLfloat positions3[] = {
            100.0f,100.0f,0.0f,
            300.0f,100.0f,0.0f,
            300.0f,300.0f,0.0f,
            100.0f,300.0f,0.0f
    };

    GLuint indices3[] = {
            0,1,2,
            0,2,3
    };
     */

    {
        GLfloat positions[] = {
                -0.3f, -0.125f, 0.0f,
                0.3f, -0.125f, 0.0f,
                0.3f, 0.125f, 0.0f,
                -0.3f, 0.125f, 0.0f,
        };

        GLuint indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        VertexArray vertexArray;
        VertexBuffer vertexBuffer(positions, sizeof(positions));
        VertexBufferLayout vertexBufferLayout;
        vertexBufferLayout.push<GLfloat>(3);
        vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);
        IndexBuffer indexBuffer(indices, 6);
        Shaders shaders("../res/shaders/VertexShader.vertexshader",
                        "../res/shaders/FragmentShader.fragmentshader");
        shaders.bind();
        //shaders.setUniform4f("u_color", 0.8f,0.3f,0.8f,1.0f);
        //shaders.setUniformMat4f("u_projection", identity);


        vertexArray.unbind();
        vertexBuffer.unbind();
        indexBuffer.unbind();
        shaders.unbind();

        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();
            renderer.draw(vertexArray, indexBuffer, shaders);
            //shaders.setUniform4f("u_color", 1.0f,1.0f,1.0f,1.0f);
            //shaders.setUniformMat4f("u_projection", identity);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
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
