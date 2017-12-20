#include "Cuboid.h"

Cuboid::Cuboid(GLfloat length, GLfloat width, GLfloat height)
	:size(length, width, height)
{
	;
}

Cuboid::Cuboid(Size size)
	:size(size)
{
	;
}

Cuboid::Cuboid(Vector bottomCenter, Size size)
	:Geometry(bottomCenter), size(size)
{
	;
}

void Cuboid::setSize(Size size)
{
	this->size = size;
}
Size Cuboid::getSize()
{
	return size;
}

void Cuboid::draw()
{
	glPushMatrix();
	
	glColor3f(0.4, 0.2, 0.1);	// brown
	glTranslatef(bottomCenter.x, bottomCenter.y, bottomCenter.z + size.z / 2);
	glScalef(size.x, size.y, size.z);
	glRotatef(angle, 0, 0, 1);
	glutSolidCube(1);

	glPopMatrix();
}
