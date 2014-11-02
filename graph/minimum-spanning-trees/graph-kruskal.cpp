#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

/*
kruskal_mst - O(m * log(n) + n^2)

kruskal_mst_dsu - O(m * log(n))

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

const int INF = 1000000;

// disjoint set union implementation
class DSU
{
private:
    int parent[INF];
    int rank[INF];
public:
    void make_set(int v);
    int find_set(int v);
    void union_sets(int a, int b);
};

void DSU::make_set(int v) 
{
    parent[v] = v;
    rank[v] = 0;
}

int DSU::find_set(int v) 
{
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void DSU::union_sets(int a, int b) 
{
    a = find_set(a);
    b = find_set(b);

    if (a != b) 
    {
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) ++rank[a];
    }
}

// kruskal algorithm implementation
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
    int kruskal_mst();
    int kruskal_mst_dsu();
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

int Graph::kruskal_mst()
{
    result.clear();
    sort(edge_set.begin(), edge_set.end());

    vector<int> tree(n);
    for (int i = 0; i < n; ++i) tree[i] = i;

    int cost(0);
    for (int i = 0; i < m; ++i)
    {
        int a = edge_set[i].second.first,
            b = edge_set[i].second.second,
            len = edge_set[i].first;

        if (tree[a] != tree[b])
        {
            cost += len;
            result.push_back(make_pair(make_pair(a, b), len));

            int old_t = tree[a], new_t = tree[b];

            for (int j = 0; j < n; ++j)
                if (tree[j] == old_t) tree[j] = new_t;
        }
    }

    return cost;
}

int Graph::kruskal_mst_dsu()
{
    result.clear();
    sort(edge_set.begin(), edge_set.end());

    DSU dsu;
    for (int i = 0; i < n; ++i) dsu.make_set(i);

    int cost(0);
    for (int i = 0; i < m; ++i)
    {
        int a = edge_set[i].second.first,
            b = edge_set[i].second.second,
            len = edge_set[i].first;

        if (dsu.find_set(a) != dsu.find_set(b))
        {
            cost += len;
            result.push_back(make_pair(make_pair(a, b), len));
            dsu.union_sets(a, b);
        }
    }

    return cost;
}

void Graph::print_mst() 
{
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i)
        cout << '(' << result[i].first.first << ',' << result[i].first.second << ") " << result[i].second << endl;
    cout << endl;
}

int main(int argc, char const *argv[])
{
    Graph g;
    g.read_graph();
    
    cout << "cost: " << g.kruskal_mst() << endl;
    g.print_mst();

    cout << "cost: " << g.kruskal_mst_dsu() << endl;
    g.print_mst();
    
    return 0;
}