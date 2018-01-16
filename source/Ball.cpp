#include "Ball.h"

const unsigned int Ball::BALL_MASS = 5;
const GLfloat Ball::BALL_DEFAULT_FACTOR = 0.0001f;
const GLfloat Ball::BALL_RADIUS = 1.5f;

Ball::Ball()
	:Entity(BALL_MASS)
{
	setDecelerationFactor(BALL_DEFAULT_FACTOR);
	
	// Use a sphere as its physical model
	objects.push_back(new Sphere(BALL_RADIUS));
	// the center of sphere is the center of this entity
	displacements.push_back(Vector(0, 0, 0));

	apperance.load("Football.obj", "Football.mtl");

	followCenter();
}

GLfloat Ball::getRadius()
{
	Sphere* sphere = dynamic_cast<Sphere*>(objects[0]);
	if (sphere == NULL)
		throw new exception("Internal Error: Tank class inconsistent types");
	return sphere->getRadius();
}

void Ball::render()
{
	const Vector offset(-3.48, -36.1, 33.8);
	static GLfloat y_angle, x_angle;
	y_angle = 180.0f * center.x / (2.0f * BALL_RADIUS);
	x_angle = 180.0f * center.y / (2.0f * BALL_RADIUS);
	
	glPushMatrix();
	
	glTranslatef(center.x, center.y, center.z);
	glScalef(0.048f, 0.048f, 0.048f);
	glTranslatef(offset.x, offset.y, offset.z + BALL_RADIUS);
	
	// Rolling
	glRotatef(y_angle, 0, 1, 0);
	glRotatef(x_angle, 1, 0, 0);
	
	// Draw obj
	apperance.draw();

	glPopMatrix();
	
	// Older verision
	//Entity::render();
}
