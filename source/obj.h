#ifndef OBJ_H
#define OBJ_H

#include "Basic.h"
#include "mtl.h"
#include <sstream>
using namespace std;

class obj {
private:
	static const int MAX = 10000;
	GLfloat v[MAX][3]; //vertex
	GLfloat vt[MAX][3]; //texture
	GLfloat vn[MAX][3]; //normal vector
	int f[MAX][12], count[MAX], mtl_no[MAX]; //surface  f 0/1/2 3/4/5 6/7/8, count--每个面有多少个顶点
	int nv = -1, nt = -1, nn = -1, nf = -1; //number of vertex, texture, normal vector
	mtl m;
	int mtl_no_now;

	int atoi(char buf[]); //ascii to integer
	GLfloat atof(char buf[]); //ascii to float
	int divide(char buffer[100], char buf[][100], char c);
public:
	obj();
	~obj();
	void load(char path_obj[], char path_mtl[]); //read obj
	void draw();
	/*void draw(GLuint texture); //draw obj
	void draw(GLfloat color[]);*/
	void print(); //print obj
};

#endif