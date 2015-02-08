/*	WindowScene.h

	Created: 2012 August 1.
	Author: Tyler White.
	TODO: license and legal here.
	
	Implements the WindowScene class from WindowScene.h
*/

#include "WindowScene.hpp"

int WindowScene::_windowHeight = 0;
int WindowScene::_windowWidth = 0;

bool WindowScene::MakeGLWindow(int width, int height, int redBits, int greenBits, int blueBits, int alphaBits, int depthBits, int stencilBits, int mode)
{
	_windowWidth = width;
	_windowHeight = height;

	//TODO: get supported resolutions from the monitor.
	//users can't resize the window all willy nilly, they need to select a resolution!
	if(mode == GLFW_WINDOW)
	{
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	}

	if(!glfwOpenWindow(width, height, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, mode))
	{
		glfwTerminate();
		return false;
	}

	return true;
}

void WindowScene::ResizeScene(int width, int height)
{
	//TODO: handle resizing the window here.
}