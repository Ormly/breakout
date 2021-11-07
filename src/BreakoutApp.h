#ifndef BREAKOUT_BREAKOUTAPP_H
#define BREAKOUT_BREAKOUTAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "objects/Frame.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

Frame* frame;
VertexArray* frameVertexArray;
VertexBuffer* frameVertexBuffer;
IndexBuffer* frameIndexBuffer;

GLboolean initializeWindow();
GLboolean initializeGameObjects();

#endif //BREAKOUT_BREAKOUTAPP_H
