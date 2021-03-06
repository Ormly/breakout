#ifndef BREAKOUT_BREAKOUTAPP_H
#define BREAKOUT_BREAKOUTAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shaders.h"
#include "renderer/Renderer.h"
#include "objects/Rectangle.h"
#include "objects/RenderableRectangle.h"
#include "objects/Paddle.h"
#include "objects/Ball.h"
#include "objects/Brick.h"
#include "objects/BrickGroup.h"
#include "objects/EndScreen.h"

enum GameState
{
    RUNNING, WON, LOST
};

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

GLdouble deltaTime;
glm::mat4 projection;
glm::mat4 paddleTranslation;
glm::mat4 identity;
glm::mat4 ballTranslation;

Renderer renderer;
Shaders* shaders;

RenderableRectangle* leftBorder;
RenderableRectangle* lowerBorder;
RenderableRectangle* rightBorder;
RenderableRectangle* upperBorder;
Paddle* paddle;
Ball* ball;
std::vector<BrickGroup*> brickGroups;

GameState state;
GLuint numberOfUpdates;
GLdouble limitFPS;
GLdouble previousTime;
GLdouble timer;
GLuint numberOfFrames;
GLint collisionWaitTimer;
GLint collisionWaitTime;

EndScreen* lossScreen;
EndScreen* winScreen;

GLboolean initializeWindow();
void init();
void checkEndStates();
void initializeGameObjects();
void initializeBorders();
void initializePaddle();
void initializeBricks();
void initializeBall();
void initializeWinScreen();
void initializeLossScreen();
void update();
void checkForCollisions();
GLboolean areOverlapping(std::vector<GLfloat> collisionBoxBall, std::vector<GLfloat> collisionBoxOther);
void render();
BrickGroup* createBrickGroup(glm::vec2 originBrickCenter, GLfloat brickWidth, GLfloat brickHeight, std::vector<GLfloat> brickColor,
                              GLuint rowsPerBrickGroup, GLuint bricksPerBrickGroupRow, GLfloat bufferZone);

#endif //BREAKOUT_BREAKOUTAPP_H
