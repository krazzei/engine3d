/*  Sprite.h

	Created: 2012 July 25.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 4.

	Sprite.h defines the sprite class.
*/

#ifndef _SPRITE_H
#define _SPRITE_H

#include "Mesh.hpp"

class Sprite : public Mesh
{
public:
	Sprite(int framesPerSecond, int totalFrames, float frameWidth, float frameHeight, float textureWidth, float textureHeight);

	virtual			~Sprite();

	virtual			void				Draw();
private:

	int				_framesPerSecond;
	int				_totalFrames;
	float			_frameWidth;
	float			_frameHeight;
	float			_textureWidth;
	float			_textureHeight;

	//temp
	int				_currentFrame;
	int				_systemFrame;
	int				_loop;
	int				_maxWidthFrames;
	int				_currentWidthFrame;
};

#endif