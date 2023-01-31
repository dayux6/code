#include <bits/stdc++.h>

const int maxn = 3e5;

struct node
{
    int l, r, sum;

    node operator+(const node rhs) const
    {
        node ret;
        ret.l = l;
        ret.r = rhs.r;
        ret.sum = sum + rhs.sum + (r != rhs.l);
        return ret;
    }
};

int fa[maxn + 1], dep[maxn + 1], siz[maxn + 1], hs[maxn + 1], top[maxn + 1], dfc, dfn[maxn + 1], pos[maxn + 1];
std::vector<int> g[maxn + 1];

void dfs(int x)
{
    siz[x] = 1;

    for (int v : g[x])
        if (v != fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs(v);
            siz[x] += siz[v];

            if (hs[x] != 0 || siz[hs[x]] < siz[v])
                hs[x] = v;
        }
}

void dfs(int x, int t)
{
    top[x] = t;
    ++dfc;
    dfn[x] = dfc;
    pos[dfc] = -x;

    if (hs[x] != 0)
    {
        dfs(hs[x], t);

        for (int v : g[x])
            if (v != fa[x] && v != hs[x])
                dfs(v, v);
    }
}

class segt
{
private:
    int n, tag[maxn * 4];
    node t[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void build(int x, int l, int r)
    {
        if (l == r)
        {
            t[x].l = t[x].r = pos[l];
            t[x].sum = 0;
        }
        else
        {
            int mid = (l + r) / 2;
            build(ls(x), l, mid);
            build(rs(x), mid + 1, r);
            t[x] = t[ls(x)] + t[rs(x)];
        }
    }

    void pushup(int x, int l, int r, int v)
    {
        t[x].l = t[x].r = v;
        t[x].sum = 0;
        tag[x] = v;
    }

    void pushdown(int x, int l, int r, int mid)
    {
        if (tag[x] != 0)
        {
            pushup(ls(x), l, mid, tag[x]);
            pushup(rs(x), mid + 1, r, tag[x]);
            tag[x] = 0;
        }
    }

    void modify(int x, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
        {
            pushup(x, l, r, v);
            return;
        }

        int mid = (l + r) / 2;
        pushdown(x, l, r, mid);
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr, v);
        t[x] = t[ls(x)] + t[rs(x)];
    }

    node query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[x];

        int mid = (l + r) / 2;
        pushdown(x, l, r, mid);
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
            return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
    }

public:
    segt(int _n) : n(_n) { build(1, 1, n); }

    void modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }

    node query(int l, int r) { return query(1, 1, n, l, r); }
};

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    dfs(1, 1);

    int q;
    std::cin >> q;
    segt t(n);
    for (int i = 1; i <= q; ++i)
    {
        int op, x, y;
        std::cin >> op >> x >> y;

        switch (op)
        {
        case 1:
        {
            while (top[x] != top[y])
            {
                if (dep[top[x]] < dep[top[y]])
                    std::swap(x, y);
                t.modify(dfn[top[x]], dfn[x], i);
                x = fa[top[x]];
            }
            if (dep[x] > dep[y])
                std::swap(x, y);
            t.modify(dfn[x], dfn[y], i);
            break;
        }

        case 2:
        {
            int u = x, v = y;
            while (top[u] != top[v])
            {
                if (dep[top[u]] < dep[top[v]])
                    std::swap(u, v);
                u = fa[top[u]];
            }
            int lca;
            if (dep[u] < dep[v])
                lca = u;
            else
                lca = v;

            bool flg = false;
            node tmpx;
            while (top[x] != top[lca])
            {
                if (flg)
                    tmpx = t.query(dfn[top[x]], dfn[x]) + tmpx;
                else
                {
                    flg = true;
                    tmpx = t.query(dfn[top[x]], dfn[x]);
                }
                x = fa[top[x]];
            }
            if (flg)
                tmpx = t.query(dfn[lca], dfn[x]) + tmpx;
            else
                tmpx = t.query(dfn[lca], dfn[x]);

            flg = false;
            node tmpy;
            while (top[y] != top[lca])
            {
                if (flg)
                    tmpy = t.query(dfn[top[y]], dfn[y]) + tmpy;
                else
                {
                    flg = true;
                    tmpy = t.query(dfn[top[y]], dfn[y]);
                }
                y = fa[top[y]];
            }
            if (flg)
                tmpy = t.query(dfn[lca], dfn[y]) + tmpy;
            else
                tmpy = t.query(dfn[lca], dfn[y]);

            std::cout << tmpx.sum + tmpy.sum << std::endl;
            break;
        }
        }
    }
    return 0;
}