int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<int> used;

bool try_kuhn(int v)
{
	if (used[v])
		return false;
	used[v] = true;

	for (int i = 0; i < g[v].size(); ++i)
	{
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to]))
		{
			mt[to] = v;
			return true;
		}
	}
	return false;
}

int main()
{
	... чтение графа ...
	mt.assign(k, -1);

	for (int v = 0; v < n; ++v)
	{
		used.assign(n, 0);
		try_kuhn(v);
	}

	for (int i = 0; i < k; ++i)
		if (mt[i] != -1)
			cout << mt[i] + 1 << " " << i + 1 << "\n";

	return 0;
}