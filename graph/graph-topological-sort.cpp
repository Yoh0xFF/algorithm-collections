#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

/*
O(n + m)
n - number of vertex
m - number of edges
*/

/*
test case
7 8
0 1
0 3
1 4
4 3
2 4
2 5
2 6
5 6
*/

class Graph 
{
private:
    int n, m;
    vector< vector<int> > graph;
    vector<int> t_sort;
    vector<bool> used;

    void dfs_visit(int v);
public:
    Graph();
    void read_graph();
    void topological_sort();
    void print_topological_sort();
};

Graph::Graph(): n(0), m(0) {}

void Graph::dfs_visit(int v) 
{
    used[v] = true; 
    
    for (int i = 0; i < graph[v].size(); ++i) 
    {
        int u = graph[v][i];

        if (!used[u]) dfs_visit(u);
    }

    t_sort.push_back(v);
}

void Graph::read_graph() 
{
    cin >> n >> m;

    vector<int> tmp;
    for (int i = 0; i < n; ++i) graph.push_back(tmp);

    int x(0), y(0);
    for (int i = 0; i < m; ++i) 
    {
        cin >> x >> y;
        graph[x].push_back(y);
        // graph[y].push_back(x); // for undirected graphs
    }

    cout << endl;
    getchar();
}

void Graph::topological_sort() 
{
    used.assign(n, false);

    for (int i = 0; i < n; ++i) 
        if (!used[i]) dfs_visit(i);

    reverse(t_sort.begin(), t_sort.end());
}

void Graph::print_topological_sort() 
{
    for (int i = 0; i < t_sort.size(); ++i) 
        cout << t_sort[i] << ' ';
    cout << endl;
}

int main(int argc, char const *argv[]) 
{
    Graph g;
    g.read_graph();
    g.topological_sort();
    g.print_topological_sort();
    return 0;
}