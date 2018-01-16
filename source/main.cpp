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
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow("Tank Soccer");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	TextureManager::init();
	glutMainLoop();
	return 0;
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(60.0f, whRatio, 0.1f, 400.0f);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	game.updateCamera();
	Point eye = game.camera.getEye();
	Point focus = game.camera.getFocus();
	
	gluLookAt(eye.x, eye.y, eye.z,
		focus.x, focus.y, focus.z,
		0, 0, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);							// ������ԴЧ��
	/*GLfloat Va[] = { 0.4f, 0.4f, 0.4f, 1.0f };           // ��Դ������ǿ������  
	GLfloat Vd[] = { 0.6f, 0.6f, 0.6f, 1.0f };           // ��Դɢ���ǿ������  
	GLfloat Vs[] = { 0.6f, 0.6f, 0.6f, 1.0f };           // ��Դ���淴���ǿ������  
	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, game.posLight);	// ָ��0�Ź�Դ��λ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);			// ���0�Ź�Դ�Ļ���������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);			// ����0�Ź�Դ��ɢ�������  
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);			// ����0�Ź�Դ�ľ��淴�������  
	if (game.bEnvir)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);*/
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 20,20,20,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	
	if(game.bChange)
		game.changeScene();
	
	// Draw game scene
	game.display();
	game.gotoNextFrame();

	glutSwapBuffers();
}
