#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

void read_graph(vector< vector<int> > &g, int &n, int &m);

void dfs_visit(const vector< vector<int> > &g, int v);

int main(int argc, char const *argv[]) {
	vector< vector<int> > g;
	int n(0), m(0);

	read_graph(g, n, m);

	vector<int> color, parent, t_in, t_out; // 0, 1, 2

	for (int i = 0; i < n; ++i) {
		if (color[i] == 0) {
			dfs_visit(g, i);
		}
	}

	return 0;
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

void dfs_visit(const vector< vector<int> > &g, int v) {
	
}