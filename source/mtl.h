#ifndef MTL_H
#define MTL_H

#include "Basic.h"
#include <sstream>
using namespace std;

class mtl {
public:
	static const int MAX = 100;
	int n = -1;
	char name[MAX][100];
	GLfloat Ns[MAX];
	GLfloat Ni[MAX];
	GLfloat d[MAX];
	GLfloat Tr[MAX];
	GLfloat Tf[MAX][3];
	int illum[MAX];
	GLfloat Ka[MAX][3];
	GLfloat Kd[MAX][3];
	GLfloat Ks[MAX][3];
	GLfloat Ke[MAX][3];

	int atoi(char buf[]); //ascii to integer
	GLfloat atof(char buf[]); //ascii to float
	int divide(char buffer[100], char buf[][100], char c);

	mtl();
	~mtl();
	void load(char path[]);
	void print();
};

#endif