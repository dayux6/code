#include <bits/stdc++.h>

const int maxn = 1e5, mod = 1e9 + 7;

int n, a[maxn + 1];

class segt
{
private:
    struct node
    {
        int sum, add, diff;
    } t[maxn * 4];

    inline int ls(int x) { return x * 2; }
    inline int rs(int x) { return x * 2 + 1; }

    inline void update(int x) { t[x].sum = (t[ls(x)].sum + t[rs(x)].sum) % mod; }

    void build(int x, int l, int r)
    {
        t[x].add = t[x].diff = 0;
        if (l == r)
        {
            t[x].sum = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    inline void pushupadd(int x, int l, int r, int v)
    {
        t[x].sum = (t[x].sum + 1ll * (r - l + 1) * v % mod) % mod;
        t[x].add = (t[x].add + v) % mod;
    }

    inline void pushup(int x, int l, int r, int fir, int diff)
    {
        pushupadd(x, l, r, fir);
        t[x].sum = (t[x].sum + (1ll * (r - l + 1) * (r - l) / 2) % mod * diff % mod) % mod;
        t[x].diff = (t[x].diff + diff) % mod;
    }

    inline void pushdownadd(int x, int l, int r)
    {
        if (t[x].add != 0)
        {
            int mid = (l + r) / 2;
            pushupadd(ls(x), l, mid, t[x].add);
            pushupadd(rs(x), mid + 1, r, t[x].add);
            t[x].add = 0;
        }
    }

    inline void pushdown(int x, int l, int r)
    {
        if (t[x].diff != 0)
        {
            int mid = (l + r) / 2;
            pushup(ls(x), l, mid, 0, t[x].diff);
            pushup(rs(x), mid + 1, r, 1ll * (mid - l + 1) * t[x].diff % mod, t[x].diff);
            t[x].diff = 0;
        }
    }

    void modifyadd(int x, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
        {
            pushupadd(x, l, r, v);
            return;
        }

        pushdownadd(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid)
            modifyadd(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            modifyadd(rs(x), mid + 1, r, ql, qr, v);
        update(x);
    }

    void modify(int x, int l, int r, int ql, int qr, int diff)
    {
        if (ql <= l && r <= qr)
        {
            pushup(x, l, r, 1ll * l * diff % mod, diff);
            return;
        }

        pushdownadd(x, l, r);
        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr, diff);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr, diff);
        update(x);
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[x].sum;

        pushdownadd(x, l, r);
        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
            return (query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr)) % mod;
    }

public:
    void build() { build(1, 1, n); }

    void modify()
    {
        int l, r, x, b;
        std::cin >> l >> r >> x >> b;
        modifyadd(1, 1, n, l, r, (x + 1ll * l * b % mod) % mod);
        modify(1, 1, n, l, r, -b);
    }

    int query(int p) { return query(1, 1, n, p, p); }

    int query()
    {
        int l, r;
        std::cin >> l >> r;
        return query(1, 1, n, l, r);
    }
} t;

int main()
{
    freopen("D.in", "r", stdin);

    int m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    t.build();
    for (int i = 0; i < m; ++i)
    {
        bool b;
        std::cin >> b;

        if (b)
            std::cout << (t.query() + mod) % mod << std::endl;
        else
            t.modify();
    }
    return 0;
}