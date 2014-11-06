#pragma once

template<class T>
class Matrix
{
public:
	Matrix(int, int);
	Matrix(T* matrix,int, int);
	virtual ~Matrix();

	void loadIdentityMatrix();
	T* getDataPointer();
	Matrix<T>* operator*(const Matrix<T> *matrix);
	Matrix<T>* operator*(const Matrix<T> &matrix);
	void multiply(const Matrix<T>* matrix);
private:
	int row, col, size;
	T* data;
};

template<class T>
Matrix<T>::Matrix(int rowCount, int colCount) : row(rowCount), col(colCount), size(rowCount * colCount), data(new T[rowCount * colCount])
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			data[i*col + j] = 0;
}

template<class T>
Matrix<T>::Matrix(T* matrix, int rowCount, int colCount) : row(rowCount), col(colCount), size(rowCount * colCount), data(matrix)
{
}

template<class T>
Matrix<T>::~Matrix()
{
	delete[] data;
}

template<class T>
void Matrix<T>::loadIdentityMatrix() {
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (i == j)
				data[i*col + j] = 1;
}

template<class T>
T* Matrix<T>::getDataPointer() {
	return data;
}

template<class T>
Matrix<T>* Matrix<T>::operator*(const Matrix<T>* matrix) {
	int col2 = matrix->col;
	int row2 = matrix->row;
	T* tempMatrix = new T[row*col2];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col2; ++j) {
			T temp = 0;
			for (int k = 0; k < row; ++k) {
				temp += data[i * col + k] * matrix->data[k * col2 + j];
			}
			tempMatrix[i*col2 + j] = temp;
		}
	}
	return new Matrix<T>(tempMatrix, row, col2);
}

template<class T>
Matrix<T>* Matrix<T>::operator*(const Matrix<T>& matrix) {
	int col2 = matrix.col;
	int row2 = matrix.row;
	T* tempMatrix = new T[row*col2];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col2; ++j) {
			T temp = 0;
			for (int k = 0; k < row; ++k) {
				temp += data[i * col + k] * matrix.data[k * col2 + j];
			}
			tempMatrix[i*col2 + j] = temp;
		}
	}
	return new Matrix<T>(tempMatrix, row, col2);
}

template<class T>
void Matrix<T>::multiply(const Matrix<T>* matrix) {
	int col2 = matrix->col;
	T* tempMatrix = new T[row*col2];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col2; ++j) {
			T temp = 0;
			for (int k = 0; k < row; ++k) {
				temp += data[i * col + k] * matrix->data[k * col2 + j];
			}
			tempMatrix[i*col2 + j] = temp;
		}
	}
	delete[] data;
	data = tempMatrix;
}