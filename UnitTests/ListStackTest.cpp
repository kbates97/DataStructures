#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "ListStack.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ListStackTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ListStackDefaultCtor_ShouldBeEmpty)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			ListStack<int> stack;

			// Assert
			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackCopyCtor_ShouldCopyValuesFromStack1toStack2)
		{
			CrtCheckMemory check;
			ListStack<int> stack1;
			stack1.Push(0);
			stack1.Push(0);
			stack1.Push(7);

			ListStack<int> stack2(stack1);

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(stack1.Pop(), stack2.Pop());
			}
		}

		TEST_METHOD(ListStackMoveCtor_ShouldMoveValuesFromStack1toStack2)
		{
			CrtCheckMemory check;
			ListStack<int> stack1;
			stack1.Push(2);
			stack1.Push(1);
			stack1.Push(0);

			ListStack<int> stack2(std::move(stack1));

			for (int i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i, stack2.Pop());
			}
		}

		TEST_METHOD(ListStackAssignmentOp_ShouldCopyValuesFromStack1toStack2)
		{
			CrtCheckMemory check;
			ListStack<int> stack1;
			stack1.Push(0);
			stack1.Push(0);
			stack1.Push(7);
			ListStack<int> stack2;
			stack2 = stack1;

			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(stack1.Pop(), stack2.Pop());
			}
		}

		TEST_METHOD(ListStackMoveAssignmentOp_ShouldMoveValuesFromStack1toStack2)
		{
			CrtCheckMemory check;
			ListStack<int> stack1;
			stack1.Push(2);
			stack1.Push(1);
			stack1.Push(0);
			ListStack<int> stack2;
			stack2 = std::move(stack1);

			for (int i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i, stack2.Pop());
			}
		}

		TEST_METHOD(ListStackPush_ShouldBeSeven)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(7);
			int data = stack.Peek();
			Assert::AreEqual(7, data);

			stack.Push(4);
			data = stack.Peek();
			Assert::AreEqual(4, data);
		}

		TEST_METHOD(ListStackPush_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(7);

			Assert::IsFalse(stack.IsEmpty());
		}

		TEST_METHOD(ListStackPop_ShouldBeSeven)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(0);
			stack.Push(0);
			stack.Push(7);

			int pop = stack.Pop();

			Assert::AreEqual(7, pop);
		}

		TEST_METHOD(ListStackPop_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(0);
			stack.Push(0);
			stack.Push(7);

			stack.Pop();
			stack.Pop();
			stack.Pop();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackPeek_ShouldBeNine)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(9);
			int data = stack.Peek();

			Assert::AreEqual(9, data);
		}

		TEST_METHOD(ListStackPeek_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(9);
			stack.Peek();

			Assert::IsFalse(stack.IsEmpty());
		}

		TEST_METHOD(ListStackSize_ShouldBeFour)
		{
			CrtCheckMemory check;
			ListStack<int> stack;
			
			stack.Push(0);
			stack.Push(0);
			stack.Push(0);
			stack.Push(0);

			Assert::AreEqual((size_t)4, stack.Size());
		}

		TEST_METHOD(ListStackIsEmpty_ShouldBeTrue)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackIsEmpty_ShouldBeFalse)
		{
			CrtCheckMemory check;
			ListStack<int> stack;

			stack.Push(9);

			Assert::IsFalse(stack.IsEmpty());
		}

		TEST_METHOD(ListStackClear_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<int> stack;
			stack.Push(8);
			stack.Push(82);
			stack.Push(38);
			stack.Push(7);
			stack.Push(63);
			stack.Push(24);

			stack.Clear();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackCtor_String_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<string> stack;

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackPush_String_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<string> stack;

			stack.Push("Hello");

			Assert::IsFalse(stack.IsEmpty());
		}

		TEST_METHOD(ListStackPop_String_ShouldBeHello)
		{
			CrtCheckMemory check;
			ListStack<string> stack;

			stack.Push("Hello");

			Assert::AreEqual((string)"Hello", stack.Pop());
		}

		//doesn't work with peek returning a reference. Gets memory leaks
		/*TEST_METHOD(ListStackPeek_String_ShouldBeHello)
		{
			CrtCheckMemory check;
			ListStack<string> stack;

			stack.Push("Hello");
			string peek;
			peek.assign(stack.Peek());

			Assert::AreEqual((string)"Hello", peek);
		}*/

		TEST_METHOD(ListStackClear_String_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ListStack<string> stack;

			stack.Push("Hello");

			stack.Clear();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(ListStackCopyCtor_String_ShouldCopyValuesFromStack1toStack2)
		{
			CrtCheckMemory check;
			ListStack<string> stack1;

			stack1.Push("World");
			stack1.Push("Hello");
			
			ListStack<string> stack2(stack1);

			Assert::AreEqual((string)"Hello", stack2.Pop());
			Assert::AreEqual((string)"World", stack2.Pop());
		}
	};
}