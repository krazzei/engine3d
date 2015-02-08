/*  Mesh.h

	Created: 2012 July 29.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 18.

	Mesh.h contains the interface for the Mesh
	class, Mesh class is a non animated Mesh,
	that can be textured, uv's can be changed,
	position can be moved/rotated/scaled.
*/

#ifndef _MESH_H
#define _MESH_H

#include "Main.hpp"
#include "IDrawable.hpp"
#include "ResourceManager.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include "Material.hpp"
#include "RenderingManager.hpp"
#include "ITransformable.hpp"

//TODO: animations.
class Mesh : IDrawable, ITransformable
{
public:
	Mesh(glm::vec3 worldPos);
	virtual	~Mesh();

	virtual		void				Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix);
	virtual		void				LoadMesh(char* fileName);
	virtual		void				LoadTexture(char* fileName);
	virtual		Material*			GetMaterial();
	virtual		AABox*				GetAABox();
	virtual		unsigned int*		GetLightCount();
	virtual		void				SetTransform(glm::mat4* transform);
	
				void				Translate(glm::vec3 pos);

protected:
	void InitializeVAO();

	//Buffer IDs.
	unsigned int _vaoID;
	unsigned int _vboId;
	unsigned int _elementBufferId;

	unsigned int* p_lightCount;

	//shader uniform locations
	int _matrixID;
	int _viewID;
	int _projectionID;
	//attributes.
	int _vertexLocation;
	int _normalLocation;
	int _uvLocation;

	Material*		p_material;
	AABox*			p_boundingBox;
	glm::mat4*		p_modelMatrix;
};

static const float PLANE_QUAD[] = { 1.0f, 1.0f, 0.0f,
									-1.0f, 1.0f, 0.0f,
									-1.0f,-1.0f, 0.0f,
									 1.0f,-1.0f, 0.0f};

static const float PLANE_TRI[] = { 1.0f, 1.0f, 0.0f,
								   -1.0f, 1.0f, 0.0f,
								   -1.0f,-1.0f, 0.0f,
								    1.0f, 1.0f, 0.0f,
								    1.0f,-1.0f, 0.0f,
								   -1.0f,-1.0f, 0.0f};

static const float CUBE_QUAD[] = { 1.0f, 1.0f, 1.0f, //front face
								  -1.0f, 1.0f, 1.0f,
								  -1.0f,-1.0f, 1.0f,
								   1.0f,-1.0f, 1.0f,
								   1.0f, 1.0f,-1.0f, //right face
								   1.0f, 1.0f, 1.0f,
								   1.0f,-1.0f, 1.0f,
								   1.0f,-1.0f,-1.0f,
								   1.0f, 1.0f,-1.0f, //back face
								  -1.0f, 1.0f,-1.0f,
								  -1.0f,-1.0f,-1.0f,
								   1.0f,-1.0f,-1.0f,
								  -1.0f, 1.0f,-1.0f, //left face
								  -1.0f, 1.0f, 1.0f,
								  -1.0f,-1.0f, 1.0f,
								  -1.0f,-1.0f,-1.0f,
								   1.0f, 1.0f,-1.0f, //top face
								  -1.0f, 1.0f,-1.0f,
								  -1.0f, 1.0f, 1.0f,
								   1.0f, 1.0f, 1.0f,
								   1.0f,-1.0f, 1.0f, //bottom face
								  -1.0f,-1.0f, 1.0f,
								  -1.0f,-1.0f,-1.0f,
								   1.0f,-1.0f,-1.0f};
																//from center
static const float CUBE_QUAD_SMALL[] =	{	-1.0f,  1.0f,  1.0f,  //left up forward		0
											1.0f, 1.0f,  1.0f,  //right up forward		1
											1.0f, -1.0f, 1.0f, //right down forwad		2
											-1.0f, -1.0f, 1.0f, //left down forward		3
											-1.0f,  1.0f, -1.0f,  //left up backward	4
											1.0f, 1.0f,  -1.0f,  //right up backward	5
											1.0f, -1.0f, -1.0f, //right down backward	6
											-1.0f, -1.0f, -1.0f,}; //left down backward	7

static const int QUAD_CUBE_INDICIES[] = { 0, 1, 2, 3, //front face
										  1, 5, 6, 2, //right face
										  4, 5, 6, 7, //back face
										  4, 0, 3, 7, //left face
										  4, 5, 1, 0, //top face
										  7, 6, 2, 3}; //bottom face

static const int TRIANGLE_CUBE_INDICIES[] = { 0, 1, 2, 2, 3, 0, //front face
											  1, 5, 6, 6, 2, 1, //right face
											  5, 4, 7, 7, 6, 5, //back face
											  4, 0, 3, 3, 7, 4, //left face
											  4, 5, 1, 1, 0, 4, //top face
											  7, 6, 2, 2, 3, 7}; //bottom face

static const int TRIANGLE_UV_INDICIES[] = { 1, 2, 3, 3, 0, 1 };

static const float CUBE_NORMALS[] = { 0, 0, 1, //front		0
									  1, 0, 0, //right		1
									  0, 0, -1, //back		2
									  -1, 0, 0, //left		3
									  0, 1, 0, //top		4
									  0, -1, 0}; //bottom	5

static const float UV_COORDS[] = { 0.0f, 0.0f, //left down.
								   0.0f, 1.0f, //left up.
								   1.0f, 1.0f, //right up.
								   1.0f, 0.0f}; //right down.

#endif