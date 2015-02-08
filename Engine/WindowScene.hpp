/*	WindowScene.h

	Created: 2012 August 1.
	Author: Tyler White.
	TODO: license and legal here.

	Defines the WindowScene class that will handle
	the window for openGL (and possibly DriectX _)
*/

#ifndef _WINDOWSCENE_H
#define _WINDOWSCENE_H

#include "Main.hpp"
#include "../3rd_party/glfw-2.7.6/include/GL/glfw.h"

class WindowScene
{
public:
	static		int			_windowWidth;
	static		int			_windowHeight;

				bool		MakeGLWindow(int width, int height, int redBits, int greenBits, int blueBits, int alphaBits, int depthBits, int stencilBits, int mode);
				void		ResizeScene(int width, int height);
};

#endif