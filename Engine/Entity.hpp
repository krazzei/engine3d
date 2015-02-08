/*  Entity.h

	Created: 2012 July 29.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 2.

	Entity will be an abstract class that implements
	IEntity.
*/

#ifndef _ENTITY_H
#define _ENTITY_H

#include "Main.hpp"
#include "IEntity.hpp"
#include "EntityManager.hpp"

class Entity abstract : IEntity
{
public:
	Entity(void) : IEntity()
	{
		EntityManager::Instance()->AddEntity(this);
	}
	virtual ~Entity() 
	{
		EntityManager::Instance()->RemoveEntites(this);
	}
	virtual void Update(double deltaTime) {};
};

#endif