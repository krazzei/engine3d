/*	ResourceManager.h

	Created: 2012 August 14.
	Author: Tyler White.
	TODO: license and legal here.

	Edite: 2012 August 27.

	Defines the ResourceManager Singleton, holds
	resource data, texture names, audio, meshs,
	and any other data that isn't code.
*/

#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include"Main.hpp"
#include "PNGReader.hpp"
#include "Texture.hpp"
#include "../3rd_party/tinyxml2-master/tinyxml2.h"
#include <map>
#include <fstream>
#include <string>
#include <direct.h>

// TODO: stop reading pngs! the gpu should support compressed texture loading!
// also need to read things from custom resource files, and collada files.
class ResourceManager
{
public:
				void									LoadTexture(char* textureFileName, unsigned int** textureName);
				void									LoadMesh(char* meshFileName, float** verts, unsigned short** indices);
	unsigned	int										LoadShader(const char* vertexFile, const char* fragmentFile);
	static		ResourceManager*						Instance();

protected:
	ResourceManager();

private:
	//members
				std::map<char*, unsigned int>			_textureNames;
				PNGReader*								p_pngReader;
	static		ResourceManager*						p_instance;
	const		char*									WORKING_DIRECTORY;

				std::map<const char*, unsigned int>		_programNames;

	//methods
				void									ResourcesDirectory(char* fileName, char* tempDirectory);
};
#endif