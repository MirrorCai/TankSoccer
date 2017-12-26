#include "Game.h"
Game::Game()
	:tank(Point(-40, 0, 0))
{
	followItem = BALL;
}
void Game::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: {exit(0); break; }	// ESC
	//case ' ': {ball.setVelocity(Vector(0.1, 0, 0)); break; }
	case 'w': {tank.setSpeed(0.02); break; }
	case 's': {tank.setSpeed(-0.01); break; }
	case 'a': {tank.turn(2.5); break; }
	case 'd': {tank.turn(-2.5); break; }
	case 'q': {tank.turnTurret(2.5); break; }
	case 'e': {tank.turnTurret(-2.5); break; }

	case 'i': {camera.zoom(1.0); break; }
	case 'k': {camera.zoom(-1.0); break; }
	case 'j': {if (followItem == BALL) camera.rotateFreeEye(2.5); break; }
	case 'l': {if (followItem == BALL) camera.rotateFreeEye(-2.5); break; }
	case ' ': 
		camera.changeMode();
		if (camera.getMode() == PLAYER)
			followItem = TANK;
		else
			followItem = BALL;
		break;
	}
}
void Game::updateCamera()
{
	if (followItem == BALL)
		camera.follow(ball.getCenter());
	else
		camera.follow(tank.getCenter(), tank.getAngle());
}
void Game::display()
{
	pitch.draw();
	ball.render();
	tank.render();
}
void Game::gotoNextFrame()
{
	orthoCollide();
	ball.update();
	tank.update();
}
void Game::orthoCollide()
{
	// Now only consider one tank and one ball
	Point c1 = tank.getCenter(), c2 = ball.getCenter();
	Size blockSize = tank.getBlockSize();
	Vector force_ball_to_tank = collision2D(c1.x, c1.y, blockSize.x, blockSize.y,
		tank.getAngle(), c2.x, c2.y, ball.getRadius());
	if (force_ball_to_tank != Vector(0, 0, 0))	// Collided
	{
		// Assume the speed of tank will not be changed after a collision
		// formula: v_n_ball' = 2 * v_n_tank - v_n_ball
		
		// Resolve return value
		GLfloat depth = force_ball_to_tank.z;
		force_ball_to_tank.z = 0;

		// f_*_i: direction vector accepted by *
		Vector f_tank_i = force_ball_to_tank.getIdentityVector();
		Vector f_ball_i = -f_tank_i;

		Vector v_ball = ball.getVelocity();
		Vector v_n_ball = (v_ball * f_tank_i) * f_tank_i;	// dotted product first and
		Vector v_t_ball = v_ball - v_n_ball;				// scalar product second
		
		Vector v_tank = tank.getVelocity();
		Vector v_n_tank = (v_tank * f_ball_i) * f_ball_i;

		// First: keep objects separated
		// TODO: if ball will not go outside; else tank roll back
		ball.setCenter(ball.getCenter() + depth * f_ball_i + 
			v_n_tank - v_n_ball);	// add relative speed

		v_n_ball = 2 * v_n_tank - v_n_ball;
		v_ball = v_n_ball + v_t_ball;
		ball.setVelocity(v_ball);
	}
}
/** Family of collision detection functions. For simplicity here we use a
*	centroid model, thus only the direction of elastic force matters. All
*	functions of this family will return the direction vector of elastic force
*	against the first object. Also, the speed of object should not be too fast,
*	or there're possibilities that the answer doesn't make any sense.
*/

/** Rectangle vs Rectangle
*	Parameters: vertices of two rectangle, adjacent vertices should also be
*	adjacent in parameters.
*	Principle from: High school mathematics. If two rectangles intersect, then
*	one of their vertices must be in the other rectangles. In other word, if a
*	vertex is included by the opposite angles of the other rectangles, then two
*	rectangle intersects. This could be check quickly using the property of 
*	dotted product and the right angle. (< 90 ~ > 0; == 90 ~ == 0; > 90 ~ < 0)
*/
Vector Game::collision2D(
	GLfloat x1, GLfloat y1, GLfloat l1, GLfloat w1, GLfloat a1,
	GLfloat x2, GLfloat y2, GLfloat l2, GLfloat w2, GLfloat a2)
{
	GLfloat** vertices1 = getVertices(x1, y1, l1, w1, a1);
	GLfloat** vertices2 = getVertices(x2, y2, l2, w2, a2);
	int v1_x = vertices1[1][0] - vertices1[0][0], v1_y = vertices1[1][1] - vertices1[0][1];
	int v2_x = vertices1[3][0] - vertices1[0][0], v2_y = vertices1[3][1] - vertices1[0][1];
	int v3_x = vertices1[1][0] - vertices1[2][0], v3_y = vertices1[1][1] - vertices1[2][1];
	int v4_x = vertices1[3][0] - vertices1[2][0], v4_y = vertices1[3][1] - vertices1[2][1];
	
	for (int i = 0; i < 4; i++)
	{
		int v_x = vertices1[i][0] - vertices1[i][0];
		int v_y = vertices1[i][1] - vertices1[i][1];
		if (v_x * v1_x + v_y * v1_y >= 0 && v_x * v2_x + v_y * v2_y >= 0 &&	// angle[0] includes!
			v_x * v3_x + v_y * v3_y >= 0 && v_x * v4_x + v_y * v4_y >= 0)	// angle[2] includes!
		{
			releaseVertices(vertices1);
			releaseVertices(vertices2);
			return Vector(v1_x - v2_x, v1_y - v2_y, 0);	// a simplified centeroid model
		}
	}
	releaseVertices(vertices1);
	releaseVertices(vertices2);
	return Vector(0, 0, 0);
}

/**	Rectangle vs. Circle
*	Parameters: centers of geometries and their scale parameters.
*	Return a 3-D vector, the third field holds intersection depth.
*	Principle from: Arvo, "A Simple Method for Box-Sphere Intersection Testing"
*
*	Potential bug: corner detection miss. caused by miscalculation of "y2".
*	The precise cause is still unknown.
*/
Vector Game::collision2D(GLfloat x1, GLfloat y1, GLfloat length, GLfloat width,
	GLfloat angle, GLfloat x2, GLfloat y2, GLfloat radius)
{
	// quick-test first
	GLfloat d = length / 2 + radius;
	if (x2 - x1 > d || x1 - x2 > d || y2 - y1 > d || y1 - y2 > d)
		return Vector(0, 0, 0);

	// change coordinates to align rectangle with the axes, center it at origin
	x2 -= x1;
	y2 -= y1;
	angle = angle / 180 * 3.1415926;	// degree --> rad
	GLfloat cos_angle = cos(angle);
	GLfloat sin_angle = sin(angle);
	GLfloat tempX = cos_angle * x2 + sin_angle * y2;
	GLfloat tempY = -sin_angle * x2 + cos_angle * y2;
	x2 = tempX;
	y2 = tempY;

	bool negX = x2 >= 0;
	bool negY = y2 >= 0;
	Vector p = Vector(x2, y2, 0).abs();
	
	// set a safe margin: avoid problem caused by precisions
	const Vector h = Vector(0.5 * length, 0.5 * width, 0);
	Vector u = p - h;

	u.x = u.x > 0 ? u.x : 0;
	u.y = u.y > 0 ? u.y : 0;

	GLfloat depth = radius - u.getLength();
	if (depth <= 0)	// no collision
		return Vector(0, 0, 0);
	
	/** As the "z" field of a vector will never be used, we use it to hold the 
	*	"intersection depth". This value is used to ensure that no part of an object
	*	will stay in another object. (Doesn't work when multiple obejcts crashes)
	*/

	/** If x and y here are positive, this simply means that there're force on 
	*	this direction. It is not the final direction.
	*/
	Vector ret(1, 1, depth);
	
	/** totally inside, we should figure out from which edge the ball crashes
	*	using history information. It's a really rare case.
	*/
	static Vector last_u(1, 1, 0);
	if (u.x == 0 && u.y == 0)
	{
		cout << "Insider called.\n";
		//cout << x2 << "\t" <<  y2 << "\t" << last_u << endl;
		if (last_u.x != 0 && last_u.y != 0)
		{
			// push to the corner
			ret = h - p;
			ret.z = radius + ret.getLength();
		}
		else if (last_u.x != 0)
		{
			// push to the right border
			ret.y = 0;
			ret.z = radius + 0.5 * length - x2;
		}
		else
		{
			// push to the top border
			ret.y = 0;
			ret.z = radius + 0.5 * width - y2;
		}
	}
	else
	{
		last_u = u;
		if (u.x == 0)
			ret.x = 0;
		if (u.y == 0)
			ret.y = 0;
	}

	// Decide direction
	if (negX) ret.x = -ret.x;
	if (negY) ret.y = -ret.y;

	// rotate back to world coordinates
	tempX = cos_angle * ret.x - sin_angle * ret.y;
	tempY = sin_angle * ret.x + cos_angle * ret.y;
	ret.x = tempX;
	ret.y = tempY;
	return ret;
}

/**	Circle vs. Circle
*	parameters: center coordinates & radii
*	Principle from: High school mathematics
*/
Vector Game::collision2D(GLfloat x1, GLfloat y1, GLfloat r1,
	GLfloat x2, GLfloat y2, GLfloat r2)
{
	// quick-test first
	GLfloat d = r1 + r2;
	if (x2 - x1 > d || x1 - x2 > d || y2 - y1 > d || y1 - y2 > d)
		return Vector(0, 0, 0);
	
	if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) > d * d)
		return Vector(0, 0, 0);
	
	return Vector(x1 - x2, y1 - y2, 0);
}

// get coordinates of a rectangle in rectagle-coordinates
GLfloat** Game::getVertices(GLfloat x, GLfloat y, GLfloat length,
	GLfloat width, GLfloat angle)
{
	GLfloat** ret = new GLfloat*[4];
	for (int i = 0; i < 4; i++)
		ret[i] = new GLfloat[2];
	
	angle = angle / 180 * 3.1415926;	// degree --> rad
	GLfloat cos_angle = cos(angle);
	GLfloat sin_angle = sin(angle);
	// rotate half length & half width
	GLfloat hlx = 0.5 * cos_angle * length;
	GLfloat hly = 0.5 * sin_angle * length;
	GLfloat hwx = 0.5 * (-sin_angle) * width;
	GLfloat hwy = 0.5 * cos_angle * width;
	GLfloat hl = 0.5 * length, hw = 0.5 * width;
	
	ret[0][0] = x + hlx + hwx;
	ret[0][1] = y + hly + hwy;
	ret[1][0] = x + hlx - hwx;
	ret[1][1] = y + hly - hwy;
	ret[2][0] = x - hlx - hwx;
	ret[2][1] = y - hly - hwy;
	ret[3][0] = x - hlx + hwx;
	ret[3][1] = y - hly + hwy;
	return ret;
}

void Game::releaseVertices(GLfloat** vertices)
{
	for (int i = 0; i < 4; i++)
		delete[]vertices[i];
	delete[]vertices;
}