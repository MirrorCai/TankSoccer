#include "Tank.h"
#include "Game.h"

const unsigned int Tank::TANK_MASS = 8000;	// for 800kg
const GLfloat Tank::TANK_DEFAULT_FACTOR = 0.1f;
const GLfloat Tank::FIELD_ANGLE = 80.0f;

Tank::Tank(Point center)
	:Entity(TANK_MASS, center)
{
	setDecelerationFactor(TANK_DEFAULT_FACTOR / 10);

	// base block of the tank1
	objects.push_back(new Cuboid(Size(9, 5, 3)));
	displacements.push_back(Vector(0, 0, 0));
	
	// turret
	objects.push_back(new Cuboid(Size(5, 4, 2)));
	// bottom.z = block height
	displacements.push_back(Vector(0, 0, 3));
	
	// gun
	objects.push_back(new Cylinder(0.5, 6, 0, false));
	// bottom.z = block height + turret height
	displacements.push_back(Vector(0, 0, 5));

	followCenter();
}

Size Tank::getBlockSize()
{
	Cuboid* base = dynamic_cast<Cuboid*>(objects[0]);
	if (base == NULL)
		throw new exception("Internal Error: Tank class inconsistent types");
	return base->getSize();
}

void Tank::turnTurret(GLfloat angle)
{
	// do bound check

	// normalized "-field_angle"
	const GLfloat MINUS_FIELD_ANGLE = 360 - FIELD_ANGLE;
	Geometry *tank = objects[0], *turret = objects[1], *gun = objects[2];
	GLfloat includedAngle = 
		Geometry::normalize(turret->getAngle() - tank->getAngle());
	
	if (includedAngle <= FIELD_ANGLE && includedAngle + angle >= FIELD_ANGLE)
	{
		turret->setAngle(tank->getAngle() + FIELD_ANGLE);
		gun->setAngle(tank->getAngle() + FIELD_ANGLE);
	}
	else if (includedAngle >= MINUS_FIELD_ANGLE && 
		includedAngle + angle <= MINUS_FIELD_ANGLE)
	{
		turret->setAngle(tank->getAngle() + MINUS_FIELD_ANGLE);
		gun->setAngle(tank->getAngle() + MINUS_FIELD_ANGLE);
	}
	else
	{
		turret->addAngle(angle);
		gun->addAngle(angle);
	}
}