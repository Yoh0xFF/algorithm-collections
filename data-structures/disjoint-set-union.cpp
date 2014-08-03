#include <iostream>

using namespace std;

const int INF = 1000000;

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

int main(int argc, char const *argv[])
{
	DSU dsu;

	dsu.make_set(1);
	dsu.make_set(2);
	dsu.make_set(3);
	dsu.make_set(4);
	dsu.make_set(5);

	dsu.union_sets(1, 2);
	dsu.union_sets(3, 4);
	dsu.union_sets(2, 5);

	cout << dsu.find_set(1) << endl;
	cout << dsu.find_set(2) << endl;
	cout << dsu.find_set(3) << endl;
	cout << dsu.find_set(4) << endl;
	cout << dsu.find_set(5) << endl;

	return 0;
}