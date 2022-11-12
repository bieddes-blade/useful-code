#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500000;
vector<vector<int>> g(MAXN, vector<int>(0)), q(MAXN, vector<int>(0));
vector<int> root(MAXN), anc(MAXN), used(MAXN);

map<pair<int, int>, int> ans;
vector<pair<int, int>> qlist;
 
inline int dsu_find(int v)
{
	return root[v] == v ? v : root[v] = dsu_find(root[v]);
}
 
inline void dsu_join(int a, int b, int new_anc)
{
	a = dsu_find(a);
	b = dsu_find (b);
	if (rand() & 1)
		swap (a, b);
	root[a] = b;
	anc[b] = new_anc;
}
 
void dfs(int v)
{
	root[v] = v;
	anc[v] = v;
	used[v] = 1;

	for (int i = 0; i < (int)g[v].size(); ++i)
		if (!used[g[v][i]])
		{
			dfs(g[v][i]);
			dsu_join(v, g[v][i], v);
		}

	for (int i = 0; i < (int)q[v].size(); ++i)
		if (used[q[v][i]])
		{
			int u = q[v][i];

			if (v < u)
				ans.insert(make_pair(make_pair(v, u), anc[dsu_find(q[v][i])] + 1));
			else
				ans.insert(make_pair(make_pair(u, v), anc[dsu_find(q[v][i])] + 1));
		}
}
 
int main()
{
	int k;
	cin >> k;
 
 	string query;
 	int a, b;

 	for (int i = 0; i < k; ++i)
 	{
 		cin >> query >> a >> b;
 		--a;
 		--b;
 		if (query == "ADD")
 		{
 			g[a].push_back(b);
 			g[b].push_back(a);
 		}
 		else
 		{
 			q[a].push_back(b);
 			q[b].push_back(a);
 			if (a < b)
 				qlist.push_back(make_pair(a, b));
 			else
 				qlist.push_back(make_pair(b, a));
 		}
 	}

	dfs(0);

	for (auto i : qlist)
		cout << ans[i] << "\n";

	return 0;
}