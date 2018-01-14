#ifndef CYLINDER_H
#define CYLINDER_H

#include "Geometry.h"

class Cylinder: public Geometry
{
public:
	Cylinder(GLfloat radius, GLfloat height, GLfloat angle, bool isVertical);
	Cylinder(Point bottomCenter, GLfloat radius, GLfloat height, GLfloat angle,
		bool axis_direction);
	void setRadius(GLfloat radius);
	void setHeight(GLfloat radius);
	virtual void draw();

private:
	bool isVertical;
	GLfloat radius;
	GLfloat height;
};

#endif // !CYLINDER_H

