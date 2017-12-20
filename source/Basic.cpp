#include "Basic.h"

Vector::Vector(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector& Vector::operator+= (Vector op)
{
	this->x += op.x;
	this->y += op.y;
	this->z += op.z;
	return *this;
}
Vector& Vector::operator-= (Vector op)
{
	this->x -= op.x;
	this->y -= op.y;
	this->z -= op.z;
	return *this;
}
Vector Vector::operator- ()
{
	return Vector(-x, -y, -z);
}
bool Vector::operator== (Vector op)
{
	return x == op.x && y == op.y && z == op.z;
}
bool Vector::operator!= (Vector op)
{
	return x != op.x || y != op.y || z != op.z;
}
Vector Vector::abs()
{
	return Vector(x >= 0 ? x : -x,
		y >= 0 ? y : -y,
		z >= 0 ? z : -z);
}
Vector& Vector::rotate_z(GLfloat angle)
{
	angle = angle / 180 * 3.1415926;	// degree --> rad
	GLfloat cos_angle = cos(angle);
	GLfloat sin_angle = sin(angle);
	GLfloat tempX = cos_angle * x - sin_angle * y;
	GLfloat tempY = sin_angle * x + cos_angle * y;
	x = tempX;
	y = tempY;
	return *this;
}

GLfloat Vector::getLength()
{
	return sqrt(x * x + y * y + z * z);
}
Vector Vector::getIdentityVector()
{
	GLfloat length = getLength();
	if (length != 0)
		return Vector(x / length, y / length, z / length);
	else
		return Vector(0, 0, 0);
}

Vector operator+ (const Vector& op1, const Vector& op2)
{
	return Vector(op1.x + op2.x, op1.y + op2.y, op1.z + op2.z);
}
Vector operator- (const Vector& op1, const Vector& op2)
{
	return Vector(op1.x - op2.x, op1.y - op2.y, op1.z - op2.z);
}
GLfloat operator* (const Vector& op1, const Vector& op2)	// dot product
{
	return op1.x * op2.x + op1.y + op2.y + op1.z * op2.z;
}
Vector operator* (GLfloat op1, const Vector& op2)
{
	return Vector(op1 * op2.x, op1 * op2.y, op1 * op2.z);
}
Vector operator* (const Vector& op1, GLfloat op2)
{
	return op2 * op1;
}
ostream& operator<<(ostream& out, const Vector& v)
{
	out << "[" << v.x << "," << v.y << "," << v.z << "]";
	return out;
}
