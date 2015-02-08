#ifndef _VERTEX_H
#define _VERTEX_H
struct vertex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	vertex()
	{
		x = 0;
		y = 0;
		z = 0;

		nx = 0;
		ny = 0;
		nz = 0;

		u = 0;
		v = 0;
	}
};
#endif