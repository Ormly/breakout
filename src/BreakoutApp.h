#ifndef BREAKOUT_BREAKOUTAPP_H
#define BREAKOUT_BREAKOUTAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "objects/Frame.h"
#include "objects/Paddle.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shaders.h"
#include "renderer/Renderer.h"
#include "objects/BrickGroup.h"
#include "objects/Ball.h"

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

Frame* frame;
Paddle* paddle;
Ball* ball;

std::vector<BrickGroup*> brickGroups;
GLuint rowsPerBrickGroup;
GLuint numberOfBrickGroups;

GLuint numberOfUpdates;
GLdouble limitFPS;
GLint collisionWaitTimer;
GLint collisionWaitTime;

GLboolean initializeWindow();
void initializeGameObjects();
void initializeFrame();
void initializePaddle();
void initializeBricks();
void initializeBall();
void update();
void checkForCollisions();
GLboolean areOverlapping(std::vector<GLfloat> collisionBoxBall, std::vector<GLfloat> collisionBoxOther, GLfloat ballSize,GLfloat otherWidth, GLfloat otherHeight);
void render();
BrickGroup* createBrickGroup(std::vector<GLfloat> originBrickPositions, std::vector<GLuint> originBrickIndices, std::vector<GLfloat> color);

#endif //BREAKOUT_BREAKOUTAPP_H
