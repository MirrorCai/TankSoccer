#include "Pitch.h"

Pitch::Pitch()
	:leftGoal(true), rightGoal(false)
{
	texture = 0;
}

void Pitch::changeTexture()
{
	texture = texture ? 0 : 1;
}

void Pitch::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::PITCH_TEXT));
	// Set texture: will not be affected by environment light
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	// TODO
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	drawPitch();
	glDisable(GL_TEXTURE_2D);
	
	leftGoal.draw();
	rightGoal.draw();

	drawBoard();
}

void Pitch::drawBoard()
{
	// Set Texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(TextureManager::AD_TEXT));
	// Set texture: will not be affected by environment light
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	GLfloat x_long_neg = -76.0f, x_long_pos = 76.0f;
	GLfloat y_long_neg = -2.0f, y_long_pos = 2.0f;

	//GLfloat x_short_neg = -2.0f, x_short_pos = 2.0f;
	//GLfloat y_short_neg = -39.0f, y_short_pos = 39.0f;
	GLfloat x_short_neg = -39.0f, x_short_pos = 39.0f;
	GLfloat y_short_neg = -2.0f, y_short_pos = 2.0f;

	static GLfloat point[2][4][3] = 
	{ 
		{
			{ x_long_neg, y_long_neg, 0.0f },{ x_long_pos, y_long_neg, 0.0f },
			{ x_long_pos, y_long_pos, 0.0f },{ x_long_neg, y_long_pos, 0.0f }
		},
		{
			{ x_short_neg, y_short_neg, 0.0f },{ x_short_pos, y_short_neg, 0.0f },
			{ x_short_pos, y_short_pos, 0.0f },{ x_short_neg, y_short_pos, 0.0f }
		}
	};
	const int dir[4][4][2] = 
	{ 
		{ { 6,1 },{ 0,1 },{ 0,0 },{ 6,0 } },
		{ { 0,1 },{ 6,1 },{ 6,0 },{ 0,0 } }, 
		{ { 0,1 },{ 3,1 },{ 3,0 },{ 0,0 } },
		{ { 3,1 },{ 0,1 },{ 0,0 },{ 3,0 } },
	};

	// Left (to player 1)
	glPushMatrix();
	glTranslatef(0.0f, 37.5f, 2.0f);
	glRotatef(75.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2iv(dir[0][i]);
		glVertex3fv(point[0][i]);
	}
	glEnd();
	glPopMatrix();
	
	// Right
	glPushMatrix();
	glTranslatef(0.0f, -37.5f, 2.0f);
	glRotatef(105.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2iv(dir[1][i]);
		glVertex3fv(point[0][i]);
	}
	glEnd();
	glPopMatrix();

	// Front
	glPushMatrix();
	glTranslatef(75.0f, 0.0f, 2.0f);
	glRotatef(105.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2iv(dir[2][i]);
		glVertex3fv(point[1][i]);
	}
	glEnd();
	glPopMatrix();
	
	// Back
	glPushMatrix();
	glTranslatef(-75.0f, 0.0f, 2.0f);
	glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2iv(dir[3][i]);
		glVertex3fv(point[1][i]);
	}
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Pitch::drawPitch()
{
	const int height = 2;
	glPushMatrix();

	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, refPitch);//设置桌面漫反射
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, refPitch);//设置桌面镜面反射
	//glTranslatef(0, 0, -height / 2);	// Keep the board underground
	glScalef(LENGTH, WIDTH, height);
	
	TextureManager::drawSurface(1);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}