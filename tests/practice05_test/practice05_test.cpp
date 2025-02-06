#include "pch.h"
#include "CppUnitTest.h"
#include "../../practice/practice03/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice05test
{
	TEST_CLASS(practice05test)
	{
	public:
		
		TEST_METHOD(testAdd1)
		{
			Assert::AreEqual(5, add(2, 3));
		}
	};
}
