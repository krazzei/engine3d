
#ifndef _MOVELIGHT_H
#define _MOVELIGHT_H

#include "Main.hpp"
#include "Entity.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "Input.hpp"
//Had to add this manually, first time I had to do that. Find the cause!
#include "../3rd_party/glm-0.9.4.2/glm/gtc/matrix_transform.hpp"

//Temporary class for testing input.
class MoveLight : Entity
{
public:
	MoveLight();
	~MoveLight();

	virtual			void		Update(double deltaTime);
	void		SetTransform(glm::mat4* transform);
private:
	glm::mat4*		p_transform;
	glm::vec3		moveVector;
};
#endif