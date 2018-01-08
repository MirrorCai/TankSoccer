#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, bool axis_direction)
{
	this->axis_direction;
	this->radius = radius;
	this->height = height;
}
Cylinder::Cylinder(Vector bottomCenter, GLfloat radius, GLfloat height,
	bool axis_direction)
	:Geometry(bottomCenter)
{
	this->axis_direction;
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
	GLfloat refCylinder[3] = { 1.0f,0.0f,1.0f };			//桌腿4反射参数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, refCylinder);//设置桌面漫反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, refCylinder);//设置桌面镜面反射
	/** LIU: gluCylinder is different from glSolid* functions. It keeps the origin
	*	as the center of its bottom circle, rather than the center of the shape.
	*	Thus, its transformation matrices are slightly different from those for 
	*	balls.
	*/
	glTranslatef(bottomCenter.x, bottomCenter.y, bottomCenter.z);
	glRotatef(angle, 0, 0, 1);
	if (axis_direction == VERTICAL)
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
