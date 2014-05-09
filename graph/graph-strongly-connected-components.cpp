#include <iostream>
#include <vector>
#include <cstdio>

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
8 14
0 1
1 2
1 5
1 4
2 3
2 6
3 2
3 7
4 0
4 5
5 6
6 5
6 7
7 7
*/

class Graph
{
private:
	int n, m;
	vector< vector<int> > graph, graph_t, components;
	vector<int> order, component;
	vector<bool> used;

	void dfs_visit_1(int v);
	void dfs_visit_2(int v);
public:
	Graph();

	void read_graph();
	void search_components();
	void print_components();
};

Graph::Graph(): n(0), m(0) {}

void Graph::dfs_visit_1(int v) 
{
	used[v] = true;
	for (int i = 0; i < graph[v].size(); ++i)
	{
		int to = graph[v][i];
		if (!used[to]) 
		{
			dfs_visit_1(to);
		}
	}
	order.push_back(v);
}

void Graph::dfs_visit_2(int v) 
{
	used[v] = true;
	component.push_back(v);
	for (int i = 0; i < graph_t[v].size(); ++i)
	{
		int to = graph_t[v][i];
		if (!used[to]) 
		{
			dfs_visit_2(to);
		}
	}
}

void Graph::read_graph() 
{
	cin >> n >> m;

	for (int i = 0; i < m; ++i) 
	{
		vector<int> tmp;
		graph.push_back(tmp);
		graph_t.push_back(tmp);
	}

	for (int i = 0; i < m; ++i) 
	{
		int x(0), y(0);
		cin >> x >> y;
		graph[x].push_back(y);
		graph_t[y].push_back(x);
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
			dfs_visit_1(i);
		}
	}

	used.assign(n, false);
	for (int i = 0; i < n; ++i)
	{
		int v = order[n - 1 - i];
		if (!used[v]) 
		{
			dfs_visit_2(v);
		}
		if (!component.empty())
		{
			components.push_back(component);
			component.clear();	
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