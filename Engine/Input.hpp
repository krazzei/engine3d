/*  Input.h

	Created: 2012 July 22.
	Author: Tyler White.
	TODO: license and legal here.

	Input.h will structure our Input class.
	The Input class will use glfw for cross-platform input and joystick support.
	Not sure of the best way to do this, Input seems game specific.
*/

#ifndef _INPUT_H
#define _INPUT_H

#include "Main.hpp"
#include "../3rd_party/glfw-2.7.6/include/GL/glfw.h"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

class Input
{
public:
	static			void			Initialize();
	static			void			Update();
	static			glm::vec2		GetMousePos();
	static			glm::vec2		GetDeltaMousePos();
	static			bool			GetKey(int key);
	static			bool			GetMouseButton(int button);
private:
	Input();
	~Input();

	static		int*			_mousePositionX;
	static		int*			_mousePositionY;
	static		int*			_lastMousePosX;
	static		int*			_lastMousePosY;
	static		int*			_deltaMousePositionX;
	static		int*			_deltaMousePositionY;
};
#endif