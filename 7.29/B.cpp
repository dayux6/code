#include <bits/stdc++.h>

const int maxn = 1e5;

int fa[maxn + 1], dep[maxn + 1], siz[maxn + 1], hs[maxn + 1], top[maxn + 1], dfc, dfn[maxn + 1];
std::vector<int> g[maxn + 1];

class segt
{
private:
    int n, s[maxn * 4], tag[maxn * 4];
    int ls(int);
    int rs(int);
    void update(int);
    void build(int, int, int);
    void pushup(int, int, int, int);
    void pushdown(int, int, int);
    void modify(int, int, int, int, int, int);
    int query(int, int, int, int, int);

public:
    segt(int);
    void modify(int, int, int);
    int query(int, int);
};

segt::segt(int _n) : n(_n) { build(1, 1, _n); }

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x) { s[x] = s[ls(x)] + s[rs(x)]; }

void segt::build(int x, int l, int r)
{
    s[x] = 0;
    tag[x] = -1;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}

void segt::pushup(int x, int l, int r, int v)
{
    s[x] = (r - l + 1) * v;
    tag[x] = v;
}

void segt::pushdown(int x, int l, int r)
{
    if (~tag[x])
    {
        int mid = (l + r) / 2;
        pushup(ls(x), l, mid, tag[x]);
        pushup(rs(x), mid + 1, r, tag[x]);
        tag[x] = -1;
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

int segt::query(int x, int l, int r, int ql, int qr)
{
    // std::cout << x << ' ' << l << ' ' << r << ' ' << ql << ' ' << qr << std::endl;
    if (ql <= l && r <= qr)
        return s[x];
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else
        return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
}

void segt::modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }

int segt::query(int l, int r) { return query(1, 1, n, l, r); }

void dfs(int x)
{
    siz[x] = 1;
    for (int v : g[x])
        if (v ^ fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs(v);
            siz[x] += siz[v];
            if (!hs[x] || siz[v] > siz[hs[x]])
                hs[x] = v;
        }
}

void dfs(int x, int t)
{
    top[x] = t;
    ++dfc;
    dfn[x] = dfc;
    if (hs[x])
    {
        dfs(hs[x], t);
        for (int v : g[x])
            if (v ^ fa[x] && v ^ hs[x])
                dfs(v, v);
    }
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        std::cin >> fa;
        ++fa;
        g[fa].emplace_back(i);
    }
    dep[1] = 1;
    dfs(1);
    dfs(1, 1);
    int q;
    std::cin >> q;
    segt t(n);
    for (int i = 0; i < q; ++i)
    {
        std::string s;
        int x;
        std::cin >> s >> x;
        ++x;
        if (s == "install")
            if (t.query(dfn[x], dfn[x]))
                std::cout << 0 << std::endl;
            else
            {
                int res = dep[x];
                while (top[x] != 1)
                {
                    res -= t.query(dfn[top[x]], dfn[x]);
                    t.modify(dfn[top[x]], dfn[x], 1);
                    x = fa[top[x]];
                }
                res -= t.query(1, dfn[x]);
                t.modify(1, dfn[x], 1);
                std::cout << res << std::endl;
            }
        else if (t.query(dfn[x], dfn[x]))
        {
            std::cout << t.query(dfn[x], dfn[x] + siz[x] - 1) << std::endl;
            t.modify(dfn[x], dfn[x] + siz[x] - 1, 0);
        }
        else
            std::cout << 0 << std::endl;
    }
    return 0;
}