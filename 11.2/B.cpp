#include <bits/stdc++.h>

const int maxn = 1e5;

int n, a[maxn + 1], b[maxn + 1];

class segt
{
private:
    struct node
    {
        int add, ass;
        bool tag;
        long long res, suma, sumb;
    } t[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x)
    {
        t[x].res = t[ls(x)].res + t[rs(x)].res;
        t[x].suma = t[ls(x)].suma + t[rs(x)].suma;
        t[x].sumb = t[ls(x)].sumb + t[rs(x)].sumb;
    }

    void build(int x, int l, int r)
    {
        t[x].add = 0;
        t[x].tag = false;

        if (l == r)
        {
            t[x].res = 1ll * a[l] * b[r];
            t[x].suma = a[r];
            t[x].sumb = b[l];
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    void pushupadd(int x, int l, int r, int v)
    {
        t[x].res += 1ll * v * t[x].sumb;
        t[x].suma += 1ll * (r - l + 1) * v;
        t[x].add += v;
    }

    void pushupass(int x, int l, int r, int v)
    {
        t[x].res = 1ll * t[x].suma * v;
        t[x].sumb = 1ll * (r - l + 1) * v;
        t[x].ass = v;
        t[x].tag = true;
    }

    void pushdownadd(int x, int l, int r)
    {
        if (t[x].add != 0)
        {
            int mid = (l + r) / 2;
            pushupadd(ls(x), l, mid, t[x].add);
            pushupadd(rs(x), mid + 1, r, t[x].add);
            t[x].add = 0;
        }
    }

    void pushdownass(int x, int l, int r)
    {
        if (t[x].tag)
        {
            int mid = (l + r) / 2;
            pushupass(ls(x), l, mid, t[x].ass);
            pushupass(rs(x), mid + 1, r, t[x].ass);
            t[x].tag = false;
        }
    }

    void add(int x, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
        {
            pushupadd(x, l, r, v);
            return;
        }

        pushdownadd(x, l, r);
        pushdownass(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid)
            add(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            add(rs(x), mid + 1, r, ql, qr, v);
        update(x);
    }

    void assign(int x, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
        {
            pushupass(x, l, r, v);
            return;
        }

        pushdownadd(x, l, r);
        pushdownass(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid)
            assign(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            assign(rs(x), mid + 1, r, ql, qr, v);
        update(x);
    }

public:
    void build() { build(1, 1, n); }

    void add(int l, int r, int v) { add(1, 1, n, l, r, v); }

    void assign(int l, int r, int v) { assign(1, 1, n, l, r, v); }

    long long query() { return t[1].res; }
} t;

int main()
{
    std::freopen("car.in", "r", stdin);
    std::freopen("car.out", "w", stdout);

    int m;
    std::scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; ++i)
        std::scanf("%d%d", a + i, b + i);

    t.build();
    char op[4];
    for (int i = 0; i < m; ++i)
    {
        int l, r, v;
        std::scanf("%s%d%d%d", op, &l, &r, &v);

        if (op[0] == 'S')
            t.assign(l, r, v);
        else
            t.add(l, r, v);

        std::printf("%lld\n", t.query());
    }
    return 0;
}