#include "Texture.hpp"

Texture::Texture(unsigned int textureName, int textureType)
{
	p_textureName = new unsigned int(textureName);
	_type = static_cast<TextureType>(textureType);
}

Texture::~Texture()
{
	glDeleteTextures(1, p_textureName);
	delete p_textureName;
}

unsigned int* Texture::GetTextureName()
{
	return p_textureName;
}

int* Texture::GetTextureType()
{
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