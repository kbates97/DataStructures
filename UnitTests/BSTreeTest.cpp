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
	};
}