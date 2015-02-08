
#ifndef _ITRANSFORMABLE_H
#define _ITRANSFORMABLE_H

#include "Main.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

/// <summary> 
/// A transformable object, contains a matrix 4x4 representing a transform. 
/// </summary>
/// Simply contains a reference to a glm::mat4 
class ITransformable
{
public:
	virtual		~ITransformable()		{}

	virtual		void					SetTransform(glm::mat4* transform)		= 0;
};

#endif