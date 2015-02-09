#ifndef _IMESHLOADER_H
#define _IMESHLOADER_H

#include "Mesh.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"

/// <summary>
/// Creational 3D scene loader interface. given a 3D scene file,
/// read the file then create any and all supported objects such as
/// geometry, lights, cameras, effects, etc.
/// This is not a final Interface, just an ease of use Interface, 
/// apparently an engine should have its own propriatary data object 
/// files that can be streamed in to memory from disk.
/// </summary>
class IMeshLoader
{
public:
	virtual ~IMeshLoader() {}
};
#endif