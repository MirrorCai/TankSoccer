#ifndef SURROUNDING_H
#define SURROUNDING_H

#include "Basic.h"
#include "TextureManager.h"

class Surrounding
{
public:
	static GLfloat DISTANCE;
	static GLfloat SIZE;
	static void drawAt(Point center);
private:
	
	//void drawSurface(GLfloat offsetX, GLfloat offsetY, GLfloat offsetZ);
};

#endif // SURROUNDING_H

