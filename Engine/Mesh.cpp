/*  Mesh.cpp

	Created: 2012 July 29.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 27.

	Implements the mesh class defined in Mesh.h
*/

#include "Mesh.hpp"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

#define VAO

struct vertex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	vertex()
	{
		x = 0;
		y = 0;
		z = 0;

		nx = 0;
		ny = 0;
		nz = 0;

		u = 0;
		v = 0;
	}
};

Mesh::Mesh(glm::vec3 worldPos) : IDrawable()
{
	//because IDrawable.h can't have RenderingManager.h and IDrawable doesn't have a defined constructor,
	//the implementers of IDrawable add themselves to the RenderingManager.
	//this avoids the cyclic dependency issue, not sure if its the best solution though.
	RenderingManager::Instance()->Add((IDrawable*)this);

	_vboId = 0;
	_elementBufferId = 0;
	unsigned short* indices = new unsigned short[36];
	int i = 0;

	vertex* vertices = new vertex[36];
	for(i=0;i<36;i++)
	{
		vertices[i].x = CUBE_QUAD_SMALL[ TRIANGLE_CUBE_INDICIES[i]*3];
		vertices[i].y = CUBE_QUAD_SMALL[ TRIANGLE_CUBE_INDICIES[i]*3+1];
		vertices[i].z = CUBE_QUAD_SMALL[ TRIANGLE_CUBE_INDICIES[i]*3+2];
	}

	int texcoordIndex = 0;
	for(i=0;i<36;i++)
	{
		if(texcoordIndex > 5)
		{
			texcoordIndex = 0;
		}

		vertices[i].u = UV_COORDS[TRIANGLE_UV_INDICIES[texcoordIndex]*2];
		vertices[i].v = UV_COORDS[TRIANGLE_UV_INDICIES[texcoordIndex]*2+1];
		texcoordIndex++;
	}

	//can't use normals with vao, also I havn't gotten indices and texcoords to work.
	int normalIndex = 0;
	for(i=0;i<36;i++)
	{
		if( (i % 6) == 0 && i != 0)
		{
			normalIndex++;
		}

		//should make indeicies for normals!
		vertices[i].nx = CUBE_NORMALS[normalIndex*3];
		vertices[i].ny = CUBE_NORMALS[normalIndex*3+1];
		vertices[i].nz = CUBE_NORMALS[normalIndex*3+2];
	}

	for(i=0;i<36;i++)
	{
		indices[i] = i;
	}

	
	glGenBuffers(1, &_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 36, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 36, indices, GL_STATIC_DRAW);

	p_material = new Material("../Engine3D_express/Resources/light_texture.vert", "../Engine3D_express/Resources/light_texture.frag");

	_matrixID = glGetUniformLocation(*(p_material->GetProgramID()), "M");
	PrintGLError();

	_viewID = glGetUniformLocation(*(p_material->GetProgramID()), "V");
	PrintGLError();

	_projectionID = glGetUniformLocation(*(p_material->GetProgramID()), "P");
	PrintGLError();

	_vertexLocation = glGetAttribLocation(*(p_material->GetProgramID()), "vertexPosition_modelspace");
	PrintGLError();

	_normalLocation = glGetAttribLocation(*(p_material->GetProgramID()), "vertexNormal_modelspace");
	PrintGLError();

	_uvLocation = glGetAttribLocation(*(p_material->GetProgramID()), "vertexUV");
	PrintGLError();

#ifdef VAO
	if(GLEW_VERSION_3_0)
	{
		glGenVertexArrays(1, &_vaoID);
		PrintGLError();
		InitializeVAO();
	}
#endif
	
	//lighthose3d did not explain this very well, corner (first parameter) is the "lowest" vertex in world space.
	//because we (currrently) have a box whoes vertices are in world space, we can take our world position - (1,1,1) to get the world position of the vertex (-1, -1, -1).
	//the other parameters are the amounts we need to add to the "lowest" vertex to get the "highest" vertex in world space, for our test cube it would be 2 across the board (x,y,z)
	//becase -1(lowest) + 2(amount) = 1(highest).
	p_boundingBox = new AABox(glm::vec3(-1), 2, 2, 2);

	p_modelMatrix = new glm::mat4(1.0f);
	*p_modelMatrix = glm::translate(*p_modelMatrix, worldPos);
	SetTransform(p_modelMatrix);

	//these are now in GPU memory, delete them from heap.
	delete[] indices;
	delete[] vertices;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vaoID);
	glDeleteBuffers(1, &_vboId);
	glDeleteBuffers(1, &_elementBufferId);
}

void Mesh::InitializeVAO()
{
	glBindVertexArray(_vaoID);
	
	//this happens first so we don't have to have multiple location checks.
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);

	//do we have a valid handle to the vertex location.
	if(_vertexLocation > -1)
	{
		glEnableVertexAttribArray(_vertexLocation);
		glVertexAttribPointer(_vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
	}

	if(_normalLocation > -1)
	{
		glEnableVertexAttribArray(_normalLocation);
		glVertexAttribPointer(_normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(sizeof(float) * 3));
	}

	if(_uvLocation > -1)
	{
		glEnableVertexAttribArray(_uvLocation);
		glVertexAttribPointer(_uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(sizeof(float) * 6));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);

	glBindVertexArray(0);
}

void Mesh::Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix)
{
	p_material->Enable();
	
	//Let the gpu calculate the MVP matrix
	// This might worth testing if its faster on the GPU or CPU, after writing this I would think just doing it on CPU
	// and then copying one matrix to the GPU would be faster ... Tyler White 20150208
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &((*p_modelMatrix)[0][0]));
	glUniformMatrix4fv(_projectionID, 1, GL_FALSE, &((*projectionMatrix)[0][0]));
	glUniformMatrix4fv(_viewID, 1, GL_FALSE, &((*viewMatrix)[0][0]));

#ifndef VAO
	glEnableVertexAttribArray(0); //submitting vertices on stream 0.
	glEnableVertexAttribArray(1); //submitting normals on stream 1.
	glEnableVertexAttribArray(2); //submitting texcoords on stream 2.
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	//vertext coordinates on 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
	//normals on 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(sizeof(float) * 3));
	//uv coordinates on 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(sizeof(float) * 6));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
#else
	glBindVertexArray(_vaoID);
#endif

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
	
#ifndef VAO
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//bind with 0 so we switch (vboId and elementeId) back to normal pointer operation.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	PrintGLError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	PrintGLError();
#else
	glBindVertexArray(0);
#endif

	p_material->Disable();
}

// This is untested! Tyler White 20150208
void Mesh::Translate(glm::vec3 pos)
{
	*p_modelMatrix = glm::translate(*p_modelMatrix, pos);
	p_boundingBox->SetTransform(p_modelMatrix);
}

void Mesh::LoadMesh(char* fileName)
{
	// TODO: load a mesh from data files (collada, mb, fbx, etc).
//	ResourceManager::Instance()->LoadMesh(fileName, &_vertices, &_indices);
}

void Mesh::LoadTexture(char* fileName)
{
	p_material->LoadTexture(fileName);
}

Material* Mesh::GetMaterial()
{
	return p_material;
}

AABox* Mesh::GetAABox()
{
	return p_boundingBox;
}

void Mesh::SetTransform(glm::mat4* transform)
{
	p_modelMatrix = transform;
	p_boundingBox->SetTransform(transform);
}