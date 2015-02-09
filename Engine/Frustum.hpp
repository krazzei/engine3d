#ifndef _FRUSTUM_H
#define _FRUSTUM_H

#include "AABox.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

#define ANG2RAD 3.14159265358979323846/180.0

struct Plane
{
public:
	glm::vec3 normal, point;
	float d;

	Plane(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	Plane(void);
	~Plane();

	void SetPoints(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	void SetNormalAndPoint( glm::vec3 normal, glm::vec3 point);
	void SetCoeficients(float a, float b, float c, float d);

	float Distance(glm::vec3 p);

	void Print();//not sure if needed.
};

struct Frustum
{
private:
	enum
	{
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};

public:
	static enum {OUTSIDE = 0, INTERSECT, INSIDE};
	Plane pl[6];
	//glm::vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
	float nearD, farD, ratio, angle, tang;
	float nw, nh, fw, fh;

	Frustum();
	~Frustum();

	void SetCamInternals(float angle, float ratio, float nearD, float farD);
	void SetCamDef(glm::vec3 pos, glm::vec3 lookAtPos, glm::vec3 up);
	void SetCamDef(glm::mat4* view);
	void SetFrustum(glm::mat4);

	int PointInFrustum(glm::vec3 point);
	int SphereInFrustum(glm::vec3 point, float radius);
	int BoxInFrustum(AABox box);
};

#endif