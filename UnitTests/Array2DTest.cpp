#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Array2D.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(Array2DTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(TestDefaultConstructor_Sunny)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			Array2D<int> array;


			// Assert
			Assert::AreEqual(1, array.GetRow(), L"row_ not equal 1");
			Assert::AreEqual(1, array.GetColumn(), L"col_ not equal 1");
		}

		TEST_METHOD(TestDefaultConstructor_Strings)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			Array2D<string> array;


			// Assert
			Assert::AreEqual(1, array.GetRow(), L"row_ not equal 1");
			Assert::AreEqual(1, array.GetColumn(), L"col_ not equal 1");
		}

		TEST_METHOD(TestAssignmentConstructor_Sunny)
		{
			CrtCheckMemory check;

			Array2D<int> array(4, 3);

			Assert::AreEqual(4, array.GetRow(), L"Rows are not equal");
			Assert::AreEqual(3, array.GetColumn(), L"Columns are not equal");
		}

		TEST_METHOD(TestAssignmentConstructor_Strings)
		{
			CrtCheckMemory check;

			Array2D<string> array(4, 3);

			Assert::AreEqual(4, array.GetRow(), L"Rows are not equal");
			Assert::AreEqual(3, array.GetColumn(), L"Columns are not equal");
		}

		TEST_METHOD(TestCopyConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array1(3, 4);

			Array2D<int> array2(array1);

			Assert::AreEqual(array1.GetRow(), array2.GetRow(), L"Rows are not equal");
			Assert::AreEqual(array1.GetColumn(), array2.GetColumn(), L"Columns are not equal");
		}

		TEST_METHOD(TestAssignmentOperator_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array1(1, 2);
			Array2D<int> array2;

			array2 = array1;

			Assert::AreEqual(array1.GetRow(), array2.GetRow(), L"Rows are not equal");
			Assert::AreEqual(array1.GetColumn(), array2.GetColumn(), L"Columns are not equal");
		}

		TEST_METHOD(TestMoveConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array1(12, 7);

			Array2D<int> array2(std::move(array1));

			Assert::AreEqual(12, array2.GetRow(), L"Rows are not equal");
			Assert::AreEqual(7, array2.GetColumn(), L"Columns are not equal");
			//Assert::AreEqual(0, array1.GetRow(), L"array1 row not 0");
			//Assert::AreEqual(0, array1.GetColumn(), L"array1 column not 0");
		}

		TEST_METHOD(TestMoveOperator_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array1(12, 7);
			Array2D<int> array2;

			array2 = std::move(array1);

			Assert::AreEqual(12, array2.GetRow(), L"Rows are not equal");
			Assert::AreEqual(7, array2.GetColumn(), L"Columns are not equal");
			//Assert::AreEqual(0, array1.GetRow(), L"array1 row not 0");
			//Assert::AreEqual(0, array1.GetColumn(), L"array1 column not 0");
		}

		TEST_METHOD(TestSelectMutable_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(3, 3);

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					array.Select(i, k) = i * k;
				}
			}

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					Assert::AreEqual((int)i*(int)k, array.Select(i, k));
				}
			}
		}

		TEST_METHOD(TestSelectConst_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(3, 3);
			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					array.Select(i, k) = i * k;
				}
			}

			const Array2D<int> arrayConst(std::move(array));

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					Assert::AreEqual((int)i*(int)k, arrayConst.Select(i, k));
				}
			}
		}

		TEST_METHOD(TestBracketOperatorMutable_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(3, 3);

			array[1][2] = 7;

			Assert::AreEqual(7, array[1][2]);
		}

		TEST_METHOD(TestBracketOperatorConst_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(3, 3);
			array[1][2] = 7;
			const Array2D<int> arrayConst(array);

			Assert::AreEqual(7, arrayConst[1][2]);
		}

		TEST_METHOD(TestGetRow_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(7, 4);

			int row = array.GetRow();

			Assert::AreEqual(7, row);
		}

		TEST_METHOD(TestGetColumn_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(7, 4);

			int col = array.GetColumn();

			Assert::AreEqual(4, col);
		}

		TEST_METHOD(TestSetRows_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(4, 3);
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					array[i][k] = i * k;
				}
			}

			array.SetRow(3);

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					Assert::AreEqual((int)i*(int)k, array[i][k], L"Vaules do not match in storage_");
				}
			}
			Assert::AreEqual(3, array.GetRow(), L"row_ not correct length");
		}

		TEST_METHOD(TestSetColumns_Sunny)
		{
			CrtCheckMemory check;
			Array2D<int> array(4, 3);
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t k = 0; k < 3; ++k)
				{
					array[i][k] = i * k;
				}
			}

			array.SetColumn(2);

			for (size_t i = 0; i < 3; ++i)
			{
				for (size_t k = 0; k < 2; ++k)
				{
					Assert::AreEqual((int)i*(int)k, array[i][k], L"Values do not match in storage");
				}
			}
			Assert::AreEqual(2, array.GetColumn(), L"col_ not correct length");
			//Assert::ExpectException(array[4][3]);
		}
	};
}