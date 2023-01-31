#include <bits/stdc++.h>

int dfc, *a, *fa, *dep, *sum, *hs, *top, *dfn, *nv;
std::vector<int> *g;

class segt
{
private:
    int n;
    struct node
    {
        int cnt, max, tag;
        long long sum;
    } * t;
    int ls(int);
    int rs(int);
    void update(int);
    void build(int, int, int);
    void pushup(int, int, int, int);
    void pushdown(int, int, int);
    void modify(int, int, int, int, int, int);
    long long query(int, int, int, int, int);

public:
    segt(int);
    void modify(int, int, int);
    long long query(int, int);
};

segt::segt(int _n) : n(_n), t(new node[_n * 4]) { build(1, 1, _n); }

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x)
{
    t[x].sum = t[ls(x)].sum + t[rs(x)].sum;
    t[x].cnt = t[ls(x)].cnt + t[rs(x)].cnt;
    t[x].max = std::max(t[ls(x)].max, t[rs(x)].max);
}

void segt::build(int x, int l, int r)
{
    t[x].tag = 0;
    if (l == r)
    {
        if (nv[l] >= 0)
        {
            t[x].sum = nv[l];
            t[x].cnt = 0;
            t[x].max = INT_MIN;
        }
        else
        {
            t[x].sum = -nv[l];
            t[x].cnt = 1;
            t[x].max = nv[l];
        }
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
    update(x);
}

void segt::pushup(int x, int l, int r, int v)
{
    if (t[x].cnt == 0)
    {
        t[x].sum += 1ll * (r - l + 1) * v;
        t[x].tag += v;
    }
    else if (t[x].max + v < 0)
    {
        t[x].sum += 1ll * (r - l + 1 - t[x].cnt * 2) * v;
        t[x].max += v;
        t[x].tag += v;
    }
    else if (l == r)
    {
        t[x].sum = v - t[x].sum;
        t[x].cnt = 0;
        t[x].max = INT_MIN;
    }
    else
    {
        int mid = (l + r) / 2;
        pushup(ls(x), l, mid, v + t[x].tag);
        pushup(rs(x), mid + 1, r, v + t[x].tag);
        t[x].tag = 0;
        update(x);
    }
}

void segt::pushdown(int x, int l, int r)
{
    if (t[x].tag != 0)
    {
        int mid = (l + r) / 2;
        pushup(ls(x), l, mid, t[x].tag);
        pushup(rs(x), mid + 1, r, t[x].tag);
        update(x);
        t[x].tag = 0;
    }
}

void segt::modify(int x, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        pushup(x, l, r, v);
        return;
    }
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid)
        modify(ls(x), l, mid, ql, qr, v);
    if (qr > mid)
        modify(rs(x), mid + 1, r, ql, qr, v);
    update(x);
}

long long segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x].sum;
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else
        return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
}

void segt::modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }

long long segt::query(int l, int r) { return query(1, 1, n, l, r); }

void dfs1(int x)
{
    sum[x] = 1;
    for (int v : g[x])
        if (v != fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs1(v);
            sum[x] += sum[v];
            if (hs[x] == 0 || sum[v] > sum[hs[x]])
                hs[x] = v;
        }
}

void dfs2(int x, int t)
{
    top[x] = t;
    dfn[x] = ++dfc;
    nv[dfc] = a[x];
    if (hs[x] != 0)
    {
        dfs2(hs[x], t);
        for (int v : g[x])
            if (v != fa[x] && v != hs[x])
                dfs2(v, v);
    }
}

int main()
{
    freopen("BZOJ4127.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;
    a = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    g = new std::vector<int>[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    fa = new int[n + 1];
    dep = new int[n + 1];
    dep[1] = 1;
    sum = new int[n + 1];
    hs = new int[n + 1]();
    dfs1(1);
    top = new int[n + 1];
    dfn = new int[n + 1];
    nv = new int[n + 1];
    dfs2(1, 1);
    segt t(n);
    for (int i = 0; i < m; ++i)
    {
        int op;
        std::cin >> op;
        switch (op)
        {
        case 1:
        {
            int u, v, d;
            std::cin >> u >> v >> d;
            while (top[u] != top[v])
            {
                if (dep[top[u]] < dep[top[v]])
                    std::swap(u, v);
                t.modify(dfn[top[u]], dfn[u], d);
                u = fa[top[u]];
            }
            if (dep[u] > dep[v])
                std::swap(u, v);
            t.modify(dfn[u], dfn[v], d);
            break;
        }
        case 2:
        {
            int u, v;
            std::cin >> u >> v;
            long long res = 0;
            while (top[u] != top[v])
            {
                if (dep[top[u]] < dep[top[v]])
                    std::swap(u, v);
                res += t.query(dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            }
            if (dep[u] > dep[v])
                std::swap(u, v);
            std::cout << res + t.query(dfn[u], dfn[v]) << std::endl;
            break;
        }
        }
    }
    return 0;
}