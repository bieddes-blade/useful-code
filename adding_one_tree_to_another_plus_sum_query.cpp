#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int n, q;
vector<ll> tree_a, tree_b;
vector<ll> a, b, flag;

void build_a(int v, int tl, int tr)
{
    if (tl == tr)
        tree_a[v] = (tl < a.size() ? a[tl] : 0);
    else
    {
        int tm = (tl + tr) / 2;
        build_a(v * 2, tl, tm);
        build_a(v * 2 + 1, tm + 1, tr);
        tree_a[v] = tree_a[v * 2] + tree_a[v * 2 + 1];
    }
}

void build_b(int v, int tl, int tr)
{
    if (tl == tr)
        tree_b[v] = (tl < b.size() ? b[tl] : 0);
    else
    {
        int tm = (tl + tr) / 2;
        build_b(v * 2, tl, tm);
        build_b(v * 2 + 1, tm + 1, tr);
        tree_b[v] = tree_b[v * 2] + tree_b[v * 2 + 1];
    }
}

void push(int v)
{
    if (2 * v < flag.size())
    {
        flag[2 * v] += flag[v];
        tree_a[2 * v] += tree_b[2 * v] * flag[v];
    }
    if (2 * v + 1 < flag.size())
    {
        flag[2 * v + 1] += flag[v];
        tree_a[2 * v + 1] += tree_b[2 * v + 1] * flag[v];
    }
    flag[v] = 0;
}

void modify(int vl, int vr, int ql, int qr, int v)
{
    push(v);

    if (ql > qr)
        return;

    if (ql == vl && qr == vr)
    {
        flag[v] += (ll)1;
        tree_a[v] += tree_b[v] * flag[v];
        push(v);
    }

    else
    {
        push(v);

        int m = (vl + vr) / 2;

        if (ql <= min(qr, m))
            modify(vl, m, ql, min(qr, m), v * 2);
        if (qr >= max(ql, m + 1))
            modify(m + 1, vr, max(ql, m + 1), qr, v * 2 + 1);

        tree_a[v] = tree_a[v * 2] + tree_a[v * 2 + 1];
    }
}

ll get_sum(int vl, int vr, int ql, int qr, int v)
{
    push(v);

    if (ql > qr)
        return 0;

    if (ql == vl && qr == vr)
        return tree_a[v];

    else
    {
        int m = (vl + vr) / 2;
        ll tmp1 = (ll)0, tmp2 = (ll)0;

        if (ql <= min(qr, m))
            tmp1 = get_sum(vl, m, ql, min(qr, m), v * 2);
        if (qr >= max(ql, m + 1))
            tmp2 = get_sum(m + 1, vr, max(ql, m + 1), qr, v * 2 + 1);

        return tmp1 + tmp2;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("0", "r", stdin);

    cin >> n;
    a.resize(n * 2);
    b.resize(n * 2);
    
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
        
    ll bin = 1;
    while (bin < n)
        bin *= 2;
    n = bin;
    
    flag.assign(n * 2, 0);
    tree_a.resize(n * 2);
    build_a(1, 0, n - 1);
    tree_b.resize(n * 2);
    build_b(1, 0, n - 1);

    cin >> q;
 
    for (int i = 0; i < q; ++i)
    {
        int l, r;
        string query;
        cin >> query;

        if (query[0] == '?')
        {
            cin >> l >> r;
            cout << get_sum(0, n - 1, l, r, 1) << "\n";
        }
        else
        {
            cin >> l >> r;
            modify(0, n - 1, l, r, 1);
        }
    }
    
    return 0;
}