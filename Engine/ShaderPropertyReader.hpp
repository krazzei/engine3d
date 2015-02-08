#include "Main.hpp"
#include "ShaderData.hpp"
#include "../3rd_party/glm-0.9.4.2/glm/glm.hpp"
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>

using std::list;

/// <summary>
/// Reads the source of a shader and populates 
/// <see cref="ShaderData"/> with the properties.
/// Handles uniform types only.
/// </summary>
class ShaderPropertyReader
{
public:
	ShaderPropertyReader(const char* vertexSource, const char* fragmentSource, unsigned int programId);
	list<IShaderData*> GetShaderData();
private:
	const char* VOID_MAIN;
	const char* IN;
	const char* UNIFORM;
	const char* OUT;

	void ReadShaderData(const char* shaderSource);
	bool ReadLine(std::string line);
	IShaderData* CreateShaderData(std::string loadName, std::string type, std::string name);
	std::vector<std::string> SplitString(std::string string, char character);

	list<IShaderData*> _shaderData;
	list<const char*>	_names;
	unsigned int _programId;
};