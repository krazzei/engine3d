#include "ShaderPropertyReader.hpp"

ShaderPropertyReader::ShaderPropertyReader(const char* vertextSource, const char* fragmentSource, unsigned int programID)
{
	VOID_MAIN = "void main";
	IN = "in";
	UNIFORM = "uniform";
	OUT = "out";

	_programId = programID;

	ReadShaderData(vertextSource);
	ReadShaderData(fragmentSource);
}

void ShaderPropertyReader::ReadShaderData(const char* shaderSource)
{
	std::ifstream shader(shaderSource, std::ios::in);
	std::string line = "";
	while(std::getline(shader, line))
	{
		if(!ReadLine(line))
		{
			break;
		}
	}
}

bool ShaderPropertyReader::ReadLine(std::string line)
{
	if(line.c_str() == "")
	{
		// Blank line keep going.
		return true;
	}

	if(line.find(VOID_MAIN) != std::string::npos)
	{
		printf("We have read all properties \n");
		//we are done with the properties.
		//NOTE: if there are properties past the main there better be a damn good reason. Until then it will be ignored.
		
		//we should stop.
		return false;
	}

	std::vector<std::string> splitLine = SplitString(line, ' ');
	
	if(splitLine[0] == UNIFORM)
	{
		// check if we already have this property.
		
		std::list<const char*>::iterator prop = std::find(_names.begin(), _names.end(), splitLine[2].c_str());

		// It equals the end, so it does not exist.
		if(prop == _names.end())
		{
			printf("property not found, adding it \n");
			// find the data type and create ShaderData to it
			_shaderData.push_back(CreateShaderData(splitLine[0], splitLine[1], splitLine[2]));
			// add the property name to the list.
			_names.push_back(splitLine[2].c_str());
		}
	}

	return true;
}

IShaderData* ShaderPropertyReader::CreateShaderData(std::string loadName, std::string type, std::string name)
{
	if(type == "float")
	{
		return (IShaderData*)(new ShaderData<float>(glGetUniformLocation(_programId, name.c_str()), 1, 0));
	}
	else if(type == "vec2")
	{
		return (IShaderData*)(new ShaderData<glm::vec2>(glGetUniformLocation(_programId, name.c_str()), 1, glm::vec2()));
	}
	else if(type == "vec3")
	{
		return (IShaderData*)(new ShaderData<glm::vec3>(glGetUniformLocation(_programId, name.c_str()), 1, glm::vec3()));
	}
	else if(type == "mat4")
	{
		return (IShaderData*)(new ShaderData<glm::mat4>(glGetUniformLocation(_programId, name.c_str()), 1, glm::mat4()));
	}
	else if(type == "mat3x4")
	{
		return (IShaderData*)(new ShaderData<glm::mat3x4>(glGetUniformLocation(_programId, name.c_str()), 1, glm::mat3x4()));
	}
	
	return NULL;
}

list<IShaderData*> ShaderPropertyReader::GetShaderData()
{
	return _shaderData;
}

std::vector<std::string> ShaderPropertyReader::SplitString(std::string string, char character)
{
	std::vector<std::string> rVal = std::vector<std::string>();
	int lastPosition = 0;
	for(unsigned int i=0;i<string.length();i++)
	{
		if(string[i] == character || string[i] == '\n' || string[i] == ';')
		{
			rVal.push_back(string.substr(lastPosition, i - lastPosition));
			lastPosition = i + 1;
		}
	}

	return rVal;
}