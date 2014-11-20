#include "Matrix.h"

Matrix::Matrix() {
	for (int i = 0; i < DIMENSION; ++i)
		for (int j = 0; j < DIMENSION; ++j)
			if (i == j)
				data[i*DIMENSION + j] = 1;
			else
				data[i*DIMENSION + j] = 0;
}

Matrix::Matrix(const float newData[DIMENSION*DIMENSION]) {
	for (int i = 0; i < DIMENSION; ++i)
		for (int j = 0; j < DIMENSION; ++j)
			data[i*DIMENSION + j] = newData[i*DIMENSION + j];
}

Matrix::Matrix(const Matrix& copyMatrix) {
	for (int i = 0; i < DIMENSION; ++i)
		for (int j = 0; j < DIMENSION; ++j)
			data[i*DIMENSION + j] = copyMatrix.data[i*DIMENSION + j];
}

Matrix::~Matrix() {
}

void Matrix::resetData(const float newData[DIMENSION*DIMENSION]) {
	for (int i = 0; i < DIMENSION; ++i)
		for (int j = 0; j < DIMENSION; ++j)
			data[i*DIMENSION + j] = newData[i*DIMENSION + j];
}

void Matrix::operator*(const Matrix& matrix) {
	float newMatrix[DIMENSION*DIMENSION];
	for (int i = 0; i < DIMENSION; ++i) {
		for (int j = 0; j < DIMENSION; ++j) {
			float tempElement = 0;
			for (int k = 0; k < DIMENSION; ++k) {
				tempElement += data[i * DIMENSION + k] * matrix.data[k * DIMENSION + j];
			}
			newMatrix[i*DIMENSION + j] = tempElement;
		}
	}
	resetData(newMatrix);
}

void Matrix::operator*(const float mult[DIMENSION*DIMENSION]) {
	float newMatrix[DIMENSION*DIMENSION];
	for (int i = 0; i < DIMENSION; ++i) {
		for (int j = 0; j < DIMENSION; ++j) {
			float tempElement = 0;
			for (int k = 0; k < DIMENSION; ++k) {
				tempElement += data[i * DIMENSION + k] * mult[k * DIMENSION + j];
			}
			newMatrix[i*DIMENSION + j] = tempElement;
		}
	}
	resetData(newMatrix);
}

void Matrix::translate(float x = 0, float y = 0, float z = 0) {
	data[DIMENSION - 1] = x;
	data[2 * DIMENSION - 1] = y;
	data[3 * DIMENSION - 1] = z;
}

void Matrix::rotate(float angleX = 0, float angleY = 0, float angleZ = 0) {
	float rotateX[DIMENSION*DIMENSION] = {
		1, 0, 0, 0,
		0, cos(angleX), -sin(angleX), 0,
		0, sin(angleX), cos(angleX), 0,
		0, 0, 0, 1 };
	float rotateY[DIMENSION*DIMENSION] = {
		cos(angleY), 0, sin(angleY), 0,
		0, 1, 0, 0,
		-sin(angleY), 0, cos(angleY), 0,
		0, 0, 0, 1 };
	float rotateZ[DIMENSION*DIMENSION] = {
		cos(angleZ), -sin(angleZ), 0, 0,
		sin(angleZ), cos(angleZ), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	(*this)*(rotateX);
	(*this)*(rotateY);
	(*this)*(rotateZ);
}

void Matrix::scale(float sX = 0, float sY = 0, float sZ = 0) {
	data[0] = sX;
	data[DIMENSION + 1] = sY;
	data[2 * DIMENSION + 2] = sZ;
}

float* Matrix::getData() const {
	return (float*)data;
}