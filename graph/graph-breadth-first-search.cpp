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
8 10
0 1
1 2
0 3
3 4
3 6
4 6
4 5
5 7
7 6
5 6
*/

class Graph
{
private:
	int n, m;
	vector< vector<int> > graph;
	queue<int> q;
	vector<bool> used;
	vector<int> distance, parent;

	void debug();
public:
	Graph();
	void read_graph();
	void bfs(int s);
	void print_shortest_path(int to);
};

Graph::Graph(): n(0), m(0) {}

void Graph::debug() {
	cout << "--- queue" << endl;
	queue<int> tmp_q = q;
	while (!tmp_q.empty()) {
		cout << tmp_q.front() << ' ';
		tmp_q.pop();
	}
	cout << endl;

	cout << "--- used" << endl;
	for (int i = 0; i < used.size(); ++i) cout << used[i] << ' ';
	cout << endl;

	cout << "--- distance" << endl;
	for (int i = 0; i < distance.size(); ++i) cout << distance[i] << ' ';
	cout << endl;

	cout << "--- parent" << endl;
	for (int i = 0; i < parent.size(); ++i) cout << parent[i] << ' ';
	cout << endl << endl;

	getchar();
}

void Graph::read_graph() {
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		vector<int> tmp;
		graph.push_back(tmp);
	}

	used.resize(n);
	distance.resize(n);
	parent.resize(n);

	for (int i = 0; i < m; ++i) {
		int x(0), y(0);
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);	
	}

	cout << endl;
	getchar();	
}

void Graph::bfs(int s) {
	q.push(s);
	used[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		debug();
		
		int v = q.front();
		q.pop();
		for (size_t i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i];
			if (!used[to]) {
				q.push(to);
				used[to] = true;
				distance[to] = distance[v] + 1;
				parent[to] = v;
			}
		}
	}
}

void Graph::print_shortest_path(int to) {
	if (!used[to]) {
		cout << "No path \n";
	} else {
		vector<int> path;
		for (int v = to; v != -1; v = parent[v]) {
			path.push_back(v);
		}
		reverse(path.begin(), path.end());
		for (size_t i = 0; i < path.size(); ++i) {
			if (i > 0) {
				cout << ',';
			}
			cout << path[i];
		}
		cout << endl;
	}
}

int main() {
	Graph g;
	g.read_graph();
	g.bfs(0);
	g.print_shortest_path(7);
}


