/*  Input.cpp

	Created: 2012 July 22.
	Author: Tyler White.
	TODO: license and legal here.
	
	Implements the Input class defined by Input.hpp
*/

#include "Input.hpp"

int* Input::_mousePositionX = new int(-1);
int* Input::_mousePositionY = new int(-1);

int* Input::_lastMousePosX = new int(0);
int* Input::_lastMousePosY = new int(0);

int* Input::_deltaMousePositionX = new int(0);
int* Input::_deltaMousePositionY = new int(0);

Input::Input()
{
}

Input::~Input()
{
}

void Input::Initialize()
{
}

void Input::Update()
{
	*_lastMousePosX = *_mousePositionX;
	*_lastMousePosY = *_mousePositionY;
	
	glfwGetMousePos(_mousePositionX, _mousePositionY);

	//last positions will be -1, which will never happen during game. So its safe to use for initilization, to avoid big deltas.
	if(*_lastMousePosX >= 0 || *_lastMousePosY >= 0)
	{
		*_deltaMousePositionX = *_lastMousePosX - *_mousePositionX;
		*_deltaMousePositionY = *_lastMousePosY - *_mousePositionY;
	}
}

glm::vec2 Input::GetMousePos()
{
	return glm::vec2(*_mousePositionX, *_mousePositionY);
}

glm::vec2 Input::GetDeltaMousePos()
{
	return glm::vec2(*_deltaMousePositionX, *_deltaMousePositionY);
}

bool Input::GetKey(int key)
{
	return glfwGetKey(key);
}

bool Input::GetMouseButton(int button)
{
	return glfwGetMouseButton(button);
}