#include "stdafx.h"
#include "CppUnitTest.h"
#include <Matrix.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {		
	TEST_CLASS(MatrixTest) {
	public:
		
		float PRECISION = 10.0f;

		TEST_METHOD(MatrixDimensionTest) {
			int requredDimension = 4;
			Matrix matrix;
			Assert::AreEqual(requredDimension, matrix.DIMENSION);
		}

		TEST_METHOD(MatrixArgumentConstructorTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData[dataSize];
			for (int i = 0; i < dataSize; ++i)
				testData[i] = std::rand() / PRECISION;
			Matrix matrix(testData);
			float* matrixData = matrix.getData();
			for (int i = 0; i < dataSize; ++i) {
				Assert::AreEqual(testData[i], matrixData[i]);
				Assert::AreNotSame(&testData[i], matrixData + i);
			}
		}

		TEST_METHOD(MatrixCopyConstructorTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData[dataSize];
			for (int i = 0; i < dataSize; ++i)
				testData[i] = std::rand() / PRECISION;
			Matrix m1(testData);
			Matrix m2 = m1;

			float* m1Data = m1.getData();
			float* m2Data = m2.getData();
			
			for (int i = 0; i < dataSize; ++i) {
				Assert::AreEqual(*(m1Data+i), *(m2Data+i));
				Assert::AreNotSame(m1Data + i, m2Data + i);
			}
		}

		TEST_METHOD(MatrixResetDataTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData[dataSize];
			for (int i = 0; i < dataSize; ++i)
				testData[i] = std::rand() / PRECISION;
			Matrix matrix;
			matrix.resetData(testData);
			float* matrixData = matrix.getData();

			for (int i = 0; i < dataSize; ++i) {
				Assert::AreEqual(testData[i], matrixData[i]);
				Assert::AreNotSame(&testData[i], matrixData + i);
			}
		}

		TEST_METHOD(MatrixMultiOperatorMatrixTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData1[dataSize];
			float testData2[dataSize];
			for (int i = 0; i < dataSize; ++i) {
				testData1[i] = std::rand() / PRECISION;
				testData2[i] = std::rand() / PRECISION;
			}

			Matrix m1(testData1);
			Matrix m2(testData2);

			m1*m2;

			float expectedData[dataSize] {
				testData1[0] * testData2[0] + testData1[1] * testData2[4] + testData1[2] * testData2[8] + testData1[3] * testData2[12],
				testData1[0] * testData2[1] + testData1[1] * testData2[5] + testData1[2] * testData2[9] + testData1[3] * testData2[13],
				testData1[0] * testData2[2] + testData1[1] * testData2[6] + testData1[2] * testData2[10] + testData1[3] * testData2[14],
				testData1[0] * testData2[3] + testData1[1] * testData2[7] + testData1[2] * testData2[11] + testData1[3] * testData2[15],

				testData1[4] * testData2[0] + testData1[5] * testData2[4] + testData1[6] * testData2[8] + testData1[7] * testData2[12],
				testData1[4] * testData2[1] + testData1[5] * testData2[5] + testData1[6] * testData2[9] + testData1[7] * testData2[13],
				testData1[4] * testData2[2] + testData1[5] * testData2[6] + testData1[6] * testData2[10] + testData1[7] * testData2[14],
				testData1[4] * testData2[3] + testData1[5] * testData2[7] + testData1[6] * testData2[11] + testData1[7] * testData2[15],

				testData1[8] * testData2[0] + testData1[9] * testData2[4] + testData1[10] * testData2[8] + testData1[11] * testData2[12],
				testData1[8] * testData2[1] + testData1[9] * testData2[5] + testData1[10] * testData2[9] + testData1[11] * testData2[13],
				testData1[8] * testData2[2] + testData1[9] * testData2[6] + testData1[10] * testData2[10] + testData1[11] * testData2[14],
				testData1[8] * testData2[3] + testData1[9] * testData2[7] + testData1[10] * testData2[11] + testData1[11] * testData2[15],

				testData1[12] * testData2[0] + testData1[13] * testData2[4] + testData1[14] * testData2[8] + testData1[15] * testData2[12],
				testData1[12] * testData2[1] + testData1[13] * testData2[5] + testData1[14] * testData2[9] + testData1[15] * testData2[13],
				testData1[12] * testData2[2] + testData1[13] * testData2[6] + testData1[14] * testData2[10] + testData1[15] * testData2[14],
				testData1[12] * testData2[3] + testData1[13] * testData2[7] + testData1[14] * testData2[11] + testData1[15] * testData2[15],
			};

			float* m1Data = m1.getData();
			float* m2Data = m2.getData();

			for (int i = 0; i < dataSize; ++i) {
				Assert::AreEqual(*(m1Data + i), expectedData[i]);
				Assert::AreEqual(testData2[i], *(m2Data + i));
				Assert::AreNotSame(m1Data + i, m2Data + i);
			}
		}

		TEST_METHOD(MatrixMultiOperatorArrayTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData1[dataSize];
			float testData2[dataSize];
			for (int i = 0; i < dataSize; ++i) {
				testData1[i] = std::rand() / PRECISION;
				testData2[i] = std::rand() / PRECISION;
			}

			Matrix m(testData1);

			m*testData2;

			float expectedData[dataSize] {
				testData1[0] * testData2[0] + testData1[1] * testData2[4] + testData1[2] * testData2[8] + testData1[3] * testData2[12],
				testData1[0] * testData2[1] + testData1[1] * testData2[5] + testData1[2] * testData2[9] + testData1[3] * testData2[13],
				testData1[0] * testData2[2] + testData1[1] * testData2[6] + testData1[2] * testData2[10] + testData1[3] * testData2[14],
				testData1[0] * testData2[3] + testData1[1] * testData2[7] + testData1[2] * testData2[11] + testData1[3] * testData2[15],

				testData1[4] * testData2[0] + testData1[5] * testData2[4] + testData1[6] * testData2[8] + testData1[7] * testData2[12],
				testData1[4] * testData2[1] + testData1[5] * testData2[5] + testData1[6] * testData2[9] + testData1[7] * testData2[13],
				testData1[4] * testData2[2] + testData1[5] * testData2[6] + testData1[6] * testData2[10] + testData1[7] * testData2[14],
				testData1[4] * testData2[3] + testData1[5] * testData2[7] + testData1[6] * testData2[11] + testData1[7] * testData2[15],

				testData1[8] * testData2[0] + testData1[9] * testData2[4] + testData1[10] * testData2[8] + testData1[11] * testData2[12],
				testData1[8] * testData2[1] + testData1[9] * testData2[5] + testData1[10] * testData2[9] + testData1[11] * testData2[13],
				testData1[8] * testData2[2] + testData1[9] * testData2[6] + testData1[10] * testData2[10] + testData1[11] * testData2[14],
				testData1[8] * testData2[3] + testData1[9] * testData2[7] + testData1[10] * testData2[11] + testData1[11] * testData2[15],

				testData1[12] * testData2[0] + testData1[13] * testData2[4] + testData1[14] * testData2[8] + testData1[15] * testData2[12],
				testData1[12] * testData2[1] + testData1[13] * testData2[5] + testData1[14] * testData2[9] + testData1[15] * testData2[13],
				testData1[12] * testData2[2] + testData1[13] * testData2[6] + testData1[14] * testData2[10] + testData1[15] * testData2[14],
				testData1[12] * testData2[3] + testData1[13] * testData2[7] + testData1[14] * testData2[11] + testData1[15] * testData2[15],
			};

			float* mData = m.getData();

			for (int i = 0; i < dataSize; ++i) {
				Assert::AreEqual(*(mData + i), expectedData[i]);
				Assert::AreNotSame(mData + i, expectedData + i);
			}
		}

		TEST_METHOD(MatrixTranslateTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData[dataSize];

			for (int i = 0; i < dataSize; ++i)
				testData[i] = std::rand() / PRECISION;

			float x = std::rand() / PRECISION;
			float y = std::rand() / PRECISION;
			float z = std::rand() / PRECISION;

			Matrix m(testData);
			testData[Matrix::DIMENSION - 1] = x;
			testData[2 * Matrix::DIMENSION - 1] = y;
			testData[3 * Matrix::DIMENSION - 1] = z;

			m.translate(x,y,z);

			float* mData = m.getData();

			for (int i = 0; i < dataSize; ++i)
				Assert::AreEqual(*(mData + i), testData[i]);
		}

		TEST_METHOD(MatrixScaleTest) {
			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;
			float testData[dataSize];

			for (int i = 0; i < dataSize; ++i)
				testData[i] = std::rand() / PRECISION;

			float x = std::rand() / PRECISION;
			float y = std::rand() / PRECISION;
			float z = std::rand() / PRECISION;

			Matrix m(testData);
			testData[0] = x;
			testData[Matrix::DIMENSION + 1] = y;
			testData[2 * Matrix::DIMENSION + 2] = z;

			m.scale(x, y, z);

			float* mData = m.getData();

			for (int i = 0; i < dataSize; ++i)
				Assert::AreEqual(*(mData + i), testData[i]);
		}

	};
}