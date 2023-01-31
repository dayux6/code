#include <bits/stdc++.h>

const int maxn = 1e5;

int w[maxn + 1], fa[maxn + 1], dep[maxn + 1], siz[maxn + 1], hs[maxn + 1], top[maxn + 1], bot[maxn + 1], dfc, dfn[maxn + 1], pos[maxn + 1];
std::vector<int> g[maxn + 1];
std::set<std::pair<int, int>> light[maxn + 1];

struct node
{
    int sum, lmax, rmax;

    node() {}
    node(int p)
    {
        sum = w[pos[p]];
        lmax = rmax = light[pos[p]].rbegin()->first + w[pos[p]];
    }

    node operator+(node rhs)
    {
        node ret;
        ret.sum = sum + rhs.sum;
        ret.lmax = std::max(lmax, sum + rhs.lmax);
        ret.rmax = std::max(rmax + rhs.sum, rhs.rmax);
        return ret;
    }
};

struct tnode
{
    node val;
    tnode *ls, *rs;

    tnode() { ls = rs = nullptr; }
    tnode(int p)
    {
        val = node(p);
        ls = rs = nullptr;
    }
} * rt[maxn + 1];

void update(tnode *x)
{
    if (x->ls == nullptr)
        x = x->rs;
    else if (x->rs == nullptr)
        x = x->ls;
    else
        x->val = x->ls->val + x->rs->val;
}

void build(tnode *&x, int l, int r)
{
    if (l == r)
        x = new tnode(l);
    else
    {
        int mid = (l + r) / 2;
        x = new tnode();
        build(x->ls, l, mid);
        build(x->rs, mid + 1, r);
        update(x);
    }
}

void modify(tnode *&x, int l, int r, int p)
{
    if (l == r)
        x = new tnode(p);
    else
    {
        int mid = (l + r) / 2;
        if (p <= mid)
            modify(x->ls, l, mid, p);
        else
            modify(x->rs, mid + 1, r, p);
        update(x);
    }
}

node query(tnode *x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return x->val;

    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(x->ls, l, mid, ql, qr);
    else if (ql > mid)
        return query(x->rs, mid + 1, r, ql, qr);
    else
        return query(x->ls, l, mid, ql, qr) + query(x->rs, mid + 1, r, ql, qr);
}

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

            if (hs[x] == 0 || siz[v] > siz[hs[x]])
                hs[x] = v;
        }
}

void dfs(int x, int t)
{
    top[x] = t;
    ++dfc;
    dfn[x] = dfc;
    pos[dfc] = x;

    if (hs[x] == 0)
        bot[x] = x;
    else
    {
        dfs(hs[x], t);
        bot[x] = bot[hs[x]];

        for (int v : g[x])
            if (v != fa[x] && v != hs[x])
                dfs(v, v);
    }
}

void init(int x)
{
    light[x].emplace(0, x);

    if (hs[x] == 0)
        build(rt[top[x]], dfn[top[x]], dfn[x]);
    else
    {
        for (int v : g[x])
            if (v != fa[x] && v != hs[x])
            {
                init(v);
                light[x].emplace(rt[v]->val.lmax, v);
            }

        init(hs[x]);
    }
}

void modify(int x)
{
    int pre;
    while (x != 0)
    {
        int t = top[x];
        pre = rt[t]->val.lmax;
        modify(rt[t], dfn[t], dfn[bot[x]], dfn[x]);
        if (rt[t]->val.lmax == pre)
            break;
        x = fa[t];
        light[x].erase(std::make_pair(pre, t));
        light[x].emplace(rt[t]->val.lmax, t);
    }
}

int query(int x)
{
    int ret = light[x].rbegin()->first + w[x], pre = w[x];

    while (x != 0)
    {
        int t = top[x];
        if (dfn[x] + 1 <= dfn[bot[x]])
            ret = std::max(ret, query(rt[t], dfn[t], dfn[bot[x]], dfn[x] + 1, dfn[bot[t]]).lmax + pre);
        if (dfn[t] <= dfn[x] - 1)
        {
            node tmp = query(rt[t], dfn[t], dfn[bot[x]], dfn[t], dfn[x] - 1);
            ret = std::max(ret, tmp.rmax + pre);
            pre += tmp.sum;
        }

        x = fa[t];
        if (x == 0)
            break;

        pre += w[x];
        auto it = light[x].rbegin();
        if (it->second == t)
            it = std::prev(it);
        ret = std::max(ret, it->first + pre);
    }

    return ret;
}

int main()
{
    std::freopen("lycoris.in", "r", stdin);
    std::freopen("lycoris.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> w[i];

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    dfs(1);
    dfs(1, 1);
    init(1);

    while (true)
    {
        std::string op;
        int x;
        std::cin >> op >> x;

        if (op == "Done")
            break;
        else if (op == "Change")
        {
            std::cin >> w[x];
            modify(x);
        }
        else
            std::cout << query(x) << std::endl;
    }
    return 0;
}