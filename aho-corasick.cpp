#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct node
{
	int parent;
	int in;
	bool flag;
	vector<int> index;
	vector<int> next;

	node()
	{
		parent = 0;
		flag = false;
		next.assign(26, -1);
	}
};

int n;
string t; 
vector<int> b;
vector<node> tr;
vector<int> suf, sup, ans;
vector<vector<int>> go;

void add(string s, int ind)
{
	int cur = 0;

	for (int i = 0; i < s.size(); ++i)
	{
		if (tr[cur].next[s[i] - 'a'] == -1)
		{
			tr.push_back(node());
			tr[cur].next[s[i] - 'a'] = tr.size() - 1;
			tr[tr.size() - 1].parent = cur;
			tr[tr.size() - 1].in = s[i] - 'a';
		}
		cur = tr[cur].next[s[i] - 'a'];
	}

	tr[cur].index.push_back(ind);
	tr[cur].flag = true;
}

void aho_corasick()
{
	suf[0] = -1;

	for (int v : b)
	{
		if (tr[v].parent == 0)
			suf[v] = 0;
		else
			suf[v] = go[suf[tr[v].parent]][tr[v].in];

		for (int c = 0; c < 26; ++c)
		{
			if (tr[v].next[c] != -1)
				go[v][c] = tr[v].next[c];
			else if (v == 0)
				go[v][c] = 0;
			else
				go[v][c] = go[suf[v]][c];
		}

		if (v == 0)
			sup[v] = -1;
		if (tr[suf[v]].flag)
			sup[v] = suf[v];
		else
			sup[v] = sup[suf[v]];
	}
}

int main()
{
	//freopen("input", "r", stdin);
	ios::sync_with_stdio(false);

	cin >> n;
	tr.push_back(node());

	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		add(s, i);
	}	

	suf.assign(tr.size(), 0);
	sup.assign(tr.size(), -1);
	go.assign(tr.size(), vector<int>(26, -1));

	queue<int> q;
	q.push(0);

	vector<int> used(tr.size(), 0);
	used[0] = 1;

	while (!(q.empty()))
	{
		int v = q.front();
		b.push_back(v);
		q.pop();

		for (int c = 0; c < 26; ++c)
			if (tr[v].next[c] != -1)
			{
				int to = tr[v].next[c];
				if (!used[to])
				{
					used[to] = 1;
					q.push(to);
				}
			}
	}

	aho_corasick();

	cin >> t;
	ans.assign(n, 0);

	int cur = 0, ncur;
	vector<int> vis(tr.size(), 0);

	for (int i = 0; i < t.size(); ++i)
	{
		cur = go[cur][t[i] - 'a'];
		ncur = cur;

		if (!vis[ncur])
			while (ncur != -1 && !vis[ncur])
			{
				vis[ncur] = 1;
				for (int k : tr[ncur].index)
					ans[k] = 1;
				ncur = sup[ncur];
			}
	}

	for (int i : ans)
		if (i) cout << "YES\n";
		else cout << "NO\n";

	return 0;
}