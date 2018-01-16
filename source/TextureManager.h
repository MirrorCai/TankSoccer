#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <gl\glut.h>
//#include <gl\glext.h>

#define BITMAP_ID 0x4D42

// a static class
class TextureManager
{
public:
	static void init();

	// The following code is written with reference to <Computer Graphics Course Design> 
	static unsigned char *LoadBitmapFile(const char *fileName, BITMAPINFOHEADER *bitmapInfoHeader);

	static void loadTexture(GLuint *textureID, char *fileName);

	static void drawCube(GLfloat size);
	static void drawSurface(GLfloat size);
	// whether the cube is table surface decides whether multi-texture is applied
	//static void drawCube(GLfloat size, bool multiTexture);

	static GLuint getTextureID(int index);

	static GLuint texture_id[10];

	// Indices of textures
	static const int PITCH_TEXT = 0;
	static const int CAMOUFLAGE_TEXT_1 = 1;
	static const int CAMOUFLAGE_TEXT_2 = 2;
	static const int AD_TEXT =	3;
	static const int FRONT	=	4;
	static const int BACK	=	5;
	static const int LEFT	=	6;
	static const int RIGHT	=	7;
	static const int UP		=	8;
	static const int DOWN	=	9;
};

#endif // !TEXTURE_H

