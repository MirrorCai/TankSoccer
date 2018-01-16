#include "Goal.h"

const GLfloat Goal::goalWidth = 5.0f;

Goal::Goal(bool isLeft)
	:post1(0.5f, 8.0f, 0.0f, true), post2(0.5f, 8.0f, 0.0f, true), bar(0.5f, 10.0f, 90.0f, false)
{
	this->isLeft = isLeft;
	GLfloat x = 67.0f;
	if (isLeft)
		x = -x;
	post1.setBottomCenter(Point(x, goalWidth, 0));
	post2.setBottomCenter(Point(x, -goalWidth, 0));
	//bar.setBottomCenter(Point(x, 0, 4));
	bar.setBottomCenter(Point(x, -5.0f, 8.0f));
}

void Goal::draw()
{
	post1.draw();
	post2.draw();
	bar.draw();
}