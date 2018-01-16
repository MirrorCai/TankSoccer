#ifndef BALL_H
#define BALL_H

#include "Sphere.h"
#include "Entity.h"
#include "obj.h"

class Ball:  public Entity
{
public:
	Ball();
	GLfloat getRadius();
	// Override
	void render();
private:
	static const unsigned int BALL_MASS;
	static const GLfloat BALL_DEFAULT_FACTOR;
	static const GLfloat BALL_RADIUS;
	obj apperance;
};
#endif