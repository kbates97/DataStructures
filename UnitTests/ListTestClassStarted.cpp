#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "AdtException.h"
#include "List.h"

using std::string;
using std::to_string;
using std::move;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ListTestClassStarter)
	{
	public:

		TEST_METHOD_INITIALIZE(InitializeMethod)
		{
			freopen("UNIT_TEST_LOG.txt", "a+", stdout);
		}

		TEST_METHOD(ListDefaultCtor_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				List<int> list;

				Assert::IsTrue(list.IsEmpty());
			}
			catch (AdtException &exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListDefaultCtor_HeadShouldBeNull)
		{
			CrtCheckMemory check;
			try
			{
				List<int> list;

				Assert::IsNull(list.GetHead());
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListMoveCtor_ShouldMoveDataFromList1ToList2)
		{
			CrtCheckMemory check;
			{
				List<string> list_1;
				for (auto i = 0; i < 10; ++i)
					list_1.Append(to_string(i));

				List<string> list_2(move(list_1));

				auto i = 0;

				for (auto list_node = list_2.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(to_string(i++), list_node->GetData());
				}
				Assert::AreEqual(true, list_1.IsEmpty());
			}
		}

		TEST_METHOD(ListAssignmentMoveOp_ShouldMoveDataFromList1ToList2)
		{
			CrtCheckMemory check;
			{
				List<string> list_1;
				for (auto i = 0; i < 10; ++i)
					list_1.Append(to_string(i));

				List<string> list_2;
				list_2 = move(list_1);

				auto i = 0;

				for (auto list_node = list_2.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(to_string(i++), list_node->GetData());
				}
			}
		}

		TEST_METHOD(ListCopyCtor_ShouldCopyListWithOneElement)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list_1;
				list_1.Append(5);

				List<size_t> list_2(list_1);

				Assert::IsFalse(list_2.IsEmpty());
				Assert::AreEqual(static_cast<size_t>(5), list_2.First());

			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListAssignmentOp_ShouldAssignList1ToList2)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list_1;
				List<size_t> list_2;

				size_t i;

				size_t values[] = { 5, 15, 25, 35, 45 };

				for (i = 0; i < 5; ++i)
				{
					list_1.Append(values[i]);
				}

				list_2 = list_1;

				i = 0;
				for (auto list_node = list_2.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(values[i++], list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListAccessors_ShouldEqualFiveAndFourtyFive)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (auto i = 0; i < 5; ++i)
				{
					list.Append(values[i]);
				}

				Assert::AreEqual(static_cast<size_t>(5), list.GetHead()->GetData());
				Assert::AreEqual(static_cast<size_t>(45), list.GetTail()->GetData());

			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListAppend_ShouldAppendFiveValues)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;
				size_t i;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (i = 0; i < 5; ++i)
				{
					list.Append(values[i]);
				}

				i = 0;
				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(values[i++], list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(List_First_ShouldeualFive)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (auto i = 0; i < 5; ++i)
				{
					list.Append(values[i]);
				}

				Assert::AreEqual(static_cast<size_t>(5), list.First());
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(List_First_ShouldeEqualFortyFive)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> aList;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (auto i = 0; i < 5; ++i)
				{
					aList.Append(values[i]);
				}

				Assert::AreEqual(static_cast<size_t>(45), aList.Last());
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListPrepend_ShouldPrependFiveValues)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;
				size_t i;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (i = 0; i < 5; ++i)
				{
					list.Prepend(values[i]);
				}

				i = 5;
				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(values[--i], list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(List_ShouldPurgeEntireList)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;

				size_t values[] = { 5, 15, 25, 35, 45 };
				for (auto i = 0; i < 5; ++i)
				{
					list.Append(values[i]);
				}

				list.Purge();

				Assert::IsNull(list.GetHead());
				Assert::IsNull(list.GetTail());
				Assert::IsTrue(list.IsEmpty());

			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListInsertBefore_ShouldReverseList)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;
				int i;

				size_t values[] = { 5, 15, 25, 35, 45 };

				list.Append(values[4]);
				for (i = 3; i >= 0; --i)
				{
					list.InsertBefore(values[i], values[i + 1]);
				}

				i = 0;
				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(values[i++], list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListInsertAfter_ShouldReverseList)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list;
				int i;

				size_t values[] = { 5, 15, 25, 35, 45 };

				list.Append(values[0]);
				for (i = 1; i < 5; ++i)
				{
					list.InsertAfter(values[i], values[i - 1]);
				}

				i = 0;
				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(values[i++], list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListExtract_ShouldExtractTen)
		{
			CrtCheckMemory check;
			try
			{
				List<int> list;

				list.Append(5);
				list.Extract(5);

				Assert::IsTrue(list.IsEmpty());
				Assert::IsNull(list.GetHead());

				list.Append(5);
				list.Append(10);
				list.Append(15);

				list.Extract(10);

				Assert::AreEqual(5, list.First());
				Assert::AreEqual(15, list.Last());
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListForwardBegin_ShouldReturnHead)
		{
			CrtCheckMemory check;
			try
			{
				List<int> list;
				list.Append(5);
				auto iterator = list.ForwardBegin();
				Assert::AreEqual(5, *iterator, L"Fail with single item list");
				list.Append(10);
				list.Append(15);
				list.Append(20);
				iterator = list.ForwardBegin();
				Assert::AreEqual(5, *iterator, L"Fail with multi item list");
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListBackwardBegin_ShouldReturnTail)
		{
			CrtCheckMemory check;
			try
			{
				List<int> list;
				list.Append(5);
				auto iterator = list.BackwardBegin();
				Assert::AreEqual(5, *iterator, L"Fail with single item list");
				list.Append(10);
				list.Append(15);
				list.Append(20);
				iterator = list.BackwardBegin();
				Assert::AreEqual(20, *iterator, L"Fail with multi item list");
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListArrayPtrCtor_ShouldCopyValuesFromArrayToList)
		{
			CrtCheckMemory check;
			try 
			{
				size_t array[5] = { 0, 1, 2, 3, 4 };
				List<size_t> list(array, 5);
				size_t i = 0;

				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(i++, list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListArrayTCtor_ShouldCopyValuesFromArrayToList)
		{
			CrtCheckMemory check;
			try
			{
				size_t arr[5] = { 1, 2, 3, 4, 5 };
				Array<size_t> array(arr, 5);
				List<size_t> list(array);
				size_t i = 1;

				for (auto list_node = list.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(i++, list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(ListMerge_ShouldMergeList1AndList2)
		{
			CrtCheckMemory check;
			try
			{
				List<size_t> list1;
				list1.Append(0);
				list1.Append(2);
				list1.Append(4);
				list1.Append(6);
				List<size_t> list2;
				list2.Append(1);
				list2.Append(3);
				list2.Append(5);
				list2.Append(7);
				list2.Append(8);
				list2.Append(9);
				size_t i = 0;

				list1.Merge(list2);

				for (auto list_node = list1.GetHead(); list_node != nullptr; list_node = list_node->GetNext())
				{
					Assert::AreEqual(i++, list_node->GetData());
				}
			}
			catch (AdtException & exception)
			{
				Assert::Fail(exception.What());
			}
		}
	};
}