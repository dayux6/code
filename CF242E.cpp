#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 20;

int n, a[maxn + 1];

class segt
{
private:
    int sum[maxn * 4];
    bool tag[maxn * 4];

    inline int ls(int x) { return x * 2; }
    inline int rs(int x) { return x * 2 + 1; }

    inline void update(int x) { sum[x] = sum[ls(x)] + sum[rs(x)]; }

    void build(int x, int l, int r, int bit)
    {
        tag[x] = 0;
        if (l == r)
            sum[x] = (a[l] >> bit) & 1;
        else
        {
            int mid = (l + r) / 2;
            build(ls(x), l, mid, bit);
            build(rs(x), mid + 1, r, bit);
            update(x);
        }
    }

    inline void pushup(int x, int l, int r)
    {
        sum[x] = (r - l + 1) - sum[x];
        tag[x] ^= 1;
    }

    inline void pushdown(int x, int l, int r)
    {
        if (tag[x])
        {
            int mid = (l + r) / 2;
            pushup(ls(x), l, mid);
            pushup(rs(x), mid + 1, r);
            tag[x] = 0;
        }
    }

    void modify(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            pushup(x, l, r);
            return;
        }

        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr);
        update(x);
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return sum[x];

        pushdown(x, l, r);
        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
            return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
    }

public:
    void build(int bit) { build(1, 1, n, bit); }

    void modify(int l, int r) { modify(1, 1, n, l, r); }

    int query(int l, int r) { return query(1, 1, n, l, r); }
} t[maxlg];

int main()
{
#ifndef ONLINE_JUDGE
    std::freopen("CF242E.in", "r", stdin);
#endif

    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 0; i < maxlg; ++i)
        t[i].build(i);

    int m;
    std::cin >> m;
    for (int i = 0, op, l, r, x; i < m; ++i)
    {
        std::cin >> op >> l >> r;

        switch (op)
        {
        case 1:
        {
            long long res = 0;
            for (int j = 0; j < maxlg; ++j)
                res += ((long long)t[j].query(l, r)) << j;
            std::cout << res << '\n';
            break;
        }
        case 2:
        {
            std::cin >> x;
            for (int j = 0; j < maxlg; ++j)
                if ((x >> j) & 1)
                    t[j].modify(l, r);
            break;
        }
        }
    }
    return 0;
}