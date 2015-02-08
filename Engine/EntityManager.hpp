/*	EntityManager.h
	
	Created: 2012 August 2.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 3.

	defines the EntityManager calss, manages
	Entities and allows them to be Updated easily.
*/

#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include "Main.hpp"
#include "IEntity.hpp"
#include <list>

class EntityManager
{
public:
	static EntityManager* Instance();
	void UpdateEntities(double deltaTime);
	void AddEntity(IEntity* entity);
	void RemoveEntites(IEntity* entity);
protected:
	EntityManager();
private:
	static EntityManager* p_instance;
	std::list<IEntity*> _entityList;
	std::list<IEntity*>::iterator _iterator;
	unsigned int _uniqueEntityID;
};

#endif