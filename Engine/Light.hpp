
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Main.hpp"
#include "IDrawable.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/gtc/matrix_access.hpp"
#include <list>

//this object can move
class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color, float power);
	void Update(std::list<IDrawable*>* effectedObjects);
	void SetTransform(glm::mat4 *transform);

private:
	//light matrix, column 1 is world position, column 2 is light's color, column 3 is the lights direction (length is power)
	glm::mat3x4 _lightInfo;
	glm::mat4* p_transform;
	unsigned int _lightID;
	static unsigned int _nextLightID;
};
#endif