#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>

using namespace std;

/*
O(m * log(n))
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
	vector<int> p, k;
	vector<bool> u;
public:
	Graph();
	void read_graph();
	void prim_mst(int s);
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
	}

	cout << endl;
	getchar();
}

void Graph::prim_mst(int s) 
{
	p.assign(n, -1);
	k.assign(n, INF);
	u.assign(n, false);

	k[s] = 0;
	
	set< pair<int, int> > q;
	q.insert(make_pair(k[s], s));

	while (!q.empty())
	{
		int v = q.begin()->second;
		q.erase(q.begin());
		
		u[v] = true;

		for (int i = 0; i < graph[v].size(); ++i) 
		{
			int to = graph[v][i].first, len = graph[v][i].second;

			if (!u[to] && len < k[to])
			{
				q.erase(make_pair(k[to], to));
				p[to] = v;
				k[to] = len;
				q.insert(make_pair(k[to], to));
			}
		}
	}
}

void Graph::print_mst() 
{
	for (int v = 0; v < n; ++v)
		cout << '(' 
			<< p[v] 
			<< ',' 
			<< v 
			<< ") " 
			<< k[v] 
			<< endl;
}

int main(int argc, char const *argv[])
{
	Graph g;
	g.read_graph();
	g.prim_mst(0);
	g.print_mst();
	return 0;
}