#include "BreakoutApp.h"

#include <iostream>
#include <utility>
#include <vector>
#include <random>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    shaders = new Shaders("../res/shaders/VertexShader.vertexshader",
                    "../res/shaders/FragmentShader.fragmentshader");
    shaders->bind();

    init();
    //shaders.unbind();

    while (!glfwWindowShouldClose(window))
    {
        checkEndStates();

        GLdouble currentTime = glfwGetTime();
        deltaTime += (currentTime - previousTime) / limitFPS;
        previousTime = currentTime;

        while (deltaTime >= 1.0)
        {
            glfwPollEvents();
            update();
            deltaTime--;
        }

        render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void init()
{
    initializeGameObjects();
    state = RUNNING;

    projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
    identity = glm::mat4(1.0f);
    paddleTranslation = identity;
    shaders->setUniformMat4f("u_projection", projection);
    shaders->setUniformMat4f("u_translation", identity);

    limitFPS = 1.0 / 60.0;
    previousTime = glfwGetTime();
    timer = previousTime;
    deltaTime = 0;
    numberOfFrames = 0;
    numberOfUpdates = 0;
    collisionWaitTime = 7;
    collisionWaitTimer = collisionWaitTime;
}

void checkEndStates()
{
    if(state == WON || state == LOST)
    {
        if(glfwGetKey(window, GLFW_KEY_ENTER))
        {
            init();
            update();
            render();
        }
    }
}

void update()
{
    GLfloat paddleSpeed = paddle->getSpeed();

    if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
    {
        paddle->addToOffset(paddleSpeed * deltaTime);
        paddleTranslation = glm::translate(identity, glm::vec3(paddle->getOffset(), 0.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
    {
        paddle->addToOffset(paddleSpeed * deltaTime * -1.0f);
        paddleTranslation = glm::translate(identity, glm::vec3(paddle->getOffset(), 0.0f, 0.0f));
    }

    checkForCollisions();

    ball->addToOffset(ball->getVelocity().x * deltaTime, ball->getVelocity().y * deltaTime);
    ballTranslation = glm::translate(identity, glm::vec3(ball->getOffset().x, ball->getOffset().y, 0.0f));

    if (state == RUNNING)
    {
        state = WON;
        for (BrickGroup *brickGroup: brickGroups)
        {
            if (!(brickGroup->wasCleared()))
                state = RUNNING;
        }
    }

}

void checkForCollisions()
{
    glm::vec2 changedVelocity;

    std::vector<GLfloat> collisionBoxBall = ball->getCollisionBox();
    std::vector<GLfloat> collisionBoxPaddle = paddle->getCollisionBox();
    std::vector<GLfloat> collisionBoxFrameLeft = leftBorder->getCollisionBox();
    std::vector<GLfloat> collisionBoxFrameRight = rightBorder->getCollisionBox();
    std::vector<GLfloat> collisionBoxFrameTop = upperBorder->getCollisionBox();
    std::vector<GLfloat> collisionBoxFrameBottom = lowerBorder->getCollisionBox();

    //paddle collision
    if (areOverlapping(collisionBoxBall, collisionBoxPaddle))
    {
        GLfloat radius = ball->getWidth() / 2;
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

        glm::vec2 position(ball->getCenter().x, paddle->getCenter().y + paddle->getHeight() / 2 + ball->getHeight() / 2 + 1.0f);
        ball->setPosition(position);
    }

    //frame collision
    if(areOverlapping(collisionBoxBall, collisionBoxFrameLeft))
    {
        changedVelocity.x = -ball->getVelocity().x;
        changedVelocity.y = ball->getVelocity().y;
        ball->setVelocity(changedVelocity);

        glm::vec2 position(leftBorder->getCenter().x + leftBorder->getWidth() / 2 + ball->getWidth() / 2 + 1.0f, ball->getCenter().y);
        ball->setPosition(position);
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameRight))
    {
        changedVelocity.x = -ball->getVelocity().x;
        changedVelocity.y = ball->getVelocity().y;
        ball->setVelocity(changedVelocity);

        glm::vec2 position(rightBorder->getCenter().x - rightBorder->getWidth() / 2 - ball->getWidth() / 2 - 1.0f, ball->getCenter().y);
        ball->setPosition(position);
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameTop))
    {
        changedVelocity.x = ball->getVelocity().x;
        changedVelocity.y = -ball->getVelocity().y;
        ball->setVelocity(changedVelocity);

        glm::vec2 position(ball->getCenter().x, upperBorder->getCenter().y - upperBorder->getHeight() / 2 - ball->getHeight() / 2 - 1.0f);
        ball->setPosition(position);
    }

    if(areOverlapping(collisionBoxBall, collisionBoxFrameBottom))
        state = LOST;

    //brick collision
    for(BrickGroup* brickGroup : brickGroups)
    {
        for(Brick* brick : brickGroup->getBricks())
        {
            std::vector<GLfloat> box = brick->getCollisionBox();
            if(brick->isAlive() && areOverlapping(collisionBoxBall, box))
            {
                changedVelocity.x = ball->getVelocity().x;
                changedVelocity.y = -ball->getVelocity().y;
                ball->setVelocity(changedVelocity);
                brick->kill();
            }
        }
    }
}

GLboolean areOverlapping(std::vector<GLfloat> collisionBoxBall, std::vector<GLfloat> collisionBoxOther)
{
    GLfloat ballLeftX = collisionBoxBall.at(0);
    GLfloat ballRightX = collisionBoxBall.at(2);
    GLfloat ballTopY = collisionBoxBall.at(5);
    GLfloat ballBottomY = collisionBoxBall.at(1);

    GLfloat otherLeftX = collisionBoxOther.at(0);
    GLfloat otherRightX = collisionBoxOther.at(2);
    GLfloat otherTopY = collisionBoxOther.at(5);
    GLfloat otherBottomY = collisionBoxOther.at(1);

    if((ballLeftX < otherRightX && ballRightX > otherLeftX) &&
       (ballTopY > otherBottomY && ballBottomY < otherTopY) &&
       collisionWaitTimer == collisionWaitTime)
    {
        collisionWaitTimer--;
        return GL_TRUE;
    }
    else
    {
        if(collisionWaitTimer < collisionWaitTime)
            collisionWaitTimer--;

        if(collisionWaitTimer < 0)
            collisionWaitTimer = collisionWaitTime;

        return GL_FALSE;
    }
}

void render()
{
    renderer.clear();

    shaders->setUniformMat4f("u_translation", identity);
    if(state == RUNNING)
    {
        shaders->setUniform4f("u_color", leftBorder->getColor().at(0), leftBorder->getColor().at(1),
                              leftBorder->getColor().at(2), leftBorder->getColor().at(3));
        renderer.draw(*(leftBorder->getVertexArray()), *(leftBorder->getIndexBuffer()), *shaders);
        renderer.draw(*(rightBorder->getVertexArray()), *(rightBorder->getIndexBuffer()), *shaders);
        renderer.draw(*(upperBorder->getVertexArray()), *(upperBorder->getIndexBuffer()), *shaders);

        shaders->setUniform4f("u_color", lowerBorder->getColor().at(0), lowerBorder->getColor().at(1),
                              lowerBorder->getColor().at(2), lowerBorder->getColor().at(3));
        renderer.draw(*(lowerBorder->getVertexArray()), *(lowerBorder->getIndexBuffer()), *shaders);

        for (BrickGroup *brickGroup: brickGroups)
        {
            shaders->setUniform4f("u_color", brickGroup->getBricks().at(0)->getColor().at(0),
                                  brickGroup->getBricks().at(0)->getColor().at(1),
                                  brickGroup->getBricks().at(0)->getColor().at(2),
                                  brickGroup->getBricks().at(0)->getColor().at(3));

            for (Brick *brick: brickGroup->getBricks())
                if (brick->isAlive())
                    renderer.draw(*(brick->getVertexArray()), *(brick->getIndexBuffer()), *shaders);
        }

        shaders->setUniformMat4f("u_translation", paddleTranslation);
        shaders->setUniform4f("u_color", paddle->getColor().at(0), paddle->getColor().at(1), paddle->getColor().at(2),
                              paddle->getColor().at(3));
        renderer.draw(*(paddle->getVertexArray()), *(paddle->getIndexBuffer()), *shaders);

        shaders->setUniformMat4f("u_translation", ballTranslation);
        shaders->setUniform4f("u_color", ball->getColor().at(0), ball->getColor().at(1), ball->getColor().at(2),
                              ball->getColor().at(3));
        renderer.draw(*(ball->getVertexArray()), *(ball->getIndexBuffer()), *shaders);
    }

    if(state == WON)
    {
        shaders->setUniform4f("u_color", winScreen->getColor().at(0), winScreen->getColor().at(1), winScreen->getColor().at(2),
                              winScreen->getColor().at(3));

        for(RenderableRectangle* rectangle : winScreen->getRectangles())
            renderer.draw(*(rectangle->getVertexArray()), *(rectangle->getIndexBuffer()), *shaders);
    }

    if(state == LOST)
    {
        shaders->setUniform4f("u_color", lossScreen->getColor().at(0), lossScreen->getColor().at(1), lossScreen->getColor().at(2),
                              lossScreen->getColor().at(3));

        for(RenderableRectangle* rectangle : lossScreen->getRectangles())
            renderer.draw(*(rectangle->getVertexArray()), *(rectangle->getIndexBuffer()), *shaders);
    }
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

    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}

void initializeGameObjects()
{
    initializeBorders();
    initializePaddle();
    initializeBricks();
    initializeBall();
    initializeWinScreen();
    initializeLossScreen();
}

void initializeBorders()
{
    glm::vec2 leftCenter(10.0f,512.0f);
    glm::vec2 rightCenter(758.0f, 512.0f);
    glm::vec2 upperCenter(384.0f,1014.0f);
    glm::vec2 lowerCenter(384.0f,10.0f);
    std::vector<GLfloat> frameColor({0.823f,0.823f,0.823f,1.0f});
    std::vector<GLfloat> lowerFrameColor({0.0f, 0.0f, 0.0f,0.0f});
    GLfloat verticalWidth = 20.0f;
    GLfloat horizontalHeight = 20.0f;
    GLfloat horizontalWidth = 768.0f;
    GLfloat verticalHeight = 1024.0f;

    leftBorder = new RenderableRectangle(leftCenter, verticalWidth, verticalHeight, frameColor);
    rightBorder = new RenderableRectangle(rightCenter, verticalWidth, verticalHeight, frameColor);
    upperBorder = new RenderableRectangle(upperCenter, horizontalWidth, horizontalHeight, frameColor);
    lowerBorder = new RenderableRectangle(lowerCenter, horizontalWidth - 40.0f, horizontalHeight, lowerFrameColor);
}

void initializePaddle()
{
    glm::vec2 paddleCenter(384.0f, 60.0f);

    GLfloat paddleWidth = 100.0f;
    GLfloat paddleHeight = 20.0f;

    std::vector<GLfloat> paddleColor({0.0f, 0.36f, 0.541f, 1.0f});

    paddle = new Paddle(paddleCenter, paddleWidth, paddleHeight, paddleColor, 5.0f);
}

void initializeBricks()
{
    GLuint bricksPerRow = 12;
    GLuint rowsPerGroup = 2;
    GLfloat brickWidth = 57.0f;
    GLfloat brickHeight = 14.0f;
    GLfloat bufferZone = 2.0f;

    //Todo: make this not stupid
    glm::vec2 firstLayerOriginBrickCenter(59.5f, 827.0f);
    std::vector<GLfloat> firstLayerColor({0.631f, 0.031f, 0.0f, 1.0f});
    glm::vec2 secondLayerOriginBrickCenter(59.5f, 795.0f);
    std::vector<GLfloat> secondLayerColor({0.772f, 0.501f, 0.0f, 1.0f});
    glm::vec2 thirdLayerOriginBrickCenter(59.5f, 763.0f);
    std::vector<GLfloat> thirdLayerColor({0.0f, 0.498f, 0.137f, 1.0f});
    glm::vec2 fourthLayerOriginBrickCenter(59.5f, 731.0f);
    std::vector<GLfloat> fourthLayerColor({0.768f, 0.776f, 0.121f, 1.0f});

    brickGroups.clear();
    brickGroups.push_back(createBrickGroup(firstLayerOriginBrickCenter, brickWidth, brickHeight, firstLayerColor, rowsPerGroup, bricksPerRow, bufferZone));
    brickGroups.push_back(createBrickGroup(secondLayerOriginBrickCenter, brickWidth, brickHeight, secondLayerColor, rowsPerGroup, bricksPerRow, bufferZone));
    brickGroups.push_back(createBrickGroup(thirdLayerOriginBrickCenter, brickWidth, brickHeight, thirdLayerColor, rowsPerGroup, bricksPerRow, bufferZone));
    brickGroups.push_back(createBrickGroup(fourthLayerOriginBrickCenter, brickWidth, brickHeight, fourthLayerColor, rowsPerGroup, bricksPerRow, bufferZone));
}

BrickGroup* createBrickGroup(glm::vec2 originBrickCenter, GLfloat brickWidth, GLfloat brickHeight,
                              std::vector<GLfloat> brickColor, GLuint rowsPerGroup, GLuint bricksPerRow, GLfloat bufferZone)
{
    std::vector<Brick*> bricks;
    Brick* originBrick;
    originBrick = new Brick(originBrickCenter, brickWidth, brickHeight, std::move(brickColor));
    bricks.push_back(originBrick);

    glm::vec2 previousBrickCenter = originBrickCenter;

    for(int i = 0; i < rowsPerGroup; ++i)
    {
        if(i != 0)
        {
            glm::vec2 temp(originBrickCenter.x, originBrickCenter.y - ((brickHeight + bufferZone) * i));
            originBrick = new Brick(temp, brickWidth, brickHeight, std::move(brickColor));
            bricks.push_back(originBrick);
            previousBrickCenter = temp;
        }

        for(int j = 1; j < bricksPerRow; ++j)
        {
            glm::vec2 brickCenterToAdd(previousBrickCenter.x + brickWidth + bufferZone, previousBrickCenter.y);
            previousBrickCenter = brickCenterToAdd;
            auto* brickToAdd = new Brick(brickCenterToAdd, brickWidth, brickHeight, std::move(brickColor));
            bricks.push_back(brickToAdd);
        }
    }

    auto* brickGroup = new BrickGroup(bricks);

    return brickGroup;
}

void initializeBall()
{
    GLfloat sideLength = 16.0f;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> initialPositionDistribution(50.0f, windowWidth - 50.0f);
    GLfloat initialX = initialPositionDistribution(eng);
    GLfloat initialY = windowHeight / 2.0f;

    glm::vec2 ballCenter(initialX, initialY);

    std::vector<GLfloat> color({1.0f,1.0f,1.0f,1.0f});

    //Todo: fix this craziness
    std::uniform_real_distribution<float> initialVelocityDistributionX(-0.1f, 0.1f);
    std::uniform_real_distribution<float> initialVelocityDistributionY(-0.9f, -1.0f);
    glm::vec2 initialVelocity(initialVelocityDistributionX(eng), initialVelocityDistributionY(eng));
    GLfloat initialSpeed = 5.0f;

    ball = new Ball(ballCenter, sideLength, sideLength, color, initialVelocity, initialSpeed);
}

void initializeWinScreen()
{
    GLfloat eyeWidth = 50.0f;
    glm::vec2 leftEye(60.0f,954.0f);
    glm::vec2 rightEye(698.0f,954.0f);

    GLfloat cornerWidth = 30.0f;
    glm::vec2 mouthLeftCornerUpper(50.0f, 744.0f);
    glm::vec2 mouthLeftCornerLower(mouthLeftCornerUpper.x + cornerWidth / 2, mouthLeftCornerUpper.y - cornerWidth / 2);
    GLfloat mouthLineWidth(rightEye.x - leftEye.x);
    GLfloat mouthLineHeight = cornerWidth;
    glm::vec2 mouthLine((rightEye.x + leftEye.x) / 2, mouthLeftCornerLower.y - cornerWidth / 2);
    glm::vec2 mouthRightCornerLower(mouthLeftCornerLower.x + mouthLineWidth, mouthLeftCornerLower.y);
    glm::vec2 mouthRightCornerUpper(mouthRightCornerLower.x + cornerWidth / 2, mouthRightCornerLower.y + cornerWidth / 2);

    std::vector<GLfloat> color({0.0f, 0.498f, 0.137f, 1.0f});

    std::vector<RenderableRectangle*> rectangles;
    rectangles.push_back(new RenderableRectangle(leftEye, eyeWidth, eyeWidth, color));
    rectangles.push_back(new RenderableRectangle(rightEye, eyeWidth, eyeWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLeftCornerUpper, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLeftCornerLower, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLine, mouthLineWidth, mouthLineHeight, color));
    rectangles.push_back(new RenderableRectangle(mouthRightCornerUpper, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthRightCornerLower, cornerWidth, cornerWidth, color));

    winScreen = new EndScreen(rectangles);
}

void initializeLossScreen()
{
    GLfloat eyeWidth = 50.0f;
    glm::vec2 leftEye(60.0f,954.0f);
    glm::vec2 rightEye(698.0f,954.0f);

    GLfloat cornerWidth = 30.0f;
    GLfloat mouthLineWidth(rightEye.x - leftEye.x);
    GLfloat mouthLineHeight = cornerWidth;

    glm::vec2 mouthLine((rightEye.x + leftEye.x) / 2, 744.0f);
    glm::vec2 mouthLeftCornerUpper(mouthLine.x - mouthLineWidth / 2, mouthLine.y - cornerWidth);
    glm::vec2 mouthLeftCornerLower(mouthLeftCornerUpper.x - cornerWidth / 2, mouthLeftCornerUpper.y - cornerWidth / 2);
    glm::vec2 mouthRightCornerUpper(mouthLeftCornerUpper.x + mouthLineWidth, mouthLeftCornerUpper.y);
    glm::vec2 mouthRightCornerLower(mouthRightCornerUpper.x + cornerWidth / 2, mouthRightCornerUpper.y - cornerWidth / 2);

    std::vector<GLfloat> color({0.631f, 0.031f, 0.0f, 1.0f});

    std::vector<RenderableRectangle*> rectangles;
    rectangles.push_back(new RenderableRectangle(leftEye, eyeWidth, eyeWidth, color));
    rectangles.push_back(new RenderableRectangle(rightEye, eyeWidth, eyeWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLeftCornerUpper, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLeftCornerLower, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthLine, mouthLineWidth, mouthLineHeight, color));
    rectangles.push_back(new RenderableRectangle(mouthRightCornerUpper, cornerWidth, cornerWidth, color));
    rectangles.push_back(new RenderableRectangle(mouthRightCornerLower, cornerWidth, cornerWidth, color));

    lossScreen = new EndScreen(rectangles);
}


