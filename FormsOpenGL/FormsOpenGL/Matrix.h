#pragma once

template<class T>
class Matrix
{
public:
	Matrix(int, int);
	Matrix(T* matrix,int, int);
	virtual ~Matrix();

	void loadIdentityMatrix();
	T* getDataPointer() const;
	Matrix<T>* operator*(const Matrix<T> *matrix) const;
	Matrix<T>* operator*(const Matrix<T> &matrix) const;
	Matrix<T>* operator+(const Matrix<T> *matrix) const;
	Matrix<T>* operator+(const Matrix<T> &matrix) const;
	Matrix<T>* multiply(const Matrix<T>* matrix);
	Matrix<T>* multiply(const Matrix<T>& matrix);
	void add(const Matrix<T>* matrix);
	void add(const Matrix<T>& matrix);
	void reset(T* newData, int row, int col);
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
			else
				data[i*col + j] = 0;
}

template<class T>
T* Matrix<T>::getDataPointer() const{
	return data;
}

template<class T>
Matrix<T>* Matrix<T>::operator*(const Matrix<T>* matrix) const {
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
Matrix<T>* Matrix<T>::operator*(const Matrix<T>& matrix) const {
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
Matrix<T>* Matrix<T>::multiply(const Matrix<T>* matrix) {
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
	return this;
}

template<class T>
Matrix<T>* Matrix<T>::multiply(const Matrix<T>& matrix) {
	int col2 = matrix.col;
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
	delete[] data;
	data = tempMatrix;
	return this;
}

template<class T>
Matrix<T>* Matrix<T>::operator+(const Matrix<T>* matrix) const {
	T* tempMatrix = new T[row*col];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col2; ++j) {
			tempMatrix[i*col + j] = data[i*col + j] + matrix->data[i*col + j];
		}
	}
	return new Matrix<T>(tempMatrix, row, col);
}

template<class T>
Matrix<T>* Matrix<T>::operator+(const Matrix<T>& matrix) const {
	T* tempMatrix = new T[row*col];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col2; ++j) {
			tempMatrix[i*col + j] = data[i*col + j] + matrix.data[i*col + j];
		}
	}
	return new Matrix<T>(tempMatrix, row, col);
}

template<class T>
void Matrix<T>::add(const Matrix<T>* matrix) {
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col2; ++j)
			data[i*col + j] += matrix->data[i*col + j];
}

template<class T>
void Matrix<T>::add(const Matrix<T>& matrix) {
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col2; ++j)
			data[i*col + j] += matrix.data[i*col + j];
}

template<class T>
void Matrix<T>::reset(T* newData, int row, int col) {
	delete[] data;
	this->row = row;
	this->col = col;
	data = newData;
}