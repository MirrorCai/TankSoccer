#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry
{
public:
	Sphere();
	void setRadius(GLfloat radius);
	GLfloat getRadius();
	virtual void draw();
	
private:
	static const GLfloat DEFAULT_RADIUS;

	GLfloat radius;	
};


#endif
