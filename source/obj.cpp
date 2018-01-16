#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "obj.h"
using namespace std;

obj::obj()
{

}

obj::~obj()
{

}

int obj::atoi(char buf[])
{
	int i, res;
	for (i = res = 0; buf[i] != '\0'; i++)
		res = 10 * res + buf[i] - '0';
	return res;
}

GLfloat obj::atof(char buf[])
{
	char buf_int[20], buf_float[20];
	int i, j, res_int, res_float, flag;
	GLfloat res;

	if (buf[0] == '-') {
		flag = -1;
		i = 1;
	}
	else {
		flag = 1;
		i = 0;
	}

	for (j = 0; buf[i + j] != '.'; j++)
		buf_int[j] = buf[i + j];
	buf_int[j] = '\0';
	res_int = atoi(buf_int);
	i = i + j + 1;

	for (j = 0; buf[i + j] != '\0'; j++)
		buf_float[j] = buf[i + j];
	buf_float[j] = '\0';
	res_float = atoi(buf_float);
	res = res_int + res_float / pow(10.0, j);

	return res * flag;
}

int obj::divide(char buffer[100], char buf[][100], char c)
{
	int i, j, k;
	i = 0;
	for (k = 0; true; k++) {
		for (j = 0; buffer[i + j] != c && buffer[i + j] != '\0'; j++) buf[k][j] = buffer[i + j];
		buf[k][j] = '\0';
		i = i + j;
		while (buffer[i] == c) i++;
		if (buffer[i] == '\0') break;
	}
	return k;
}

void obj::load(char path_obj[], char path_mtl[])
{
	char buffer[100], buf[100][100], b[3][100];
	int i, j, n;

	m.load(path_mtl);

	ifstream file(path_obj, std::ios::in);
	while (file.getline(buffer, sizeof(buffer))) {
		n = divide(buffer, buf, ' ');
		if (buf[0][0] == 'f') {
			nf++;
			count[nf] = n;
			for (i = 1; i <= n; i++) {
				divide(buf[i], b, '/');
				for (j = 0; j < 3; j++) f[nf][3 * i - 3 + j] = atoi(b[j]);
			}
			mtl_no[nf] = mtl_no_now;
		}
		else if (buf[0][0] == 'v' && buf[0][1] == 'n') {
			nn++;
			for (i = 0; i < 3; i++) vn[nn][i] = atof(buf[i + 1]);
		}
		else if (buf[0][0] == 'v' && buf[0][1] == 't') {
			nt++;
			for (i = 0; i < 3; i++) vt[nt][i] = atof(buf[i + 1]);
		}
		else if (buf[0][0] == 'v') {
			nv++;
			for (i = 0; i < 3; i++) v[nv][i] = atof(buf[i + 1]);
		}
		else if (buf[0][0] == 'u' && buf[0][1] == 's' && buf[0][2] == 'e') {
			for (i = 0; true; i++)
				if (strcmp(buf[1], m.name[i]) == 0) {
					mtl_no_now = i;
					break;
				}
		}
	}
	file.close();
}

void obj::print()
{
	int i, j;
	printf("v, nv=%d\n", nv);
	for (i = 0; i <= nv; i++) cout << v[i][0] << "," << v[i][1] << "," << v[i][2] << ";" << endl;
	printf("vt, nt=%d\n", nt);
	for (i = 0; i <= nt; i++) cout << vt[i][0] << "," << vt[i][1] << ";" << vt[i][2] << ";" << endl;
	printf("vn, nn=%d\n", nn);
	for (i = 0; i <= nn; i++) cout << vn[i][0] << "," << vn[i][1] << "," << vn[i][2] << ";" << endl;
	printf("f, nf=%d\n", nf);
	for (i = 0; i <= nf; i++) {
		for (j = 0; j < 3 * count[i]; j++)
			if (j % 3 == 2)cout << f[i][j] << "  "; else cout << f[i][j] << "/";
		cout << endl;
	}
}

void obj::draw()
{
	int i;

	for (i = 0; i <= nf; i++) {
		//glMaterialfv(GL_FRONT, GL_SPECULAR, m.Kd[mtl_no[i]]);//镜面颜色  
		//glMateriali(GL_FRONT, GL_SHININESS, 50);//镜面指数  
		//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m.Kd[mtl_no[i]]);//材料的环境和散射颜色
		glMaterialfv(GL_FRONT, GL_SPECULAR, m.Ks[mtl_no[i]]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m.Kd[mtl_no[i]]);
		glMaterialfv(GL_FRONT, GL_AMBIENT, m.Ka[mtl_no[i]]);
		if (count[i] == 3) {
			glBegin(GL_TRIANGLES);
			glTexCoord2fv(vt[f[i][1] - 1]); glVertex3fv(v[f[i][0] - 1]);
			glTexCoord2fv(vt[f[i][4] - 1]); glVertex3fv(v[f[i][3] - 1]);
			glTexCoord2fv(vt[f[i][7] - 1]); glVertex3fv(v[f[i][6] - 1]);
			glEnd();
		}
		if (count[i] == 4) {
			glBegin(GL_QUADS);
			glTexCoord2fv(vt[f[i][1] - 1]); glVertex3fv(v[f[i][0] - 1]);
			glTexCoord2fv(vt[f[i][4] - 1]); glVertex3fv(v[f[i][3] - 1]);
			glTexCoord2fv(vt[f[i][7] - 1]); glVertex3fv(v[f[i][6] - 1]);
			glTexCoord2fv(vt[f[i][10] - 1]); glVertex3fv(v[f[i][9] - 1]);
			glEnd();
		}
	}
}

/*void obj::draw(GLuint texture)
{
	int i;

	for (i = 0; i <= nf; i++) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		if (count[i] == 3) {
			glBegin(GL_TRIANGLES);
			glTexCoord2fv(vt[f[i][1] - 1]); glVertex3fv(v[f[i][0] - 1]);
			glTexCoord2fv(vt[f[i][4] - 1]); glVertex3fv(v[f[i][3] - 1]);
			glTexCoord2fv(vt[f[i][7] - 1]); glVertex3fv(v[f[i][6] - 1]);
			glEnd();
		}
		if (count[i] == 4) {
			glBegin(GL_QUADS);
			glTexCoord2fv(vt[f[i][1] - 1]); glVertex3fv(v[f[i][0] - 1]);
			glTexCoord2fv(vt[f[i][4] - 1]); glVertex3fv(v[f[i][3] - 1]);
			glTexCoord2fv(vt[f[i][7] - 1]); glVertex3fv(v[f[i][6] - 1]);
			glTexCoord2fv(vt[f[i][10] - 1]); glVertex3fv(v[f[i][9] - 1]);
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
	}
}

void obj::draw(GLfloat color[])
{
	int i, j;
	for (i = 0; i <= nf; i++) {
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_SPECULAR, color);//设置镜面颜色  
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		if (count[i] == 3) {
			glBegin(GL_TRIANGLES);
			glVertex3fv(v[f[i][0] - 1]);
			glVertex3fv(v[f[i][3] - 1]);
			glVertex3fv(v[f[i][6] - 1]);
			glEnd();
		}
		if (count[i] == 4) {
			glBegin(GL_QUADS);
			glVertex3fv(v[f[i][0] - 1]);
			glVertex3fv(v[f[i][3] - 1]);
			glVertex3fv(v[f[i][6] - 1]);
			glVertex3fv(v[f[i][9] - 1]);
			glEnd();
		}
		glPopMatrix();
	}
}*/