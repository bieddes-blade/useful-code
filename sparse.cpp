#include <bits/stdc++.h>

using namespace std;

const int ONE = 23, TWO = 21563, THREE = 16714589;
int n, m, an, u, v;
vector<int> a, lg;
vector<vector<int>> st;

int find_min(int u, int v)
{
	if (u > v)
		swap(u, v);
	int k = lg[v - u + 1];
	return min(st[k][u], st[k][v - (1 << k) + 1]);
}

int main()
{
	//freopen("input", "r", stdin);
	
	cin >> n >> m >> an >> u >> v;
	a.resize(n + 1);
	lg.resize(n + 1);
	a[1] = an;
	
	for (int i = 2; i < n + 1; ++i)
		a[i] = (ONE * a[i - 1] + TWO) % THREE;
	// записали последовательность в вектор a
	
	
	int lgc = 0, power = 1;
	for (int i = 1; i < n + 1; ++i)
	{
		if (i == power * 2)
		{
			power *= 2;
			++lgc;
		}
		lg[i] = lgc;
	}
	// заполнили массив с логарифмами
	
	
	st.resize(lg[n] + 1, vector<int>(n + 1, 0));
	st[0] = a;
	power = 1;
	
	for (int k = 1; k < lg[n] + 1; ++k)
	{
		for (int i = 1; i < n + 1 - power; ++i)
			st[k][i] = min(st[k - 1][i], st[k - 1][i + power]);
		power *= 2;
	}
	// заполнили разреженную таблицу
	
	for (int q = 0; q < m; ++q)
	{
		int ans = find_min(u, v);
		// ответили на запрос
		
		if (q == m - 1)
			cout << u << " " << v << " " << ans;
			
		u = ((17 * u + 751 + ans + 2 * (q + 1)) % n) + 1;
		v = ((13 * v + 593 + ans + 5 * (q + 1)) % n) + 1;
	}
	
	return 0;
}
