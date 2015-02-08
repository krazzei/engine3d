
#ifndef _MOUSELOOK_H
#define _MOUSELOOK_H

#include "Main.hpp"
#include "Entity.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "Input.hpp"
//Had to add this manually, first time I had to do that. Find the cause!
#include "../3rd_party/glm-0.9.4.2/glm/gtc/matrix_transform.hpp"

//Temporary class for testing input.
class MouseLook : Entity
{
public:
	MouseLook();
	~MouseLook();

	virtual			void		Update(double deltaTime);
					void		SetTransform(glm::mat4* transform);
private:
	glm::mat4*		p_transform;
	glm::mat4		_translation;
	glm::mat4		_rotation;
};
#endif