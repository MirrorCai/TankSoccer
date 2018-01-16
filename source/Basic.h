#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <gl\glut.h>

using namespace std;

class Vector
{
public:
	//Vector();
	Vector(GLfloat x, GLfloat y, GLfloat z);
	
	// overload operations
	Vector& operator+= (Vector op);
	Vector& operator-= (Vector op);
	Vector operator- ();
	bool operator== (Vector op);
	bool operator!= (Vector op);

	Vector abs();
	Vector& rotate_z(GLfloat angle);

	GLfloat getSquareLength();	// avoid sqrt
	GLfloat getLength();
	Vector getIdentityVector();
	GLfloat x, y, z;
};
typedef Vector Point;
typedef Vector Size;

/*class Color
{
public:
	Color();
	Color(GLfloat r, GLfloat g, GLfloat ball);

	GLfloat r, g, ball;
};*/

Vector operator+ (const Vector& op1, const Vector& op2);
Vector operator- (const Vector& op1, const Vector& op2);
GLfloat operator* (const Vector& op1, const Vector& op2);
Vector operator* (GLfloat op1, const Vector& op2);
Vector operator* (const Vector& op1, GLfloat op2);
ostream& operator<<(ostream& out, const Vector& v);

#endif

