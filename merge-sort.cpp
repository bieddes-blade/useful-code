#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int pos = 0, all = -1, cur;

vector<int> merge(vector<int> a, vector<int> b, int start, int middle)
{   
    //cout << start << " " << middle << "\n";
    vector<int> res;
    int i = 0, j = 0;

    while (i < a.size() && j < b.size())
        if (a[i] <= b[j])
            res.push_back(a[i]), ++i;
        else
            res.push_back(b[j]), ++j, cur += middle - start - i;

    for (int z = i; z < a.size(); ++z)
    	res.push_back(a[z]);//, cur += middle - start - i;
    for (int z = j; z < b.size(); ++z)
    	res.push_back(b[z]);

    return res;
}

vector<int> ms(vector<int> a, int start, int finish)
{
    if (a.size() <= 1)
        return a;
    
    vector<int> l, r;
    int middle = a.size() / 2;

    for (int i = 0; i < middle; ++i)
    	l.push_back(a[i]);
    for (int i = middle; i < a.size(); ++i)
        r.push_back(a[i]);

    middle = (start + finish) / 2;

    return merge(ms(l, start, middle), ms(r, middle, finish), start, middle);
}

int main()
{
	//freopen("0", "r", stdin);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < k; ++i)
    {
        cur = 0;
    	vector<int> v(n), t(n);
    	for (int j = 0; j < n; ++j)
            cin >> v[j];
    	t = ms(v, 0, n);

        //cout << cur << "\n";

        if (cur > all)
            all = cur, pos = i + 1;
    }

    cout << pos << "\n";

	return 0;
}
