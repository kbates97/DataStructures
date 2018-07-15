#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Array2DP.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(Array2DPTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(TestAssignmentConstructor)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			Array2DP<int> array(2, 3);

			// Assert
			Assert::AreEqual(2, array.GetRow(), L"Number of rows not equal");
			Assert::AreEqual(3, array.GetColumn(), L"Number of columns not equal");
		}

		TEST_METHOD(TestCopyConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array2DP<int> array(5, 5);
			for (size_t i = 0; i < 5; ++i)
			{
				for (size_t k = 0; k < 5; ++k)
				{
					array[i][k] = i * k;
				}
			}

			Array2DP<int> arrayCopy(array);

			Assert::AreEqual(5, arrayCopy.GetRow(), L"Number of rows not equal");
			Assert::AreEqual(5, arrayCopy.GetColumn(), L"Number of columns not equal");
			for (size_t i = 0; i < 5; i++)
			{
				for (size_t k = 0; k < 5; k++)
				{
					Assert::AreEqual((int)i * (int)k, arrayCopy[i][k], L"Data does not match");
				}
			}
		}

		TEST_METHOD(TestAssignmentOperator_Sunny)
		{
			CrtCheckMemory check;
			Array2DP<int> array(5, 5);
			Array2DP<int> arrayCopy;
			for (size_t i = 0; i < 5; ++i)
			{
				for (size_t k = 0; k < 5; ++k)
				{
					array[i][k] = i * k;
				}
			}

			arrayCopy = array;

			Assert::AreEqual(5, arrayCopy.GetRow(), L"Number of rows not equal");
			Assert::AreEqual(5, arrayCopy.GetColumn(), L"Number of columns not equal");
			for (size_t i = 0; i < 5; i++)
			{
				for (size_t k = 0; k < 5; k++)
				{
					Assert::AreEqual((int)i * (int)k, arrayCopy[i][k], L"Data does not match");
				}
			}
		}

		TEST_METHOD(TestMoveConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array2DP<int> array1(3, 4);
			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 4; ++k)
				{
					array1[i][k] = i * k;
				}
			}

			Array2DP<int> array2(std::move(array1));

			Assert::AreEqual(3, array2.GetRow(), L"Number of rows not equal");
			Assert::AreEqual(4, array2.GetColumn(), L"Number of columns not equal");
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t k = 0; k < 4; k++)
				{
					Assert::AreEqual((int)i * (int)k, array2[i][k], L"Data does not match");
				}
			}
		}

		TEST_METHOD(TestMoveOperator_Sunny)
		{
			CrtCheckMemory check;
			Array2DP<int> array1(3, 4);
			Array2DP<int> array2;
			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 4; ++k)
				{
					array1[i][k] = i * k;
				}
			}

			array2 = std::move(array1);

			Assert::AreEqual(3, array2.GetRow(), L"Number of rows not equal");
			Assert::AreEqual(4, array2.GetColumn(), L"Number of columns not equal");
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t k = 0; k < 4; k++)
				{
					Assert::AreEqual((int)i * (int)k, array2[i][k], L"Data does not match");
				}
			}
		}

		TEST_METHOD(TestSelectMutable_Sunny)
		{
			Array2DP<int> array(3, 4);

			array.Select(1, 2) = 75;

			Assert::AreEqual(75, array.Select(1, 2));
		}

		TEST_METHOD(TestSelectConst_Sunny)
		{
			Array2DP<int> array(2, 3);
			array.Select(1, 2) = 26;

			const Array2DP<int> arrayConst(array);

			Assert::AreEqual(26, arrayConst.Select(1, 2));
		}

		TEST_METHOD(TestBracketOperator_Sunny)
		{
			Array2DP<int> array(3, 4);

			array[1][3] = 12;

			Assert::AreEqual(12, array[1][3]);
		}

		TEST_METHOD(TestBracketOperatorConst_Sunny)
		{
			Array2DP<int> array(3, 4);
			array[1][3] = 12;

			const Array2DP<int> arrayConst(array);

			Assert::AreEqual(12, arrayConst[1][3]);
		}

		TEST_METHOD(TestGetRow_Sunny)
		{
			Array2DP<int> array(3, 4);

			int row = array.GetRow();

			Assert::AreEqual(3, row);
		}

		TEST_METHOD(TestGetColumn_Sunny)
		{
			Array2DP<int> array(3, 4);

			int col = array.GetColumn();

			Assert::AreEqual(4, col);
		}

		TEST_METHOD(TestSetRow_Sunny)
		{
			Array2DP<int> array(3, 5);

			array.SetRow(2);

			Assert::AreEqual(2, array.GetRow());
		}

		TEST_METHOD(TestSetColumn_Sunny)
		{
			Array2DP<int> array(3, 5);

			array.SetColumn(2);

			Assert::AreEqual(2, array.GetColumn());
		}
	};
}