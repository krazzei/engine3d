/*	Camera.h

	Created: 2012 July 25.
	Author: Tyler White.
	TODO: license and legal here.
	
	Edited: 2012 October 21.

	Our Camera will contain all the data for 
	a camera ~_^. Things like near and far
	clip plane, angle of the frustrum (perspective),
	ablity to have perspective or orthogonal frustrums, etc.
*/

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Main.hpp"
#include "IDrawable.hpp"
#include "AABox.hpp"
#include "ITransformable.hpp"
#include "Frustum.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/gtc/matrix_transform.hpp"
#include <list>

class Camera : ITransformable
{
public:
	enum ViewPerspective
	{
		PERSPECTIVE = 0,
		ORTHOGONAL = 1
	};

	Camera(	int width, int height, ViewPerspective perspective, float fov, double nearClip, double farClip,
			int clearFlags, glm::vec3 worldPosition, glm::vec3 lookAtPoint);

	~Camera();

	virtual		void						Update(void);
	virtual		void						SetTransform(glm::mat4* tranform);

				float*						GetAspecRatio();
				int*						GetWidth();
				int*						GetHeight();
				float*						GetFOV();
				glm::mat4*					GetViewMatrix();
				glm::mat4*					GetProjectionMatrix();
				std::list<IDrawable*>*		FrustumCull(std::list<IDrawable*>* drawables);

private:
	int _width;
	int _height;
	float* p_aspectRatio;
	float _fov;
	ViewPerspective _perspectiveMode;
	glm::mat4* p_viewMatrix;
	//this is a projection matrix, rename it!
	glm::mat4 _projectionMatrix;
	int _clearFlags;
	Frustum _frustum;
};

#endif