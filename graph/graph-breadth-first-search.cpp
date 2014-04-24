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

void debug(queue<int> q, 
	const vector<bool> &used,
	const vector<int> &d,
	const vector<int> &p);

void read_graph(vector< vector<int> > &g, int &n, int &m);

void print_shortest_path(int to,
	const vector<bool> &used,
	const vector<int> &p);

int main() {
	vector< vector<int> > g;
	int n(0), m(0);

	read_graph(g, n, m);

	queue<int> q;
	vector<bool> used(n);
	vector<int> d(n), p(n);

	int s(0);
	q.push(s);
	used[s] = true;
	p[s] = -1;

	while (!q.empty()) {
		debug(q, used, d, p);
		getchar();
		
		int v = q.front();
		q.pop();
		for (size_t i = 0; i < g[v].size(); ++i) {
			int to = g[v][i];
			if (!used[to]) {
				q.push(to);
				used[to] = true;
				d[to] = d[v] + 1;
				p[to] = v;
			}
		}
	}

	print_shortest_path(7, used, p);
}

void debug(queue<int> q, 
	const vector<bool> &used,
	const vector<int> &d,
	const vector<int> &p) {
	cout << "--- q" << endl;
	while (!q.empty()) {
		cout << q.front() << ' ';
		q.pop();
	}
	cout << endl;

	cout << "--- used" << endl;
	for (int i = 0; i < used.size(); ++i) cout << used[i] << ' ';
	cout << endl;

	cout << "--- d" << endl;
	for (int i = 0; i < d.size(); ++i) cout << d[i] << ' ';
	cout << endl;

	cout << "--- p" << endl;
	for (int i = 0; i < p.size(); ++i) cout << p[i] << ' ';
	cout << endl << endl;
}

void read_graph(vector< vector<int> > &g, int &n, int &m) {
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		vector<int> tmp;
		g.push_back(tmp);
	}

	for (int i = 0; i < m; ++i) {
		int x(0), y(0);
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);	
	}

	cout << endl;
	getchar();	
}

void print_shortest_path(int to,
	const vector<bool> &used,
	const vector<int> &p) {
	if (!used[to]) {
		cout << "No path \n";
	} else {
		vector<int> path;
		for (int v = to; v != -1; v = p[v]) {
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