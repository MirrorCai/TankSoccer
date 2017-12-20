#include "Geometry.h"

const Point Geometry::CENTER(0, 0, 0);

Geometry::Geometry()
	:bottomCenter(CENTER)
{
	angle = 0.0f;
}

Geometry::Geometry(Point bottomCenter)
	:bottomCenter(bottomCenter)
{
	angle = 0.0f;
}

void Geometry::setBottomCenter(Point bottomCenter)
{
	if (bottomCenter.z < 0)
		bottomCenter.z = 0;
	this->bottomCenter = bottomCenter;
}

void Geometry::setAngle(GLfloat angle)
{
	this->angle = normalize(angle);
}

GLfloat Geometry::normalize(GLfloat angle)
{
	// ensure 0 <= angle < 360
	if (angle >= 360)
		return angle - 360 * int(angle / 360);
	else if (angle < 0)
		return angle - 360 * int(angle / 360) + 360;
	else
		return angle;	
}

GLfloat Geometry::getAngle()
{
	return angle;
}
Point Geometry::getBottomCenter()
{
	return bottomCenter;
}
void Geometry::addAngle(GLfloat angle)
{
	this->angle = normalize(this->angle + angle);
}
