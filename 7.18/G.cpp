#include <bits/stdc++.h>

struct edge
{
    int u, v, w;

    edge() { std::cin >> u >> v >> w; }

    bool operator<(edge rhs) const { return w > rhs.w; }
};

class UnionFind
{
private:
    int n, *fa;
    int find(int);

public:
    UnionFind(int);
    void merge(int, int);
    bool query(int, int);
};

UnionFind::UnionFind(int _n) : n(_n), fa(new int[_n + 1]) { std::iota(fa + 1, fa + n + 1, 1); }

int UnionFind::find(int x)
{
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

void UnionFind::merge(int x, int y) { fa[find(x)] = find(y); }

bool UnionFind::query(int x, int y) { return find(x) == find(y); }

class segt
{
private:
    int n;
    struct node
    {
        int min, tag;

        node() : min(INT_MAX), tag(INT_MAX) {}
    } * t;
    int ls(int);
    int rs(int);
    void update(int);
    void pushup(int, int);
    void pushdown(int, int, int);
    void modify(int, int, int, int, int, int);
    int query(int, int, int, int, int);

public:
    segt(int);
    void modify(int, int, int);
    int query(int, int);
};

segt::segt(int _n) : n(_n), t(new node[_n * 4]()) {}

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x) { t[x].min = std::min(t[ls(x)].min, t[rs(x)].min); }

void segt::pushup(int x, int v)
{
    t[x].min = std::min(t[x].min, v);
    t[x].tag = std::min(t[x].tag, v);
}

void segt::pushdown(int x, int l, int r)
{
    if (t[x].tag != INT_MAX)
    {
        int mid = (l + r) / 2;
        pushup(ls(x), t[x].tag);
        pushup(rs(x), t[x].tag);
        t[x].tag = INT_MAX;
    }
}

void segt::modify(int x, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        pushup(x, v);
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

int segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x].min;
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else
        return std::min(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
}

void segt::modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }

int segt::query(int l, int r) { return query(1, 1, n, l, r); }

int dfc, *fa, *dep, *sum, *hs, *top, *dfn;
std::vector<int> *g;

void dfs(int x)
{
    sum[x] = 1;
    for (int v : g[x])
        if (v != fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs(v);
            sum[x] += sum[v];
            if (hs[x] == 0 || sum[v] > sum[hs[x]])
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
        for (int v : g[x])
            if (v != fa[x] && v != hs[x])
                dfs(v, v);
    }
}

int main()
{
    freopen("G.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;
    int cnt = 1, sum = 0;
    bool *flg = new bool[m]();
    edge *e = new edge[m]();
    std::priority_queue<std::pair<edge, int>> q;
    for (int i = 0; i < m; ++i)
        q.emplace(e[i], i);
    UnionFind uf(n);
    g = new std::vector<int>[n + 1];
    while (!q.empty() && cnt < n)
    {
        auto pr = q.top();
        q.pop();
        if (!uf.query(pr.first.u, pr.first.v))
        {
            ++cnt;
            sum += pr.first.w;
            flg[pr.second] = true;
            uf.merge(pr.first.u, pr.first.v);
            g[pr.first.u].emplace_back(pr.first.v);
            g[pr.first.v].emplace_back(pr.first.u);
        }
    }
    if (cnt < n - 1)
    {
        for (int i = 1; i < n; ++i)
            std::cout << "-1\n";
    }
    else
    {
        fa = new int[n + 1];
        dep = new int[n + 1];
        dep[1] = 0;
        sum = new int[n + 1];
        hs = new int[n + 1]();
        dfs(1);
        top = new int[n + 1];
        dfn = new int[n + 1];
        dfs(1, 1);
        segt t(n);
        for (int i = 0; i < m; ++i)
            if (!flg[i])
            {
                int x = e[i].u, y = e[i].v;
                while (top[x] != top[y])
                {
                    if (dep[top[x]] < dep[top[y]])
                        std::swap(x, y);
                    t.modify(dfn[top[x]], dfn[x], e[i].w);
                    x = fa[top[x]];
                }
                if (dep[x] > dep[y])
                    std::swap(x, y);
                if (x != y)
                    t.modify(dfn[x] + 1, dfn[y], e[i].w);
            }
        for (int i = 0; i < m; ++i)
            if (flg[i])
            {
                int x = e[i].u, y = e[i].v, min = INT_MAX;
                while (top[x] != top[y])
                {
                    if (dep[top[x]] < dep[top[y]])
                        std::swap(x, y);
                    min = std::min(min, t.query(dfn[top[x]], dfn[x]));
                    x = fa[top[x]];
                }
                if (dep[x] > dep[y])
                    std::swap(x, y);
                if (x != y)
                    min = std::min(min, t.query(dfn[x] + 1, dfn[y]));
                if (min == INT_MAX)
                    std::cout << "-1\n";
                else
                    std::cout << sum - e[i].w + min << '\n';
            }
            else
                std::cout << sum << '\n';
    }
    return 0;
}