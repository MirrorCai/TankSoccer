#include "Sphere.h"

const GLfloat Sphere::DEFAULT_RADIUS = 1.5f;

Sphere::Sphere()
{
	radius = DEFAULT_RADIUS;
}
Sphere::Sphere(GLfloat radius)
{
	this->radius = radius;
}
void Sphere::setRadius(GLfloat radius)
{
	this->radius = radius;
}
GLfloat Sphere::getRadius()
{
	return radius;
}
/*void Sphere::setColor(Color color)
{
this->color = color;
}*/

void Sphere::draw()
{
	glPushMatrix();
	GLfloat refSphere[3] = { 1.0f,0.0f,0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, refSphere);
	glMaterialfv(GL_FRONT, GL_SPECULAR, refSphere);

	glTranslatef(bottomCenter.x, bottomCenter.y, bottomCenter.z + radius);
	//glColor3f(color.x, color.y, color.z);	// white
	//glColor3f(0.8, 0.8, 0.8);	// Light Gray
	glRotatef(angle, 0, 0, 1);
	glutSolidSphere(radius, 10, 10);

	glPopMatrix();
}
