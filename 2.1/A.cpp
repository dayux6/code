#include <bits/stdc++.h>

const int maxn = 1e5;

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

int res, a[maxn + 1], c[maxn];

namespace segt
{
    int sum[maxn * 4];
    std::vector<int> vid[maxn * 4];

    inline int ls(int x) { return x * 2; }
    inline int rs(int x) { return x * 2 + 1; }
    inline void update(int x) { sum[x] = sum[ls(x)] + sum[rs(x)]; }

    void build(int x, int l, int r)
    {
        if (l == r)
        {
            sum[x] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    void cover(int x, int l, int r, int id, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            ++c[id];
            vid[x].emplace_back(id);
            return;
        }

        int mid = (l + r) / 2;
        if (ql <= mid)
            cover(ls(x), l, mid, id, ql, qr);
        if (qr > mid)
            cover(rs(x), mid + 1, r, id, ql, qr);
    }

    void dec(int x, int l, int r, int p)
    {
        --sum[x];
        if (sum[x] == 0)
            for (int id : vid[x])
            {
                --c[id];

                if (c[id] == 0)
                    ++res;
            }

        if (l == r)
            return;

        int mid = (l + r) / 2;
        if (p <= mid)
            dec(ls(x), l, mid, p);
        else
            dec(rs(x), mid + 1, r, p);
    }
};

int main()
{
    std::freopen("balloon.in", "r", stdin);
    std::freopen("balloon.out", "w", stdout);

    int n, m;
    read(n), read(m);

    for (int i = 1; i <= n; ++i)
        read(a[i]);
    segt::build(1, 1, n);

    for (int i = 0, l, r; i < m; ++i)
    {
        read(l), read(r);
        segt::cover(1, 1, n, i, l, r);
    }

    int q;
    read(q);
    for (int i = 0, x; i < q; ++i)
    {
        read(x);
        x = (x + res - 1) % n + 1;

        segt::dec(1, 1, n, x);

        std::cout << res << '\n';
    }
    return 0;
}