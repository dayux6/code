#include <bits/stdc++.h>

int m, *fa, *dep, *siz, *hs, *top, dfc, *dfn;
std::vector<int> *s;

class gen
{
private:
    const int x = 1 << 16, y = INT_MAX;

public:
    int a, b, q;
    gen();
    int getint();
};

gen::gen() {}

int gen::getint()
{
    a = ((a ^ b) + (b / x) + (b * x)) & y;
    b = ((a ^ b) + (a / x) + (a * x)) & y;
    return (a ^ b) % q;
}

void mergemax(int *a, int *b, int *c)
{
    for (int i = 0; i <= m; ++i)
        a[i] = std::max(b[i], c[i]);
}

void mergef(int *a, int *b, int *c)
{
    std::fill_n(a, m + 1, 0);
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= i; ++j)
            a[i] = std::max(a[i], b[j] + c[i - j]);
}

class segt
{
private:
    int n, **a;
    struct node
    {
        int *max, *f;
    } * t;
    int ls(int);
    int rs(int);
    void update(int);
    void build(int, int, int);
    void modify(int, int, int, int, int *);
    node query(int, int, int, int, int);

public:
    segt(int, int **);
    void modify(int, int *);
    int *querymax(int, int);
    int *queryf(int, int);
};

segt::segt(int _n, int **_a) : n(_n), a(_a), t(new node[_n * 4]) { build(1, 1, _n); }

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x)
{
    mergemax(t[x].max, t[ls(x)].max, t[rs(x)].max);
    mergef(t[x].f, t[ls(x)].f, t[rs(x)].f);
}

void segt::build(int x, int l, int r)
{
    t[x].max = new int[m + 1];
    t[x].f = new int[m + 1];
    if (l == r)
        for (int i = 0; i <= m; ++i)
            t[x].max[i] = t[x].f[i] = a[l][i];
    else
    {
        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }
}

void segt::modify(int x, int l, int r, int p, int *v)
{
    if (l == r)
        for (int i = 0; i <= m; ++i)
            t[x].max[i] = t[x].f[i] = v[i];
    else
    {
        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }
}

segt::node segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x];
    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else
    {
        node nl = query(ls(x), l, mid, ql, qr), nr = query(rs(x), mid + 1, r, ql, qr), ret;
        ret.max = new int[m + 1];
        mergemax(ret.max, nl.max, nr.max);
        ret.f = new int[m + 1];
        mergef(ret.f, nl.f, nr.f);
        return ret;
    }
}

void segt::modify(int p, int *v) { modify(1, 1, n, p, v); }

int *segt::querymax(int l, int r) { return query(1, 1, n, l, r).max; }

int *segt::queryf(int l, int r) { return query(1, 1, n, l, r).f; }

void dfs(int x)
{
    siz[x] = 1;
    for (int v : s[x])
        if (v ^ fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs(v);
            siz[x] += siz[v];
            if (hs[x] == 0 || siz[v] > siz[hs[x]])
                hs[x] = v;
        }
}

void dfs(int x, int t)
{
    top[x] = t;
    ++dfc;
    dfn[x] = dfc;
    if (hs[x] != 0)
    {
        dfs(hs[x], t);
        for (int v : s[x])
            if (v ^ fa[x] && v ^ hs[x])
                dfs(v, v);
    }
}

int main()
{
    freopen("BZOJ2164.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    gen g;
    std::cin >> n >> m >> g.a >> g.b >> g.q;
    fa = new int[n + 1];
    fa[1] = 0;
    s = new std::vector<int>[n + 1];
    for (int i = 2; i <= n; ++i)
    {
        std::cin >> fa[i];
        s[fa[i]].emplace_back(i);
    }
    dep = new int[n + 1];
    dep[1] = 0;
    siz = new int[n + 1];
    hs = new int[n + 1]();
    dfs(1);
    top = new int[n + 1];
    dfn = new int[n + 1];
    dfs(1, 1);
    int **a = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        a[i] = new int[m + 1];
        a[i][0] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            a[dfn[i]][j] = g.getint();
        std::sort(a[dfn[i]] + 1, a[dfn[i]] + m + 1);
    }
    int c;
    std::cin >> c;
    segt t(n, a);
    for (int i = 0; i < c; ++i)
    {
        bool op;
        std::cin >> op;
        switch (op)
        {
        case 0:
        {
            int p;
            std::cin >> p;
            int *v = new int[m + 1];
            v[0] = 0;
            for (int i = 1; i <= m; ++i)
                v[i] = g.getint();
            std::sort(v + 1, v + m + 1);
            t.modify(dfn[p], v);
            break;
        }
        case 1:
        {
            int u, v;
            std::cin >> u >> v;
            int *f = t.queryf(dfn[u], dfn[u] + siz[u] - 1), *max = new int[m + 1]();
            if (u != v)
            {
                u = fa[u];
                while (top[u] != top[v])
                {
                    if (dep[top[u]] < dep[top[v]])
                        std::swap(u, v);
                    int *tmp = t.querymax(dfn[top[u]], dfn[u]);
                    mergemax(max, max, tmp);
                    u = fa[top[u]];
                }
                if (dep[u] > dep[v])
                    std::swap(u, v);
                int *tmp = t.querymax(dfn[u], dfn[v]);
                mergemax(max, max, tmp);
            }
            int *res = new int[m + 1];
            mergef(res, f, max);
            int ans = 0;
            for (int i = 0; i <= m; ++i)
                ans = std::max(ans, res[i]);
            std::cout << ans << '\n';
            break;
        }
        }
    }
    return 0;
}