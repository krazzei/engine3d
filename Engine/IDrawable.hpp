/*  IDrawable.h

	Created: 2012 July 25.
	Author: Tyler White.
	TODO: license and legal here.
	
	Edited: 2012 July 30.

	Interface for anything that can be drawn,
	(mesh, skinned mesh, sprite, particle, etc).
	This header file will also contain common drawing
	structs (verticies, textures, etc).
*/

#ifndef _IDRAWABLE_H
#define _IDRAWABLE_H

#include "Material.hpp"
#include "AABox.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

class IDrawable
{
public:
	virtual ~IDrawable() {}

	virtual		void				Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix)		= 0;
	virtual		Material*			GetMaterial()													= 0;
	virtual		AABox*				GetAABox()														= 0;
	virtual		unsigned int*		GetLightCount()													= 0;
};
#endif