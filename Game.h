#ifndef GAME_H
#define GAME_H

#include "Basic.h"
#include "Ball.h"
#include "Tank.h"
#include "Pitch.h"

class Game
{
public:
	Game();
	void keyboard(unsigned char key, int x, int y);
	void display();
	void gotoNextFrame();
	void setCamera(Vector &eye, Vector &center);

private:
	void orthoCollide();
	Pitch pitch;
	Ball ball;
	Tank tank;

//private:
	const GLfloat safeMargin = 15;
	
	// All parameters are their value in world coordinates.
	// Rectangle vs Rectangle
	static Vector collision2D(
		GLfloat x1, GLfloat y1, GLfloat l1, GLfloat w1, GLfloat a1,
		GLfloat x2, GLfloat y2, GLfloat l2, GLfloat w2, GLfloat a2);
	
	// Fundamental, no-orientation function
	// Rectangle vs. Circle
	static Vector collision2D(GLfloat x1, GLfloat y1, GLfloat length, GLfloat width,
		GLfloat angle, GLfloat x2, GLfloat y2, GLfloat radius);
	
	// Circle vs. Circle
	static Vector collision2D(GLfloat x1, GLfloat y1, GLfloat r1,
		GLfloat x2, GLfloat y2, GLfloat r2);
	
	static GLfloat** getVertices(GLfloat x, GLfloat y, GLfloat length, GLfloat width,
		GLfloat angle);
	static void releaseVertices(GLfloat** vertices);
};

#endif // !GAME_H

