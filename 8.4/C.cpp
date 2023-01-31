#include <bits/stdc++.h>

const int maxn = 2e5;

int p[maxn + 1], c[maxn + 1], f[maxn + 1];

class segt
{
private:
    int n, minh;
    struct node
    {
        int maxh, lmin;

        node() : maxh(0), lmin(INT_MAX) {}
    } t[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    int query(int x, int l, int r, int limh)
    {
        if (t[x].maxh <= limh)
            return INT_MAX;
        if (l == r)
            return f[t[x].maxh];

        int mid = (l + r) / 2;
        if (t[rs(x)].maxh <= limh)
            return query(ls(x), l, mid, limh);
        else
            return std::min(t[x].lmin, query(rs(x), mid + 1, r, limh));
    }

    void update(int x, int l, int r)
    {
        t[x].maxh = std::max(t[ls(x)].maxh, t[rs(x)].maxh);

        int mid = (l + r) / 2;
        t[x].lmin = query(ls(x), l, mid, t[rs(x)].maxh);
    }

    void modify(int x, int l, int r, int p, int v)
    {
        if (l == r)
        {
            t[x].maxh = v;
            return;
        }

        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x, l, r);
    }

    int getminf(int x, int l, int r, int p)
    {
        int mid = (l + r) / 2;
        if (r <= p)
        {
            int ret = query(x, l, r, minh);
            minh = std::max(minh, t[x].maxh);
            return ret;
        }
        if (l == r)
            return 0;

        int ret = INT_MAX;
        if (p > mid)
            ret = std::min(ret, getminf(rs(x), mid + 1, r, p));
        return std::min(getminf(ls(x), l, mid, p), ret);
    }

public:
    segt(int _n) : n(_n) {}

    void modify(int p, int v) { modify(1, 1, n, p, v); }

    int query(int p)
    {
        minh = 0;
        return getminf(1, 1, n, p);
    }
};

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    f[1] = c[1];
    segt t(n);
    t.modify(p[1], 1);
    for (int i = 2; i <= n; ++i)
    {
        f[i] = t.query(p[i] - 1);
        if (f[i] ^ INT_MAX)
            f[i] += c[i];
        else
            f[i] = c[i];
        t.modify(p[i], i);
    }

    std::cout << t.query(n) << std::endl;
    return 0;
}