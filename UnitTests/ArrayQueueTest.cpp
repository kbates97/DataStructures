#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "ArrayQueue.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ArrayQueueTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ArrayQueueConstructor_ShouldBeEmpty)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			ArrayQueue<int> queue(4);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);
			queue.Enqueue(3);

			// Assert
			Assert::IsTrue(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueConstructor_ShouldBeFull)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			ArrayQueue<int> queue(4);

			// Assert
			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(ArrayQueueCopyConstructor_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(queue);

			Assert::IsTrue(queueCopy.IsFull());
		}

		TEST_METHOD(ArrayQueueCopyConstructor_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(queue);

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(i, queue.Dequeue());
			}
		}

		TEST_METHOD(ArrayQueueMoveConstructor_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(std::move(queue));

			Assert::IsTrue(queueCopy.IsFull(), L"New Queue should be full");

			Assert::IsTrue(queue.IsEmpty(), L"Old Queue should be empty");
		}

		TEST_METHOD(ArrayQueueMoveConstructor_ShouldHaveNewData)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(std::move(queue));

			for (int i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i, queueCopy.Dequeue());
			}
		}

		TEST_METHOD(ArrayQueueAssignmentOperator_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(3);
			queueCopy = queue;

			Assert::IsTrue(queueCopy.IsFull());
		}

		TEST_METHOD(ArrayQueueAssignmentOperator_ShouldBeEqual)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(3);
			queueCopy = queue;

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(i, queue.Dequeue());
			}
		}

		TEST_METHOD(ArrayQueueMoveOperator_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(3);
			queueCopy = std::move(queue);

			Assert::IsTrue(queueCopy.IsFull(), L"New Queue should be full");

			Assert::IsTrue(queue.IsEmpty(), L"Old Queue should be empty");
		}

		TEST_METHOD(ArrayQueueMoveOperator_ShouldHaveNewData)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(3);
			queue.Enqueue(0);
			queue.Enqueue(1);
			queue.Enqueue(2);

			ArrayQueue<int> queueCopy(3);
			queueCopy = std::move(queue);

			for (int i = 0; i < 3; ++i)
			{
				Assert::AreEqual(i, queueCopy.Dequeue());
			}
		}

		TEST_METHOD(ArrayQueueEnqueue_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(1);

			queue.Enqueue(5);

			Assert::IsTrue(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueDequeue_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(1);
			queue.Enqueue(5);

			int pop = queue.Dequeue();

			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(ArrayQueueDequeue_ShouldBeFive)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(1);
			queue.Enqueue(5);

			int pop = queue.Dequeue();

			Assert::AreEqual(5, pop);
		}

		TEST_METHOD(ArrayQueueFront_ShouldBeFive)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(1);
			queue.Enqueue(5);

			int front = queue.Front();

			Assert::AreEqual(5, front);
		}

		TEST_METHOD(ArrayQueueFront_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(1);
			queue.Enqueue(5);

			int front = queue.Front();

			Assert::IsTrue(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueSize_ShouldBeThree)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(10);

			queue.Enqueue(2);
			queue.Enqueue(2);
			queue.Enqueue(7);

			Assert::AreEqual((size_t)3, queue.Size());
		}

		TEST_METHOD(ArrayQueueIsEmpty_ShouldBeTrue)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(10);

			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(ArrayQueueIsEmpty_ShouldBeFalse)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(10);

			queue.Enqueue(10);

			Assert::IsFalse(queue.IsEmpty());
		}

		TEST_METHOD(ArrayQueueIsFull_ShouldBeTrue)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(2);

			queue.Enqueue(10);
			queue.Enqueue(11);

			Assert::IsTrue(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueIsFull_ShouldBeFalse)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(2);

			queue.Enqueue(10);

			Assert::IsFalse(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueConstructor_Strings_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayQueue<string> queue(10);

			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(ArrayQueueEnque_Strings_ShouldBeFull)
		{
			CrtCheckMemory check;
			ArrayQueue<string> queue(2);

			queue.Enqueue("Hello");
			queue.Enqueue("World");

			Assert::IsTrue(queue.IsFull());
		}

		TEST_METHOD(ArrayQueueDequeue_Strings_ShouldBeWorld)
		{
			CrtCheckMemory check;
			ArrayQueue<string> queue(2);
			queue.Enqueue("Hello");
			queue.Enqueue("World");

			string hello = "Hello";

			Assert::AreEqual(hello, queue.Dequeue());
		}

		TEST_METHOD(ArrayQueueFront_Strings_ShouldBeWorld)
		{
			CrtCheckMemory check;
			ArrayQueue<string> queue(2);
			queue.Enqueue("Hello");
			queue.Enqueue("World");

			string hello = "Hello";

			Assert::AreEqual(hello, queue.Front());
		}

		TEST_METHOD(ArrayQueueSize_Strings_ShouldBeTwo)
		{
			CrtCheckMemory check;
			ArrayQueue<string> queue(3);
			queue.Enqueue("Hello");
			queue.Enqueue("World");

			Assert::AreEqual((size_t)2, queue.Size());
		}

		TEST_METHOD(ArrayQueueClear_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			ArrayQueue<int> queue(10);
			queue.Enqueue(2);
			queue.Enqueue(12);
			queue.Enqueue(3);
			queue.Enqueue(4);
			queue.Enqueue(2);
			queue.Enqueue(32);
			queue.Enqueue(26);
			queue.Enqueue(0);
			queue.Enqueue(8);
			queue.Enqueue(7);

			queue.Clear();

			Assert::IsTrue(queue.IsEmpty());
		}
	};
}