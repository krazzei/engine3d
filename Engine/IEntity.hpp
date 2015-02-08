/*  IEntity.h

	Created: 2012 July 29.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 2.

	IEntity is the base interface for all objects
	in the game. Including; but not limited to; 
	camera, player, AI, Triggers, levels, etc.
*/

#ifndef _IENTITY_H
#define _IENTITY_H

class IEntity
{
public:
	virtual ~IEntity() {}
	virtual void Update(double deltaTime) = 0;
	unsigned int entityID;
};

#endif