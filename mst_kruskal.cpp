// may the force be with this code

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, ans = 0;
vector<int> root;
vector<pair<int, pair<int, int>>> g;

int find(int v)
{
	if (v == root[v])
		return root[v];
	else
		return root[v] = find(root[v]);
}

void merge(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);
	if (rand() & 1)
		swap(v1, v2);
	if (v1 != v2)
		root[v1] = v2;
}

int main()
{
	//freopen("0", "r", stdin);

	cin >> n >> m;
	g.resize(m);
	root.resize(n);

	for (int i = 0; i < n; ++i)
		root[i] = i;

	int a, b, w;
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b >> w;
		--a, --b;
		g[i].first = w;
		g[i].second.first = a;
		g[i].second.second = b;
	}

	sort(g.begin(), g.end());

	for (int i = 0; i < m; ++i)
	{
		w = g[i].first;
		a = g[i].second.first;
		b = g[i].second.second;
		if (find(a) != find(b))
		{
			ans += w;
			merge(a, b);
		}
	}

	cout << ans;

	return 0;
}