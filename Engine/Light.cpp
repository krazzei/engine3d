
#include "Light.hpp"

unsigned int Light::_nextLightID = 0;

Light::Light(glm::vec3 position, glm::vec3 color, float power)
{
	_lightInfo = glm::mat3x4(1.0f);

	_lightInfo[0] = glm::vec4(position.x, position.y, position.z, 1);
	
	_lightInfo[1] = glm::vec4(color.x, color.y, color.z, 1);

	_lightInfo[2] = glm::vec4(power, 0, 0, 0);
}

void Light::SetTransform(glm::mat4 *transform)
{
	p_transform = transform;
}

void Light::Update(std::list<IDrawable*>* effectedObjects)
{
	unsigned int programID = 0;
	int lightLocation = 0;

	_lightInfo[0] = glm::vec4((*p_transform)[3].xyz, 1);
	printf("light pos (%f,%f,%f)\n", _lightInfo[0].x, _lightInfo[0].y, _lightInfo[0].z);

	std::list<IDrawable*>::iterator drawable;
	for(drawable = effectedObjects->begin(); drawable != effectedObjects->end(); drawable++)
	{
		programID = *( (drawable._Ptr->_Myval)->GetMaterial()->GetProgramID());
		
		glUseProgram(programID);

		lightLocation = glGetUniformLocation(programID, "lightInfo");
		
		if(lightLocation > -1)
		{
			glUniformMatrix3x4fv(lightLocation, 1, GL_FALSE, &_lightInfo[0][0]);
		}
		else
		{
			PrintGLError();
		}

		glUseProgram(0);
	}
}