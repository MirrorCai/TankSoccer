#ifndef CYLINDER_H
#define CYLINDER_H

#include "Geometry.h"

class Cylinder: public Geometry
{
public:
	Cylinder(GLfloat radius, GLfloat height, bool axis_direction);
	Cylinder(Vector bottomCenter, GLfloat radius, GLfloat height, 
		bool axis_direction);
	void setRadius(GLfloat radius);
	void setHeight(GLfloat radius);
	virtual void draw();

	static const bool VERTICAL = true;
	static const bool HORIZONTAL = false;

private:
	bool axis_direction;
	GLfloat radius;
	GLfloat height;
};

#endif // !CYLINDER_H

