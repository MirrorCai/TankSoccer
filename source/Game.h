#ifndef GAME_H
#define GAME_H

#include "Basic.h"
#include "Ball.h"
#include "Tank.h"
#include "Pitch.h"
#include "Camera.h"
#include "Surrounding.h"

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
	void capture();
	void changeScene();

	Camera camera;
	GLfloat posLight[4] = { 5.0f,-14.0f,.0f,0.0f };	//环境光位置
	bool bEnvir;
	bool bSpot;
	bool bChange;
	bool outsidePause;
	bool goalPause;
	bool userPause;
	
private:
	Pitch pitch;
	Ball ball;
	Tank tank1;
	Tank tank2;
	FollowItem followItem;
	unsigned int score_p1, score_p2;
	int tCount;
	int tFlag;

	const int pausePeriod = 1500;	// 1.5s

	void resetAllObjects();

	void printInfo();

	const GLfloat safeMargin = 15;
	
	// Detect collision and change their motion
	static void tankBallCollide(Tank& tank, Ball& ball);
	static void tanksCollide(Tank& tank1, Tank& tank2);

	void checkBounds(Tank& tank);
	void checkBounds(Ball& ball);

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
	
	static void setTankVertices(GLfloat x, GLfloat y, GLfloat length,
		GLfloat width, GLfloat angle, GLfloat vertices[4][2]);

	static GLfloat** getVertices(GLfloat x, GLfloat y, GLfloat length, GLfloat width,
		GLfloat angle);
	static void releaseVertices(GLfloat** vertices);

	static GLfloat max_of_4(GLfloat op1, GLfloat op2, GLfloat op3, GLfloat op4);
	static GLfloat min_of_4(GLfloat op1, GLfloat op2, GLfloat op3, GLfloat op4);
};

#endif // !GAME_H

