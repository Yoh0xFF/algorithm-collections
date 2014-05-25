#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

/*
O(n + m)
n - number of vertex
m - number of edges

Connected is usually associated with undirected graphs (two way edges): there is a path between every two nodes.

Strongly connected is usually associated with directed graphs (one way edges): there is a route between every two nodes.
*/

/*
test case
10 9
0 1
0 5
1 5
1 6
2 3
2 7
3 8
7 8
4 9
*/

class Graph 
{
private:
	int n, m;
	vector< vector<int> > graph;
	vector< vector<int> > components;
	vector<int> component;
	vector<bool> used;

	void dfs_visit(int v);
public:
	Graph();
	void read_graph();
	void search_components();
	void print_components();
};

Graph::Graph(): n(0), m(0) {}

void Graph::dfs_visit(int v) 
{
	used[v] = true;
	component.push_back(v);	
	for (int i = 0; i < graph[v].size(); ++i) 
	{
		int u = graph[v][i];
		if (!used[u]) 
		{
			dfs_visit(u);
		}
	}
}

void Graph::read_graph() 
{
	cin >> n >> m;

	for (int i = 0; i < n; ++i) 
	{
		vector<int> tmp;
		graph.push_back(tmp);
	}

	for (int i = 0; i < m; ++i) 
	{
		int x(0), y(0);
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x); // for undirected graphs
	}

	cout << endl;
	getchar();
}

void Graph::search_components() 
{
	used.assign(n, false);

	for (int i = 0; i < n; ++i) 
	{
		if (!used[i]) 
		{
			dfs_visit(i);
			if (!component.empty()) 
			{
				components.push_back(component);
				component.clear();	
			}
		}
	}
}

void Graph::print_components() 
{
	for (int i = 0; i < components.size(); ++i) 
	{
		cout << "Component #" << (i + 1) << ": ";
		for (int j = 0; j < components[i].size(); ++j) 
		{
			cout << components[i][j] << ' ';
		}
		cout << endl << endl;
	}
	cout << endl;
}

int main(int argc, char const *argv[]) 
{
	Graph g;
	g.read_graph();
	g.search_components();
	g.print_components();
	return 0;
}