#include <bits/stdc++.h>

using namespace std;

struct pt { double x, y; };

double op(pt a, pt b, pt c) { return a.x * (b.y - c.y); }

bool cmp(pt a, pt b) { return a.x < b.x || a.x == b.x && a.y < b.y; }

bool cw(pt a, pt b, pt c) { return op(a, b, c) + op(b, c, a) + op(c, a, b) < 0; }

bool ccw(pt a, pt b, pt c) { return op(a, b, c) + op(b, c, a) + op(c, a, b) > 0; }

int n;
vector<pt> a;

void convex_hull(vector<pt> & a)
{
	if (a.size() == 1) return;

	sort(a.begin(), a.end(), &cmp);
	pt p1 = a[0], p2 = a.back();
	vector<pt> up, down;
	up.push_back(p1);
	down.push_back(p1);

	for (int i = 1; i < a.size(); ++i)
	{
		if (i == a.size() - 1 || cw(p1, a[i], p2))
		{
			while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
				up.pop_back();
			up.push_back(a[i]);
		}

		if (i == a.size() - 1 || ccw(p1, a[i], p2))
		{
			while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
				down.pop_back();
			down.push_back(a[i]);
		}
	}

	cout << up.size() + down.size() - 2 << "\n";
}

int main()
{
	freopen("input", "r", stdin);

	cin >> n;
	a.resize(n);

	for (int i = 0; i < n; ++i)
		cin >> a[i].x >> a[i].y;

	convex_hull(a);

	return 0;
}