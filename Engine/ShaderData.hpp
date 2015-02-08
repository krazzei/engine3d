#ifndef _SHADERDATA_H
#define _SHADERDATA_H

#include "Main.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

//Interface for shader data, made so we can have a reference to shader data without having to know the type.
class IShaderData
{
public:
	//sends the data to the shader, make sure you call glUseProgram before calling this!
	virtual		void		Send() = 0;
	virtual		~IShaderData() {};
private:
	int			_location;
	GLsizei		_count;
	bool		_transpose;
};

//shader data, implements IShaderData. Templates are used for laziness. 
template<typename T>
class ShaderData : IShaderData
{
public:
	ShaderData(int location, GLsizei count, T value) : IShaderData()
	{
		_location = location;
		_count = count;
		_value = value;
	}

	ShaderData(int location, GLsizei count, bool transpose, T value) : IShaderData()
	{
		_location = location;
		_count = count;
		_value = value;
		_transpose = transpose;
	}

	virtual ~ShaderData()
	{
	}

	virtual void Send()
	{
		//printf("no method for your type: ", T);
	}
private:
	int			_location;
	GLsizei		_count;
	bool		_transpose;
	T			_value;
};

//specific methods for types of data a shader will have, if data is not here we will get a message.
//begin float
void ShaderData<const float*>::Send()
{
	glUniform1fv(_location, _count, _value);
}

void ShaderData<glm::vec2>::Send()
{
	glUniform2fv(_location, _count, &_value.x);
}

void ShaderData<glm::vec3>::Send()
{
	glUniform3fv(_location, _count, &(_value.x));
}

void ShaderData<glm::vec4>::Send()
{
	glUniform4fv(_location, _count, &_value.x);
}
//end float

//begin int
void ShaderData<const int*>::Send()
{
	glUniform1iv(_location, _count, _value);
}

//Todo int vectors, might not even be worth it.
//end int

//todo matrix, might not be worth it or even needed.
#endif