#include <bits/stdc++.h>

const int maxn = 2e5;

int m, k, cnt, fa[maxn + 1], siz[maxn + 1], ptr, pre[maxn + 1];
std::vector<int> t[maxn * 4];
std::stack<std::pair<int, int>> s;

struct prove
{
    int u, v;
} p[maxn + 1];

int find(int x)
{
    if (x == fa[x])
        return x;
    else
        return find(fa[x]);
}

void merge(int x, int y)
{
    int u = find(x), v = find(y);

    if (u != v)
    {
        --cnt;
        if (siz[u] < siz[v])
            std::swap(u, v);
        s.emplace(u, v);
        fa[v] = u;
        siz[u] += siz[v];
    }
}

void undo(int old)
{
    while (s.size() > old)
    {
        ++cnt;
        auto pr = s.top();
        s.pop();
        fa[pr.second] = pr.second;
        siz[pr.first] -= siz[pr.second];
    }
}

int ls(int x) { return x * 2; }
int rs(int x) { return x * 2 + 1; }

void modify(int x, int l, int r, int ql, int qr, int pos)
{
    if (ql <= l && r <= qr)
    {
        t[x].push_back(pos);
        return;
    }

    int mid = (l + r) / 2;
    if (ql <= mid)
        modify(ls(x), l, mid, ql, qr, pos);
    if (qr > mid)
        modify(rs(x), mid + 1, r, ql, qr, pos);
}

void divide(int x, int l, int r)
{
    int old = s.size();

    for (int pos : t[x])
        merge(p[pos].u, p[pos].v);

    if (l == r)
    {
        while (ptr > 0 && cnt > k)
        {
            --ptr;
            if (ptr == 0)
                break;
            merge(p[ptr].u, p[ptr].v);
            if (ptr < l)
                modify(1, 1, m, ptr, l - 1, ptr);
        }
        pre[l] = ptr;
    }
    else
    {
        int mid = (l + r) / 2;
        divide(rs(x), mid + 1, r);
        divide(ls(x), l, mid);
    }

    undo(old);
}

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int n;
    bool tp;
    std::cin >> n >> m >> k >> tp;

    for (int i = 1; i <= m; ++i)
        std::cin >> p[i].u >> p[i].v;

    ptr = m + 1;
    cnt = n;
    std::iota(fa + 1, fa + n + 1, 1);
    std::fill_n(siz + 1, n, 1);
    divide(1, 1, m);

    int q;
    std::cin >> q;
    unsigned lans = 0;
    for (int i = 0; i < q; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        if (tp)
        {
            l = (l + lans) % m + 1;
            r = (r + lans) % m + 1;

            if (l > r)
                std::swap(l, r);
        }

        lans <<= 1;
        if (l <= pre[r])
        {
            std::cout << "Yes" << std::endl;
            ++lans;
        }
        else
            std::cout << "No" << std::endl;
    }
    return 0;
}