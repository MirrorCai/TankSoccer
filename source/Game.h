#ifndef GAME_H
#define GAME_H

#include "Basic.h"
#include "Ball.h"
#include "Tank.h"
#include "Pitch.h"
#include "Camera.h"

#define BMP_Length 54
#define WinWidth  600  
#define WinHeight 350  

enum FollowItem {BALL, TANK};

class Game
{
public:
	Game();
	void keyboard(unsigned char key, int x, int y);
	void display();
	void gotoNextFrame();
	void updateCamera();
	Camera camera;
	GLfloat posLight[4] = { 5.0f,-14.0f,.0f,0.0f };	//环境光位置
	bool bEnvir;
	bool bSpot;
	bool bChange;
	void capture();
	void changeScene();

private:
	void orthoCollide(Point c1, Point c2,int TankNum);
	void TankCollision(Point c1, Point c2);
	Pitch pitch;
	Ball ball;
	Tank tank;
	Tank tank2;
	FollowItem followItem;
	int tCount;
	int tFlag;

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

