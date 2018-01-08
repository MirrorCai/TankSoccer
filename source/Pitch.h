#ifndef PITCH_H
#define PITCH_H

class Pitch
{
public:
	static const unsigned int LENGTH = 100;
	static const unsigned int WIDTH = 50;
	GLfloat refPitch[3] = { 0.0f,1.0f,0.0f };			//����3�������
	void draw()
	{
		const int height = 2;
		glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, refPitch);//��������������
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, refPitch);//�������澵�淴��
		glTranslatef(0, 0, -height / 2);	// Keep the board underground
		glScalef(LENGTH, WIDTH, height);
		//glColor3f(0, 0.6, 0);	// Green
		glutSolidCube(1);

		glPopMatrix();
	}

};
#endif // !PITCH_H

