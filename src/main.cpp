#include <iostream>

//#define GLFW_INCLUDE_GLU

//#include "SimpleGLApp.h"
#include <GLFW/glfw3.h>

char g_WndTitle[] = "Visualization Tool";
int g_WndWidth  = 640;
int g_WndHeight = 480;
// SimpleGLApp MyGlApp;

void displayWindow(GLFWwindow* _pWindowPtr)
{
//	MyGlApp.render();
}

void resizeWindow(GLFWwindow* _pWindowPtr, int width, int height)
{
//	MyGlApp.onResize(width, height);
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

// 	MyGlApp.init();
// 	if(!MyGlApp.isInitialized())
// 	{
// 		std::cout << "ERROR: Cannot initialize OpenGL\n";
// 		return -1;
// 	}

	double prevt = glfwGetTime();

	while(!glfwWindowShouldClose(mainWindow))
	{
		double t = glfwGetTime();
//		MyGlApp.prepare(prevt - t);
		prevt = t;
		
		displayWindow(mainWindow);
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}