#include "stdafx.h"
#include <CppUnitTest.h>
#include "CrtCheckMemory.h"
#include <List.h>
#include <ForwardIterator.h>
#include <BackwardIterator.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Iterators)
	{
	public:

		TEST_METHOD_INITIALIZE(IteratorsTestClassStarter)
		{
			freopen("UNIT_TEST_LOG.txt", "a+", stdout);
		}

		TEST_METHOD(ForwardIteratorBeginTest_FirstShoulEqualOperatorStar)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i * 5);
			}

			const auto forward_iterator = list.ForwardBegin();

			Assert::AreEqual(list.First(), *forward_iterator);
		}

		TEST_METHOD(BackwardIteratorBeginTest_LastShouldEqualOperatorStar)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i * 5);
			}

			const auto backward_iterator = list.BackwardBegin();

			Assert::AreEqual(list.Last(), *backward_iterator);
		}

		TEST_METHOD(ForwardIteratorEndTest_ForwardIteratorShouldBeDone)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i * 5);
			}

			auto forward_iterator = list.ForwardEnd();

			Assert::IsTrue(forward_iterator.IsDone());
		}

		TEST_METHOD(BackwardIteratorEndTest_BackwardIteratorShouldBeDone)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i * 5);
			}

			auto backward_iterator = list.BackwardEnd();

			Assert::IsTrue(backward_iterator.IsDone());
		}

		TEST_METHOD(ForwardIteratorBeginNextTest_ValuesShouldEqualIteratedValues)
		{
			CrtCheckMemory check;
			size_t values[] = { 1, 2, 3, 4, 5, 6, 7 };
			size_t i = 0;

			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			for (auto forward_iterator = list.ForwardBegin(); forward_iterator != list.ForwardEnd(); ++forward_iterator)
				Assert::AreEqual(values[i++], *forward_iterator);

		}

		TEST_METHOD(BackwardIteratorBeginNextTest_ValuesShouldEqualIteratedValues)
		{
			CrtCheckMemory check;
			size_t values[] = { 1, 2, 3, 4, 5, 6, 7 };
			size_t i = 6;

			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			for (auto backward_iterator = list.BackwardBegin(); backward_iterator != list.BackwardEnd(); ++backward_iterator)
				Assert::AreEqual(values[i--], *backward_iterator);
		}

		TEST_METHOD(ForwardIteratorAssignment_ForwardBeginShouldReturnFirst)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i * 5);
			}

			const auto forward_iterator = list.ForwardBegin();

			Assert::AreEqual(list.First(), *forward_iterator);
		}

		TEST_METHOD(BackwardIteratorAssignment_BackwardBeginShouldReturnLast)
		{
			CrtCheckMemory check;
			List<size_t> list;

			for (size_t i = 0; i < 5; ++i)
			{
				list.Append(i);
			}

			const auto backward_iterator = list.BackwardBegin();

			Assert::AreEqual(list.Last(), *backward_iterator);
		}

		TEST_METHOD(ForwardIteratorReset)
		{
			CrtCheckMemory check;
			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			auto forward_iterator = list.ForwardBegin();

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					++forward_iterator;
				}

				forward_iterator.Reset();
			}

			Assert::AreEqual(list.First(), *forward_iterator);
		}

		TEST_METHOD(BackwardIteratorReset_ShouldReset)
		{
			CrtCheckMemory check;
			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			auto backward_iterator = list.BackwardBegin();


			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					++backward_iterator;
				}

				backward_iterator.Reset();
			}

			Assert::AreEqual(list.Last(), *backward_iterator);
		}

		TEST_METHOD(ForwardIteratorMoveNext_ShouldMoveNext)
		{
			CrtCheckMemory check;
			size_t values[] = { 1, 2, 3, 4, 5, 6, 7 };
			size_t i = 0;

			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			auto forward_iterator = list.ForwardBegin();

			while (!forward_iterator.IsDone())
			{
				Assert::AreEqual(values[i++], *forward_iterator++);
			}
		}

		TEST_METHOD(BackwardIteratorMoveNext_ShouldMoveNext)
		{
			CrtCheckMemory check;
			size_t values[] = { 1, 2, 3, 4, 5, 6, 7 };
			auto i = 6;

			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
			list.Append(7);

			auto backward_iterator = list.BackwardBegin();

			while (backward_iterator != list.BackwardEnd())
			{
				Assert::AreEqual(values[i--], *backward_iterator++);
			}
		}

		TEST_METHOD(PreAndPostFixOperations_ShouldIncrementPreAndPost)
		{
			CrtCheckMemory check;
			size_t values[] = { 1, 2, 3, 4, 5, 6, 7 };

			List<size_t> list;
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);

			auto forward_iterator = list.ForwardBegin();

			const auto current_value = *forward_iterator;
			Assert::AreEqual(static_cast<size_t>(1), current_value);

			const auto value_with_post_increment = *forward_iterator++;
			Assert::AreEqual(static_cast<size_t>(1), value_with_post_increment);

			const auto value_after_post_increment = *forward_iterator;
			Assert::AreEqual(static_cast<size_t>(2), value_after_post_increment);

			const auto value_with_pre_increment = *++forward_iterator;
			Assert::AreEqual(static_cast<size_t>(3), value_with_pre_increment);

			const auto value_after_pre_increment = *forward_iterator;
			Assert::AreEqual(static_cast<size_t>(3), value_after_pre_increment);
		}

	};
}