#include "Cuboid.h"
#include "TextureManager.h"

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

	GLfloat refCuboid[3] = { 0.4f,0.2f ,0.1f };			// brown
	glMaterialfv(GL_FRONT, GL_DIFFUSE, refCuboid);
	glMaterialfv(GL_FRONT, GL_SPECULAR, refCuboid);
	glColor3f(0.4f, 0.2f, 0.1f);	// brown
	glTranslatef(bottomCenter.x, bottomCenter.y, bottomCenter.z + size.z / 2);
	glScalef(size.x, size.y, size.z);
	glRotatef(angle, 0, 0, 1);
	TextureManager::drawCube(1);

	glPopMatrix();
}
