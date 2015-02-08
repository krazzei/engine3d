/*	PNGReader.cpp

	Created: 2012 August 15
	Author: Tyler White
	TODO: license and legal here.

	Edited: 2012 August 27.

	Implements the PNGReader class defined by PNGReader.h
*/

#include "PNGReader.hpp"

PNGReader::PNGReader()
{
	
}

PNGReader::~PNGReader()
{

}

//Loades a PNG file into the graphics card via OpenGL.
//the texture path is the file path to the texture.
//it returns the name of the texture in the card, if its -1 something went wrong.
Image* PNGReader::LoadPNG(char* texturePath)
{
	FILE* filePointer = fopen(texturePath, "rb");

	if(filePointer == NULL)
	{
		return NULL; //invalad file path.
	}

	//the header for a png is 8 bytes.
	unsigned char* header = (unsigned char*) malloc(sizeof(char)*8);

	fread(header, 1, 8, filePointer);
	
	if(!(png_check_sig(header, 8)))
	{
		fclose(filePointer);
		return NULL; //not a png file.
	}

	png_structp pngPtr;
	png_infop pngInfo;

	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(pngPtr == NULL)
	{
		fclose(filePointer);
		return NULL;//out of memory.
	}

	pngInfo = png_create_info_struct(pngPtr);
	if(pngInfo == NULL)
	{
		png_destroy_read_struct(&pngPtr, NULL, NULL);
		fclose(filePointer);
		return NULL; //out of memory.
	}

	//TODO: need to do png error handeling with png's longjmp()
	/*if (setjmp(pngPtr->jumpbuf))
	{
		png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
		return NULL;
	}*/

	png_init_io(pngPtr, filePointer); //initialize the pointer
	png_set_sig_bytes(pngPtr, 8); //lets the pngLib know we checked the header.
	png_read_info(pngPtr, pngInfo); //read up to the first IDAT

	Image* texture = new Image();
	unsigned int* width = new unsigned int(1);
	unsigned int* height = new unsigned int(1);
	int* colorType = new int(1);
	int* bitDepth = new int(1);

	png_get_IHDR(pngPtr, pngInfo, width, height, bitDepth, colorType, NULL, NULL, NULL);

	texture->Width = (int)(*width);
	texture->Height = (int)(*height);

	texture->channels = png_get_channels(pngPtr, pngInfo);
	
	if(*colorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_expand(pngPtr);
	}
	
	if(*colorType == PNG_COLOR_TYPE_GRAY && *bitDepth < 8)
	{
		png_set_expand(pngPtr);
	}
	
	if(png_get_valid(pngPtr, pngInfo, PNG_INFO_tRNS))
	{
		png_set_expand(pngPtr);
	}

	if(*bitDepth == 16)
	{
		png_set_strip_16(pngPtr);
	}
	
	if(*colorType == PNG_COLOR_TYPE_GRAY || *colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(pngPtr);
	}

	png_read_update_info(pngPtr, pngInfo);

	unsigned int rowBytes = png_get_rowbytes(pngPtr, pngInfo);
	//still don't know why I can't just allocat a "blob" of memeory and have png read to it but. . .
	//this is needed due to the differences in pnglib's reading and openGL's texture creation.
	unsigned char** rowPointers = new unsigned char*[*height];

	//inizialize the "length" of our "array"
	texture->Data = new unsigned char[(*height) * rowBytes];
	
	for(int i=0;i<(*height);++i)
	{
		//this flips the image upside down by pnglib's standards but is oriented correctly with openGL.
		rowPointers[(*height) - 1 - i ] = texture->Data + i * rowBytes;
	}

	png_read_image(pngPtr, rowPointers);
	
	png_read_end(pngPtr, NULL);

	//clean up!
	if(pngPtr != NULL && pngInfo != NULL)
	{
		png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
		pngPtr = NULL;
		pngInfo = NULL;
	}

	delete[] rowPointers;
	delete width;
	delete height;
	delete colorType;
	delete bitDepth;
	fclose(filePointer);

	return texture;
}