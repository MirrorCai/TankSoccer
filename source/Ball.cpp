#include "Ball.h"

const unsigned int Ball::BALL_MASS = 5;
const GLfloat Ball::BALL_DEFAULT_FACTOR = 0.0001f;

Ball::Ball()
	:Entity(BALL_MASS)
{
	setDecelerationFactor(BALL_DEFAULT_FACTOR);
	
	objects.push_back(new Sphere());
	// the center of sphere is the center of this entity
	displacements.push_back(Vector(0, 0, 0));

	followCenter();
}

GLfloat Ball::getRadius()
{
	Sphere* sphere = dynamic_cast<Sphere*>(objects[0]);
	if (sphere == NULL)
		throw new exception("Internal Error: Tank class inconsistent types");
	return sphere->getRadius();
}
