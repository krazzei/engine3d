#include "AABox.hpp"

AABox::AABox(void)
{
	corner.x = 0;
	corner.y = 0;
	corner.z = 0;

	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
}

AABox::AABox(glm::vec3 corner, float x, float y, float z)
{
	SetBox(corner, x, y, z);
}

AABox::~AABox()
{

}

//lighthouse3d did not explain this very well, corner (first parameter) is the "lowest" vertex in world space.
//because we (currrently) have a box whose vertices are in world space, we can take our world position - (1,1,1) to get the world position of the vertex (-1, -1, -1).
//the other parameters are the amounts we need to add to the "lowest" vertex to get the "highest" vertex in world space, for our test cube it would be 2 across the board (x,y,z)
//becase -1(lowest) + 2(amount) = 1(highest).
void AABox::SetBox(glm::vec3 corner, float x, float y, float z)
{
	this->corner = corner;

	if(x < 0.0)
	{
		x = -x;
		this->corner.x -= x;
	}

	if(y < 0.0)
	{
		y = -y;
		this->corner.y -= y;
	}

	if(z < 0.0)
	{
		z = -z;
		this->corner.z -= z;
	}

	this->x = x;
	this->y = y;
	this->z = z;
}

//need to test Oriented Boxes
glm::vec3 AABox::GetVertexPositive(glm::vec3 normal)
{
	// Our current position - the mesh's lowest corner is the lowest corner in world space.
	glm::vec3 res = (*_transform)[3].xyz - corner;

	if(normal.x > 0)
	{
		res.x += x;
	}

	if(normal.y > 0)
	{
		res.y += y;
	}

	if(normal.z > 0)
	{
		res.z += z;
	}

	return res;
}

//need to test Oriented Boxes
glm::vec3 AABox::GetvertexNegative(glm::vec3 normal)
{
	// Our current position - the mesh's lowest corner is the lowest corner in world space.
	glm::vec3 res = (*_transform)[3].xyz - corner;

	if(normal.x < 0)
	{
		res.x += x;
	}

	if(normal.y < 0)
	{
		res.y += y;
	}

	if(normal.z < 0)
	{
		res.z += z;
	}

	return res;
}

void AABox::SetTransform(glm::mat4* transform)
{
	_transform = transform;
}