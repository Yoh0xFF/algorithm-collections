#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <algorithm>
#include <utility> 

using namespace std;

/*
witout set
O(n^2 + m)

with set (can be replaced with priority_queue)
O(m*log(n))

n - number of vertex
m - number of edges
*/

/* test case

5 10
0 1 10
0 2 5
1 2 2
1 3 1
2 1 3
2 3 9
2 4 2
3 4 4
4 3 6
4 0 7

*/

const int INF = 1000000000;

class Graph 
{
private:
	int n, m;
	vector< vector< pair<int, int> > > graph;
	vector<int> d, p;
	vector<bool> u;

	void debug();
public:
	Graph();
	void read_graph();
	void dijkstra(int s);
	void dijkstra_set(int s);
	void print_shortest_path(int to);
	void print_all_shortest_path();
};

Graph::Graph(): n(0), m(0) {}

void Graph::debug() 
{
	cout << "--- distance" << endl;
	for (int i = 0; i < d.size(); ++i) cout << d[i] << ' ';
	cout << endl;

	cout << "--- parent" << endl;
	for (int i = 0; i < p.size(); ++i) cout << p[i] << ' ';
	cout << endl;

	getchar();
}

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
		// graph[y].push_back(make_pair(x, d)); // for undirected graphs
	}

	cout << endl;
	getchar();
}

void Graph::dijkstra(int s)
{
	u.assign(n, false);
	d.assign(n, INF);
	p.assign(n, -1);

	d[s] = 0;
	for (int i = 0; i < n; ++i)
	{
		int v = -1;
		for (int j = 0; j < n; ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		
		if (d[v] == INF) break;

		u[v] = true;

		for (int j = 0; j < graph[v].size(); ++j) 
		{
			int to = graph[v][j].first, len = graph[v][j].second;

			if (d[v] + len < d[to])
			{
				d[to] = d[v] + len;
				p[to] = v;
			}
		}

		debug();
	}

	debug();
}

void Graph::dijkstra_set(int s)
{
	d.assign(n, INF);
	p.assign(n, -1);

	d[s] = 0;
	set< pair<int, int> > q;
	q.insert(make_pair(d[s], s));
	
	while (!q.empty())
	{
		int v = q.begin()->second;
		q.erase(q.begin());

		for (int i = 0; i < graph[v].size(); ++i)
		{
			int to = graph[v][i].first, len = graph[v][i].second;

			if (d[v] + len < d[to])
			{
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert(make_pair(d[to], to));
			}
		}

		debug();
	}

	debug();
}

void Graph::print_shortest_path(int to) 
{
	vector<int> path;

	for (int v = to; v != -1; v = p[v]) path.push_back(v);

	reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); ++i) cout << path[i] << ' ';
	cout << endl;
}

void Graph::print_all_shortest_path()
{
	for (int i = 0; i < n; ++i) 
	{
		cout << "from: " << 0 
			<< " to: " << i 
			<< " distance: " << d[i] 
			<< endl;

		this->print_shortest_path(i);
	}
}

int main(int argc, char const *argv[])
{
	Graph g;
	g.read_graph();
	g.dijkstra(0);
	// g.dijkstra_set(0);
	g.print_all_shortest_path();

	return 0;
}