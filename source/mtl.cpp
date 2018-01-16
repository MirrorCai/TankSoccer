#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mtl.h"
using namespace std;

mtl::mtl()
{

}

mtl::~mtl()
{

}

int mtl::atoi(char buf[])
{
	int i, res;
	for (i = res = 0; buf[i] != '\0'; i++)
		res = 10 * res + buf[i] - '0';
	return res;
}

GLfloat mtl::atof(char buf[])
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

int mtl::divide(char buffer[100], char buf[][100], char c)
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

void mtl::load(char path[])
{
	char buffer[100], buf[100][100];
	int i;
	ifstream file(path, std::ios::in);
	while (file.getline(buffer, sizeof(buffer))) {
		divide(buffer, buf, ' ');
		//cout << "[" << buffer << "]{" << buf[0] << "}{" << buf[1] << "}" << endl;
		if (buf[0][0] == 'n' && buf[0][1] == 'e' && buf[0][2] == 'w') {
			n++;
			strcpy(name[n], buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'N' && buf[0][2] == 's') {
			Ns[n] = atof(buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'N' && buf[0][2] == 'i') {
			Ni[n] = atof(buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'd') {
			d[n] = atof(buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'T' && buf[0][2] == 'r') {
			Tr[n] = atof(buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'T' && buf[0][2] == 'f') {
			for (i = 1; i <= 3; i++)Tf[n][i - 1] = atof(buf[i]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'i' && buf[0][2] == 'l') {
			illum[n] = atoi(buf[1]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'K' && buf[0][2] == 'a') {
			for (i = 1; i <= 3; i++)Ka[n][i - 1] = atof(buf[i]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'K' && buf[0][2] == 'd') {
			for (i = 1; i <= 3; i++)Kd[n][i - 1] = atof(buf[i]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'K' && buf[0][2] == 's') {
			for (i = 1; i <= 3; i++)Ks[n][i - 1] = atof(buf[i]);
		}
		else if (buf[0][0] == '\t' && buf[0][1] == 'K' && buf[0][2] == 'e') {
			for (i = 1; i <= 3; i++)Ke[n][i - 1] = atof(buf[i]);
		}
	}
}

void mtl::print()
{
	int i;
	for (i = 0; i <= n; i++) {
		cout << "name:" << name[i] <<endl;
		cout << "Ns:" << Ns[i] << endl;
		cout << "Ni:" << Ni[i] << endl;
		cout << "d:" << d[i] << endl;
		cout << "Tr:" << Tr[i] << endl;
		cout << "Tf:" << Tf[i][0] << " " << Tf[i][1] << " " << Tf[i][2] << " " << endl;
		cout << "illum:" << illum[i] << endl;
		cout << "Ka:" << Ka[i][0] << " " << Ka[i][1] << " " << Ka[i][2] << " " << endl;
		cout << "Kd:" << Kd[i][0] << " " << Kd[i][1] << " " << Kd[i][2] << " " << endl;
		cout << "Ks:" << Ks[i][0] << " " << Ks[i][1] << " " << Ks[i][2] << " " << endl;
		cout << "Ke:" << Ke[i][0] << " " << Ke[i][1] << " " << Ke[i][2] << " " << endl;
		cout << endl;
	}
}