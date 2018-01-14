#include "Surrounding.h"

GLfloat Surrounding::DISTANCE = 150;
GLfloat Surrounding::SIZE = 300;

void Surrounding::drawAt(Point cameraPos)
{
	GLfloat &x = cameraPos.x;
	GLfloat &y = cameraPos.y;
	GLfloat &z = cameraPos.z;
	
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	// not affected by light
	
	const GLfloat x_neg = -DISTANCE, x_pos = DISTANCE;
	const GLfloat y_neg = -DISTANCE, y_pos = DISTANCE;
	const GLfloat z_neg = -DISTANCE, z_pos = DISTANCE;

	// Specify the 4 points of 6 plains of a cube
	GLfloat point[6][4][3] =
	{
		// take +x as front
		{ { x_pos,y_pos,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_neg,z_pos },{ x_pos,y_pos,z_pos } },	// front
		{ { x_neg,y_neg,z_neg },{ x_neg,y_pos,z_neg },{ x_neg,y_pos,z_pos },{ x_neg,y_neg,z_pos } },	// back
		{ { x_neg,y_pos,z_neg },{ x_pos,y_pos,z_neg },{ x_pos,y_pos,z_pos },{ x_neg,y_pos,z_pos } },	// leftGoal
		{ { x_pos,y_neg,z_neg },{ x_neg,y_neg,z_neg },{ x_neg,y_neg,z_pos },{ x_pos,y_neg,z_pos } },	// rightGoal
		{ { x_neg,y_pos,z_pos },{ x_pos,y_pos,z_pos },{ x_pos,y_neg,z_pos },{ x_neg,y_neg,z_pos } },	// up
		{ { x_neg,y_neg,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_pos,z_neg },{ x_neg,y_pos,z_neg } }		// down
	};

	// front
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::FRONT));
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	// not affected by light
	
	int dir[4][2] = { { 1,1 },{ 0,1 },{ 0,0 },{ 1,0 } };

	for (int i = 0; i < 6; i++)
	{
		// hard code here
		glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::FRONT + i));
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	// not affected by light
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; j++)
		{
			glTexCoord2iv(dir[j]);
			glVertex3fv(point[i][j]);
		}
		glEnd();
	}
	/*
	glPushMatrix();
	glScalef(SIZE, SIZE, 1.0f);
	//glTranslatef(x + 151, y, z);
	
	//glRotatef(90, 0, 0, 1);
	TextureManager::drawCube(1);
	TextureManager::drawSurface(1);
	//glutSolidCube(1);
	glPopMatrix();

	// back
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::BACK));
	glPushMatrix();
	glTranslatef(x - DISTANCE, y, z);
	glScalef(SIZE, SIZE, 1.0f);
	glRotatef(90, 0, 0, 1);
	
	TextureManager::drawSurface(1);
	glPopMatrix();

	// leftGoal
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::LEFT));
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	// not affected by light
	glPushMatrix();
	glTranslatef(x, y + DISTANCE, z);
	glScalef(SIZE, SIZE, 1.0f);
	TextureManager::drawSurface(1);
	//glutSolidCube(1);
	glPopMatrix();

	// rightGoal
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::RIGHT));
	glPushMatrix();
	glTranslatef(x, y - DISTANCE, z);
	glScalef(SIZE, SIZE, 1.0f);
	TextureManager::drawSurface(1);
	glPopMatrix();
	*/
	glDisable(GL_TEXTURE_2D);
}

