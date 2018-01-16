#include "Game.h"
#include <time.h>

Game::Game()
	:tank1(Point(-40, 0, 0)),tank2(Point(40, 0, 0))
{
	score_p1 = 0;
	score_p2 = 0;
	tFlag = 1;
	tCount = 0;
	bEnvir = true;
	bSpot = false;
	bChange = false;
	followItem = BALL;
	tank1.turn(0);
	tank1.setTextureID(TextureManager::CAMOUFLAGE_TEXT_1);
	tank2.turn(180);
	tank2.setTextureID(TextureManager::CAMOUFLAGE_TEXT_2);
	outsidePause = false;
	userPause = false;
}
void Game::keyboard(unsigned char key, int x, int y)
{
	if (outsidePause || userPause)
		return;
	switch (key)
	{
	case 27: {exit(0); break; }	// ESC
	//case ' ': {ball.setVelocity(Vector(0.1, 0, 0)); break; }
	case 'w': {tank1.setSpeed(0.08); break; }
	case 's': {tank1.setSpeed(-0.03); break; }
	case 'a': {tank1.turn(2.5); break; }
	case 'd': {tank1.turn(-2.5); break; }
	case 'q': {tank1.turnTurret(2.5); break; }
	case 'e': {tank1.turnTurret(-2.5); break; }

	case '0': {bEnvir = !bEnvir; break; }
	case 'b': {capture(); break; }
	case '9': {bChange = !bChange; break; }

	case 't': {tank2.setSpeed(0.08); break; }
	case 'g': {tank2.setSpeed(-0.03); break; }
	case 'f': {tank2.turn(2.5); break; }
	case 'h': {tank2.turn(-2.5); break; }
	case 'r': {tank2.turnTurret(2.5); break; }
	case 'y': {tank2.turnTurret(-2.5); break; }

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
		camera.follow(tank1.getCenter(), tank1.getAngle());
}
void Game::display()
{
	Surrounding::drawAt(camera.getEye());
	pitch.draw();
	ball.render();
	tank1.render();
	tank2.render();
	printInfo();
}
void Game::gotoNextFrame()
{
	static int pauseStart = 0;
	int time = glutGet(GLUT_ELAPSED_TIME);
	tanksCollide(tank1, tank2);
	tankBallCollide(tank1, ball);
	tankBallCollide(tank2, ball);
	
	checkBounds(ball);
	checkBounds(tank1);
	checkBounds(tank2);
	if (ball.getVelocity().getSquareLength() > 0.04)
		ball.setSpeed(0.2);
	ball.update();
	tank1.update();
	tank2.update();

	if (outsidePause || goalPause)
	{
		if (pauseStart == 0)
			pauseStart = time;
		else if (time - pauseStart > pausePeriod)
		{
			goalPause = outsidePause = false;
			pauseStart = 0;
		}
	}
}

/* Check whether the ball collides with the bound. */
void Game::checkBounds(Ball& ball)
{
	static const GLfloat halfLength = 67.5f;
	static const GLfloat halfWidth = 37.5f;
	Vector velocity = ball.getVelocity();
	Point c = ball.getCenter() + velocity;

	if (c.x >= halfLength || c.x <= -halfLength || c.y >= halfWidth || c.y <= -halfWidth)
	{

		if (-Goal::goalWidth <= c.y && c.y <= Goal::goalWidth)
		{
			resetAllObjects();
			goalPause = true;
			if (c.x > 0)
				score_p1++;
			else
				score_p2++;
		}
		else
		{
			outsidePause = true;
			// Set ball a random position that does not collide with tanks.
			srand((unsigned)time(NULL));

			GLfloat x = rand() % 80 - 40, y = rand() % 40 - 20;
			GLfloat t1x = tank1.getCenter().x;
			GLfloat t2x = tank1.getCenter().x;

			while (t1x - 6 < x && x < t1x + 6 || t2x - 6 < x && x < t2x + 6)
				x = rand() % 80 - 40;

			ball.setCenter(Point(x, y, 0));
			ball.setVelocity(Vector(0, 0, 0));
		}
			
		
		
	}
}

/* Check whether the tank collides with the bound and keep all its four 
* vertices inside the pitch, then set the Vn to be zero.
*/
void Game::checkBounds(Tank& tank)
{
	// use hard code to accerlerate
	static const GLfloat halfLength = 67.5f;
	static const GLfloat halfWidth = 37.5f;
	Vector v1 = 0.5 * tank.getBlockSize();
	Vector v2 = Vector(v1.x, -v1.y, 0);
	// after rotate
	v1.rotate_z(tank.getAngle());
	v2.rotate_z(tank.getAngle());

	// get updated vertex coodinate
	Point c = tank.getCenter() + tank.getVelocity();
	
	// expected coordinate of the tank after collision
	Point p1 = c + v1, p2 = c + v2, p3 = c - v1, p4 = c - v2;

	Vector adjust = Vector(0, 0, 0);
	Vector velocity = tank.getVelocity();
	GLfloat exceed;

	// adjustment in x
	if ((exceed = halfLength - max_of_4(p1.x, p2.x, p3.x, p4.x)) < 0)
	{
		adjust.x = exceed;
		if (velocity.x > 0) velocity.x = 0;
	}
	else if ((exceed = -halfLength - min_of_4(p1.x, p2.x, p3.x, p4.x)) > 0)
	{
		adjust.x = exceed;
		if (velocity.x < 0) velocity.x = 0;
	}

	// adjustment in y
	if ((exceed = halfWidth - max_of_4(p1.y, p2.y, p3.y, p4.y)) < 0)
	{
		adjust.y = exceed;
		if (velocity.y > 0) velocity.y = 0;
	}
	else if ((exceed = -halfWidth - min_of_4(p1.y, p2.y, p3.y, p4.y)) > 0)
	{
		adjust.y = exceed;
		if (velocity.y < 0) velocity.y = 0;
	}

	tank.setVelocity(velocity);
}

GLfloat Game::max_of_4(GLfloat op1, GLfloat op2, GLfloat op3, GLfloat op4)
{
	op1 = op1 > op2 ? op1 : op2;
	op3 = op3 > op4 ? op3 : op4;
	return op1 > op3 ? op1 : op3;
}

GLfloat Game::min_of_4(GLfloat op1, GLfloat op2, GLfloat op3, GLfloat op4)
{
	op1 = op1 < op2 ? op1 : op2;
	op3 = op3 < op4 ? op3 : op4;
	return op1 < op3 ? op1 : op3;
}

void Game::tanksCollide(Tank& tank1, Tank& tank2)
{
	Point c1 = tank1.getCenter() + tank1.getVelocity();
	Point c2 = tank2.getCenter() + tank2.getVelocity();
	Size blockSize = tank1.getBlockSize();

	Vector ret = collision2D(c1.x, c1.y, blockSize.x, blockSize.y, tank1.getAngle(),
		c2.x, c2.y, blockSize.x, blockSize.y, tank2.getAngle());
	if (ret == Vector(0, 0, 0))
		return;
	cout << ret << endl;
	
	Vector force_to_tank1 = ret.getIdentityVector();
	Vector force_to_tank2 = -force_to_tank1;

	// step1: keep 2 tanks separated
	GLfloat rejectFactor = 0.5;
	tank1.setCenter(tank1.getCenter() + rejectFactor * force_to_tank1);
	tank2.setCenter(tank2.getCenter() + rejectFactor * force_to_tank2);

	// step2: update speed
	Vector vn_tank1 = (tank1.getVelocity() * force_to_tank1) * force_to_tank1;
	Vector vt_tank1 = tank1.getVelocity() - vn_tank1;
	Vector vn_tank2 = (tank2.getVelocity() * force_to_tank2) * force_to_tank2;
	Vector vt_tank2 = tank2.getVelocity() - vn_tank2;
	Vector temp = vn_tank1;
	vn_tank1 = vn_tank2;
	vn_tank2 = temp;
	tank1.setVelocity(vn_tank1 + vt_tank1);
	tank2.setVelocity(vn_tank2 + vt_tank2);
}

void Game::resetAllObjects()
{
	tank1.setCenter(Point(-40, 0, 0));
	tank2.setCenter(Point(40, 0, 0));
	ball.setCenter(Point(0, 0, 0));
	tank1.setSpeed(0);
	tank1.setAngle(0);
	tank2.setSpeed(0);
	tank2.setAngle(180);
	ball.setSpeed(0);
}

void Game::printInfo()
{
	static char scoreBuffer[32];
	static const char *outMessage = "The ball has go outside!";
	static const char *goalMessage = "GOAAAAAAAL!!!";
	sprintf(scoreBuffer, "P1 vs. P2: [%u : %u]", score_p1, score_p2);

	// prepare
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 600, 0, 350, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// print information
	
	// Score information
	glRasterPos2f(10, 10);
	for (const char *c = scoreBuffer; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	
	// Pause information
	if (goalPause)
	{
		glRasterPos2f(200, 150);
		for (const char *c = goalMessage; *c != '\0'; c++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	else if (outsidePause)
	{
		glRasterPos2f(200, 150);
		for (const char *c = outMessage; *c != '\0'; c++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	// recover
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Game::tankBallCollide(Tank& tank, Ball& ball)
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
*	dotted product and the rightGoal angle. (< 90 ~ > 0; == 90 ~ == 0; > 90 ~ < 0)
*/
Vector Game::collision2D(
	GLfloat x1, GLfloat y1, GLfloat l1, GLfloat w1, GLfloat a1,
	GLfloat x2, GLfloat y2, GLfloat l2, GLfloat w2, GLfloat a2)
{
	// actually const
	static int safe = l1 + w1;
	if (x1 - x2 > safe || x2 - x1 > safe || y1 - y2 > safe || y2 - y1 > safe)
		return Vector(0, 0, 0);

	//GLfloat*** vertices = new GLfloat**[2];
	static GLfloat vertices[2][4][2];
	setTankVertices(x1, y1, l1, w1, a1, vertices[0]);
	setTankVertices(x2, y2, l2, w2, a2, vertices[1]);

	/*for (int i = 0; i < 4; i++)
		cout << vertices[0][i][0] << "\t" << vertices[0][i][1] << endl;
	cout << "\n";
	for (int i = 0; i < 4; i++)
		cout << vertices[1][i][0] << "\t" << vertices[1][i][1] << endl;
	cout << "\n";*/
	//vertices[0] = getVertices(x1, y1, l1, w1, a1);
	//vertices[1] = getVertices(x2, y2, l2, w2, a2);
	//cout << "survive!\n";
	
	// two rectangle
	for (int rec = 0; rec < 2; rec++)
	{
		int other = 1 - rec;
		// 4 edges displayed in 2-D vector
		int v1_x = vertices[rec][1][0] - vertices[rec][0][0], v1_y = vertices[rec][1][1] - vertices[rec][0][1];
		int v2_x = vertices[rec][3][0] - vertices[rec][0][0], v2_y = vertices[rec][3][1] - vertices[rec][0][1];
		int v3_x = vertices[rec][1][0] - vertices[rec][2][0], v3_y = vertices[rec][1][1] - vertices[rec][2][1];
		int v4_x = vertices[rec][3][0] - vertices[rec][2][0], v4_y = vertices[rec][3][1] - vertices[rec][2][1];

		for (int i = 0; i < 4; i++)
		{
			int _v1_x = vertices[other][i][0] - vertices[rec][0][0], _v1_y = vertices[other][i][1] - vertices[rec][0][1];
			int _v2_x = vertices[other][i][0] - vertices[rec][2][0], _v2_y = vertices[other][i][1] - vertices[rec][2][1];
			
			if (_v1_x * v1_x + _v1_y * v1_y >= 0 && _v1_x * v2_x + _v1_y * v2_y >= 0 &&	// angle[0] includes!
				_v2_x * v3_x + _v2_y * v3_y >= 0 && _v2_x * v4_x + _v2_y * v4_y >= 0)	// angle[2] includes!
			{
				cout << other << '\t' << i;
				//releaseVertices(vertices[1]);
				//releaseVertices(vertices[2]);
				
				// Centeroid model. indicate the direction of rec1's movement
				return Vector(x1 - x2, y1 - y2, 0);	
			}
		}
	}
	//releaseVertices(vertices[1]);
	//releaseVertices(vertices[2]);
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
			// push to the rightGoal border
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

void Game::setTankVertices(GLfloat x, GLfloat y, GLfloat length,
	GLfloat width, GLfloat angle, GLfloat vertices[4][2])
{
	angle = angle / 180 * 3.1415926;	// degree --> rad
	GLfloat cos_angle = cos(angle);
	GLfloat sin_angle = sin(angle);

	// naming: h - half, l - length, w - width
	// half length vector
	GLfloat hlx = 0.5 * cos_angle * length;
	GLfloat hly = 0.5 * sin_angle * length;
	// half width vector
	GLfloat hwx = 0.5 * (-sin_angle) * width;
	GLfloat hwy = 0.5 * cos_angle * width;

	// calculate coordinates from the center
	vertices[0][0] = x + hlx + hwx;
	vertices[0][1] = y + hly + hwy;
	vertices[1][0] = x + hlx - hwx;
	vertices[1][1] = y + hly - hwy;
	vertices[2][0] = x - hlx - hwx;
	vertices[2][1] = y - hly - hwy;
	vertices[3][0] = x - hlx + hwx;
	vertices[3][1] = y - hly + hwy;
}
// get coordinates of a rectangle in rectangle-coordinates
// parameter: center coordinates, size, angle
GLfloat** Game::getVertices(GLfloat x, GLfloat y, GLfloat length,
	GLfloat width, GLfloat angle)
{
	GLfloat** ret = new GLfloat*[4];
	for (int i = 0; i < 4; i++)
		ret[i] = new GLfloat[2];
	
	angle = angle / 180 * 3.1415926;	// degree --> rad
	GLfloat cos_angle = cos(angle);
	GLfloat sin_angle = sin(angle);
	
	// naming: h - half, l - length, w - width
	
	// half length vector
	GLfloat hlx = 0.5 * cos_angle * length;
	GLfloat hly = 0.5 * sin_angle * length;
	// half width vector
	GLfloat hwx = 0.5 * (-sin_angle) * width;
	GLfloat hwy = 0.5 * cos_angle * width;
	
	// calculate coordinates from the center
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

// TODO: get rid of this dynamic allocation
// Should be paired with every use of getVertices to avoid memory leak
void Game::releaseVertices(GLfloat** vertices)
{
	for (int i = 0; i < 4; i++)
		delete[] vertices[i];
	delete[] vertices;
}

void Game::capture()
{
	FILE*    pDummyFile;	//指向另一bmp文件，用于复制它的文件头和信息头数据  
	FILE*    pWritingFile;  //指向要保存截图的bmp文件  
	GLubyte* pPixelData;    //指向新的空的内存，用于保存截图bmp文件数据  
	GLubyte  BMP_Header[BMP_Length];
	GLint    i, j;
	GLint    PixelDataLength;   //BMP文件数据总长度  

								// 计算像素数据的实际长度  
	i = WinWidth * 3;			// 得到每一行的像素数据长度  
	while (i % 4 != 0)			// 补充数据，直到i是的倍数  
		++i;
	PixelDataLength = i * WinHeight;  //补齐后的总位数  

									  // 分配内存和打开文件  
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);

	pDummyFile = fopen("demo.bmp", "rb");//只读形式打开  
	if (pDummyFile == 0)
		exit(0);

	pWritingFile = fopen("capture.bmp", "wb"); //只写形式打开  
	if (pWritingFile == 0)
		exit(0);

	//把读入的bmp文件的文件头和信息头数据复制，并修改宽高数据  
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);  //读取文件头和信息头，占据54字节  
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET); //移动到0X0012处，指向图像宽度所在内存  
	i = WinWidth;
	j = WinHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 读取当前画板上图像的像素数据  
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  //设置4位对齐方式  
	glReadPixels(0, 0, WinWidth, WinHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 写入像素数据  
	fseek(pWritingFile, 0, SEEK_END);
	//把完整的BMP文件数据写入pWritingFile  
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件  
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
	//free(timeInfo);
}

void Game::changeScene() {

	if (posLight[2] == 20.0f)
		tFlag = -1;
	if (posLight[2] == -5.0f)
		tFlag = 1;

	tCount++;
	if (tCount == 1000) {
		tCount = 0;
		posLight[2] += tFlag;
		posLight[1] += 1.0f;
		if (posLight[1] == 25)
			posLight[1] = -20;
		printf("%lf,%lf\n", posLight[1], posLight[2]);
	}
}