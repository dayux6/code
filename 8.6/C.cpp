#include <bits/stdc++.h>

const int maxn = 1e5;

std::bitset<maxn + 1> isp;
std::vector<int> vct[2];

void sieve(int n)
{
    isp.set(1);

    for (int i = 2; i <= n; ++i)
    {
        if (!isp.test(i))
        {
            vct[0].push_back(i);
            for (int j = i * 2; j <= n; j += i)
                isp.set(j);
        }
        else
            vct[1].push_back(i);
    }
}

class segt
{
private:
    int n;

    struct node
    {
        int sum;
        bool tag;

        node() : sum(0), tag(false) {}
    } * t;

    int ls(int x) { return x * 2; }
    int rs(int x) { return x * 2 + 1; }

    void update(int x) { t[x].sum = t[ls(x)].sum + t[rs(x)].sum; }

    void pushup(int x, int l, int r)
    {
        t[x].sum = (r - l + 1) - t[x].sum;
        t[x].tag ^= 1;
    }

    void pushdown(int x, int l, int r)
    {
        if (t[x].tag)
        {
            int mid = (l + r) / 2;
            pushup(ls(x), l, mid);
            pushup(rs(x), mid + 1, r);
            t[x].tag = false;
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
            return t[x].sum;

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
    void build(int _n)
    {
        n = _n;
        t = new node[n * 4]();
    }

    void modify(int l, int r)
    {
        if (l <= r)
            modify(1, 1, n, l, r);
    }

    int query(int l, int r)
    {
        if (l <= r)
            return query(1, 1, n, l, r);
        else
            return 0;
    }
} row[2], col[2];

int main()
{
    freopen("C.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    sieve(n);
    for (int i = 0; i < 2; ++i)
    {
        row[i].build(vct[i].size());
        col[i].build(vct[i].size());
    }

    bool row1 = false, col1 = false;
    for (int i = 0; i < m; ++i)
    {
        char op;
        std::cin >> op;

        switch (op)
        {
        case 'M':
        {
            int l, r;
            std::cin >> l >> r;

            if (l == 1)
                row1 ^= 1;

            for (int i = 0; i < 2; ++i)
                if (!vct[i].empty())
                {
                    int ql = std::lower_bound(vct[i].begin(), vct[i].end(), l) - vct[i].begin() + 1, qr = std::upper_bound(vct[i].begin(), vct[i].end(), r) - vct[i].begin();
                    row[i].modify(ql, qr);
                }
            break;
        }

        case 'N':
        {
            int l, r;
            std::cin >> l >> r;

            if (l == 1)
                col1 ^= 1;

            for (int i = 0; i < 2; ++i)
                if (!vct[i].empty())
                {
                    int ql = std::lower_bound(vct[i].begin(), vct[i].end(), l) - vct[i].begin() + 1, qr = std::upper_bound(vct[i].begin(), vct[i].end(), r) - vct[i].begin();
                    col[i].modify(ql, qr);
                }
            break;
        }

        case 'P':
        {
            bool v;
            std::cin >> v;

            if (v)
                col[0].modify(1, vct[0].size());
            else
                row[0].modify(1, vct[0].size());
            break;
        }

        case 'R':
        {
            bool v;
            std::cin >> v;

            if (v)
                col[1].modify(1, vct[1].size());
            else
                row[1].modify(1, vct[1].size());
            break;
        }

        case 'Q':
        {
            int l1, r1, l2, r2;
            std::cin >> l1 >> r1 >> l2 >> r2;

            int rc = l1 ^ 1 ? 0 : row1, cc = l2 ^ 1 ? 0 : col1;
            for (int i = 0; i < 2; ++i)
                if (!vct[i].empty())
                {
                    int rl = std::lower_bound(vct[i].begin(), vct[i].end(), l1) - vct[i].begin() + 1, rr = std::upper_bound(vct[i].begin(), vct[i].end(), r1) - vct[i].begin();
                    rc += row[i].query(rl, rr);

                    int cl = std::lower_bound(vct[i].begin(), vct[i].end(), l2) - vct[i].begin() + 1, cr = std::upper_bound(vct[i].begin(), vct[i].end(), r2) - vct[i].begin();
                    cc += col[i].query(cl, cr);
                }

            std::cout << 1ll * rc * (r2 - l2 + 1 - cc) + 1ll * (r1 - l1 + 1 - rc) * cc << std::endl;
            break;
        }
        }
    }
    return 0;
}