#ifndef _TEXTURE_H
#define _TEXTURE_H

//because main is not included.
#ifndef GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GL3
#endif

#include "../3rd_party/glfw-2.7.6/include/GL/glfw.h" //really only need the gl.h but glfw will choose that for us.

//Wrapper enum for GL_TEXTURE_{TYPE}
enum TextureType
{
	TX_1D						= GL_TEXTURE_1D,
	TX_2D						= GL_TEXTURE_2D, 
	TX_3D						= GL_TEXTURE_3D,
	TX_RECTANGLE				= GL_TEXTURE_RECTANGLE,
	TX_BUFFER					= GL_TEXTURE_BUFFER,
	TX_CUBE_MAP					= GL_TEXTURE_CUBE_MAP,
	TX_1D_ARRAY					= GL_TEXTURE_1D_ARRAY,
	TX_2D_ARRAY					= GL_TEXTURE_2D_ARRAY,
	TX_CUBE_MAP_ARRAY			= GL_TEXTURE_CUBE_MAP_ARRAY,
	TX_2D_MULTISAMPLE			= GL_TEXTURE_2D_MULTISAMPLE,
	TX_2D_MULTISAMPLE_ARRAY		= GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

class Texture
{
public:
	Texture(unsigned int textureName, int textureType);
	~Texture();

	unsigned int*	GetTextureName();
	int*			GetTextureType();
	void			BindTexture();
	void			UnbindTexture();
protected:
	unsigned int*		p_textureName;
	TextureType			_type;
};
#endif