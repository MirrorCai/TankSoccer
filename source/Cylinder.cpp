#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLfloat angle, bool isVertical)
{
	this->angle = angle;
	this->isVertical = isVertical;
	this->radius = radius;
	this->height = height;
}
Cylinder::Cylinder(Point bottomCenter, GLfloat radius, GLfloat angle, GLfloat height,
	bool isVertical)
	:Geometry(bottomCenter)
{
	this->angle = angle;
	this->isVertical = isVertical;
	this->radius = radius;
	this->height = height;
}
void Cylinder::setRadius(GLfloat radius)
{
	this->radius = radius;
}
void Cylinder::setHeight(GLfloat radius)
{
	this->height = height;
}

void Cylinder::draw()
{
	glPushMatrix();
	//glColor3f(1.0, 0, 0);
	GLfloat cycinderDiffuse[3] = { 0.5f, 0.0f, 0.5f };
	GLfloat cylinderSpecular[3] = { 1.0f, 1.0f, 1.0f };	// Make it metal-like
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cycinderDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cylinderSpecular);
	/** LIU: gluCylinder is different from glSolid* functions. It keeps the origin
	*	as the center of its bottom circle, rather than the center of the shape.
	*	Thus, its transformation matrices are slightly different from those for 
	*	balls.
	*/
	glTranslatef(bottomCenter.x, bottomCenter.y, bottomCenter.z);
	glRotatef(angle, 0, 0, 1);
	if (isVertical == true)
	{
		gluCylinder(gluNewQuadric(), radius, radius, height, 10, 10);
	}
	else
	{
		glRotatef(90, 0, 1, 0);
		gluCylinder(gluNewQuadric(), radius, radius, height, 10, 10);
	}
	glPopMatrix();
}
