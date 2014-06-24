#include <iostream>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <utility> 

using namespace std;

/*
O(n * m)

n - number of vertex
m - number of edges

Works only in case, when graph doesn't contains negative-weight cycle.
*/

/* test case

5 10
0 1 6
0 3 7
1 2 5
1 3 8
1 4 -4
2 1 -2
3 2 -3
3 4 9
4 0 2
4 2 7

*/

const int INF = 1000000000;

class Graph 
{
private:
	int n, m;
	vector< vector< pair<int, int> > > graph;
	vector<int> d, p, id;

	void debug();
public:
	Graph();
	void read_graph();
	void levit(int s);
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

void Graph::levit(int s)
{
	d.assign(n, INF);
	p.assign(n, -1);
	id.assign(n, 2);
	
	d[s] = 0;
	id[s] = 1;
	
	deque<int> q;
	q.push_back(s);
	
	while (!q.empty())
	{
		int v = q.front();
		q.pop_front();
		id[v] = 0;

		for (int i = 0; i < graph[v].size(); ++i)
		{
			int to = graph[v][i].first, len = graph[v][i].second;

			if (d[v] + len < d[to])
			{
				d[to] = d[v] + len;
				p[to] = v;

				if (id[to] == 2) q.push_back(to);

				if (id[to] == 0)
				{
					q.push_front(to);
					id[to] = 1;
				}
			}
		}
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
	if (d.empty()) return;

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
	g.levit(0);
	g.print_all_shortest_path();

	return 0;
}