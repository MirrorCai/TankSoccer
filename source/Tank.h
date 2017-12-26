#ifndef TANK_H
#define TANK_H

#include "Cuboid.h"
#include "Entity.h"
#include "Cylinder.h"

class Tank: public Entity
{
public:
	Tank(Point center);
	void turnTurret(GLfloat angle);
	Size getBlockSize();

private:
	static const unsigned int TANK_MASS;
	static const GLfloat TANK_DEFAULT_FACTOR;
	static const GLfloat FIELD_ANGLE;
};

#endif // !TANK_H