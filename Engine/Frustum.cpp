#include "Frustum.hpp"

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::SetCamInternals(float angle, float ratio, float nearD, float farD)
{
	this->ratio = ratio;
	this->angle = angle;
	this->nearD = nearD;
	this->farD = farD;

	tang = (float)tan(ANG2RAD * angle * 0.5);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD * tang;
	fw = fh * ratio;
}

void Frustum::SetCamDef(glm::vec3 position, glm::vec3 lookAtPos, glm::vec3 up)
{
	glm::vec3 dir, nc, fc, x, y, z;

	z = position - lookAtPos;
	z = glm::normalize(z);

	x = glm::cross(up, z);
	x = glm::normalize(x);

	//the tutorial i was following said to do this, however there was some debaits in the comments.
	//TODO: understand this better and fit it for our needs.
	y = glm::cross(z, x);
	
	nc = position - z * nearD;
	fc = position - z * farD;

	pl[NEARP].SetNormalAndPoint(-z, nc);
	pl[FARP].SetNormalAndPoint(z, fc);

	glm::vec3 aux, normal;

	aux = (nc + y * nh) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(aux, x); //cross product?
	pl[TOP].SetNormalAndPoint(normal, nc+y*nh);

	aux = (nc - y * nh) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(x, aux);
	pl[BOTTOM].SetNormalAndPoint(normal, nc - y * nh);

	aux = (nc - x * nw) -position;
	aux = glm::normalize(aux);
	normal = glm::cross(aux, y);
	pl[LEFT].SetNormalAndPoint(normal, nc - x * nw);

	aux = (nc + x * nw) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(y, aux);
	pl[RIGHT].SetNormalAndPoint(normal, nc + x * nw);
}

void Frustum::SetCamDef(glm::mat4* view)
{
	glm::vec3 dir, nc, fc, x, y, z, position;

	x = glm::vec3((*view)[0].x, (*view)[0].y, (*view)[0].z);

	y = glm::vec3((*view)[1].x, (*view)[1].y, (*view)[1].z);
	
	z = glm::vec3((*view)[2].x, (*view)[2].y, (*view)[2].z);

	position = glm::vec3((*view)[3].x, (*view)[3].y, (*view)[3].z);

	nc = position - z * nearD;
	fc = position - z * farD;

	pl[NEARP].SetNormalAndPoint(-z, nc);
	pl[FARP].SetNormalAndPoint(z, fc);

	glm::vec3 aux, normal;

	aux = (nc + y * nh) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(aux, x); //cross product?
	pl[TOP].SetNormalAndPoint(normal, nc+y*nh);

	aux = (nc - y * nh) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(x, aux);
	pl[BOTTOM].SetNormalAndPoint(normal, nc - y * nh);

	aux = (nc - x * nw) -position;
	aux = glm::normalize(aux);
	normal = glm::cross(aux, y);
	pl[LEFT].SetNormalAndPoint(normal, nc - x * nw);

	aux = (nc + x * nw) - position;
	aux = glm::normalize(aux);
	normal = glm::cross(y, aux);
	pl[RIGHT].SetNormalAndPoint(normal, nc + x * nw);
}

//not sure why this won't work, the tutorial I was following (lighthouse3d) says that I still need an
//AABox so the geometric method seems better (for now).
void Frustum::SetFrustum(glm::mat4 viewProjectionMatrix)
{
	pl[NEARP].SetCoeficients(	viewProjectionMatrix[2][0] + viewProjectionMatrix[3][0],
								viewProjectionMatrix[2][1] + viewProjectionMatrix[3][1],
								viewProjectionMatrix[2][2] + viewProjectionMatrix[3][2],
								viewProjectionMatrix[2][3] + viewProjectionMatrix[3][3]);

	pl[FARP].SetCoeficients(	-viewProjectionMatrix[2][0] + viewProjectionMatrix[3][0],
								-viewProjectionMatrix[2][1] + viewProjectionMatrix[3][1],
								-viewProjectionMatrix[2][2] + viewProjectionMatrix[3][2],
								-viewProjectionMatrix[2][3] + viewProjectionMatrix[3][3]);
							
	pl[BOTTOM].SetCoeficients(	viewProjectionMatrix[1][0] + viewProjectionMatrix[3][0],
								viewProjectionMatrix[1][1] + viewProjectionMatrix[3][1],
								viewProjectionMatrix[1][2] + viewProjectionMatrix[3][2],
								viewProjectionMatrix[1][3] + viewProjectionMatrix[3][3]);

	pl[TOP].SetCoeficients(		-viewProjectionMatrix[1][0] + viewProjectionMatrix[3][0],
								-viewProjectionMatrix[1][1] + viewProjectionMatrix[3][1],
								-viewProjectionMatrix[1][2] + viewProjectionMatrix[3][2],
								-viewProjectionMatrix[1][3] + viewProjectionMatrix[3][3]);

	pl[LEFT].SetCoeficients(	viewProjectionMatrix[0][0] + viewProjectionMatrix[3][0],
								viewProjectionMatrix[0][1] + viewProjectionMatrix[3][1],
								viewProjectionMatrix[0][2] + viewProjectionMatrix[3][2],
								viewProjectionMatrix[0][3] + viewProjectionMatrix[3][3]);

	pl[RIGHT].SetCoeficients(	-viewProjectionMatrix[0][0] + viewProjectionMatrix[3][0],
								-viewProjectionMatrix[0][1] + viewProjectionMatrix[3][1],
								-viewProjectionMatrix[0][2] + viewProjectionMatrix[3][2],
								-viewProjectionMatrix[0][3] + viewProjectionMatrix[3][3]);
}

int Frustum::BoxInFrustum(AABox box)
{
	int result = INSIDE;

	for(int i=0; i< 6; i++)
	{
		if(pl[i].Distance(box.GetVertexPositive(pl[i].normal)) < 0)
		{
			return OUTSIDE;
		}
		else if(pl[i].Distance(box.GetvertexNegative(pl[i].normal)) < 0)
		{
			result = INTERSECT;
		}
	}

	return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~ PLANE DEFINITION ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// TODO: split these up into different files.

Plane::Plane( glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	SetPoints(v1, v2, v3);
}

Plane::Plane()
{

}

Plane::~Plane()
{

}

void Plane::SetPoints(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	glm::vec3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = glm::cross(aux2, aux1); //cross product?

	normal = glm::normalize(normal);
	point = v2;//make sure this works
	d = -(glm::dot(normal, point));
}

void Plane::SetNormalAndPoint(glm::vec3 normal, glm::vec3 point)
{
	this->normal = glm::normalize(normal);
	d = -(glm::dot(this->normal, point));
}

float Plane::Distance(glm::vec3 p)
{
	return (d + glm::dot(normal, p));
}

void Plane::SetCoeficients(float a, float b, float c, float d)
{
	normal = glm::vec3(a, b, c);

	float l = glm::length(normal);

	normal = glm::normalize(normal);

	this->d = d/l;
}