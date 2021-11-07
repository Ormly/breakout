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

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

GLdouble deltaTime;
glm::mat4 projection;
glm::mat4 paddleTranslation;
glm::mat4 identity;

Renderer renderer;
Shaders* shaders;

Frame* frame;
Paddle* paddle;

GLboolean initializeWindow();
void initializeGameObjects();
void update();
void render();

#endif //BREAKOUT_BREAKOUTAPP_H
