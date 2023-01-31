#include <bits/stdc++.h>

const int maxn = 1e5;

int n;

class segt
{
private:
    std::array<int, maxn * 4> min, pos;

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x)
    {
        min[x] = INT_MAX;

        if (min[ls(x)] <= min[x])
        {
            min[x] = min[ls(x)];
            pos[x] = pos[ls(x)];
        }

        if (min[rs(x)] <= min[x])
        {
            min[x] = min[rs(x)];
            pos[x] = pos[rs(x)];
        }
    }

    void modify(int x, int l, int r, int p, int v)
    {
        if (l == r)
        {
            min[x] = v;
            pos[x] = p;
            return;
        }

        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }

    std::pair<int, int> query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return std::make_pair(min[x], pos[x]);

        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
            return std::min(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
    }

public:
    void modify(int p, int v) { modify(1, 1, n, p, v); }

    std::pair<int, int> query(int l, int r) { return query(1, 1, n, l, r); }
};

int main()
{
    std::freopen("CF1665E.in", "r", stdin);

    int _t;
    std::cin >> _t;

    for (int _i = 0; _i < _t; ++_i)
    {
        std::cin >> n;

        segt t;
        for (int i = 1; i <= n; ++i)
        {
            int a;
            std::cin >> a;
            t.modify(i, a);
        }

        int q;
        std::cin >> q;
        for (int i = 0; i < q; ++i)
        {
            int l, r;
            std::cin >> l >> r;

            int lim = std::min(r - l + 1, 31);
            std::vector<std::pair<int, int>> pr;
            pr.resize(lim);
            for (int j = 0; j < lim; ++j)
            {
                pr[j] = t.query(l, r);
                t.modify(pr[j].second, INT_MAX);
            }

            int min = INT_MAX;
            for (int j = 0; j < lim; ++j)
                for (int k = 0; k < lim; ++k)
                    if (j != k)
                        min = std::min(min, pr[j].first | pr[k].first);

            std::cout << min << std::endl;

            for (int j = 0; j < lim; ++j)
                t.modify(pr[j].second, pr[j].first);
        }
    }
    return 0;
}