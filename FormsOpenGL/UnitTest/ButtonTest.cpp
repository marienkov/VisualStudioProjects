#include "stdafx.h"
#include "CppUnitTest.h"
#include <Button.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ButtonTest)
	{
	public:

		TEST_METHOD(IdTest)
		{
			Button b1;
			Assert::AreEqual(true, b1.getId().empty());

			std::string name = "id";
			std::string buttonName = "id";
			Button b2(buttonName);
			Assert::AreEqual(0, b2.getId().compare(name));

			std::string name2 = "id2";
			std::string buttonName2 = "id2";
			Button b3;
			b3.setId(buttonName2);
			Assert::AreEqual(0, b3.getId().compare(name2));
		}
	};
}