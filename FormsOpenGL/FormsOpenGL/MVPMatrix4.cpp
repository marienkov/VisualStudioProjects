#include "MVPMatrix4.h"


MVPMatrix4::MVPMatrix4() : changed(true)
{
	model4 = new float[16]      {1,0,0,0,   0,1,0,0,	0,0,1,0,	0,0,0,1};
	view4 = new float[16]       {1,0,0,0,	0,1,0,0,	0,0,1,0,	0,0,0,1};
	projection4 = new float[16] {1,0,0,0,	0,1,0,0,	0,0,1,0,	0,0,0,1};
	MVP4 = new float[16]        {1,0,0,0,	0,1,0,0,	0,0,1,0,	0,0,0,1};
}
MVPMatrix4::~MVPMatrix4()
{
	delete[] model4;
	delete[] view4;
	delete[] projection4;
	delete[] MVP4;
}

float* MVPMatrix4::getCurrentModelMatrix4(){
	return model4;
}

float* MVPMatrix4::getCurrentViewMatrix4(){
	return view4;
}

float* MVPMatrix4::getCurrentProjectionMatrix4(){
	return projection4;
}

float* MVPMatrix4::getCurrentMVP4() {
	if (changed) {
		float temp4[16];
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				temp4[i * 4 + j] = view4[i * 4] * projection4[j] + view4[i * 4 + 1] * projection4[j + 4]
					+ view4[i * 4 + 2] * projection4[j + 8] + view4[i * 4 + 3] * projection4[j + 12];
			}
		}
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				MVP4[i * 4 + j] = model4[i * 4] * temp4[j] + model4[i * 4 + 1] * temp4[j + 4]
					+ model4[i * 4 + 2] * temp4[j + 8] + model4[i * 4 + 3] * temp4[j + 12];
			}
		}
	}
	return MVP4;
}

void MVPMatrix4::makeIdentityMatrix4(float* matrix4) {
	changed = true;
	matrix4[0]  = 1;  matrix4[1]  = 0;  matrix4[2]  = 0;  matrix4[3]  = 0;
	matrix4[4]  = 0;  matrix4[5]  = 1;  matrix4[6]  = 0;  matrix4[7]  = 0;
	matrix4[8]  = 0;  matrix4[9]  = 0;	matrix4[10] = 1;  matrix4[11] = 0;
	matrix4[12] = 0;  matrix4[13] = 0;	matrix4[14] = 0;  matrix4[15] = 1;
}

void MVPMatrix4::translateModel4(const float(&translation)[4]) {
	changed = true;
	model4[3]  = model4[3] + translation[0];
	model4[7]  = model4[7] + translation[1];
	model4[11] = model4[11] + translation[2];
	model4[15] = model4[15] + translation[3];
}

void MVPMatrix4::scaleModel4(const float(&translation)[4]) {
	changed = true;
	model4[0]  = model4[0]  * translation[0];
	model4[5]  = model4[5]  * translation[1];
	model4[10] = model4[10] * translation[2];
	model4[15] = model4[15] * translation[3];
}

void MVPMatrix4::rotateModel4(const float(&rotate4)[4]) {
	changed = true;
}