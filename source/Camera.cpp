#include "Camera.h"

Camera::Camera()
	:focus(0, 0, 0), fixedEye(0, -GLfloat(Pitch::WIDTH) / 2 - 10, 40), 
	freeEye(fixedEye), firstPersonPersDist(30.0f),
	playerEye(-firstPersonPersDist, 0, firstPersonPersHeight)
{
	mode = FIXED;
}

Point Camera::getEye()
{
	switch (mode)
	{
	case FIXED:
		return fixedEye;
	case FREE:
		return freeEye;
	case PLAYER:
		return playerEye;
	}
	return fixedEye;
}

Point Camera::getFocus()
{
	return focus;
}

CameraMode Camera::getMode()
{
	return mode;
}

void Camera::moveFreeEye(Vector movement)
{
	freeEye += movement;
}

void Camera::zoom(GLfloat length)
{
	if (mode == PLAYER)
		firstPersonPersDist -= length;
	else
		freeEye -= (freeEye - focus).getIdentityVector() * length;
}

void Camera::rotateFreeEye(GLfloat angle)
{
	if (mode != PLAYER)
		freeEye = (freeEye - focus).rotate_z(angle) + focus;
}

void Camera::setZoomedEye(Point eye)
{
	freeEye = eye;
}

void Camera::setFixedEye(Point eye)
{
	fixedEye = eye;
}

void Camera::setFocus(Point focus)
{
	this->focus = focus;
}

void Camera::changeMode()
{
	switch (mode)
	{
	case FIXED:
		mode = FREE;
		break;
	case FREE:
		mode = PLAYER;
		freeEye = fixedEye;	// This is a little bit controversial
		break;
	case PLAYER:
		mode = FIXED;
		break;
	default:
		mode = FIXED;
		break;
	}
}

void Camera::follow(Point objectPos)
{
	static const Vector fixedEyeDistance(0, -GLfloat(Pitch::WIDTH) / 2 - 10, 40);
	static const GLfloat
		bound_x = 0.45 * Pitch::LENGTH, bound_y = 0.25 * Pitch::WIDTH;
	
	Vector freeEyeDistance(freeEye - focus);
	focus = objectPos;

	if (focus.x > bound_x) focus.x = bound_x;
	if (focus.x < -bound_x) focus.x = -bound_x;
	if (focus.y > bound_y) focus.y = bound_y;
	if (focus.y < -bound_y) focus.y = -bound_y;

	if (mode == FIXED)
		fixedEye = fixedEyeDistance + focus;
	if (mode == FREE)
		freeEye = freeEyeDistance + focus;
}

void Camera::follow(Point objectPos, GLfloat angle)
{
	angle = angle * 3.1415926 / 180;
	focus = objectPos;
	playerEye = Vector(-firstPersonPersDist * cos(angle), 
						-firstPersonPersDist * sin(angle), 
						firstPersonPersHeight) 
				+ focus;
}