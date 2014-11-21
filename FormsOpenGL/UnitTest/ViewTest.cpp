#include "stdafx.h"
#include "CppUnitTest.h"
#include <Rectangle2D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(ViewTest) {
	public:

		float PRECISION = 10.0f;

		TEST_METHOD(ViewIdTest)	{
			Rectangle2D b1;
			Assert::AreEqual(true, b1.getId().empty());

			std::string name = "id";
			std::string rectanlgeName = "id";
			Rectangle2D b2(rectanlgeName);
			Assert::AreEqual(0, b2.getId().compare(name));

			std::string name2 = "id2";
			std::string rectanlgeName2 = "id2";
			Rectangle2D b3;
			b3.setId(rectanlgeName2);
			Assert::AreEqual(0, b3.getId().compare(name2));
		}

		TEST_METHOD(ViewSetCoordinatesTest)	{
			Rectangle2D b1;
			const int positionCount = 4;
			View::VertexPosition position[positionCount];
			for (int i = 0; i < positionCount; ++i)
				position[i] = View::VertexPosition(std::rand() / PRECISION, std::rand() / PRECISION, std::rand() / PRECISION);
			b1.setCoordinates(position[0], position[1], position[2], position[3]);
			auto* rectanlgePosition = b1.getVertexPosition();

			int positioneSize = sizeof(View::VertexPosition) / sizeof(*rectanlgePosition);

			for (int i = 0; i < positionCount; ++i) {
				for (int j = 0; j < positioneSize; ++j)
					Assert::AreEqual(position[i].position[j], rectanlgePosition[i * positioneSize + j]);
			}

		}

		TEST_METHOD(ViewAtributeCountTest) {
			Rectangle2D b1;
			Assert::AreEqual(b1.getVertexIndexCount(), b1.getVertexNormalsCount());
		}

		TEST_METHOD(ViewColorTest) {
			Rectangle2D view;
			float testColor[] = { (std::rand() / PRECISION), std::rand() / PRECISION, std::rand() / PRECISION, std::rand() / PRECISION };
			view.setColor(testColor[0], testColor[1], testColor[2], testColor[3]);
			
			float* viewColor = view.getVertexColors();
			int colorCount = 4;

			for (int i = 0; i < colorCount; ++i)
				Assert::AreEqual(testColor[i], view.getVertexColors()[i]);
		}

		TEST_METHOD(ViewMoveTest) {
			Rectangle2D view;

			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;

			float dx = std::rand() / PRECISION;
			float dy = std::rand() / PRECISION;
			float dz = std::rand() / PRECISION;

			view.move(dx, dy, dz);
			float* viewMatrix = view.getModelMatrixData();

			Matrix m;
			m.translate(dx, dy, dz);
			float* testData = m.getData();

			for (int i = 0; i < dataSize; ++i)
				Assert::AreEqual(*(viewMatrix + i), testData[i]);
		}

		TEST_METHOD(ViewScaleTest) {
			Rectangle2D view;

			const int dataSize = Matrix::DIMENSION * Matrix::DIMENSION;

			float x = std::rand() / PRECISION;
			float y = std::rand() / PRECISION;
			float z = std::rand() / PRECISION;

			view.scale(x, y, z);
			float* viewMatrix = view.getModelMatrixData();

			Matrix m;
			float* testData = m.getData();
			testData[0] = x;
			testData[Matrix::DIMENSION + 1] = y;
			testData[2 * Matrix::DIMENSION + 2] = z;

			for (int i = 0; i < dataSize; ++i)
				Assert::AreEqual(*(viewMatrix + i), testData[i]);
		}
	};
}