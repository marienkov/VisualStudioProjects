#include "stdafx.h"
#include "CppUnitTest.h"
#include <FormsOpenGL\Button.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFormsOpenGL
{		
	TEST_CLASS(UnitMatrix)
	{
	public:
		
		TEST_METHOD(MatrixDimension)
		{
			Matrix testMatrix;
			Assert::AreEqual(4, testMatrix.DIMENSION);
		}

	};
}