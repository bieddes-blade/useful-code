#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 1000000;

vector<int> suf;

void build_array(int n, string s)
{
	vector<int> p(N, 0), p2(N, 0), len(N, 0), num(N + 1, 0), col(N, 0);

	int ma = n, cc = 0;

	for (int i = 0; i < n; ++i)
		ma = max(ma, (int)s[i]);

	for (int i = 0; i < n; ++i)
	{
		col[i] = s[i];
		p[i] = i;
	}

	for (int k2 = 1; k2 / 2 < n && cc != n - 1; k2 *= 2)
	{
		int k = k2 / 2;

		num.assign(ma + 1, 0);

		for (int i = 0; i < n; ++i)
			num[col[i] + 1]++;

		for (int i = 0; i < ma; ++i)
			num[i + 1] += num[i];

		for (int i = 0; i < n; ++i)
			p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;

		cc = 0;
		for (int i = 0; i < n; ++i)
		{
			cc += (i && (col[p2[i]] != col[p2[i - 1]] || col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]));
			num[p2[i]] = cc;
		}

		for (int i = 0; i < n; ++i)
			p[i] = p2[i], col[i] = num[i];
	}

	for (int i = 0; i < n; ++i)
		p2[p[i]] = i;

	suf.resize(n);
	for (int i = 0; i < n; ++i)
		suf[i] = p[i];
}

int main()
{
	freopen("input", "r", stdin);

	string s;
	cin >> s;

	s += "#";
	
	build_array(s.size(), s);

	int n = s.size();
	vector<int> lcp(n), pos(n);

	for (int i = 0; i < n; ++i)
		pos[suf[i]] = i;

	int k = 0;

	for (int i = 0; i < n; ++i)
	{
		if (k > 0)
			--k;
		if (pos[i] == n - 1)
		{
			lcp[n - 1] = -1;
			k = 0;
		}
		else
		{
			int j = suf[pos[i] + 1];
			while (max(i + k, j + k) < n && s[i + k] == s[j + k])
				++k;
			lcp[pos[i]] = k;
		}
	}

	for (int i : lcp)
		cout << i << " ";

	return 0;
}