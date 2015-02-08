#include "Texture.hpp"

Texture::Texture(unsigned int textureName, int textureType)
{
	p_textureName = new unsigned int(textureName);
	_type = static_cast<TextureType>(textureType);
}

Texture::~Texture()
{
	//TODO: make sure the texture is released from graphics memory.
	delete p_textureName;
}

unsigned int* Texture::GetTextureName()
{
	return p_textureName;
}

int* Texture::GetTextureType()
{
	//aparently using c style cast is bad practice in c++
	//FIXME
	return (int*)&_type;
}

void Texture::BindTexture()
{
	glBindTexture(_type, *p_textureName);
}

void Texture::UnbindTexture()
{
	glBindTexture(_type, 0);
}