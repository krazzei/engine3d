
#include "MouseLook.hpp"

#define SENSITIVITY 5.0f

MouseLook::MouseLook() : Entity()
{

}

MouseLook::~MouseLook()
{

}

void MouseLook::SetTransform(glm::mat4* transform)
{
	p_transform = transform;

	_rotation = glm::mat4(1);
	_rotation[0] = (*transform)[0];
	_rotation[1] = (*transform)[1];
	_rotation[2] = (*transform)[2];

	_translation = glm::mat4(1);
	_translation[3] = (*transform)[3];
}

void MouseLook::Update(double deltaTime)
{
	glm::vec2 delta = Input::GetDeltaMousePos();
	
	// TODO: make a rotation matrix, like this one, but just multiply it with the current transform matrix.
	// then translate the result (or the other way around?). Tyler White 20150208
	_rotation = glm::rotate(_rotation, (float)(delta.x * deltaTime) * SENSITIVITY, glm::vec3(0,1,0));
	_rotation = glm::rotate(_rotation, (float)(-delta.y * deltaTime) * SENSITIVITY, glm::vec3(1,0,0));

	glm::vec3 moveDir = glm::vec3(0);

	if(Input::GetKey('W'))
	{
		//z is forward
		moveDir += _rotation[2].xyz();
	}

	if(Input::GetKey('S'))
	{
		moveDir -= _rotation[2].xyz();
	}

	if(Input::GetKey('A'))
	{
		moveDir += _rotation[0].xyz();
	}

	if(Input::GetKey('D'))
	{
		moveDir -= _rotation[0].xyz();
	}

	moveDir * (float)deltaTime;

	_translation = glm::translate(_translation, moveDir);

	*p_transform = glm::lookAt(_translation[3].xyz(), _translation[3].xyz + _rotation[2].xyz, glm::vec3(0,1,0));
}