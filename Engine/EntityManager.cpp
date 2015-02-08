/*	EntityManager.cpp
	
	Created: 2012 August 2.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 3.

	implements the class EntityManager defined by EntityManager.h
*/

#include "EntityManager.hpp"

EntityManager* EntityManager::p_instance = 0;

EntityManager* EntityManager::Instance()
{
	if(p_instance == NULL)
	{
		p_instance = new EntityManager;
	}

	return p_instance;
}

EntityManager::EntityManager()
{
}

void EntityManager::AddEntity(IEntity* entity)
{
	_entityList.push_back(entity);
	entity->entityID = _uniqueEntityID;
	_uniqueEntityID++;
}

void EntityManager::RemoveEntites(IEntity* entity)
{
	_entityList.remove(entity);
}

void EntityManager::UpdateEntities(double deltaTime)
{
	for( _iterator = _entityList.begin() ; _iterator != _entityList.end();_iterator++)
	{
		_iterator._Ptr->_Myval->Update(deltaTime);
	}
}