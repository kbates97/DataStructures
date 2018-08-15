#include "stdafx.h"
#include "crtdbg.h"

#include <string>
#include <functional>
#include "CrtCheckMemory.h"
#include "Graph.h"
#include "Arc.h"

using std::string;
using std::move;

template <class V, class E>
using Edge = Graphs::Arc<V, E>;

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Graphs;

namespace UnitTests
{
	TEST_CLASS(GraphTest)
	{
	public:

		TEST_METHOD(GraphDepthFirstTest)
		{
			CrtCheckMemory check; 
			{
				const string correct_order[] = { "A", "X", "H", "P", "E", "Y", "M", "J", "G" };
				Graph<string, string> graph;

				std::queue<string> graph_traversal;
				const auto visit = [&](const Vertex<string, string> & vertex) { graph_traversal.emplace(vertex.GetData()); };

				graph.SetFunction(visit);

				graph.InsertVertex("A");
				graph.InsertVertex("X");
				graph.InsertVertex("H");
				graph.InsertVertex("P");
				graph.InsertVertex("E");
				graph.InsertVertex("Y");
				graph.InsertVertex("M");
				graph.InsertVertex("J");
				graph.InsertVertex("G");

				graph.InsertArc("A", "X", "A-X", 5);
				graph.InsertArc("X", "G", "X-G", 5);
				graph.InsertArc("X", "H", "X-H", 10);
				graph.InsertArc("H", "E", "H-E", 5);
				graph.InsertArc("H", "P", "H-P", 10);
				graph.InsertArc("E", "M", "E-M", 10);
				graph.InsertArc("E", "Y", "E-Y", 5);
				graph.InsertArc("M", "J", "M-J", 5);
				graph.InsertArc("G", "P", "G-P", 10);

				graph.DepthFirst("A");

				const int size = graph_traversal.size();
				Assert::AreEqual(9, size);

				for (auto i = 0; i < size; ++i)
				{
					const auto vertex = graph_traversal.front();
					graph_traversal.pop();
					Assert::AreEqual(correct_order[i], vertex);
				}
			}
		}

		TEST_METHOD(GraphBreadthFirstTest)
		{
			CrtCheckMemory check;
			{
				const string correct_order[] = { "A", "X", "G", "H", "P", "E", "M", "Y", "J" };
				Graph<string, string> graph;

				std::queue<string> graph_traversal;
				const auto visit = [&](const Vertex<string, string> & vertex) { graph_traversal.emplace(vertex.GetData()); };

				graph.SetFunction(visit);

				graph.InsertVertex("A");
				graph.InsertVertex("X");
				graph.InsertVertex("H");
				graph.InsertVertex("P");
				graph.InsertVertex("E");
				graph.InsertVertex("Y");
				graph.InsertVertex("M");
				graph.InsertVertex("J");
				graph.InsertVertex("G");

				graph.InsertArc("A", "X", "A-X", 5);
				graph.InsertArc("X", "G", "X-G", 5);
				graph.InsertArc("X", "H", "X-H", 10);
				graph.InsertArc("H", "P", "H-P", 10);
				graph.InsertArc("H", "E", "H-E", 5);
				graph.InsertArc("G", "P", "G-P", 10);
				graph.InsertArc("E", "M", "E-M", 10);
				graph.InsertArc("E", "Y", "E-Y", 5);
				graph.InsertArc("M", "J", "M-J", 5);

				graph.BreadthFirst("A");
				const auto size = graph_traversal.size();
				Assert::AreEqual(static_cast<size_t>(9), size);

				for (auto i = 0; i < size; ++i)
				{
					const string vertex = graph_traversal.front();
					graph_traversal.pop();
					Assert::AreEqual(correct_order[i], vertex);
				}
			}
		}

		TEST_METHOD(GraphTestDelete)
		{
			CrtCheckMemory check;
			{
				const string correct_order[] = { "A", "X", "H", "P", "E", "M", "Y", "J" };
				Graph<string, string> graph;

				std::queue<string> graph_traversal;
				const auto visit = [&](const Vertex<string, string> & vertex) { graph_traversal.emplace(vertex.GetData()); };

				graph.SetFunction(visit);

				graph.InsertVertex("A");
				graph.InsertVertex("X");
				graph.InsertVertex("H");
				graph.InsertVertex("P");
				graph.InsertVertex("E");
				graph.InsertVertex("Y");
				graph.InsertVertex("M");
				graph.InsertVertex("J");
				graph.InsertVertex("G");

				graph.InsertArc("A", "X", "A-X", 5);
				graph.InsertArc("X", "G", "X-G", 5);
				graph.InsertArc("X", "H", "X-H", 10);
				graph.InsertArc("H", "P", "H-P", 10);
				graph.InsertArc("H", "E", "H-E", 5);
				graph.InsertArc("G", "P", "G-P", 10);
				graph.InsertArc("E", "M", "E-M", 10);
				graph.InsertArc("E", "Y", "E-Y", 5);
				graph.InsertArc("M", "J", "M-J", 5);

				graph.DeleteVertex("G");

				graph.BreadthFirst("A");
				const auto size = graph_traversal.size();
				Assert::AreEqual(static_cast<size_t>(8), size);

				for (auto i = 0; i < size; ++i)
				{
					const string vertex = graph_traversal.front();
					graph_traversal.pop();
					Assert::AreEqual(correct_order[i], vertex);
				}
			}
		}

		TEST_METHOD(GraphTestCopyCon)
		{
			CrtCheckMemory check;
			{
				const string correct_order[] = { "A", "X", "G", "H", "P", "E", "M", "Y", "J" };
				Graph<string, string> graph;

				std::queue<string> graph_traversal;
				const auto visit = [&](const Vertex<string, string> & vertex) { graph_traversal.emplace(vertex.GetData()); };

				graph.SetFunction(visit);

				graph.InsertVertex("A");
				graph.InsertVertex("X");
				graph.InsertVertex("H");
				graph.InsertVertex("P");
				graph.InsertVertex("E");
				graph.InsertVertex("Y");
				graph.InsertVertex("M");
				graph.InsertVertex("J");
				graph.InsertVertex("G");

				graph.InsertArc("A", "X", "A-X", 5);
				graph.InsertArc("X", "G", "X-G", 5);
				graph.InsertArc("X", "H", "X-H", 10);
				graph.InsertArc("H", "P", "H-P", 10);
				graph.InsertArc("H", "E", "H-E", 5);
				graph.InsertArc("G", "P", "G-P", 10);
				graph.InsertArc("E", "M", "E-M", 10);
				graph.InsertArc("E", "Y", "E-Y", 5);
				graph.InsertArc("M", "J", "M-J", 5);

				Graph<string, string> graphCopy(graph);

				graphCopy.BreadthFirst("A");
				const auto size = graph_traversal.size();
				Assert::AreEqual(static_cast<size_t>(9), size);

				for (auto i = 0; i < size; ++i)
				{
					const string vertex = graph_traversal.front();
					graph_traversal.pop();
					Assert::AreEqual(correct_order[i], vertex);
				}
			}
		}

		TEST_METHOD(GraphTestDefaultCon_ShouldBeEmpty)
		{
			CrtCheckMemory check;
			{
				Graph<string, string> graph;

				Assert::IsTrue(graph.IsEmpty());
			}
		}
	};
}