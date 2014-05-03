#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

/*
mushaobis dro: O(n + m)
n - number of vertex
m - number of edges
*/

/*
test case
6 8
0 1
0 3
3 1
1 4
4 3
2 4
2 5
5 5
*/

class Graph
{
private:
	int n, m, dfs_timer;
	vector< vector<int> > graph;
	vector<int> color, parent, t_in, t_out; // color: 0,1,2

	void debug();
	void dfs_visit(int v);
public:
	Graph();
	void read_graph();
	void dfs();
};

Graph::Graph(): n(0), m(0), dfs_timer(0) {}

void Graph::debug() {
	cout << "--- color" << endl;
	for (int i = 0; i < color.size(); ++i) cout << color[i] << ' ';
	cout << endl;

	cout << "--- parent" << endl;
	for (int i = 0; i < parent.size(); ++i) cout << parent[i] << ' ';
	cout << endl;

	cout << "--- t_in" << endl;
	for (int i = 0; i < t_in.size(); ++i) cout << t_in[i] << ' ';
	cout << endl;

	cout << "--- t_out" << endl;
	for (int i = 0; i < t_out.size(); ++i) cout << t_out[i] << ' ';
	cout << endl << endl;
	
	getchar();
}

void Graph::read_graph() {
	cin >> n >> m;

	color.resize(n);
	parent.resize(n, -1);
	t_in.resize(n);
	t_out.resize(n);

	for (int i = 0; i < m; ++i) {
		vector<int> tmp;
		graph.push_back(tmp);
	}

	for (int i = 0; i < m; ++i) {
		int x(0), y(0);
		cin >> x >> y;
		graph[x].push_back(y);
		// graph[y].push_back(x);	
	}

	cout << endl;
	getchar();
}

void Graph::dfs() {
	for (int i = 0; i < n; ++i) {
		if (color[i] == 0) {
			dfs_visit(i);
		}
		debug();
	}
}

void Graph::dfs_visit(int v) {
	t_in[v] = ++dfs_timer;
	color[v] = 1;
	
	for (int i = 0; i < graph[v].size(); ++i) {
		int u = graph[v][i];
		if (color[u] == 0) {
			parent[u] = v;
			dfs_visit(u);
		}
	}

	color[v] = 2;
	t_out[v] = ++dfs_timer;
}

int main(int argc, char const *argv[]) {
	Graph g;
	g.read_graph();
	g.dfs();
	return 0;
}