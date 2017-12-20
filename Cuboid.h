#ifndef CUBOID_H
#define CUBOID_H

#include "Geometry.h"

class Cuboid: public Geometry
{
public:
	Cuboid(GLfloat length, GLfloat width, GLfloat height);
	Cuboid(Size size);
	Cuboid(Vector bottomCenter, Size size);
	
	void setSize(Size size);
	Size getSize();
	
	virtual void draw();
private:
	Size size;		// (length, width, height)
};

#endif // !CUBOID_H

