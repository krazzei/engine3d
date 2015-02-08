#include "MoveLight.hpp"

#define SENSITIVITY 3.0f

MoveLight::MoveLight()
{
}

MoveLight::~MoveLight()
{
}

void MoveLight::SetTransform(glm::mat4 *transform)
{
	p_transform = transform;
}

void MoveLight::Update(double deltaTime)
{
	moveVector = glm::vec3(0);

	if (Input::GetKey('I'))
	{
		//forward
		moveVector.z += deltaTime * SENSITIVITY;
	}

	if (Input::GetKey('K'))
	{
		//backward
		moveVector.z -= deltaTime * SENSITIVITY;
	}

	if (Input::GetKey('J'))
	{
		//left
		moveVector.x += deltaTime * SENSITIVITY;
	}

	if (Input::GetKey('L'))
	{
		//right
		moveVector.x -= deltaTime * SENSITIVITY;
	}

	if (Input::GetKey('U'))
	{
		//up
		moveVector.y += deltaTime * SENSITIVITY;
	}

	if (Input::GetKey('O'))
	{
		//down
		moveVector.y -= deltaTime * SENSITIVITY;
	}

	*p_transform = glm::translate(*p_transform, moveVector);
}