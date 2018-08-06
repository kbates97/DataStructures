#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "ListQueue.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ListQueueTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ListQueueCtor_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueCopyCtor_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(2);

				ListQueue<int> queue2(queue1);

				Assert::IsFalse(queue1.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueCopyCtor_ShouldCopyValuesFromQueue1ToQueue2)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);

				ListQueue<int> queue2(queue1);

				for (int i = 0; i < 4; ++i)
				{
					Assert::AreEqual(i, queue2.Dequeue());
				}
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueMoveCopyCtor_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(2);

				ListQueue<int> queue2(std::move(queue1));

				Assert::IsFalse(queue2.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueMoveCopyCtor_ShouldCopyValuesFromQueue1ToQueue2)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);

				ListQueue<int> queue2(std::move(queue1));

				for (int i = 0; i < 4; ++i)
				{
					Assert::AreEqual(i, queue2.Dequeue());
				}
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueAssignmentOp_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);
				ListQueue<int> queue2;
				
				queue2 = queue1;

				Assert::IsFalse(queue2.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueAssignmentOp_ShouldCopyValuesFromQueue1ToQueue2)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);
				ListQueue<int> queue2;

				queue2 = queue1;

				for (int i = 0; i < 4; ++i)
				{
					Assert::AreEqual(i, queue2.Dequeue());
				}
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueMoveAssignmentOp_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);
				ListQueue<int> queue2;

				queue2 = std::move(queue1);

				Assert::IsFalse(queue2.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueMoveAssignmentOp_ShouldMoveValuesFromQueue1ToQueue2)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue1;
				queue1.Enqueue(0);
				queue1.Enqueue(1);
				queue1.Enqueue(2);
				queue1.Enqueue(3);
				ListQueue<int> queue2;

				queue2 = std::move(queue1);

				for (int i = 0; i < 4; ++i)
				{
					Assert::AreEqual(i, queue2.Dequeue());
				}
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueEnqueue_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(8);

				Assert::IsFalse(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueEnqueue_ShouldBeEight)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(8);

				Assert::AreEqual(8, queue.Dequeue());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueDequeue_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(8);

				queue.Dequeue();

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueDequeue_ShouldBeEight)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(8);

				int pop = queue.Dequeue();

				Assert::AreEqual(8, pop);
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueFront_ShouldBeTwelve)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(12);

				int front = queue.Front();

				Assert::AreEqual(12, front);
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueFront_ShouldNoBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(12);

				int front = queue.Front();

				Assert::IsFalse(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueSize_ShouldBeThree)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(12);
				queue.Enqueue(2);
				queue.Enqueue(78);

				int size = queue.Size();

				Assert::AreEqual(3, size);
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueIsEmpty_ShouldBeTrue)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueIsEmpty_ShouldBeFalse)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<int> queue;
				queue.Enqueue(9);

				Assert::IsFalse(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueCtor_String_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<string> queue;

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueEnqueue_String_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<string> queue;
				queue.Enqueue("Heyo");

				Assert::IsFalse(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueDequeue_String_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<string> queue;
				queue.Enqueue("Heyo");

				string data = queue.Dequeue();

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueDequeue_String_ShouldBeHeyo)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<string> queue;
				queue.Enqueue("Heyo");

				string data = queue.Dequeue();

				Assert::AreEqual((string)"Heyo", data);
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}

		TEST_METHOD(ListQueueClear_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				ListQueue<string> queue;
				queue.Enqueue("Heyo");

				queue.Clear();

				Assert::IsTrue(queue.IsEmpty());
			}
			catch (AdtException & exception)
			{
				exception.What();
			}
		}
	};
}