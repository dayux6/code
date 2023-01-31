#include <bits/stdc++.h>

const int maxn = 1e5;

int n, w[maxn + 1], fa[maxn + 1], siz[maxn + 1], hs[maxn + 1], top[maxn + 1], dfc, dfn[maxn + 1];
std::vector<int> g[maxn + 1];

class segt
{
private:
    int max[maxn * 4], tag[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x) { max[x] = std::max(max[ls(x)], max[rs(x)]); }

    void build(int x, int l, int r)
    {
        if (l == r)
        {
            max[x] = -1;
            tag[x] = 0;
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    void modify(int x, int l, int r, int p, int v)
    {
        if (l == r)
        {
            max[x] = std::max(max[x], v);
            return;
        }

        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }

    void modify(int x, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
        {
            tag[x] += v;
            return;
        }

        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr, v);
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return max[x];

        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
            return std::max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
    }

    int query(int x, int l, int r, int p)
    {
        if (l == r)
            return tag[x];

        int mid = (l + r) / 2;
        if (p <= mid)
            return query(ls(x), l, mid, p) + tag[x];
        else
            return query(rs(x), mid + 1, r, p) + tag[x];
    }

public:
    void build() { build(1, 1, n); }

    void modify(int x, int v) { modify(1, 1, n, x, v); }

    void modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }

    int query(int l, int r) { return query(1, 1, n, l, r); }

    int query(int p) { return query(1, 1, n, p); }
} t;

void dfs(int x)
{
    siz[x] = 1;

    for (int v : g[x])
        if (v != fa[x])
        {
            fa[v] = x;
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
        dfs(hs[x], t);
    for (int v : g[x])
        if (v != fa[x] && v != hs[x])
            dfs(v, v);
}

int main()
{
    std::freopen("lca.in", "r", stdin);
    std::freopen("lca.out", "w", stdout);

    int m;
    std::scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; ++i)
        std::scanf("%d", w + i);

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    dfs(1);
    dfs(1, 1);

    t.build();
    char op[7];
    for (int i = 0; i < m; ++i)
    {
        int x;
        std::scanf("%s%d", op, &x);

        switch (op[0])
        {
        case 'M':
        {
            while (top[x] != 1)
            {
                t.modify(dfn[x], w[x]);
                t.modify(dfn[top[x]], dfn[x], 1);
                x = fa[top[x]];
            }
            t.modify(dfn[x], w[x]);
            t.modify(dfn[top[x]], dfn[x], 1);
            break;
        }

        case 'Q':
        {
            int res = t.query(dfn[x]) == 0 ? -1 : w[x];
            while (x != 0)
            {
                if (x != top[x])
                    res = std::max(res, t.query(dfn[top[x]], dfn[fa[x]]));
                x = top[x];
                if (t.query(dfn[fa[x]]) - t.query(dfn[x]) != 0)
                    res = std::max(res, w[fa[x]]);
                x = fa[x];
            }
            std::printf("%d\n", res);
            break;
        }
        }
    }
    return 0;
}