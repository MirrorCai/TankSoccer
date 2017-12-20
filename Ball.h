#ifndef BALL_H
#define BALL_H

#include "Sphere.h"
#include "Entity.h"

class Ball:  public Entity
{
public:
	Ball();
	GLfloat getRadius();

private:
	static const unsigned int BALL_MASS;
	static const GLfloat BALL_DEFAULT_FACTOR;
};
#endif