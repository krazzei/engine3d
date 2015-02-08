/*  Sprite.cpp

	Created: 2012 July 25.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 20.
	
	implements the Sprite class defined in Sprit.h
	Not complient with OpenGL 3.0
*/

#include "Sprite.hpp"
/*
Sprite::Sprite(int framesPerSecond, int totalFrames, float frameWidth, float frameHeight, float textureWidth, float textureHeight)// : Mesh()
{
	_framesPerSecond = framesPerSecond;
	_totalFrames = totalFrames;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_textureWidth = textureWidth;
	_textureHeight = textureHeight;
	_currentFrame = 0;
	_currentWidthFrame = 0;
	_maxWidthFrames = _textureWidth / _frameWidth - 1;
	_systemFrame = 0;

	float temp = (*(CameraManager::Instance()->GetCamera(0)->GetHeight())) / 10;

	for(int i=0;i<12;i++)
	{
		if((i % 2) == 0)
		{
			//x
			_vertices[i] = PLANE_QUAD[i] * (frameWidth / temp);
		}
		else
		{
			//y
			_vertices[i] = PLANE_QUAD[i] * (frameHeight / temp);
		}
	}

	//temp:
	//_texCoords = new float[8];
	//assumes first frame is top left of texture.
	//1, 1 top right.
	_texCoords[0] = frameWidth / textureWidth;
	_texCoords[1] = frameHeight / textureHeight;
	//0, 1
	_texCoords[2] = 0.0f;
	_texCoords[3] = frameHeight / textureHeight;
	//0,0
	_texCoords[4] = 0;
	_texCoords[5] = 0;
	//1, 0
	_texCoords[6] = frameWidth / textureWidth;
	_texCoords[7] = 0.0f;
}

Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	//now would be a good time to pass in delta time.
	//for now assume that we run at 60 fps and every call to draw is a frame.
	//currently mesh is loading in a plane in its ctor. normally you need to use LoadMesh().
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -6.0f);

	glBindTexture(GL_TEXTURE_2D, *_textureName);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, _texCoords);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	_systemFrame++;
	
	if(_systemFrame >= (60 / _framesPerSecond))
	{
		_currentFrame++;
		_currentWidthFrame++;

		if(_currentFrame > _totalFrames)
		{
			//start at frame one!
			//assumes first frame is top left of texture.
			//1, 1 top right.
			_texCoords[0] = _frameWidth / _textureWidth;
			_texCoords[1] = _frameHeight / _textureHeight;
			//0, 1
			_texCoords[2] = 0;
			_texCoords[3] = _frameHeight / _textureHeight;
			//0,0
			_texCoords[4] = 0;
			_texCoords[5] = 0;
			//1, 0
			_texCoords[6] = _frameWidth / _textureWidth;
			_texCoords[7] = 0;

			_currentFrame = 0;
		}
		else
		{
			for(_loop = 0; _loop < 8 ;_loop++)
			{
				//even is x.
				if(_loop % 2 == 0)
				{
					_texCoords[_loop] += _frameWidth / _textureWidth;
				}
				else //odd is y.
				{
					if(_currentWidthFrame > _maxWidthFrames)
					{
						_texCoords[_loop-1] -= _maxWidthFrames * _frameWidth;
						_texCoords[_loop] += _frameHeight;
					}
				}
			}
		}

		_systemFrame = 0;
	}
}*/