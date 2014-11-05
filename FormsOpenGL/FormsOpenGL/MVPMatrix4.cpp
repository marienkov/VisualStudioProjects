#include "MVPMatrix4.h"


MVPMatrix4::MVPMatrix4() : changed(true)
{
	modelTransfer4 = new Matrix<float>(4,4);
	modelTransfer4->loadIdentityMatrix();
	modelScaling4 = new Matrix<float>(4, 4);
	modelScaling4->loadIdentityMatrix();
	modelRotating4 = new Matrix<float>(4, 4);
	modelRotating4->loadIdentityMatrix();
	modelTransform4 = new Matrix<float>(4, 4);
	modelTransform4->loadIdentityMatrix();

	viewTransform4 = new Matrix<float>(4, 4);
	viewTransform4->loadIdentityMatrix();

	projectionTransform4 = new Matrix<float>(4, 4);
	projectionTransform4->loadIdentityMatrix();
	MVP4 = new Matrix<float>(4, 4);
	MVP4->loadIdentityMatrix();
}
MVPMatrix4::~MVPMatrix4()
{
	delete[] modelTransfer4;
	delete[] modelScaling4;
	delete[] modelRotating4;
	delete[] modelTransform4;

	delete[] viewTransform4;
	delete[] projectionTransform4;
	delete[] MVP4;
}

Matrix<float>* MVPMatrix4::getModelRotating4(){
	return modelRotating4;
}

Matrix<float>* MVPMatrix4::getModelScaling4(){
	return modelScaling4;
}

Matrix<float>* MVPMatrix4::getModelTransfer4(){
	return modelTransfer4;
}

Matrix<float>* MVPMatrix4::getModelTransform4(){
	delete modelTransform4;
	modelTransform4 = *((*modelRotating4) * (modelTransfer4)) * (modelScaling4);
	return modelTransform4;
}

Matrix<float>* MVPMatrix4::getViewTransform4(){
	return viewTransform4;
}

Matrix<float>* MVPMatrix4::getProjectionTransfor4(){
	return projectionTransform4;
}

Matrix<float>* MVPMatrix4::getMVPTransform4() {
	delete MVP4;
	MVP4 = *((*projectionTransform4) * (viewTransform4)) * (getModelTransform4());
	return MVP4;
}

/*void MVPMatrix4::translateModel4(const float(&translation)[4]) {
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

void MVPMatrix4::rotateModel4(float angleX, float angleY, float angleZ) {
	changed = true;
	model4[0] = 1;		model4[1] = 0;				model4[2] = 0;				model4[3] = 0;
	model4[4] = 0;		model4[5] = cos(angleX);	model4[6] = -sin(angleX);	model4[7] = ;
	model4[8] = 0;		model4[9] = sin(angleX);	model4[10] = cos(angleX);	model4[11] = ;
	model4[12] = 0;		model4[13] = ;				model4[14] = ;				model4[15] = ;

	model4[0] = ;		model4[1] = ;		model4[2] = ;		model4[3] = ;
	model4[4] = ;		model4[5] = ;		model4[6] = ;		model4[7] = ;
	model4[8] = ;		model4[9] = ;		model4[10] = ;		model4[11] = ;
	model4[12] = ;		model4[13] = ;		model4[14] = ;		model4[15] = ;

	model4[0] = ;		model4[1] = ;		model4[2] = ;		model4[3] = ;
	model4[4] = ;		model4[5] = ;		model4[6] = ;		model4[7] = ;
	model4[8] = ;		model4[9] = ;		model4[10] = ;		model4[11] = ;
	model4[12] = ;		model4[13] = ;		model4[14] = ;		model4[15] = ;
}*/