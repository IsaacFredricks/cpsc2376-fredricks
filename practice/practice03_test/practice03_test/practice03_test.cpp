#include "pch.h"
#include "../../practice/practice03/mathyStuff.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
	TEST_CLASS(practice03test)
	{
	public:

		TEST_METHOD(TestingAdd1)
		{
			Assert::AreEqual(5, add(2, 3));
		}

		TEST_METHOD(TestAdd2)
		{
			Assert::AreEqual(5, add(3, 1);
		}

		TEST_METHOD(TestRect1)
		{
			Rectangle r{ 3, 4 };
			Assert::AreEqual(12, r.area());

			rect.width++; 

			Assert::AreEqual(16, r.area());
		}
	};
}