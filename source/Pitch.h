#ifndef PITCH_H
#define PITCH_H

class Pitch
{
public:
	static const unsigned int LENGTH = 100;
	static const unsigned int WIDTH = 50;
	void draw()
	{
		const int height = 0.2;
		glPushMatrix();

		glTranslatef(0, 0, -height / 2);	// Keep the board underground
		glScalef(LENGTH, WIDTH, height);
		glColor3f(0, 0.6, 0);	// Green
		glutSolidCube(1);

		glPopMatrix();
	}
};
#endif // !PITCH_H

