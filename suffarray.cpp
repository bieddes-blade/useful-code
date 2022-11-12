#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 1000000;

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

	for (int i = 1; i < n; ++i)
		cout << p[i] + 1 << " ";
}

int main()
{
	//freopen("input", "r", stdin);

	string s;
	cin >> s;

	s += "#";
	
	build_array(s.size(), s);

	return 0;
}