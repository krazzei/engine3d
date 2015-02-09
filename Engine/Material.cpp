
#include "Material.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"

//should just be fed the program id and shader data.
//should it? Just playing devil's advocate because I can't remember why the above comment was written. Tyler White 20150208.
Material::Material(const char* vertexSourceLocation, const char* fragmentSourceLocation)
{
	_programID = ResourceManager::Instance()->LoadShader(vertexSourceLocation, fragmentSourceLocation);
	_textureNames = list<Texture*>();
	//temporary, need to rework the loading/creation of things.
	_dataCount = 1;
	_shaderData = (IShaderData**)(malloc(sizeof(IShaderData)));
	
	_shaderData[0] = (IShaderData*)(new ShaderData<glm::vec3>(glGetUniformLocation(_programID, "_color"), 1, glm::vec3(1.0f, 1.0f, 1.0f)));
}

void Material::LoadTexture(char* fileName)
{
	//TODO: detect if we need multiple textures.
	
	unsigned int* textureName = new unsigned int;
	ResourceManager::Instance()->LoadTexture(fileName, &textureName);
	//Temp need to get the texture type
	_textureNames.push_back(new Texture(*textureName, GL_TEXTURE_2D));
}

unsigned int* Material::GetProgramID()
{
	return &_programID;
}

void Material::Enable()
{
	list<Texture*>::iterator currentTexture;
	unsigned short textureNumber = GL_TEXTURE0; //guaranteed to have 80 textures.
	for(currentTexture = _textureNames.begin();currentTexture != _textureNames.end();currentTexture++, textureNumber++) //is this too confusing/hard to read?
	{
		glActiveTexture(textureNumber);
		currentTexture._Ptr->_Myval->BindTexture();
	}

	glUseProgram(_programID);
	//must be after because gl does not know what program to send the data to.
	for(int i = 0;i<_dataCount;i++)
	{
		_shaderData[i]->Send();
	}
}

void Material::Disable()
{
	list<Texture*>::iterator currentTexture;
	unsigned short textureNumber = GL_TEXTURE0;
	for(currentTexture = _textureNames.begin();currentTexture != _textureNames.end();currentTexture++, textureNumber++)
	{
		glActiveTexture(textureNumber);

		currentTexture._Ptr->_Myval->UnbindTexture();
	}

	glUseProgram(0);
}