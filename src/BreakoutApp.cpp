#include "BreakoutApp.h"

#include <iostream>
#include <utility>
#include <vector>
#include <random>

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

    //ball step
    GLfloat centerX = ball->getCenter().x;
    GLfloat centerY = ball->getCenter().y;
    //GLfloat velocityX = centerX + ball->getVelocity().x;
    //GLfloat velocityY = centerY + ball->getVelocity().y;
    GLfloat additionX = 0;
    GLfloat additionY = 0;

    /*
    if(velocityX < 0 && velocityY < 0)
    {
        additionX += centerX - velocityX;
        additionY += centerY - velocityY;
    }
    if(velocityX > 0 && velocityY < 0)
    {
        additionX += velocityX - centerX;
        additionY += centerY - velocityY;
    }
    if(velocityX > 0 && velocityY > 0)
    {
        additionX += velocityX - centerX;
        additionY += velocityY - centerY;
    }
    if(velocityX < 0 && velocityY > 0)
    {
        additionX += centerX - velocityX;
        additionY += velocityY - centerY;
    }
     */

    //ball->addToOffset(additionX, additionY);
    ball->addToOffset(ball->getVelocity().x * deltaTime, ball->getVelocity().y * deltaTime);
    ballTranslation = glm::translate(identity, glm::vec3(ball->getOffset().x, ball->getOffset().y, 0.0f));

    /*
    std::cout << "Ball position x0/y0: " << ball->getPositions().at(0) << "/" << ball->getPositions().at(1) << "\n" <<
                 "Ball position x1/y1: " << ball->getPositions().at(2) << "/" << ball->getPositions().at(3) << "\n" <<
                 "Ball position x2/y2: " << ball->getPositions().at(4) << "/" << ball->getPositions().at(5) << "\n" <<
                 "Ball position x3/y3: " << ball->getPositions().at(6) << "/" << ball->getPositions().at(7) << "\n" <<
    std::endl;
     */
    std::cout << "Ball velocity x:" << ball->getVelocity().x << " | y: " << ball->getVelocity().y << std::endl;
    std::cout << "Ball addition (velocity * deltaTime) x:" << ball->getVelocity().x * deltaTime << " | y: " << ball->getVelocity().y * deltaTime << std::endl;
    std::cout << "Ball offset x:" << ball->getOffset().x << " | y: " << ball->getOffset().y << std::endl;

    checkForCollisions();
}

void checkForCollisions()
{
    glm::vec2 changedVelocity;

    std::vector<GLfloat> collisionBoxBall = ball->getCollisionBox();
    std::vector<GLfloat> collisionBoxPaddle = paddle->getCollisionBox();
    std::vector<GLfloat> collisionBoxFrameLeft = frame->getCollisionBoxLeft();
    std::vector<GLfloat> collisionBoxFrameRight = frame->getCollisionBoxRight();
    std::vector<GLfloat> collisionBoxFrameTop = frame->getCollisionBoxTop();

    GLfloat ballSize = ball->getSideLength();
    GLfloat paddleWidth = paddle->getWidth();
    GLfloat paddleHeight = paddle->getHeight();
    GLfloat frameLeftHeight = frame->getLeftHeight();
    GLfloat frameRightHeight = frame->getRightHeight();
    GLfloat frameTopHeight = frame->getTopHeight();
    GLfloat frameLeftWidth = frame->getLeftWidth();
    GLfloat frameRightWidth = frame->getRightWidth();
    GLfloat frameTopWidth = frame->getTopWidth();


    if (areOverlapping(collisionBoxBall, collisionBoxPaddle, ballSize, paddleWidth, paddleHeight))
    {
        GLfloat radius = ball->getSideLength() / 2;
        GLfloat ballLocation = ball->getCenter().x - (paddle->getCenter().x - radius - paddle->getWidth() / 2);
        GLfloat paddleEdge = ballLocation / paddle->getWidth();

        if(paddleEdge < 0.33f)
        {
            changedVelocity.x = -0.196f;
            changedVelocity.y = -0.981f;
            ball->setVelocity(glm::reflect(ball->getVelocity(), changedVelocity));
        }
        else if(paddleEdge > 0.66)
        {
            changedVelocity.x = 0.196f;
            changedVelocity.y = -0.981f;
            ball->setVelocity(glm::reflect(ball->getVelocity(), changedVelocity));
        }
        else
        {
            changedVelocity.x = ball->getVelocity().x;
            changedVelocity.y = -ball->getVelocity().y;
            ball->setVelocity(changedVelocity);
        }
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameLeft, ballSize, frameLeftWidth, frameLeftHeight))
    {
        changedVelocity.x = -ball->getVelocity().x;
        changedVelocity.y = ball->getVelocity().y;
        ball->setVelocity(changedVelocity);
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameRight, ballSize, frameRightWidth, frameRightHeight))
    {
        changedVelocity.x = -ball->getVelocity().x;
        changedVelocity.y = ball->getVelocity().y;
        ball->setVelocity(changedVelocity);
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameTop, ballSize, frameTopWidth, frameTopHeight))
    {
        changedVelocity.x = ball->getVelocity().x;
        changedVelocity.y = -ball->getVelocity().y;
        ball->setVelocity(changedVelocity);
    }
}

GLboolean areOverlapping(std::vector<GLfloat> collisionBoxBall, std::vector<GLfloat> collisionBoxOther, GLfloat ballSize,GLfloat otherWidth, GLfloat otherHeight)
{
    GLfloat ballOriginX = collisionBoxBall.at(6);
    GLfloat ballOriginY = collisionBoxBall.at(7);
    GLfloat otherOriginX = collisionBoxOther.at(6);
    GLfloat otherOriginY = collisionBoxOther.at(7);

    if(ballOriginX < otherOriginX + otherWidth &&
       ballOriginX + ballSize > otherOriginX &&
       ballOriginY < otherOriginY + otherHeight &&
       ballSize + ballOriginY > otherOriginY)
    {
        return GL_TRUE;
    }
    else
        return GL_FALSE;
    /*
    if (ballOriginX + ballSize >= otherOriginX &&
        ballOriginX <= otherOriginX + otherWidth &&
        ballOriginY + ballSize >= otherOriginY &&
        ballOriginY <= otherOriginY + otherHeight)
    {
        return GL_TRUE;
    }
    else
        return GL_FALSE;
        */
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

    shaders->setUniformMat4f("u_translation", ballTranslation);
    shaders->setUniform4f("u_color", ball->getColor().at(0), ball->getColor().at(1), ball->getColor().at(2), ball->getColor().at(3));
    renderer.draw(*(ball->getVertexArray()),*(ball->getIndexBuffer()), *shaders);
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
    initializeFrame();
    initializePaddle();
    initializeBricks();
    initializeBall();
}

void initializeFrame()
{
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

    std::vector<GLfloat> widths;
    widths.push_back(frameData.at(2) - frameData.at(0));
    widths.push_back(frameData.at(6) - frameData.at(4));
    widths.push_back(frameData.at(8) - frameData.at(18));

    std::vector<GLfloat> heights;
    heights.push_back(frameData.at(17) - frameData.at(1));
    heights.push_back(frameData.at(13) - frameData.at(5));
    heights.push_back(frameData.at(11) - frameData.at(9));


    /*
    GLfloat xCenter = (paddleData.at(6) + paddleData.at(2)) / 2;
    GLfloat yCenter = (paddleData.at(7) + paddleData.at(3)) / 2;
    glm::vec2 paddleCenter(xCenter, yCenter);
     */

    std::vector<glm::vec2> centers;
    GLfloat leftXCenter = (frameData.at(16) + frameData.at(2)) / 2;
    GLfloat leftYCenter = (frameData.at(17) + frameData.at(3)) / 2;
    glm::vec2 leftCenter(leftXCenter, leftYCenter);
    centers.push_back(leftCenter);
    GLfloat rightXCenter = (frameData.at(12) + frameData.at(6)) / 2;
    GLfloat rightYCenter = (frameData.at(13) + frameData.at(7)) / 2;
    glm::vec2 rightCenter(rightXCenter, rightYCenter);
    centers.push_back(rightCenter);
    GLfloat topXCenter = (frameData.at(16) + frameData.at(8)) / 2;
    GLfloat topYCenter = (frameData.at(17) + frameData.at(9)) / 2;
    glm::vec2 topCenter(topXCenter, topYCenter);
    centers.push_back(topCenter);

    frame = new Frame(frameData, frameData.size() * sizeof(GLfloat), frameIndices, frameIndices.size(), frameCollisionBoxes, frameColor, widths, heights, centers);
}

void initializePaddle()
{
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

    std::vector<GLfloat> paddleColor({0.0f,0.36f,0.541f,1.0f});
    GLfloat xCenter = (paddleData.at(6) + paddleData.at(2)) / 2;
    GLfloat yCenter = (paddleData.at(7) + paddleData.at(3)) / 2;
    glm::vec2 paddleCenter(xCenter, yCenter);


    paddle = new Paddle(paddleData, paddleData.size() * sizeof(GLfloat), paddleIndices, paddleIndices.size(),
                        paddleColor, paddleData.at(2) - paddleData.at(0), paddleData.at(5) - paddleData.at(3),
                        paddleCenter);
}

void initializeBricks()
{
    rowsPerBrickGroup = 2;
    numberOfBrickGroups = 1;

    std::vector<GLuint> originBrickIndices =
    {
        0,1,2,
        2,3,0
    };

    std::vector<GLfloat> firstLayerOriginBrickPositions =
    {
        31.0f, 820.0f,
        88.0f, 820.0f,
        88.0f, 834.0f,
        31.0f, 834.0f
    };
    std::vector<GLfloat> firstLayerColor({0.631f, 0.031f, 0.0f, 1.0f});
    BrickGroup* firstLayer = createBrickGroup(firstLayerOriginBrickPositions, originBrickIndices, firstLayerColor);
    brickGroups.push_back(firstLayer);

    /*
    numberOfBrickGroups++;
    std::vector<GLfloat> secondLayerOriginBrickPositions;
    for(int i = 0; i < firstLayer->getBricks().at(0).getPositions().size(); ++i)
    {
        if(i % 2 != 0)
        {
            secondLayerOriginBrickPositions.push_back(firstLayer->getBricks().at(0).getPositions().at(i) - numberOfBrickGroups *
                                                     (firstLayer->getBricks().at(0).getPositions().at(5) - firstLayer->getBricks().at(0).getPositions().at(3) + 2.0f));
        }
        else
            secondLayerOriginBrickPositions.push_back(firstLayer->getBricks().at(0).getPositions().at(i));
    }
     */

    //Todo: derive subsequent layer positions from first origin instead of hardcoding magic numbers
    std::vector<GLfloat> secondLayerOriginBrickPositions =
    {
        31.0f, 788.0f,
        88.0f, 788.0f,
        88.0f, 802.0f,
        31.0f, 802.0f
    };
    std::vector<GLfloat> secondLayerColor({0.772f, 0.501f, 0.0f, 1.0f});
    BrickGroup* secondLayer = createBrickGroup(secondLayerOriginBrickPositions, originBrickIndices, secondLayerColor);
    brickGroups.push_back(secondLayer);

    std::vector<GLfloat> thirdLayerOriginBrickPositions =
    {
        31.0f, 756.0f,
        88.0f, 756.0f,
        88.0f, 770.0f,
        31.0f, 770.0f
    };
    std::vector<GLfloat> thirdLayerColor({0.0f, 0.498f, 0.137f, 1.0f});
    BrickGroup* thirdLayer = createBrickGroup(thirdLayerOriginBrickPositions, originBrickIndices, thirdLayerColor);
    brickGroups.push_back(thirdLayer);

    std::vector<GLfloat> fourthLayerOriginBrickPositions =
    {
        31.0f, 724.0f,
        88.0f, 724.0f,
        88.0f, 738.0f,
        31.0f, 738.0f
    };
    std::vector<GLfloat> fourthLayerColor({0.768f, 0.776f, 0.121f, 1.0f});
    BrickGroup* fourthLayer = createBrickGroup(fourthLayerOriginBrickPositions, originBrickIndices, fourthLayerColor);
    brickGroups.push_back(fourthLayer);
}

void initializeBall()
{
    GLfloat sideLength = 16.0f;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> initialPositionDistribution(50.0f, windowWidth - 50.0f);
    GLfloat initialX = initialPositionDistribution(eng);
    GLfloat initialY = windowHeight / 2.0f;

    std::vector<GLfloat> positions =
    {
        initialX - sideLength / 2, initialY - sideLength / 2,
        initialX + sideLength / 2, initialY - sideLength / 2,
        initialX + sideLength / 2, initialY + sideLength / 2,
        initialX - sideLength / 2, initialY + sideLength / 2
    };

    std::vector<GLuint> indices =
    {
        0,1,2,
        2,3,0
    };

    std::vector<GLuint> collisionBox({0,1,2,3});
    std::vector<GLfloat> color({1.0f,1.0f,1.0f,1.0f});

    std::uniform_real_distribution<float> initialVelocityDistributionX(-1.0f, 1.0f);
    std::uniform_real_distribution<float> initialVelocityDistributionY(-0.7f, -1.0f);
    glm::vec2 initialVelocity(initialVelocityDistributionX(eng), initialVelocityDistributionY(eng));
    //glm::vec2 initialVelocity(0.5f,-1.0f);
    glm::vec2 initialCenter(initialX, initialY);
    GLfloat initialSpeed = 1.05f;
    ball = new Ball(positions, indices, color, initialVelocity, initialCenter, initialSpeed, sideLength);
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
    for(int i = 0; i < rowsPerBrickGroup; ++i)
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
