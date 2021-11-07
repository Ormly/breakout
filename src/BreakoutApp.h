#ifndef BREAKOUT_BREAKOUTAPP_H
#define BREAKOUT_BREAKOUTAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "objects/Frame.h"

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

Frame* frame;
std::vector<GLfloat> frameData;
std::vector<GLuint> frameIndices;

GLboolean initializeWindow();
GLboolean initializeGameObjects();

#endif //BREAKOUT_BREAKOUTAPP_H
