/*	Camera.cpp

	Created: 2012 July 25.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 October 21.

	Implements the Camera class from Camera.h

	OpenGL 3.0 compliant 20130224
*/

#include "Camera.hpp"

Camera::Camera(int width, int height, ViewPerspective perspectiveMode, float fov, double nearClip, double farClip, int clearFlags, glm::vec3 worldPosition, glm::vec3 lookAtPosition)
{
	//in core 3.0
	if(clearFlags != GL_SCISSOR_BIT)
	{
		glViewport(0, 0, width, height);
	}
	else
	{
		glScissor(0, 0, width, height);
	}

	//CORNFLOWER BLUE background
	glClearColor(0.39f, 0.55f, 0.929f, 0.0f);

	_perspectiveMode = perspectiveMode;
	_width = width;
	_height = height;
	p_aspectRatio = new float((float)_width / (float)_height);
	_fov = fov;
	_clearFlags = clearFlags;

	_frustum = Frustum();
	_frustum.SetCamInternals(fov, *p_aspectRatio, nearClip, farClip);

	if(_perspectiveMode == PERSPECTIVE)
	{
		_projectionMatrix = glm::perspective((double)_fov, (double)*p_aspectRatio, nearClip, farClip);
	}
	else if(_perspectiveMode == ORTHOGONAL)
	{
		_projectionMatrix = glm::ortho((-fov * (*p_aspectRatio)), (fov * (*p_aspectRatio)), -fov, fov, (float)nearClip, (float)farClip);
	}

	//the view matrix is a matrix that is used to convert the world coordinates to camaera coordinates, this matrix positions the camera in world space too.
	p_viewMatrix = new glm::mat4(1);
	*p_viewMatrix = glm::lookAt(worldPosition, lookAtPosition, glm::vec3(0,1,0));
	_frustum.SetCamDef(p_viewMatrix);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if(_clearFlags == GL_SCISSOR_BIT)
	{
		glEnable(GL_SCISSOR_TEST);
	}
	else
	{
		glDisable(GL_SCISSOR_TEST);
		//TODO: ablity to handle multiple cameras
	}
}

float* Camera::GetAspecRatio()
{
	return p_aspectRatio;
}

int* Camera::GetHeight()
{
	return &_height;
}

int* Camera::GetWidth()
{
	return &_width;
}

float* Camera::GetFOV()
{
	return &_fov;
}

glm::mat4* Camera::GetProjectionMatrix()
{
	return &_projectionMatrix;
}

glm::mat4* Camera::GetViewMatrix()
{
	return p_viewMatrix;
}

std::list<IDrawable*>* Camera::FrustumCull(std::list<IDrawable*>* drawables)
{
	std::list<IDrawable*>* result = new std::list<IDrawable*>();
	std::list<IDrawable*>::iterator drawable;
	int inFrustum = 0;

	for(drawable = drawables->begin(); drawable != drawables->end(); drawable++)
	{
		inFrustum = _frustum.BoxInFrustum(*(drawable._Ptr->_Myval->GetAABox()));
		if(inFrustum != 0)
		{
			result->push_back(drawable._Ptr->_Myval);
		}
	}

	return result;
}

void Camera::SetTransform(glm::mat4* transform)
{
	p_viewMatrix = transform;
}