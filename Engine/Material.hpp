#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Main.hpp"
#include "ShaderData.hpp"
#include "ResourceManager.hpp" //Texture is imported here.
#include <list>
#include <map>

using std::list;

// TODO: make a more robust material system, have it read the shader source to detect
// number of textures and texture types, also variables that are not passed into the material
// by the engine (ie. artist configuratble, these will be exposed in an editor). Also needs
// to detect transparent and opaque objects. Multiple light support.
// the loading above will be done in the ResourceLoader as we will have "cooked" and "uncooked" assets
class Material
{
public:
	Material(const char* vertexSourceLocation, const char* fragmentSourceLocation);
	void Enable();
	void Disable();
	unsigned int* GetProgramID();
	void LoadTexture(char* fileName);

private:
	//Members
	unsigned	int					_programID;
				list<Texture*>		_textureNames;
				//This holds non-standard shader data (ie, color, shininess, line thickness, etc)
				int					_dataCount;
				IShaderData**		_shaderData;
};
#endif