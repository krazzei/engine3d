
#ifndef _AABOX_H
#define _AABOX_H

#ifndef GLM_SWIZZLE
#define GLM_SWIZZLE
#endif

#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "ITransformable.hpp"

struct AABox : ITransformable
{
public:
	glm::vec3 corner;
	float x, y ,z;

	//corner is the minimum vetex in model space
	AABox(glm::vec3 corner, float x, float y, float z);
	AABox(void);
	~AABox();

	void SetBox(glm::vec3 corner, float x, float y, float z);

	virtual void SetTransform(glm::mat4* transform);

	glm::vec3 GetVertexPositive(glm::vec3 normal);
	glm::vec3 GetvertexNegative(glm::vec3 normal);

private:
	glm::mat4* _transform;
};

#endif