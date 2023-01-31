#include <bits/stdc++.h>

const int maxn = 2e5;

int n, cnt[maxn + 1];

struct frog
{
    int x, no;
    long long t;

    frog() {}
    frog(int _x, long long _t) : x(_x), t(_t) {}

    bool operator<(frog rhs) const { return x == rhs.x ? t < rhs.t : x < rhs.x; }
} f[maxn + 1];

struct mosquito
{
    int p, b;

    mosquito(int _p, int _b) : p(_p), b(_b) {}

    bool operator<(mosquito rhs) const { return p < rhs.p; }
};

class segt
{
private:
    long long max[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x) { max[x] = std::max(max[ls(x)], max[rs(x)]); }

    void modify(int x, int l, int r, int p, long long v)
    {
        if (l == r)
        {
            max[x] = v;
            return;
        }

        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }

    long long query(int x, int l, int r, int ql, int qr)
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

    int query(int x, int l, int r, int ql, int qr, long long lim)
    {
        if (l == r)
            return l;
        else
        {
            int mid = (l + r) / 2;

            if (qr <= mid)
                return query(ls(x), l, mid, ql, qr, lim);
            else if (ql > mid)
                return query(rs(x), mid + 1, r, ql, qr, lim);
            else if (max[ls(x)] >= lim)
                return query(ls(x), l, mid, ql, mid, lim);
            else
                return query(rs(x), mid + 1, r, mid + 1, qr, lim);
        }
    }

public:
    segt() {}

    void modify(int x, long long v) { modify(1, 1, n, x, v); }

    int query(int r, long long lim)
    {
        if (r == 0 || query(1, 1, n, 1, r) < lim)
            return 0;
        else
            return query(1, 1, n, 1, r, lim);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    std::freopen("CF609F.in", "r", stdin);
#endif

    int m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> f[i].x >> f[i].t;
        f[i].no = i;
    }

    std::sort(f + 1, f + n + 1);
    segt t;
    for (int i = 1; i <= n; ++i)
        t.modify(i, f[i].x + f[i].t);

    std::multiset<mosquito> mos;
    for (int i = 0; i < m; ++i)
    {
        int p, b;
        std::cin >> p >> b;

        int r = std::lower_bound(f + 1, f + n + 1, frog(p + 1, 0)) - f - 1, pos = t.query(r, p);
        if (pos == 0)
            mos.emplace(p, b);
        else
        {
            ++cnt[f[pos].no];
            f[pos].t += b;

            while (!mos.empty())
            {
                auto it = mos.lower_bound(mosquito(f[pos].x, 0));
                if (it == mos.end())
                    break;

                if (it->p <= f[pos].x + f[pos].t)
                {
                    ++cnt[f[pos].no];
                    f[pos].t += it->b;
                    mos.erase(it);
                }
                else
                    break;
            }

            t.modify(pos, f[pos].x + f[pos].t);
        }
    }

    std::sort(f + 1, f + n + 1, [=](frog x, frog y)
              { return x.no < y.no; });
    for (int i = 1; i <= n; ++i)
        std::cout << cnt[i] << ' ' << f[i].t << std::endl;
    return 0;
}