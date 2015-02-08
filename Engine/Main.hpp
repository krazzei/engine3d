/*	Main.h
	
	Created: 2012 July 22.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 27.

	Base includes for the engine. This should be included for all components.
*/

#ifndef _MAIN_H
#define _MAIN_H

#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif

#ifndef GLM_SWIZZLE
#define GLM_SWIZZLE
#endif

#include "../3rd_party/glew-1.9.0/include/GL/glew.h"
#include "../3rd_party/glfw-2.7.6/include/GL/glfw.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool InitializeRenderer();

void PrintGLError();

//an image read from the disk, not a texture!
struct Image
{
	int Width, Height;
	int BytesPerPixel;
	char channels;
	unsigned char* Data;
};

#endif