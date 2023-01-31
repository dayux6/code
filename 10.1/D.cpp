#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int n, lg, dep[maxn + 1], anc[maxn + 1][maxlg + 1], dfc, dfn[maxn + 1], rnk[maxn + 1], siz[maxn + 1], st[maxn + 1][maxlg + 1];
std::vector<int> g[maxn + 1], l[maxn + 1];

void dfs(int x)
{
    for (int i = 1; i <= lg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    ++dfc;
    dfn[x] = dfc;
    rnk[dfc] = x;

    siz[x] = 1;

    for (int v : g[x])
        if (v != anc[x][0])
        {
            dep[v] = dep[x] + 1;
            anc[v][0] = x;
            dfs(v);
            siz[x] += siz[v];
        }
}

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);

    while (dep[x] > dep[y])
        x = anc[x][(int)std::log2(dep[x] - dep[y])];

    if (x == y)
        return x;

    for (int i = lg; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

void init(int x)
{

    for (int v : g[x])
        if (v != anc[x][0])
        {
            init(v);

            if (dep[st[v][0]] < dep[st[x][0]])
                st[x][0] = st[v][0];
        }
}

class CMT
{
private:
    struct node
    {
        int cnt;
        node *ls, *rs;
    };

    node *modify(int l, int r, int p, node *old)
    {
        node *x = new node;
        if (old == nullptr)
        {
            x->cnt = 0;
            x->ls = x->rs = nullptr;
        }
        else
        {
            x->cnt = old->cnt;
            x->ls = old->ls;
            x->rs = old->rs;
        }

        ++x->cnt;
        if (l != r)
        {
            int mid = (l + r) / 2;

            if (p <= mid)
                x->ls = modify(l, mid, p, old == nullptr ? nullptr : old->ls);
            else
                x->rs = modify(mid + 1, r, p, old == nullptr ? nullptr : old->rs);
        }
        return x;
    }

    bool query(node *x, node *y, int l, int r, int ql, int qr)
    {
        if (y == nullptr)
            return false;
        if (ql <= l && r <= qr)
            return (x == nullptr ? 0 : x->cnt) < y->cnt;

        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(x == nullptr ? nullptr : x->ls, y->ls, l, mid, ql, qr);
        else if (ql > mid)
            return query(x == nullptr ? nullptr : x->rs, y->rs, mid + 1, r, ql, qr);
        else
            return query(x == nullptr ? nullptr : x->ls, y->ls, l, mid, ql, qr) || query(x == nullptr ? nullptr : x->rs, y->rs, mid + 1, r, ql, qr);
    }

public:
    node *rt[maxn + 1];

    CMT() { std::fill_n(rt, n + 1, nullptr); }

    void modify(int v, int p) { rt[v] = modify(1, n, p, rt[v]); }

    bool query(int l, int r, int ql, int qr) { return query(rt[l - 1], rt[r], 1, n, ql, qr); }
};

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int m, q;
    std::cin >> n >> m >> q;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    lg = std::log2(n);
    dfs(1);

    for (int i = 1; i <= n; ++i)
        st[i][0] = i;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        int lca = getlca(u, v);
        if (dep[lca] < dep[st[u][0]])
            st[u][0] = lca;
        if (dep[lca] < dep[st[v][0]])
            st[v][0] = lca;

        l[dfn[u]].push_back(dfn[v]);
        l[dfn[v]].push_back(dfn[u]);
    }

    init(1);

    CMT t;
    for (int i = 1; i <= n; ++i)
    {
        t.rt[i] = t.rt[i - 1];
        for (int j : l[i])
            t.modify(i, j);
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= lg; ++j)
            st[rnk[i]][j] = st[st[rnk[i]][j - 1]][j - 1];

    for (int i = 0; i < q; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        if (dep[x] > dep[y])
            std::swap(x, y);

        int lca = getlca(x, y), res = 0;
        if (lca == x)
        {
            for (int i = lg; i >= 0; --i)
                if (dep[st[y][i]] > dep[x])
                {
                    y = st[y][i];
                    res += 1 << i;
                }
            if (dep[st[y][0]] > dep[x])
                std::cout << -1 << std::endl;
            else
                std::cout << res << std::endl;
        }
        else
        {

            for (int i = lg; i >= 0; --i)
                if (dep[st[x][i]] > dep[lca])
                {
                    x = st[x][i];
                    res += 1 << i;
                }
            if (dep[st[x][0]] > dep[lca])
            {
                std::cout << -1 << std::endl;
                continue;
            }

            for (int i = lg; i >= 0; --i)
                if (dep[st[y][i]] > dep[lca])
                {
                    y = st[y][i];
                    res += 1 << i;
                }
            if (dep[st[y][0]] > dep[lca])
            {
                std::cout << -1 << std::endl;
                continue;
            }

            if (t.query(dfn[x], dfn[x] + siz[x] - 1, dfn[y], dfn[y] + siz[y] - 1))
                std::cout << res << std::endl;
            else
                std::cout << res + 1 << std::endl;
        }
    }
    return 0;
}