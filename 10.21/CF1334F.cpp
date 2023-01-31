#include <bits/stdc++.h>

const int maxn = 5e5;

int n;
std::array<int, maxn + 1> a, p, b;
std::array<long long, maxn + 1> f;

struct segt
{
private:
    std::array<long long, maxn * 4> max, tag;

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x) { max[x] = std::max(max[ls(x)], max[rs(x)]); }

    void pushup(int x, long long v)
    {
        max[x] += v;
        tag[x] += v;
    }

    void pushdown(int x)
    {
        if (tag[x] != 0)
        {
            pushup(ls(x), tag[x]);
            pushup(rs(x), tag[x]);
            tag[x] = 0;
        }
    }

    void modify(int x, int l, int r, int p, long long v)
    {
        if (l == r)
        {
            max[x] = std::max(max[x], v);
            return;
        }

        pushdown(x);
        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }

    void modify(int x, int l, int r, int ql, int qr, long long v)
    {
        if (ql <= l && r <= qr)
        {
            pushup(x, v);
            return;
        }

        pushdown(x);
        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr, v);
        update(x);
    }

    long long query(int x, int l, int r, int p)
    {
        if (l == r)
            return max[x];

        pushdown(x);
        int mid = (l + r) / 2;
        if (p <= mid)
            return query(ls(x), l, mid, p);
        else
            return query(rs(x), mid + 1, r, p);
    }

public:
    segt()
    {
        max.fill(LLONG_MIN);
        tag.fill(0);
    }

    void modify(int p, long long v) { modify(1, 1, n, p, v); }

    void modify(int l, int r, long long v) { modify(1, 1, n, l, r, v); }

    long long query(int x) { return query(1, 1, n, x); }
} t;

int main()
{
    std::freopen("CF1334F.in", "r", stdin);

    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    long long s = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i];
        s += p[i];
    }

    int m;
    std::cin >> m;
    b[0] = 0;
    for (int i = 1; i <= m; ++i)
        std::cin >> b[i];

    for (int i = 1; i <= n; ++i)
    {
        int pos = std::lower_bound(b.begin() + 1, b.begin() + m + 1, a[i]) - b.begin();

        if (a[i] == b[pos])
        {
            if (pos == 1)
                f[i] = p[i];
            else
                f[i] = t.query(b[pos - 1]) + p[i];
        }
        else
            f[i] = LLONG_MIN;

        if (p[i] > 0)
            t.modify(a[i], n, p[i]);
        t.modify(a[i], f[i]);
    }

    if (t.query(b[m]) < -maxn * 1e9)
        std::cout << "NO" << std::endl;
    else
        std::cout << "YES" << std::endl
                  << s - t.query(b[m]) << std::endl;
    return 0;
}