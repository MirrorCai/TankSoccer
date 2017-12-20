#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Basic.h"

class Geometry
{
public:
	Geometry();
	Geometry(Point bottomCenter);
	void setBottomCenter(Point bottomCenter);
	Point getBottomCenter();
	void setAngle(GLfloat angle);
	GLfloat getAngle();
	void addAngle(GLfloat angle);
	virtual void draw() = 0;
	static GLfloat normalize(GLfloat angle);
protected:
	Point bottomCenter;	// position of bottom center
	static const Point CENTER;
	GLfloat angle;
	//void setColor(Color color);
	//Color color;
};

#endif // !GEOMETRY_H
