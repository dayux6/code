#include <bits/stdc++.h>

const int maxn = 1e5, maxlim = 45;

int a[maxn + 1];

namespace segt
{
    std::vector<int> t[maxn * 4];

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x)
    {
        t[x].clear();
        std::merge(t[ls(x)].begin(), t[ls(x)].end(), t[rs(x)].begin(), t[rs(x)].end(), std::back_inserter(t[x]), std::greater<int>());

        if (t[x].size() > maxlim)
        {
            t[x].resize(maxlim);
            t[x].shrink_to_fit();
        }
    }

    void build(int x, int l, int r)
    {
        if (l == r)
        {
            t[x].emplace_back(a[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    void modify(int x, int l, int r, int p, int v)
    {
        if (l == r)
        {
            t[x].front() = v;
            return;
        }

        int mid = (l + r) / 2;
        if (p <= mid)
            modify(ls(x), l, mid, p, v);
        else
            modify(rs(x), mid + 1, r, p, v);
        update(x);
    }

    std::vector<int> query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[x];

        int mid = (l + r) / 2;
        if (qr <= mid)
            return query(ls(x), l, mid, ql, qr);
        else if (ql > mid)
            return query(rs(x), mid + 1, r, ql, qr);
        else
        {
            std::vector<int> vl = query(ls(x), l, mid, ql, qr), vr = query(rs(x), mid + 1, r, ql, qr), ret;
            std::merge(vl.begin(), vl.end(), vr.begin(), vr.end(), std::back_inserter(ret), std::greater<int>());

            if (ret.size() > maxlim)
            {
                ret.resize(maxlim);
                ret.shrink_to_fit();
            }

            return ret;
        }
    }
};

int main()
{
    std::freopen("triangle.in", "r", stdin);
    std::freopen("triangle.out", "w", stdout);

    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    segt::build(1, 1, n);

    for (int i = 0, op, x, y; i < q; ++i)
    {
        std::cin >> op >> x >> y;

        switch (op)
        {
        case 1:
        {
            segt::modify(1, 1, n, x, y);
            break;
        }
        case 2:
        {
            bool flg = true;
            std::vector<int> v = segt::query(1, 1, n, x, y);
            for (std::size_t j = 2; j < v.size(); ++j)
            {
                if (v[j - 2] < v[j - 1] + v[j])
                {
                    std::cout << (long long)v[j - 2] + v[j - 1] + v[j] << std::endl;
                    flg = false;
                    break;
                }
            }
            if (flg)
                std::cout << 0 << std::endl;
            break;
        }
        }
    }
    return 0;
}