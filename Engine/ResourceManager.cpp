/*	ResourceManager.cpp

	Created: 2012 August 14.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 October 21.
	
	Implements the ResourceManager class
	Defined by ResourceManager.h
*/

#include "ResourceManager.hpp"

using namespace tinyxml2;

ResourceManager* ResourceManager::p_instance = 0;

ResourceManager* ResourceManager::Instance()
{
	if(p_instance == NULL)
	{
		p_instance = new ResourceManager;
	}
	
	return p_instance;
}

ResourceManager::ResourceManager()
{
	p_pngReader = new PNGReader();
	//_numTabs = 0;
	if((WORKING_DIRECTORY = _getcwd(NULL, 0)) == NULL)
	{
		std::cout << "get cwd error!";
	}
	else
	{
		std::cout << WORKING_DIRECTORY;
		std::cout << std::endl;
	}
}

void ResourceManager::LoadTexture(char* textureFileName, unsigned int** textureName)
{
	if(_textureNames[textureFileName] != 0)
	{
		*textureName = &_textureNames[textureFileName];
		return;
	}

	char* tempDirectory = (char*) malloc(sizeof(char) * 200);
	
	ResourcesDirectory(textureFileName, tempDirectory);

	Image* texture = p_pngReader->LoadPNG(tempDirectory);

	if(texture != NULL)
	{
		glGenTextures(1, *textureName);

		glBindTexture(GL_TEXTURE_2D, **textureName);

		//is this the best way?
		if(texture->channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->Width, texture->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)texture->Data);
		}
		else if(texture->channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->Width, texture->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture->Data);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//Delete?
		if(texture->Data != NULL)
		{
			free(texture->Data);
		}

		free(texture);
	}

	if(tempDirectory != NULL)
	{
		free(tempDirectory);
	}

	_textureNames[textureFileName] = **textureName;
}

//this was a quick and dirty way to read a collada file, this WILL change!
void ResourceManager::LoadMesh(char* meshPath, float** vertices, unsigned short** indices)
{
	char* dir = new char[200];//(char*)malloc(sizeof(char) * 200);
	ResourcesDirectory(meshPath, dir);
	XMLDocument* doc = new XMLDocument();
	XMLError loadOkay = doc->LoadFile(dir);
	
	if(loadOkay == 0)
	{
		printf("loaded the file!\n");
		XMLElement* element = doc->RootElement()->FirstChildElement("library_geometries")->FirstChildElement("geometry");
		const char* title = element->Attribute("id");
		printf("The first node's first element's text %s\n", title);
		//this skips the mesh element, obviously clean this up later.
		element = element->FirstChildElement()->FirstChildElement();
		printf("source: %s id: %s\n", element->Value(), element->Attribute("id"));
		element = element->FirstChildElement();
		printf("count: %s data: %s\n", element->Attribute("count"), element->GetText());

		//temp: get the values in string form.
		const char* positionValue = element->GetText();
		//Temp: set a float array for the values.
		*vertices = new float[std::atoi(element->Attribute("count"))];//(float*)malloc(sizeof(float) * (std::atoi(element->Attribute("count"))));

		//Temp: seperate the values by space
		char* currentNumberString = new char[20];//(char*)malloc(sizeof(char) * 20);
		float number = 0;
		int stringIndex = 0;
		int vertIndex = 0;
		while(*positionValue != NULL)
		{
			//end of this value
			if(*positionValue == ' ')
			{
				currentNumberString[stringIndex] = ' ';
			//	printf("the char %s\n", currentNumberString);
				//error checking
				//parse the char in to number
			//	std::cout << std::atof(currentNumberString) << std::endl;
				number = std::atof(currentNumberString);
				//store number in our array
				(*vertices)[vertIndex] = number;
				vertIndex++;
				//reset the char
				stringIndex = 0;

				//progress passed the space
				positionValue++;
			}
			else //add the value to the char
			{
				currentNumberString[stringIndex] = *positionValue;
				stringIndex++;
				positionValue++;
			}
		}
		
		//writes the last number
		currentNumberString[stringIndex] = ' ';
		number = std::atof(currentNumberString);
		(*vertices)[vertIndex] = number;


		//now for the indices
		//goes to source "Cube-mesh-position"
		element = (XMLElement*)element->Parent();
		printf("element %s", element->Name());
		//now get the "polylist"
		//ignoring a lot of stuff here, like materials, faces "count", and normals.
		element = element->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();

		printf("element name: %s\n", element->Name());
		element = element->FirstChildElement("p");
		printf("element name: %s\n", element->Name());
		//reusing some of the variables from above
		stringIndex = 0;
		currentNumberString = new char[2];//(char*)malloc(sizeof(char) * 2);
		vertIndex = 0;
		//this is bad, need to get the count of the polylist multiplied by each value of vcount and add them up.
		*indices = new unsigned short[24];//(char*)malloc(sizeof(float) * 24);

		const char* indiceValue = element->GetText();
		int indiceNumber = 0;
		bool skipNumber = false;

		while(*indiceValue != NULL)
		{
			//if(!skipNumber)
			{
				if(*indiceValue == ' ')
				{
					currentNumberString[stringIndex] = '\n';
					indiceNumber = std::atoi(currentNumberString);
					//reusing vertIndex.
					//printf("indice: %d\n", indiceNumber);
					//std::cout << indiceNumber << std::endl;
					(*indices)[vertIndex] = indiceNumber;
					vertIndex++;
					stringIndex = 0;

					indiceValue++;
					skipNumber = true;
				}
				else
				{
					currentNumberString[stringIndex] = *indiceValue;
					stringIndex++;
					indiceValue++;
				}
			}
			//else
			//{
				//super hard coded!
				//skips the number
			//	indiceValue++;
				//skips the space
			//	indiceValue++;
			//	skipNumber = false;
			//}
		}

		//write the last number
		currentNumberString[stringIndex] = '\n';
		indiceNumber = std::atoi(currentNumberString);
		(*indices)[vertIndex] = indiceNumber;

		printf("done\n");
	}
	else
	{
		printf("did not load the file error %d", loadOkay);
	}
}

//This dose not use the ResourceManager's ResourceDirectory method because I am seeing flaws in that solution
//and currently don't know enough to fix it.
unsigned int ResourceManager::LoadShader(const char* vertexFile, const char* fragmentFile)
{
	//temp, not sure if the file path is a good way to store the program.
	//also not checking if the fragment is the same, essentially I opened a can of worms.
	if(_programNames[vertexFile] > 0)
	{
		return _programNames[vertexFile];
	}

	unsigned int vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFile, std::ios::in);
	if(vertexShaderStream.is_open())
	{
		std::string line = "";
		while(std::getline(vertexShaderStream, line))
		{
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFile, std::ios::in);
	if(fragmentShaderStream.is_open())
	{
		std::string line = "";
		while(std::getline(fragmentShaderStream, line))
		{
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	int result = GL_FALSE;
	int infoLogLength;

	printf("compiling vertex shader \n");
	const char* vertexSource = vertexShaderCode.c_str();
	glShaderSource(vertShaderID, 1, &vertexSource, NULL);
	glCompileShader(vertShaderID);

	//check for errors
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* vertexShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(vertShaderID, infoLogLength, NULL, vertexShaderErrorMessage);
	printf(vertexShaderErrorMessage);
	printf("\n");

	printf("compiling fragment shader\n");
	const char* fragSource = fragmentShaderCode.c_str();
	glShaderSource(fragShaderID, 1, &fragSource, NULL);
	glCompileShader(fragShaderID);

	//check for errors
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* fragShaderErrorMessage = new char[infoLogLength];
	glGetShaderInfoLog(fragShaderID, infoLogLength, NULL, fragShaderErrorMessage);
	printf("%s\n", fragShaderErrorMessage);

	//linking the program
	printf("Linking program\n");
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* programErrorMessage = new char(infoLogLength);
	glGetProgramInfoLog(programID, infoLogLength, NULL, programErrorMessage);
	printf("%s\n", programErrorMessage);

	//delete shaders.
	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	_programNames[vertexFile] = programID;

	return programID;
}

void ResourceManager::ResourcesDirectory(char* fileName, char* tempDirectory)
{
	if(tempDirectory == NULL)
	{
		tempDirectory = (char*)malloc(sizeof(char) * 200); //todo: get the length of the file path. also double check that sizeof(char) is correct
	}

	if(fileName == NULL)
	{
		//TODO: error messages.
		return;
	}

	strcpy(tempDirectory, WORKING_DIRECTORY);
	strcat(tempDirectory, "\\Resources\\"); //possibly need a type folder, if so make an enum (?)
	strcat(tempDirectory, fileName);
}