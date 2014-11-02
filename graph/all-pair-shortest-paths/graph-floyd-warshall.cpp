#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility> 

using namespace std;

/*
O(n^3)

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
    vector< vector<int> > d;
    vector< vector<int> > p;

    void debug(int k);
public:
    Graph();
    void read_graph();
    void floyd_warshall();
    void print_path(int i, int j);
    void print_all_path();
};

void Graph::debug(int k) 
{
    cout << "step: " << k << endl;
    
    cout << "--- distance" << endl;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j)
        {
            cout << '[' << i << ',' << j << "]\t";
            if (d[i][j] == INF) 
                cout << "INF" << '\t';
            else
                cout << d[i][j] << '\t';
        } 
        cout << endl;
    }

    cout << "--- parent" << endl;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j)
        {
            cout << '[' << i << ',' << j << "]\t";
            cout << p[i][j] << '\t';
        } 
        cout << endl;
    }

    cout << endl;

    getchar();
}

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
        // graph[y].push_back(make_pair(x, d)); // for undirected graphs
    }

    cout << endl;
    getchar();
}

void Graph::floyd_warshall()
{
    vector<int> tmp(n, -1);
    d.assign(n, tmp);
    p.assign(n, tmp);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = INF;

    for (int v = 0; v < n; ++v)
        for (int j = 0; j < graph[v].size(); ++j)
        {
            int to = graph[v][j].first, len = graph[v][j].second;
            d[v][to] = len;
        }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (d[i][k] < INF && d[k][j] < INF) 
                {
                    if (d[i][k] + d[k][j] < d[i][j])
                    {
                        d[i][j] = d[i][k] + d[k][j];    
                        p[i][j] = k;
                    }
                }

        debug(k);       
    }
}

void Graph::print_path(int i, int j)
{
    if (p[i][j] == -1)
    {
        cout << i << ' ' << j << ", ";  
        return;
    }
    print_path(i, p[i][j]);
    print_path(p[i][j], j);
}

void Graph::print_all_path()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << "path " << i << ' ' << j << ":\n\t";
            this->print_path(i, j);
            cout << "length = " << d[i][j] << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    Graph g;
    g.read_graph();
    g.floyd_warshall();
    g.print_all_path();
    return 0;
}