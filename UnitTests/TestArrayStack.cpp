#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "ArrayStack.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ArrayStackTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ArrayStackConstructor_ShouldBeEmpty)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			ArrayStack<int> stack(10);

			// Assert
			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackCopyConstructor_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			ArrayStack<int> stack2(stack);

			Assert::IsTrue(stack2.IsFull());
		}

		TEST_METHOD(ArrayStackCopyConstructor_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			ArrayStack<int> stack2(stack);

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(stack.Pop(), stack2.Pop());
			}
		}

		TEST_METHOD(ArrayStackMoveConstructor_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(0);
			stack.Push(1);
			stack.Push(2);

			ArrayStack<int> stack2(std::move(stack));

			Assert::IsTrue(stack2.IsFull(), L"Should be full");
			Assert::IsTrue(stack.IsEmpty(), L"Original stack should be empty");
		}

		TEST_METHOD(ArrayStackMoveConstructor_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(2);
			stack.Push(1);
			stack.Push(0);

			ArrayStack<int> stack2(std::move(stack));

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual((int)i, stack2.Pop());
			}
		}

		TEST_METHOD(ArrayStackAssignmentOperator_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			ArrayStack<int> stack2(3);
			stack2 = stack;

			Assert::IsTrue(stack2.IsFull());
		}

		TEST_METHOD(ArrayStackAssignmentOperator_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			ArrayStack<int> stack2(3);
			stack2 = stack;

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(stack.Pop(), stack2.Pop());
			}
		}

		TEST_METHOD(ArrayStackMoveOperator_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(0);
			stack.Push(1);
			stack.Push(2);

			ArrayStack<int> stack2(3);
			stack2 = std::move(stack);

			Assert::IsTrue(stack2.IsFull(), L"Should be full");
			Assert::IsTrue(stack.IsEmpty(), L"Original stack should be empty");
		}

		TEST_METHOD(ArrayStackMoveOperator_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(2);
			stack.Push(1);
			stack.Push(0);

			ArrayStack<int> stack2(3);
			stack2 = std::move(stack);

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual((int)i, stack2.Pop());
			}
		}

		TEST_METHOD(ArrayStack_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);

			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			Assert::IsTrue(stack.IsFull());
		}

		TEST_METHOD(ArrayStackPush_ShouldAddFiveToStack)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(10);

			stack.Push(5);

			Assert::AreEqual(5, stack.Peek(), L"Wrong Value");
			Assert::AreEqual((size_t)1, stack.Size(), L"Wrong Size");
		}

		TEST_METHOD(ArrayStackPop_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(5);
			stack.Push(5);

			stack.Pop();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackPop_ShouldReturnFive)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(5);
			stack.Push(5);

			int pop = stack.Pop();

			Assert::AreEqual(5, pop);
		}

		TEST_METHOD(ArrayStackPeak_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			int peek = stack.Peek();

			Assert::IsTrue(stack.IsFull());
		}

		TEST_METHOD(ArrayStackPeak_ShouldReturnThree)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			int peek = stack.Peek();

			Assert::AreEqual(3, peek);
		}

		TEST_METHOD(ArrayStackSize_ShouldBeThree)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(5);
			stack.Push(0);
			stack.Push(1);
			stack.Push(2);

			Assert::AreEqual((size_t)3, stack.Size());
		}

		TEST_METHOD(ArrayStackIsFull_ShouldBeTrue)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(2);
			stack.Push(1);
			stack.Push(2);

			Assert::IsTrue(stack.IsFull());
		}

		TEST_METHOD(ArrayStackIsFull_ShouldBeFalse)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(2);
			stack.Push(1);
			stack.Push(2);

			stack.Pop();

			Assert::IsFalse(stack.IsFull());
		}

		TEST_METHOD(ArrayStackIsEmpty_ShouldBeTrue)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackIsEmpty_ShouldBeFalse)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);

			stack.Push(10);

			Assert::IsFalse(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackIsClear_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayStack<int> stack(3);
			stack.Push(10);
			stack.Push(11);
			stack.Push(12);

			stack.Clear();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackCosntructor_Strings_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayStack<string> stack(10);

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ArrayStackPush_Strings_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayStack<string> stack(2);

			stack.Push("Hello");
			stack.Push("World");

			Assert::IsTrue(stack.IsFull());
		}

		TEST_METHOD(ArrayStackPop_Strings_ShouldBeWorld)
		{
			CrtCheckMemory check;
			ArrayStack<string> stack(2);
			stack.Push("Hello");
			stack.Push("World");

			string world = "World";

			Assert::AreEqual(world, stack.Pop());
		}

		TEST_METHOD(ArrayStackSize_Strings_ShouldBeTwo)
		{
			CrtCheckMemory check;
			ArrayStack<string> stack(3);

			stack.Push("Hello");
			stack.Push("World");

			Assert::AreEqual((size_t)2, stack.Size());
		}

		TEST_METHOD(ArrayStackPeek_Strings_ShouldBeWorld)
		{
			CrtCheckMemory check;
			ArrayStack<string> stack(2);
			stack.Push("Hello");
			stack.Push("World");

			string peek = "World";

			Assert::AreEqual(peek, stack.Peek());
		}
	};
}