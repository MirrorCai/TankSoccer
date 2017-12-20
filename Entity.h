#ifndef ENTITY_H
#define ENTITY_H

#include "Basic.h"
#include "Geometry.h"

class Entity
{
public:
	//Entity();
	Entity(unsigned int mass, Point center);
	Entity(unsigned int mass);
	~Entity();

	void render();
	void update();
	void turn(GLfloat angle);
	
	GLfloat getAngle();	// return the angle of its base object
	Point getCenter();
	Vector getVelocity();
	void setAngle(GLfloat angle);	
	void setVelocity(Vector velocity);	// vector
	void setSpeed(GLfloat speed);		// scalar
	void setCenter(Point center);
	void setMass(unsigned int mass);
	void setDecelerationFactor(GLfloat decelerationFactor);

	bool isMoving();

	// Mass for fixed object
	static const unsigned int INFINITE_MASS = 4294967295;
	static const unsigned int DEFAULT_MASS = 5;
	static const Point CENTER;
	static const Vector MOTIONLESS;
	static const GLfloat highestSpeed;	// set to avoid infinite speed as a bug
	
protected:
	void updateAcceleration();
	bool move();	// return false if the object stayed still
	// TODO: add overload for different type of movement
	void followCenter();

	unsigned int mass;
	Point center;
	Vector velocity;
	Vector acceleration;
	GLfloat scalarAcceleration;
	GLfloat decelerationFactor;

	vector<Geometry *> objects;
	vector<Vector> displacements;
};

#endif

