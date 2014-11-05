#pragma once
#include <cmath>
#include "Matrix.h"

class MVPMatrix4
{
public:
	MVPMatrix4();
	virtual ~MVPMatrix4();

	Matrix<float>* getModelTransfer4();
	Matrix<float>* getModelScaling4();
	Matrix<float>* getModelRotating4();
	Matrix<float>* getModelTransform4();

	Matrix<float>* getViewTransform4();
	Matrix<float>* getProjectionTransfor4();
	Matrix<float>* getMVPTransform4();
	
	//void translateModel4(const float(&translation4)[4]);
	//void scaleModel4(const float(&scale4)[4]);
	//void rotateModel4(float angleX, float angleY, float angleZ);
private:
	bool changed;

	Matrix<float>* modelTransfer4;
	Matrix<float>* modelScaling4;
	Matrix<float>* modelRotating4;
	Matrix<float>* modelTransform4;

	Matrix<float>* viewTransform4;
	Matrix<float>* projectionTransform4;
	Matrix<float>* MVP4;
};

