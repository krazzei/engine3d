/*	PNGReader.h

	Created: 2012 August 14.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 16.

	Defines the PNGReader class,
	simply reads a png from the file path and loads it into
	the graphics card, then returns the name (int) of the
	openGL texture.
*/

#ifndef _PNGREADER_H
#define _PNGREADER_H

#include "Main.hpp"
#include "../3rd_party/lpng1616/png.h"

class PNGReader
{
public:
				PNGReader();
				~PNGReader();
	Image*		LoadPNG(char* texturePath);
};

#endif