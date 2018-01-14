#ifndef GOAL_H
#define GOAL_H

#include "Cylinder.h"

class Goal
{
public:
	Goal(bool isLeft);
	void draw();
	static const GLfloat goalWidth;
private:
	Cylinder post1;
	Cylinder post2;
	Cylinder bar;
	bool isLeft;
};

#endif // !GOAL_H

