#include "TextureManager.h"

GLuint TextureManager::texture_id[10];

void TextureManager::init()
{
	glGenTextures(10, texture_id);
	loadTexture(&texture_id[0], "pitch.bmp");
	loadTexture(&texture_id[1], "camouflage1.bmp");
	loadTexture(&texture_id[2], "camouflage2.bmp");
	loadTexture(&texture_id[3], "ad.bmp");
	loadTexture(&texture_id[4], "scene_ft.bmp");
	loadTexture(&texture_id[5], "scene_bk.bmp");
	loadTexture(&texture_id[6], "scene_lf.bmp");
	loadTexture(&texture_id[7], "scene_rt.bmp");
	loadTexture(&texture_id[8], "scene_up.bmp");
	loadTexture(&texture_id[9], "scene_dn.bmp");
}

// The following code is written with reference to <Computer Graphics Course Design> 
unsigned char* TextureManager::LoadBitmapFile(const char *fileName, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;						// file pointer
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap file header
	unsigned char *bitmapImage;			// bitmap data
	unsigned int begin, end;			// bitmap index
	unsigned char tempRGB;				// temp variable used to adjust RGB order

										// Open file
	filePtr = fopen(fileName, "rb");
	if (filePtr == NULL)
	{
		fprintf(stderr, "Failed to open bitmap file %s.\n", fileName);
		return NULL;
	}

	// Load file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// Check file type
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fprintf(stderr, "The file %s is not a bitmap file as declared.\n", fileName);
		return NULL;
	}

	// Load information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// Load bitmap file content
	bitmapImage = (unsigned char*)malloc(sizeof(unsigned char) *
		bitmapInfoHeader->biSizeImage);						// allocate memory
	if (!bitmapImage)
	{
		fprintf(stderr, "Failed to allocate memory for bitmap file %s.\n", fileName);
		return NULL;
	}
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);			// move file pointer
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);	// load content
	if (bitmapImage == NULL)										// load failed
	{
		fprintf(stderr, "Failed to load bitmap file %s after successful memory\
 allocation.\n", fileName);
		return NULL;
	}

	begin = 0;
	end = bitmapInfoHeader->biSizeImage;
	end = end - (end % 3) - 1;	// Make sure that begin = 0 , end < biSizeImage and end % 3 = 2

								// reverse what we've read to get the real content of bitmap file
	while (begin < end)
	{
		tempRGB = bitmapImage[begin];
		bitmapImage[begin] = bitmapImage[end];
		bitmapImage[end] = tempRGB;
		begin++;
		end--;
	}

	// Close file and return
	fclose(filePtr);
	return bitmapImage;
}

void TextureManager::loadTexture(GLuint *textureID, char *fileName)
{
	BITMAPINFOHEADER bitmapInfoHeader;		// bitmap information header
	unsigned char*   bitmapData;			// bitmap RedBlackSquares file, stored in RGB
								// load RGB and switch its storing order to RGB
	bitmapData = LoadBitmapFile(fileName, &bitmapInfoHeader);

	// load textureID to an textureID id
	glBindTexture(GL_TEXTURE_2D, *textureID);

	/*
	*	Specify textureID appearance when the size of our drawing and textureID
	*	mismatch
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*
	*	mipmap: at the topmost level
	*	color: specified in RGB
	*	data type: unsigned char
	*	border: none
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
}

// single texture version
void TextureManager::drawCube(GLfloat size)
{
	int i, j;
	size *= 0.5;
	const GLfloat x_neg = -size, x_pos = size;
	const GLfloat y_neg = -size, y_pos = size;
	const GLfloat z_neg = -size, z_pos = size;

	// Specify the 4 points of 6 plains of a cube
	GLfloat point[6][4][3] =
	{
		{ { x_neg,y_neg,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_pos,z_neg },{ x_neg,y_pos,z_neg } },
		{ { x_neg,y_neg,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_neg,z_pos },{ x_neg,y_neg,z_pos } },
		{ { x_pos,y_neg,z_neg },{ x_pos,y_pos,z_neg },{ x_pos,y_pos,z_pos },{ x_pos,y_neg,z_pos } },
		{ { x_neg,y_neg,z_neg },{ x_neg,y_pos,z_neg },{ x_neg,y_pos,z_pos },{ x_neg,y_neg,z_pos } },
		{ { x_neg,y_pos,z_neg },{ x_pos,y_pos,z_neg },{ x_pos,y_pos,z_pos },{ x_neg,y_pos,z_pos } },
		{ { x_neg,y_neg,z_pos },{ x_pos,y_neg,z_pos },{ x_pos,y_pos,z_pos },{ x_neg,y_pos,z_pos } }
	};
	// The 4 corners of an texture
	int dir[4][2] = { { 1,0 },{ 0,0 },{ 0,1 },{ 1,1 } };

	// Draw each plain one by one to add texture
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++)
		{
			// Bind coordinate in texture with coordinate of vertex
			//if (i == 5)
			glTexCoord2iv(dir[j]);
			glVertex3fv(point[i][j]);
		}
	glEnd();
}

void TextureManager::drawSurface(GLfloat size)
{
	int i;
	size *= 0.5;
	const GLfloat x_neg = -size, x_pos = size;
	const GLfloat y_neg = -size, y_pos = size;

	// Specify the 4 points of 6 plains of a cube
	GLfloat point[4][3] = { { x_neg, y_neg, 0.0f },{ x_pos,y_neg, 0.0f },{ x_pos,y_pos, 0.0f },{ x_neg,y_pos, 0.0f } };
	
	// The 4 corners of an texture
	int dir[4][2] = { { 1,0 },{ 0,0 },{ 0,1 },{ 1,1 } };

	// Draw each plain one by one to add texture
	glBegin(GL_QUADS);
	for (i = 0; i < 4; i++)
	{
		glTexCoord2iv(dir[i]);
		glVertex3fv(point[i]);
	}	
	glEnd();
}

// whether the cube is table surface decides whether multi-texture is applied
/*void TextureManager::drawCube(GLfloat size, bool multiTexture)
{
	int i, j;
	size *= 0.5;
	const GLfloat x_neg = -size, x_pos = size;
	const GLfloat y_neg = -size, y_pos = size;
	const GLfloat z_neg = -size, z_pos = size;

	// Specify the 4 points of 6 plains of a cube
	GLfloat cubeVertex[6][4][3] =
	{
		{ { x_neg,y_neg,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_pos,z_neg },{ x_neg,y_pos,z_neg } },
		{ { x_neg,y_neg,z_neg },{ x_pos,y_neg,z_neg },{ x_pos,y_neg,z_pos },{ x_neg,y_neg,z_pos } },
		{ { x_pos,y_neg,z_neg },{ x_pos,y_pos,z_neg },{ x_pos,y_pos,z_pos },{ x_pos,y_neg,z_pos } },
		{ { x_neg,y_neg,z_neg },{ x_neg,y_pos,z_neg },{ x_neg,y_pos,z_pos },{ x_neg,y_neg,z_pos } },
		{ { x_neg,y_pos,z_neg },{ x_pos,y_pos,z_neg },{ x_pos,y_pos,z_pos },{ x_neg,y_pos,z_pos } },
		{ { x_neg,y_neg,z_pos },{ x_pos,y_neg,z_pos },{ x_pos,y_pos,z_pos },{ x_neg,y_pos,z_pos } }
	};
	// The 4 corners of an texture
	GLfloat textureVertex[4][2] = { { 1,0 },{ 0,0 },{ 0,1 },{ 1,1 } };

	// Draw each plain one by one to add texture
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++)
		for (j = 0; j < 4; j++)
		{
			// Bind coordinate in texture with coordinate of vertex
			glMultiTexCoord2fvARB(GL_TEXTURE0_ARB, textureVertex[j]);
			if (multiTexture && i == 5)	// only apply multi-texture on desktop
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, textureVertex[j]);
			glVertex3fv(cubeVertex[i][j]);
		}
	glEnd();
}*/

GLuint TextureManager::getTextureID(int index)
{
	return texture_id[index];
}