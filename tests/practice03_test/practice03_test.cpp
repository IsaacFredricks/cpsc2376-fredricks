#include "pch.h"
#include "CppUnitTest.h"
#include "../../practice/practice03/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
	TEST_CLASS(practice03test)
	{
	public:
		
		TEST_METHOD(TestSumRange1)
		{
			Assert::AreEqual(21, MathUtils::sumRange(0, 6));

		}

		TEST_METHOD(TestSumRange2)
		{
			Assert::AreEqual(0, MathUtils::sumRange(-5, 5));
		}

		TEST_METHOD(TestSumRange3)
		{
			Assert::AreEqual(-21, MathUtils::sumRange(-6, 0));
		}

		TEST_METHOD(TestContainsNegative1)
		{
			std::vector<int> allPositive{ 1, 2, 3, 4 };

			Assert::IsFalse(MathUtils::containsNegative(allPositive));
		}

		TEST_METHOD(TestContainsNegative2)
		{
			std::vector<int> allNegative{ -44, -10, -11, -22 };

			Assert::IsTrue(MathUtils::containsNegative(allNegative));
			
		}

		TEST_METHOD(TestContainsNegative3)
		{
			std::vector<int> mixedVec{ 1, -1, 2, -3 };

			Assert::IsTrue(MathUtils::containsNegative(mixedVec));
		}

		TEST_METHOD(TestContainsNegative4)
		{
			std::vector<int> emptyVec{};

			Assert::IsFalse(MathUtils::containsNegative(emptyVec));
		}
		
		TEST_METHOD(TestFindMax1)
		{
			std::vector<int> sameNums{1, 1, 1, 1};

			Assert::AreEqual(1, MathUtils::findMax(sameNums));
		}

		TEST_METHOD(TestFindMax2)
		{
			std::vector<int> emptyVector{};

			auto funct = [] {MathUtils::findMax(emptyVector)};

			Assert::ExpectException<std::invalid_argument>(funct);
		}

		TEST_METHOD(TestFindMax3)
		{
			std::vector<int> mixedNums{-11, 33, 1, 4};

			Assert::AreEqual(33, MathUtils::findMax(mixedNums));
		}





	};
}
