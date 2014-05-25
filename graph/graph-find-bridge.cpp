#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;


/*
test case
12 18
0 1
0 6
1 6
1 7
2 3
2 7
2 8
2 9
3 8
3 9
3 4
4 5
4 10
5 10
5 11
6 7
8 9
10 11
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

	void debug();
	void is_bridge(int v, int u);
	void dfs_visit(int v, int p = -1);
public:
	Graph();
	void read_graph();
	void find_bridges();
};

Graph::Graph(): n(0), m(0), dfs_timer(0) {}

void Graph::is_bridge(int v, int u)
{
	cout << v << ' ' << u << endl;
}

void Graph::debug()
{
	for (int i = 0; i < t_in.size(); ++i)
	{
		cout << t_in[i] << ' ';
	}
	cout << endl;

	for (int i = 0; i < f_up.size(); ++i)
	{
		cout << f_up[i] << ' ';
	}
	cout << endl;

	getchar();
}

void Graph::dfs_visit(int v, int p)
{
	used[v] = true;
	t_in[v] = f_up[v] = ++dfs_timer;
	for (int i = 0; i < graph[v].size(); ++i)
	{
		int to = graph[v][i];
		
		if (to == p)
		{
			continue;
		}

		if (used[to])
		{
			f_up[v] = min(f_up[v], t_in[to]);
		} else 
		{
			dfs_visit(to, v);
			f_up[v] = min(f_up[v], f_up[to]);
			if (f_up[to] > t_in[v])
			{
				is_bridge(v, to);
			}
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

void Graph::find_bridges() 
{
	dfs_timer = 0;
	used.assign(n, false);
	t_in.assign(n, 0);
	f_up.assign(n, 0);

	for (int i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfs_visit(i);
		}
	}
}

int main(int argc, char const *argv[])
{
	Graph g;
	g.read_graph();
	g.find_bridges();
	return 0;
}