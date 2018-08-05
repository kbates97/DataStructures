#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "BSTree.h"
#include <vector>

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(BSTreeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(BSTInOrderTest)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			myTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTDefaultConTest_ShouldBeEmpty)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;

			Assert::IsTrue(myTree.IsEmpty());
		}

		TEST_METHOD(BSTCopyCon_ShouldBeEqual)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			BSTree<int, int> copyTree(myTree);

			copyTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTAssignOp_ShouldBeEqual)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			BSTree<int, int> copyTree;
			copyTree = myTree;

			copyTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTMoveCon_ShouldBeEqual)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			BSTree<int, int> copyTree(std::move(myTree));

			copyTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTMoveOp_ShouldBeEqual)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			BSTree<int, int> copyTree;

			copyTree = std::move(myTree);

			copyTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTSetVisitFunction_ShouldBeEqual)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 12, 18, 20, 22, 25 };
			std::vector<int> tree_traversal;
			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);
			
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };
			myTree.SetVisitFunction(visit);
			myTree.InOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTClear_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			myTree.Clear();

			Assert::IsTrue(myTree.IsEmpty());
		}

		TEST_METHOD(BSTHeight_ShouldBeThree)
		{
			CrtCheckMemory check;
			BSTree<int, int> myTree;
			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);
			myTree.Insert(22, 23);

			size_t height = myTree.Height();

			Assert::AreEqual(size_t(3), height);
		}

		TEST_METHOD(BSTPostOrderTest)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;
			const int correctOrder[] = { 11, 18, 12, 22, 25, 20 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			myTree.PostOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTPreOrderTest)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;
			const int correctOrder[] = { 20, 12, 11, 18, 25, 22 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			myTree.PreOrder();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTBreadthFirstTest)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;
			const int correctOrder[] = { 20, 12, 25, 11, 18, 22 };

			std::vector<int> tree_traversal;
			const auto visit = [&](const BSTNode<int, int> * const node)
			{ tree_traversal.push_back(node->GetData()); };

			myTree.SetVisitFunction(visit);

			myTree.Insert(20, 20);
			myTree.Insert(12, 12);
			myTree.Insert(25, 25);
			myTree.Insert(11, 11);
			myTree.Insert(18, 18);
			myTree.Insert(22, 22);

			myTree.BreadthFirst();

			for (int i = 0; i < tree_traversal.size(); ++i)
			{
				Assert::AreEqual(correctOrder[i], tree_traversal[i]);
			}
		}

		TEST_METHOD(BSTIsEmpty_ShouldBeTrue)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;

			Assert::IsTrue(myTree.IsEmpty());
		}

		TEST_METHOD(BSTIsEmpty_ShouldBeFalse)
		{
			CrtCheckMemory check;

			BSTree<int, int> myTree;
			myTree.Insert(10, 10);

			Assert::IsFalse(myTree.IsEmpty());
		}

		TEST_METHOD(BSTDeleteTest)
		{
			CrtCheckMemory check;
			try
			{
				BSTree<int, int> myTree;
				const int correctOrder[] = { 18, 12, 11, 25, 22 };

				std::vector<int> tree_traversal;
				const auto visit = [&](const BSTNode<int, int> * const node)
				{ tree_traversal.push_back(node->GetData()); };

				myTree.SetVisitFunction(visit);

				myTree.Insert(20, 20);
				myTree.Insert(12, 12);
				myTree.Insert(25, 25);
				myTree.Insert(11, 11);
				myTree.Insert(18, 18);
				myTree.Insert(22, 22);

				myTree.Delete(20);
				myTree.PreOrder();

				for (int i = 0; i < tree_traversal.size(); ++i)
				{
					Assert::AreEqual(correctOrder[i], tree_traversal[i]);
				}
			}
			catch (AdtException &exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(BSTDeleteTest_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			try
			{
				BSTree<int, int> myTree;

				myTree.Insert(20, 20);

				myTree.Delete(20);

				Assert::IsTrue(myTree.IsEmpty());
			}
			catch (AdtException &exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(BSTSearchTest_ShouldReturnTwelve)
		{
			CrtCheckMemory check;
			try
			{
				BSTree<int, int> myTree;

				myTree.Insert(20, 20);
				myTree.Insert(12, 12);
				myTree.Insert(25, 25);
				myTree.Insert(11, 11);
				myTree.Insert(18, 18);
				myTree.Insert(22, 22);

				int data = myTree.Search(12);

				Assert::AreEqual(12, data);
			}
			catch (AdtException &exception)
			{
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(BSTSearchTest_ShouldReturnTwelve_Const)
		{
			CrtCheckMemory check;
			try
			{
				BSTree<int, int> myTree;

				myTree.Insert(20, 20);
				myTree.Insert(12, 12);
				myTree.Insert(25, 25);
				myTree.Insert(11, 11);
				myTree.Insert(18, 18);
				myTree.Insert(22, 22);

				const BSTree<int, int> constTree(myTree);

				int data = constTree.Search(12);

				Assert::AreEqual(12, data);
			}
			catch (AdtException &exception)
			{
				Assert::Fail(exception.What());
			}
		}
	};
}