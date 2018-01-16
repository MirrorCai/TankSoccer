#include "Camera.h"

const Vector Camera::INITIAL_VECTOR(0, -70.0f, 40.0f);

Camera::Camera()
	:focus(0, 0, 0), fixedEye(INITIAL_VECTOR),
	freeEye(INITIAL_VECTOR), firstPersonPersDist(30.0f),
	playerEye(-firstPersonPersDist, 0, firstPersonPersHeight)
{
	mode = FASTENED;
}
void Camera::addEye(int xyz) {
	switch (xyz)
	{
	case 0: 
		freeEye.x += 0.1f;
		focus.x += 0.1f;
		break;
	case 1:
		freeEye.y += 0.1f;
		focus.y += 0.1f;
		break;
	case 2:
		freeEye.z += 0.1f;
		focus.z += 0.1f;
		break;
	default:
		break;
	}
}
void Camera::subEye(int xyz) {
	switch (xyz)
	{
	case 0:
		freeEye.x -= 0.1f;
		focus.x -= 0.1f;
		break;
	case 1:
		freeEye.y -= 0.1f;
		focus.y -= 0.1f;
		break;
	case 2:
		freeEye.z -= 0.1f;
		focus.z -= 0.1f;
		break;
	default:
		break;
	}
}
Point Camera::getEye()
{
	switch (mode)
	{
	case FASTENED:
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
	{
		GLfloat distance = (freeEye - focus).getLength();
		if (distance < 12 && length > 0 || distance > 80 && length < 0)
			return;
		else
			freeEye -= (freeEye - focus).getIdentityVector() * length;
	}
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
	case FASTENED:
		mode = FREE;
		break;
	case FREE:
		mode = PLAYER;
		freeEye = fixedEye;	// This is a little bit controversial
		break;
	case PLAYER:
		mode = FASTENED;
		break;
	default:
		mode = FASTENED;
		break;
	}
}

void Camera::follow(Point objectPos)
{
	static const Vector fixedEyeDistance(INITIAL_VECTOR);
	static const GLfloat
		bound_x = 0.45 * Pitch::LENGTH, bound_y = 0.25 * Pitch::WIDTH;
	
	Vector freeEyeDistance(freeEye - focus);
	focus = objectPos;

	if (focus.x > bound_x) focus.x = bound_x;
	if (focus.x < -bound_x) focus.x = -bound_x;
	if (focus.y > bound_y) focus.y = bound_y;
	if (focus.y < -bound_y) focus.y = -bound_y;

	if (mode == FASTENED)
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