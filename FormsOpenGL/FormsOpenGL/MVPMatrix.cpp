#include "MVPMatrix.h"


MVPMatrix::MVPMatrix()
{
}


MVPMatrix::~MVPMatrix()
{
}

float* MVPMatrix::getCurrentMVP(){
	return MVP[0];
}

void MVPMatrix::makeIdentityMatrix() {
	MVP[0][0] = 1; MVP[0][1] = 0; MVP[0][2] = 0; MVP[0][3] = 0;
	MVP[1][0] = 0; MVP[1][1] = 1;	MVP[1][2] = 0; MVP[1][3] = 0;
	MVP[2][0] = 0; MVP[2][1] = 0;	MVP[2][2] = 1; MVP[2][3] = 0;
	MVP[3][0] = 0; MVP[3][1] = 0;	MVP[3][2] = 0; MVP[3][3] = 1;
}

void MVPMatrix::translateMVP(const float(&translation)[4]) {
	MVP[3][0] = MVP[3][0] + translation[0];
	MVP[3][1] = MVP[3][1] + translation[1];
	MVP[3][2] = MVP[3][2] + translation[2];
	MVP[3][3] = MVP[3][3] + translation[3];
}

void MVPMatrix::scaleMVP(const float(&translation)[4]) {
	MVP[0][0] = MVP[0][0] * translation[0];
	MVP[1][1] = MVP[1][1] * translation[1];
	MVP[2][2] = MVP[2][2] * translation[2];
	MVP[3][3] = MVP[3][3] * translation[3];
}