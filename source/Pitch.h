#ifndef PITCH_H
#define PITCH_H

#include "TextureManager.h"
#include "Goal.h"

class Pitch
{
public:
	static const unsigned int LENGTH = 150;
	static const unsigned int WIDTH = 75;
//	GLfloat refPitch[3] = { 0.0f,1.0f,0.0f };

	Pitch();

	void changeTexture();
	
	void draw();

private:
	int texture;
	Goal leftGoal;
	Goal rightGoal;
	void drawPitch();
	void drawBoard();
};
#endif // !PITCH_H

