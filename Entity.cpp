#include "Entity.h"

const Vector Entity::MOTIONLESS(0, 0, 0);
const Point Entity::CENTER(0, 0, 0);
const GLfloat Entity::highestSpeed = 0.04;

Entity::Entity(unsigned int mass, Point center)
	:center(center), velocity(MOTIONLESS), acceleration(MOTIONLESS), 
	mass(mass), decelerationFactor(0.0)
{
	;
}

Entity::Entity(unsigned int mass)
	:center(CENTER), velocity(MOTIONLESS), acceleration(MOTIONLESS),
	mass(mass), decelerationFactor(0.0)
{
	;
}

Entity::~Entity()
{
	if (objects.size() == 0)
		return;
	// Caution: Do not use unsigned type here
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		delete objects[i];
		objects.pop_back();
		displacements.pop_back();
	}
}

GLfloat Entity::getAngle()
{
	if (objects.size() == 0)
		return 0;
	else
		return objects[0]->getAngle();
}
Point Entity::getCenter()
{
	return center;
}

Vector Entity::getVelocity()
{
	return velocity;
}

void Entity::setCenter(Point center)
{
	this->center = center;
	followCenter();
}
void Entity::setVelocity(Vector velocity)
{
	this->velocity = velocity;
	updateAcceleration();
}
void Entity::setSpeed(GLfloat speed)
{
	GLfloat angle = getAngle() / 180 * 3.1415926;	// degree --> rad
	this->velocity = Vector(speed * cos(angle), speed * sin(angle), 0);
	updateAcceleration();
}
void Entity::setMass(unsigned int mass)
{
	this->mass = mass;
}
void Entity::setDecelerationFactor(GLfloat decelerationFactor)
{
	this->decelerationFactor = decelerationFactor;
}
bool Entity::move()
{
	if (velocity == Vector(0, 0, 0))
		return false;
	
	center += velocity;
	if (velocity.getLength() <= scalarAcceleration)
		setVelocity(Vector(0, 0, 0));	// stop
	else
		velocity += acceleration;
	return true;
}
bool Entity::isMoving()
{
	return velocity.x != 0 || velocity.y != 0 || velocity.z != 0;
}
void Entity::update()
{
	if (move())
		followCenter();
}
void Entity::turn(GLfloat angle)
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->addAngle(angle);
	setVelocity(this->velocity.rotate_z(angle));
}

void Entity::setAngle(GLfloat angle)
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->setAngle(angle);
	setVelocity(this->velocity.rotate_z(angle));
}
void Entity::followCenter()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->setBottomCenter(center + displacements[i]);
}
void Entity::render()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->draw();
}
// should be called whenver the speed changes
void Entity::updateAcceleration()
{
	// This is correct even if velocity = 0;
	acceleration = -velocity.getIdentityVector() * decelerationFactor;
	scalarAcceleration = acceleration.getLength();
}