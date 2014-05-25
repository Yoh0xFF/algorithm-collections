#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

/*
O(n + m)
n - number of vertex
m - number of edges
*/

/*
12 14
0 1
0 2
1 3
2 3
3 4
4 5
4 6
5 7
6 7
7 8
8 9
8 10
9 11
10 11
*/

class Graph
{
private:
	int n, m, dfs_timer;
	vector< vector<int> > graph;
	vector<bool> used;
	vector<int> t_in, f_up;

	void is_cutpoint(int v);
	void dfs_visit(int v, int p = -1);
public:
	Graph();
	void read_graph();
	void find_cutpoints();
};

void Graph::is_cutpoint(int v)
{
	cout << v << endl;
}

void Graph::dfs_visit(int v, int p) 
{
	used[v] = true;
	t_in[v] = f_up[v] = ++dfs_timer;
	
	int children(0);	
	for (int i = 0; i < graph[v].size(); ++i)
	{
		int to = graph[v][i];

		if (to == p) continue;

		if (used[to])
			f_up[v] = min(f_up[v], t_in[to]);
		else
		{
			dfs_visit(to, v);

			f_up[v] = min(f_up[v], f_up[to]);

			if (f_up[to] >= t_in[v] && p != -1) is_cutpoint(v);

			++children;
		}
	}

	if (p == -1 && children > 1) is_cutpoint(v);
}

Graph::Graph(): n(0), m(0), dfs_timer(0)
{}

void Graph::read_graph() 
{
	cin >> n >> m;

	vector<int>	tmp;
	for (int i = 0; i < n; ++i) graph.push_back(tmp);

	int x(0), y(0);
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x); // for undirected graphs
	}

	cout << endl;
	getchar();
}

void Graph::find_cutpoints() 
{
	dfs_timer = 0;
	used.assign(n, false);
	t_in.assign(n, 0);
	f_up.assign(n, 0);

	dfs_visit(0);
}

int main(int argc, char const *argv[])
{
	Graph g;
	g.read_graph();
	g.find_cutpoints();
	return 0;
}