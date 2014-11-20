#include "stdafx.h"
#include "CppUnitTest.h"
#include <Matrix.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(MatrixTest)
	{
	public:
		
		TEST_METHOD(DimensionTest)
		{
			int requredDimension = 4;
			Matrix matrix;
			Assert::AreEqual(requredDimension, matrix.DIMENSION);
		}

	};
}