#pragma once
#include <cmath>

class Matrix
{
public:
	const static int DIMENSION = 4;

	Matrix();
	Matrix(float newData[DIMENSION*DIMENSION]);
	Matrix(const Matrix& copyMatrix);
	virtual ~Matrix();

	void resetData(const float newData[DIMENSION*DIMENSION]);
	void operator*(const Matrix& matrix);
	void operator*(const float mult[DIMENSION*DIMENSION]);

	void translate(float x, float y, float z);
	void rotate(float angleX, float angleY, float angleZ);
	void scale(float sX, float sY, float sZ);

	float* getData() const;
private:
	float data[DIMENSION*DIMENSION];
};