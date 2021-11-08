#include "BreakoutApp.h"

#include <iostream>
#include <utility>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "objects/Brick.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
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

    shaders = new Shaders("../res/shaders/VertexShader.vertexshader",
                    "../res/shaders/FragmentShader.fragmentshader");
    shaders->bind();

    projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
    identity = glm::mat4(1.0f);
    paddleTranslation = identity;
    shaders->setUniformMat4f("u_projection", projection);
    shaders->setUniformMat4f("u_translation", identity);
    //shaders.unbind();

    static double limitFPS = 1.0 / 60.0;
    double previousTime = glfwGetTime();
    double timer = previousTime;
    deltaTime = 0;
    int numberOfFrames = 0;
    int numberOfUpdates = 0;

    while (!glfwWindowShouldClose(window))
    {
        GLdouble currentTime = glfwGetTime();
        deltaTime += (currentTime - previousTime) / limitFPS;
        previousTime = currentTime;

        while (deltaTime >= 1.0)
        {
            glfwPollEvents();
            update();
            numberOfUpdates++;
            deltaTime--;
        }

        render();

        numberOfFrames++;
        if (glfwGetTime() - timer > 1.0)
        {
            timer++;

            std::cout <<
            "FPS: " <<
            numberOfFrames <<
            " || # updates per second: " <<
            numberOfUpdates <<
            std::endl;

            numberOfUpdates = 0, numberOfFrames = 0;
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void update()
{
    GLfloat paddleSpeed = 5.0f;

    if(glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
    {
        //paddle->translate(10.0f * deltaTime);
        paddle->addToOffset(paddleSpeed * deltaTime);
        paddleTranslation = glm::translate(identity, glm::vec3(paddle->getOffset(),0.0f,0.0f));
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
    {
        //paddle->translate(-10.0f * deltaTime);
        paddle->addToOffset(paddleSpeed * deltaTime * -1.0f);
        paddleTranslation = glm::translate(identity, glm::vec3(paddle->getOffset(),0.0f,0.0f));
    }
}

void render()
{
    renderer.clear();

    shaders->setUniformMat4f("u_translation", identity);
    shaders->setUniform4f("u_color", frame->getColor().at(0), frame->getColor().at(1), frame->getColor().at(2), frame->getColor().at(3));
    renderer.draw(*(frame->getVertexArray()),*(frame->getIndexBuffer()), *shaders);

    for(BrickGroup* brickGroup : brickGroups)
    {
        shaders->setUniform4f("u_color", brickGroup->getColor().at(0), brickGroup->getColor().at(1), brickGroup->getColor().at(2), brickGroup->getColor().at(3));
        renderer.draw(*(brickGroup->getVertexArray()),*(brickGroup->getIndexBuffer()), *shaders);
    }

    shaders->setUniformMat4f("u_translation", paddleTranslation);
    shaders->setUniform4f("u_color", paddle->getColor().at(0), paddle->getColor().at(1), paddle->getColor().at(2), paddle->getColor().at(3));
    renderer.draw(*(paddle->getVertexArray()),*(paddle->getIndexBuffer()), *shaders);
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
        "GLEW Error: Could not be initialized!" <<
        std::endl;
        return GL_FALSE;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}

void initializeGameObjects()
{
    //Initialize Frame
    std::vector<GLfloat> frameData =
    {
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

    std::vector<GLuint> frameIndices =
    {
        0,1,7,
        7,8,0,
        2,3,5,
        5,6,2,
        4,5,8,
        8,9,4
    };

    //Todo: Make this not be stupid as hell
    std::vector<GLuint> frameCollisionBoxFirst({0,1,7,8});
    std::vector<GLuint> frameCollisionBoxSecond({2,3,5,6});
    std::vector<GLuint> frameCollisionBoxThird({4,5,8,9});
    std::vector<std::vector<GLuint>> frameCollisionBoxes;
    frameCollisionBoxes.push_back(frameCollisionBoxFirst);
    frameCollisionBoxes.push_back(frameCollisionBoxSecond);
    frameCollisionBoxes.push_back(frameCollisionBoxThird);

    std::vector<GLfloat> frameColor({0.823f,0.823f,0.823f,1.0f});

    frame = new Frame(frameData, frameData.size() * sizeof(GLfloat), frameIndices, frameIndices.size(), frameCollisionBoxes, frameColor);


    //Initialize Paddle
    std::vector<GLfloat> paddleData =
    {
        334.0f,50.0f,
        434.0f,50.0f,
        434.0f,70.0f,
        334.0f,70.0f
    };

    std::vector<GLuint> paddleIndices =
    {
        0,1,2,
        2,3,0
    };

    std::vector<GLuint> paddleCollisionBox({0,1,2,3});
    std::vector<GLfloat> paddleColor({0.0f,0.36f,0.541f,1.0f});

    paddle = new Paddle(paddleData, paddleData.size() * sizeof(GLfloat), paddleIndices, paddleIndices.size(), paddleCollisionBox, paddleColor, paddleData.at(2) - paddleData.at(0));


    //Initialized Bricks
    numberOfBrickGroupLayers = 2;

    std::vector<GLuint> originBrickIndices =
    {
            0,1,2,
            2,3,0
    };

    std::vector<GLfloat> zeroLayerOriginBrickPositions =
    {
        31.0f, 940.0f,
        88.0f, 940.0f,
        88.0f, 954.0f,
        31.0f, 954.0f
    };

    std::vector<GLfloat> zeroLayerColor({0.631f, 0.031f, 0.0f, 1.0f});
    BrickGroup* zeroLayer = createBrickGroup(zeroLayerOriginBrickPositions, originBrickIndices, zeroLayerColor);
    brickGroups.push_back(zeroLayer);
}

//This is the dumbest code I've ever written
BrickGroup* createBrickGroup(std::vector<GLfloat> originBrickPositions, std::vector<GLuint> originBrickIndices, std::vector<GLfloat> color)
{
    std::vector<Brick> bricks;
    std::vector<GLuint> brickLayout;
    GLuint id = 0;
    auto* originBrick = new Brick(originBrickPositions, id++);
    bricks.push_back(*originBrick);
    brickLayout.insert(brickLayout.end(), originBrickIndices.begin(), originBrickIndices.end());

    std::vector<GLfloat> previousBrickPositions;
    std::vector<GLfloat> brickToAddPositions;
    std::vector<GLuint> brickToAddIndices;
    GLuint counter = 2;
    for(int i = 0; i < numberOfBrickGroupLayers; ++i)
    {
        if(i == 0)
            previousBrickPositions = originBrickPositions;
        else
        {
            previousBrickPositions.clear();
            for(int j = 0; j < originBrickPositions.size(); ++j)
            {
                if(j % 2 != 0)
                    previousBrickPositions.push_back(originBrickPositions.at(j) -
                                                     (originBrickPositions.at(5) - originBrickPositions.at(3) + 2.0f));
                else
                    previousBrickPositions.push_back(originBrickPositions.at(j));
            }
            bricks.push_back(*(new Brick(previousBrickPositions, id++)));

            brickToAddIndices.clear();
            for(unsigned int layerZeroOriginBrickIndex : originBrickIndices)
                brickToAddIndices.push_back(layerZeroOriginBrickIndex + counter * 4 - 4);

            counter++;

            brickLayout.insert(brickLayout.end(), brickToAddIndices.begin(), brickToAddIndices.end());
        }

        for(int j = 0; j < 11; ++j)
        {
            Brick* brickToAdd;
            brickToAddIndices.clear();
            brickToAddPositions.clear();

            for(int k = 0; k < previousBrickPositions.size(); ++k)
            {
                if(k % 2 == 0)
                    brickToAddPositions.push_back(previousBrickPositions.at(k) +
                                                  (previousBrickPositions.at(2) - previousBrickPositions.at(0) + 2.0f)); //Todo: 2.0f --> padding member
                else
                    brickToAddPositions.push_back(previousBrickPositions.at(k));
            }

            brickToAddIndices.reserve(originBrickIndices.size());
            for(unsigned int layerZeroOriginBrickIndex : originBrickIndices)
                brickToAddIndices.push_back(layerZeroOriginBrickIndex + counter * 4 - 4);

            counter++;

            brickToAdd = new Brick(brickToAddPositions, id++);
            bricks.push_back(*brickToAdd);
            brickLayout.insert(brickLayout.end(), brickToAddIndices.begin(), brickToAddIndices.end());

            previousBrickPositions = brickToAddPositions;
        }
    }

    auto* brickGroup = new BrickGroup(bricks, brickLayout, std::move(color));
    return brickGroup;
}
