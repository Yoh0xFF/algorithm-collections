#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

/*
kruskal_mst - O(m * log(n) + n^2)
n - number of vertex
m - number of edges
*/

/* test case

9 14
0 1 4
0 6 8
1 2 8
1 6 11
2 3 7
2 4 2
2 8 4
3 5 9
3 8 14
4 6 7
4 7 6
5 8 10
6 7 1
7 8 2

5 8
0 1 4
0 3 2
1 2 1
1 3 10
1 4 8
2 3 9
2 4 5
3 4 15

*/

const int INF = 1000000000;

class Graph
{
private:
	int n, m;
	vector< vector< pair<int, int> > > graph;
	vector< pair< int, pair<int, int> > > edge_set;
	vector< pair< pair<int, int>, int> > result;
public:
	Graph();
	void read_graph();
	void kruskal_mst();
	void print_mst();
};

Graph::Graph(): n(0), m(0) {}

void Graph::read_graph() 
{
	cin >> n >> m;

	vector< pair<int, int> > tmp;
	for (int i = 0; i < n; ++i) graph.push_back(tmp);

	int x(0), y(0), d(0);
	for (int i = 0; i < m; ++i) 
	{
		cin >> x >> y >> d;
		graph[x].push_back(make_pair(y, d));
		graph[y].push_back(make_pair(x, d)); // for undirected graphs

		edge_set.push_back(make_pair(d, make_pair(x, y)));
	}

	cout << endl;
	getchar();
}

void Graph::kruskal_mst()
{
	sort(edge_set.begin(), edge_set.end());

	vector<int> tree(n);
	for (int i = 0; i < n; ++i) tree[i] = i;

	for (int i = 0; i < m; ++i)
	{
		int a = edge_set[i].second.first,
			b = edge_set[i].second.second,
			len = edge_set[i].first;

		if (tree[a] != tree[b])
		{
			result.push_back(make_pair(make_pair(a, b), len));

			int old_t = tree[a], new_t = tree[b];

			for (int j = 0; j < n; ++j)
				if (tree[j] == old_t) tree[j] = new_t;
		}
	}
}

void Graph::print_mst() 
{
	sort(result.begin(), result.end());
	for (int i = 0; i < result.size(); ++i)
		cout << '(' << result[i].first.first << ',' << result[i].first.second << ") " << result[i].second << endl;
}

int main(int argc, char const *argv[])
{
	Graph g;
	g.read_graph();
	g.kruskal_mst();
	g.print_mst();
	return 0;
}