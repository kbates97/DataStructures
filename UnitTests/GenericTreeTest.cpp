#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "GenericTree.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(GenericTreeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(GenericTreeCon)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			GenericTree<int> tree;

			// Assert
			Assert::IsTrue(tree.IsEmpty());
		}

		TEST_METHOD(GenericTreeCon_String)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			GenericTree<string> tree;

			// Assert
			Assert::IsTrue(tree.IsEmpty());
		}

		TEST_METHOD(GenericTreeClear_ShouldBeEmpty)
		{
			// Arrange
			CrtCheckMemory check;
			GenericTree<int> tree;
			tree.SetRoot(new GenericTreeNode<int>(10));
			GenericTreeNode<int> * node = tree.GetRoot();

			for (size_t i = 0; i < 5; i++)
			{
				node->AddChild(new GenericTreeNode<int>(i));
			}
			node = node->GetChildren().back();
			for (size_t i = 0; i < 5; i++)
			{
				node->AddChild(new GenericTreeNode<int>(i));
			}

			// Act
			tree.Clear();
			// Assert
			Assert::IsTrue(tree.IsEmpty());
		}
	};
}