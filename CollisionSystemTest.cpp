#include "Basic.h"
#include "Ball.h"
#include "Pitch.h"
#include "Cuboid.h"
#include "Tank.h"
#include "Cylinder.h"
#include "Game.h"

Game game;

void updateView(int width, int height);
void reshape(int width, int height);
void idle();

void key(unsigned char key, int x, int y)
{
	game.keyboard(key, x, y);
}

void redraw();

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 350);
	glutCreateWindow("Tank Soccer");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
void updateView(int width, int height)
{
	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(60.0f, whRatio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}
void reshape(int width, int height)
{
	if (height == 0)									// Prevent A Divide By Zero By
		height = 1;										// Making Height Equal One
	updateView(width, height);
}
void idle()
{
	// Collision detection and reaction
	glutPostRedisplay();
}
void redraw()
{
	static Vector center(0, 0, 0), eye(0, -GLfloat(Pitch::WIDTH) / 2 - 10, 40);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	game.setCamera(eye, center);
	gluLookAt(eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		0, 0, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	// TODO: light

	// draw game scene
	game.display();
	game.gotoNextFrame();

	glutSwapBuffers();
}
