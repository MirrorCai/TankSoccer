#ifndef CAMERA_H
#define CAMERA_H

#include "Basic.h"
#include "Pitch.h"

enum CameraMode { FIXED, FREE, PLAYER };

class Camera
{
public:
	friend class Game;
	Camera();
	void addEye(int xyz);
	void subEye(int xyz);
	Point getEye();
	Point getFocus();
	CameraMode getMode();
	void zoom(GLfloat length);
	void moveFreeEye(Vector movement);
	void rotateFreeEye(GLfloat angle);
	void changeMode();
protected:
	void setZoomedEye(Point eye);
	void setFixedEye(Point eye);
	void setFocus(Point focus);
	void follow(Point objectPos);
	void follow(Point objectPos, GLfloat angle);

	Point fixedEye;
	Point freeEye;
	Point playerEye;
	Point focus;
	CameraMode mode;

	GLfloat firstPersonPersDist;
	const GLfloat firstPersonPersHeight = 30.0f;

};

#endif // !CAMERA_H

