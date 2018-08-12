#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"
#include <vector>

#include "AVLTree.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;

namespace UnitTests
{
	TEST_CLASS(AVLTreeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(AVLTreeDefaultCon_ShouldBeEmpty)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			AVLTree<int, int> tree;

			// Assert
			Assert::IsTrue(tree.IsEmpty());
		}

		TEST_METHOD(AVLTreeDefaultCon_Strings_ShouldBeEmpty)
		{
			CrtCheckMemory check;

			AVLTree<string, size_t> tree;

			Assert::IsTrue(tree.IsEmpty());
		}

		TEST_METHOD(AVLTreeCopyCon_ShouldNotBeEmpty)
		{
			CrtCheckMemory check;
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);
			tree.Insert(40, 40);
			tree.Insert(11, 11);
			tree.Insert(3, 3);
			tree.Insert(5, 5);

			AVLTree<int, size_t> treeCopy(tree);

			Assert::IsFalse(treeCopy.IsEmpty());
		}

		TEST_METHOD(AVLTreeCopyConTest_ShouldMatchVector)
		{
			CrtCheckMemory check;
			vector<int> inOrder = { 3, 5, 10, 11, 13, 40 };
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);
			tree.Insert(40, 40);
			tree.Insert(11, 11);
			tree.Insert(3, 3);
			tree.Insert(5, 5);

			AVLTree<int, size_t> treeCopy(tree);

			vector<int> data;
			treeCopy.SetVisitFunction([&](const AVLNode<int, size_t> *node) {data.push_back(node->GetData()); });
			treeCopy.InOrder();

			for (size_t i = 0; i < inOrder.size(); ++i)
			{
				Assert::AreEqual(inOrder[i], data[i]);
			}
		}

		TEST_METHOD(AVLTreeInsertTest_ShouldMatchVector)
		{
			CrtCheckMemory check;
			vector<int> inOrder = { 3, 5, 10, 11, 13, 40 };
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);
			tree.Insert(40, 40);
			tree.Insert(11, 11);
			tree.Insert(3, 3);
			tree.Insert(5, 5);

			vector<int> data;
			tree.SetVisitFunction([&](const AVLNode<int, size_t> *node) {data.push_back(node->GetData()); });

			tree.InOrder();

			for (size_t i = 0; i < inOrder.size(); ++i)
			{
				Assert::AreEqual(inOrder[i], data[i]);
			}
		}

		TEST_METHOD(AVLTreeHeightTest_ShouldBeOne)
		{
			CrtCheckMemory check;
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);

			Assert::AreEqual((size_t)1, tree.Height());
		}

		TEST_METHOD(AVLTreeTestBalance_HeightShouldBeThree)
		{
			CrtCheckMemory check;
			AVLTree<int, size_t> tree;
			tree.Insert(1, 1);
			tree.Insert(2, 2);
			tree.Insert(3, 3);
			tree.Insert(4, 4);
			tree.Insert(5, 5);
			tree.Insert(6, 6);
			tree.Insert(7, 7);

			Assert::AreEqual((size_t)2, tree.Height());
		}

		TEST_METHOD(AVLTreeTestBalance_VectorShouldMatch)
		{
			CrtCheckMemory check;
			vector<int> breadthFirst = { 4, 2, 6, 1, 3, 5, 7 };
			AVLTree<int, size_t> tree;
			tree.Insert(1, 1);
			tree.Insert(2, 2);
			tree.Insert(3, 3);
			tree.Insert(4, 4);
			tree.Insert(5, 5);
			tree.Insert(6, 6);
			tree.Insert(7, 7);

			vector<int> data;
			tree.SetVisitFunction([&](const AVLNode<int, size_t> *node) {data.push_back(node->GetData()); });

			tree.BreadthFirst();

			for (size_t i = 0; i < breadthFirst.size(); ++i)
			{
				Assert::AreEqual(breadthFirst[i], data[i]);
			}
		}

		TEST_METHOD(AVLTreeClearTest_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			AVLTree<int, size_t> tree;
			tree.Insert(1, 1);
			tree.Insert(2, 2);
			tree.Insert(3, 3);
			tree.Insert(4, 4);
			tree.Insert(5, 5);
			tree.Insert(6, 6);
			tree.Insert(7, 7);

			tree.Clear();

			Assert::IsTrue(tree.IsEmpty());
		}

		TEST_METHOD(AVLTreeDeleteTest_ShouldMatchVector)
		{
			CrtCheckMemory check;
			vector<int> inOrder = { 10, 3, 13, 11 };
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);
			tree.Insert(40, 40);
			tree.Insert(11, 11);
			tree.Insert(3, 3);

			vector<int> data;
			tree.SetVisitFunction([&](const AVLNode<int, size_t> *node) {data.push_back(node->GetData()); });

			tree.Delete(40);
			tree.BreadthFirst();

			for (size_t i = 0; i < inOrder.size(); ++i)
			{
				Assert::AreEqual(inOrder[i], data[i]);
			}
		}

		TEST_METHOD(AVLTreeDeleteTest_HeightShouldBeTwo)
		{
			CrtCheckMemory check;
			AVLTree<int, size_t> tree;
			tree.Insert(10, 10);
			tree.Insert(13, 13);
			tree.Insert(40, 40);
			tree.Insert(11, 11);
			tree.Insert(3, 3);

			tree.Delete(40);

			Assert::AreEqual((size_t)2, tree.Height());
		}
	};
}