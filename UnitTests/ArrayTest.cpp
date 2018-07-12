#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Array.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ArrayTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(TestAssignmentConstructor_Sunny)
		{
			// Arrange
			CrtCheckMemory check;
			size_t length = 80;
			int start_index_possitive = 5;
			int start_index_negative = -5;

			// Act
			Array<int> array_possitive_start(length, start_index_possitive);
			Array<int> array_negative_start(length, start_index_negative);
			Array<int> array_no_start(length);

			// Assert
			Assert::AreEqual(array_negative_start.GetLength(), length);
			Assert::AreEqual(array_negative_start.GetStartIndex(), start_index_negative);

			Assert::AreEqual(array_possitive_start.GetLength(), length);
			Assert::AreEqual(array_possitive_start.GetStartIndex(), start_index_possitive);

			Assert::AreEqual(array_no_start.GetLength(), length);
			Assert::AreEqual(array_no_start.GetStartIndex(), 0);
		}

		TEST_METHOD(TestDefaultConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array;

			Assert::AreEqual(NULL, (int)array.GetLength());
			Assert::AreEqual(0, array.GetStartIndex());
		}

		TEST_METHOD(TestDefaultConstructor_Strings)
		{
			CrtCheckMemory check;
			Array<string> array;

			Assert::AreEqual(NULL, (int)array.GetLength());
			Assert::AreEqual(0, array.GetStartIndex());
		}

		TEST_METHOD(TestMoveConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array<size_t> array1(10);
			for (size_t i = 0; i < 10; ++i)
			{
				array1[i] = i;
			}

			Array<size_t> array2(std::move(array1));

			Assert::AreEqual((size_t)10, array2.GetLength(), L"array2.GetLength() Should Be 10");
			Assert::AreEqual((size_t)0, array1.GetLength()), L"array1.GetLength() Should Be 0";
			for (size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, array2[i], L"Data Not Equal");
			}
		}

		TEST_METHOD(TestMoveOperator_Sunny)
		{
			CrtCheckMemory check;
			Array<size_t> array1(10);
			Array<size_t> array2;
			for (size_t i = 0; i < 10; ++i)
			{
				array1[i] = i;
			};

			array2 = std::move(array1);

			Assert::AreEqual((size_t)10, array2.GetLength(), L"array2.GetLength() Should Be 10");
			Assert::AreEqual((size_t)0, array1.GetLength()), L"array1.GetLength() Should Be 0";
			for (size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(i, array2[i], L"Data Not Equal");
			}
		}

		TEST_METHOD(TestCArrayConstructor_Sunny)
		{
			CrtCheckMemory check;
			int arr[5] = { 1, 2, 3, 4, 5 };

			Array<int> array_with_C_array(arr, 5);

			for (size_t i = 0; i < 5; ++i)
			{
				Assert::AreEqual(arr[i], array_with_C_array[i]);
			}
		}

		TEST_METHOD(TestCopyConstructor_Sunny)
		{
			CrtCheckMemory check;
			Array<int> initialArray(10);
			for (size_t i = 0; i < 10; ++i)
			{
				initialArray[i] = i;
			}

			Array<int> copyArray(initialArray);

			for (size_t i = 0; i < copyArray.GetLength(); ++i)
			{
				Assert::AreEqual(initialArray[i], copyArray[i], L"Data Not Equal");
			}
		}

		TEST_METHOD(TestAssignmentOperator_Sunny)
		{
			CrtCheckMemory check;
			Array<int> initalArray(10);
			Array<int> secondArray;
			for (size_t i = 0; i < 10; ++i)
			{
				initalArray[i] = i;
			}

			secondArray = initalArray;

			for (size_t i = 0; i < 10; ++i)
			{
				Assert::AreEqual(initalArray[i], secondArray[i]);
			}
		}

		TEST_METHOD(TestBracketOperator_sunny)
		{
			CrtCheckMemory check;
			Array<size_t> array(5);

			array[0] = 0;
			array[1] = 1;
			array[2] = 2;
			array[3] = 3;
			array[4] = 4;

			for (size_t i = 0; i < 5; ++i)
			{
				Assert::AreEqual(i, array[i]);
			}
		}

		TEST_METHOD(TestBracketOperatorConst_sunny)
		{
			CrtCheckMemory check;
			int arr[5] = { 0, 1, 2, 3, 4 };
			const Array<int> array(arr, 5);

			for (size_t i = 0; i < 5; ++i)
			{
				Assert::AreEqual((int)i, array[i]);
			}
		}

		TEST_METHOD(TestGetStartIndex_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array(0, 10);

			int start_index = array.GetStartIndex();

			Assert::AreEqual(10, start_index);
		}

		TEST_METHOD(TestGetLength_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array(10);

			size_t length = array.GetLength();

			Assert::AreEqual((size_t)10, length);
		}

		TEST_METHOD(TestSetStartIndex_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array;

			array.SetStartIndex(-3);

			Assert::AreEqual(-3, array.GetStartIndex());
		}

		TEST_METHOD(TestSetLength_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array;

			array.SetLength(12);

			Assert::AreEqual((size_t)12, array.GetLength());
		}

		TEST_METHOD(TestResizeArray_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array(10);
			for (size_t i = 0; i < 10; ++i)
			{
				array[i] = i;
			}

			array.SetLength(5);

			for (size_t i = 0; i < array.GetLength(); ++i)
			{
				Assert::AreEqual((int)i, array[i]);
			}
			Assert::AreEqual((size_t)5, array.GetLength());
		}

		TEST_METHOD(TestMerge_Sunny)
		{
			CrtCheckMemory check;
			Array<int> array1(10);
			for (size_t i = 0; i < 10; i++)
			{
				array1[i] = i * 2;
			}
			Array<int> array2(10);
			for (size_t i = 0; i < 10; i++)
			{
				array2[i] = 2 * i + 1;
			}

			Array<int> array3(std::move(array1.Merge(array2)));

			Assert::AreEqual((size_t)20, array3.GetLength(), L"array3.GetLength() Expected 20");
			for (int i = 0; i < 20; i++)
			{
				Assert::AreEqual(i, array3[i], L"Expected {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ... 19}");
			}
		}
	};
}