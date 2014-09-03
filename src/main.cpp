#include <iostream>

//#define GLFW_INCLUDE_GLU

#include "application.h"
#include <GLFW/glfw3.h>

char g_WndTitle[] = "Visualization Tool";
int g_WndWidth  = 640;
int g_WndHeight = 480;
VisApplication MyGlApp(g_WndWidth, g_WndHeight);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  
  if(action == GLFW_PRESS)
  {
    MyGlApp.pressKey(key);
  }
  else if(action == GLFW_RELEASE)
  {
    MyGlApp.releaseKey(key);
  }
}

void mousebutton_callback(GLFWwindow *, int button, int action, int mods)
{
  if(action == GLFW_PRESS)
    MyGlApp.mouseDown(button);
  else if(action == GLFW_RELEASE)
    MyGlApp.mouseUp(button);
    
}

void cursorenter_callback(GLFWwindow *, int entered)
{
  //std::cout << "cursor enter " << entered << std::endl;
}

void cursor_callback(GLFWwindow *, double x, double y)
{
  MyGlApp.mouseMove(x, y);
}


void scroll_callback(GLFWwindow *, double x, double y)
{
  //std::cout << "scroll_callback" << x << " " << y << std::endl;
}

void displayWindow(GLFWwindow* _pWindowPtr)
{
  MyGlApp.render();
}

void resizeWindow(GLFWwindow* _pWindowPtr, int width, int height)
{
  MyGlApp.onResize(width, height);
}

int main(int argc, char* argv[])
{
  
  GLFWwindow* mainWindow;

  // Initialize the glfw
  if(!glfwInit())
  {
	  std::cout << "ERROR: Cannot initialize the GLFW\n";
	  return -1;
  }

  // create the window
  mainWindow = glfwCreateWindow(g_WndWidth, g_WndHeight, g_WndTitle, NULL, NULL);
  if(!mainWindow)
  {
	  std::cout << "ERROR: Cannot create the window\n";
	  glfwTerminate();
	  return -1;
  }

  glfwMakeContextCurrent(mainWindow);
  glfwSetFramebufferSizeCallback(mainWindow, resizeWindow);
  resizeWindow(mainWindow, g_WndWidth, g_WndHeight);
  glfwSwapInterval(1);
  glfwSetWindowPos(mainWindow, 100, 100);
  glfwSetKeyCallback(mainWindow, key_callback);
  glfwSetMouseButtonCallback(mainWindow, mousebutton_callback);
  glfwSetCursorPosCallback(mainWindow, cursor_callback);
  glfwSetScrollCallback(mainWindow, scroll_callback);
  glfwSetCursorEnterCallback(mainWindow, cursorenter_callback);

  MyGlApp.init();
  if(!MyGlApp.isInitialized())
  {
	  std::cout << "ERROR: Cannot initialize OpenGL\n";
	  return -1;
  }

  double prevt = glfwGetTime();

  while(!glfwWindowShouldClose(mainWindow))
  {
	  double t = glfwGetTime();
	  MyGlApp.prepare(prevt - t);
	  prevt = t;
	  
	  displayWindow(mainWindow);
	  glfwSwapBuffers(mainWindow);
	  glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}