// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void InsertDataInGraph(Graphs::Graph<string, string> &map);
void ShortestPath(Graphs::Graph<string, string> &map, string from, string to);
int IndexOf(const vector<Graphs::Vertex<string, string>*> &vertices, const Graphs::Vertex<string, string>* node);
void DisplayShortestPath(vector<Graphs::Vertex<string, string>*> &vertices, const vector<int> &distance, const vector<int> &predecessor, const int start_index, const int end_index);

int main()
{
	Graphs::Graph<string, string> map;
	InsertDataInGraph(map);
	string from;
	string to;
	while (true)
	{
		cout << "Enter Start: ";
		std::getline(cin, from);
		cout << "Enter destination: ";
		std::getline(cin, to);
		ShortestPath(map, from, to);
		cout << endl << endl;
	}
    return 0;
}

void InsertDataInGraph(Graphs::Graph<string, string> &map)
{
	std::ifstream file;
	file.open("Lab_04.txt");
	if (!file.is_open())
		cout << "File Not Opened" << endl;
	string start;
	string end;
	string path;
	int milage;
	char throwAway;
	int weight;
	while (!file.eof())
	{
		if (file.peek() == '\n')
			file.getline(&throwAway, 1);
		std::getline(file, start, ',');
		std::getline(file, end, ',');
		std::getline(file, path, ',');
		file >> milage;
		map.InsertVertex(start);
		map.InsertVertex(end);
		map.InsertArc(start, end, path, milage);
	}
}

void ShortestPath(Graphs::Graph<string, string>& map, string from, string to)
{
	vector<Graphs::Vertex<string, string>*> vertices(map.GetNumberOfVertices());
	vector<int> distance(vertices.size(), -1);
	vector<int> predecessor(vertices.size(), -1);
	map.SetAllVertexesToNotProcessed();
	int i = 0;
	for (auto it = map.GetMapBeginIterator(); it != map.GetMapEndIterator(); ++it, ++i)
		vertices[i] = &*it;
	int start_index = IndexOf(vertices, map.GetVertex(from));
	int current_index = start_index;
	int end_index = IndexOf(vertices, map.GetVertex(to));
	distance[current_index] = 0;
	while (true)
	{
		list<Graphs::Arc<string, string>> arcs = vertices[current_index]->GetArcs();
		for (auto it = arcs.begin(); it != arcs.end(); ++it)
		{
			int dest_index = IndexOf(vertices, it->GetDestination());
			if (!it->GetDestination()->GetProcessed())
				if (it->GetWeight() + distance[current_index] < distance[dest_index] || distance[dest_index] == -1)
				{
					distance[dest_index] = it->GetWeight() + distance[current_index];
					predecessor[dest_index] = current_index;
				}
		}
		vertices[current_index]->SetProcessed(true);
		for (size_t i = 0; i < distance.size(); ++i)
		{
			if (!vertices[i]->GetProcessed())
			{
				if (distance[i] != -1)
				{
					if (vertices[current_index]->GetProcessed())
						current_index = i;
					else if (distance[i] < distance[current_index])
						current_index = i;
				}
			}
		}
		if (vertices[end_index]->GetProcessed())
			break;
	}
	DisplayShortestPath(vertices, distance, predecessor, start_index, end_index);
}

int IndexOf(const vector<Graphs::Vertex<string, string>*>& vertices, const Graphs::Vertex<string, string>* node)
{
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		if (vertices[i] == node)
			return i;
	}
	return -1;
}

void DisplayShortestPath(vector<Graphs::Vertex<string, string>*>& vertices, const vector<int>& distance, const vector<int>& predecessor, const int start_index, const int end_index)
{
	cout << "The distance from " << vertices[start_index]->GetData() << " to " << vertices[end_index]->GetData() << " is " << distance[end_index] << " miles." << endl;
	double time = 0;
	stack<Graphs::Arc<string, string>> path;
	int current = end_index;
	while (current != start_index)
	{
		list<Graphs::Arc<string, string>> arcs = vertices[current]->GetArcs();
		auto it = arcs.begin();
		while (it != arcs.end())
		{
			if (it->GetDestination() == vertices[predecessor[current]])
				break;
			++it;
		}
		if (it->GetData() == "I-5")
		{
			time += it->GetWeight() / 65.0;
		}
		else
		{
			time += it->GetWeight() / 55.0;
		}
		if (path.empty() || it->GetData() != path.top().GetData())
			path.push(*it);
		current = predecessor[current];
	}
	int hours = time;
	int minutes = (time - hours)*60;
	cout << "It will take " << hours << " hours and " << minutes << " minutes." << endl;
	cout << "The path is:" << endl;
	while (!path.empty())
	{
		cout << path.top().GetData() << " ";
		path.pop();
	}
	cout << endl;
}
