#ifndef BREAKOUT_BREAKOUTAPP_H
#define BREAKOUT_BREAKOUTAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "objects/Frame.h"
#include "objects/Paddle.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

GLdouble deltaTime;

Frame* frame;
Paddle* paddle;

GLboolean initializeWindow();
GLboolean initializeGameObjects();

#endif //BREAKOUT_BREAKOUTAPP_H
