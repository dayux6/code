#include <bits/stdc++.h>

const int maxn = 1e5, maxm = 1e5;

int a[maxn + 1];
std::tuple<bool, int, int> opt[maxm];

class segt
{
private:
    int n;
    struct node
    {
        int v, tag;

        node() {}
    } t[maxn * 4];
    int ls(int);
    int rs(int);
    void update(int);
    void build(int, int, int, int);
    void pushup(int, int, int, bool);
    void pushdown(int, int, int);
    void modify(int, int, int, int, int, bool);
    int query(int, int, int, int, int);

public:
    segt(int);
    void build(int);
    void modify(int, int, bool);
    int query(int, int);
};

segt::segt(int _n) : n(_n) {}

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x) { t[x].v = t[ls(x)].v + t[rs(x)].v; }

void segt::build(int x, int l, int r, int k)
{
    t[x].tag = -1;
    if (l == r)
    {
        t[x].v = a[l] >= k;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(x), l, mid, k);
    build(rs(x), mid + 1, r, k);
    update(x);
}

void segt::pushup(int x, int l, int r, bool b)
{
    t[x].v = (r - l + 1) * b;
    t[x].tag = b;
}

void segt::pushdown(int x, int l, int r)
{
    if (~t[x].tag)
    {
        int mid = (l + r) / 2;
        pushup(ls(x), l, mid, t[x].tag);
        pushup(rs(x), mid + 1, r, t[x].tag);
        t[x].tag = -1;
    }
}

void segt::modify(int x, int l, int r, int ql, int qr, bool b)
{
    if (ql <= l && r <= qr)
    {
        pushup(x, l, r, b);
        return;
    }
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid)
        modify(ls(x), l, mid, ql, qr, b);
    if (qr > mid)
        modify(rs(x), mid + 1, r, ql, qr, b);
    update(x);
}

int segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x].v;
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else
        return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
}

void segt::build(int k) { build(1, 1, n, k); }

void segt::modify(int l, int r, bool b)
{
    if (l <= r)
        modify(1, 1, n, l, r, b);
}

int segt::query(int l, int r) { return query(1, 1, n, l, r); }

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 0; i < m; ++i)
    {
        bool op;
        int l, r;
        std::cin >> op >> l >> r;
        opt[i] = std::tie(op, l, r);
    }
    int q;
    std::cin >> q;
    segt t(n);
    int L = 1, R = n, ans;
    while (L <= R)
    {
        int mid = (L + R) / 2;
        t.build(mid);
        for (int i = 0; i < m; ++i)
        {
            int l = std::get<1>(opt[i]), r = std::get<2>(opt[i]), tmp = t.query(l, r);
            switch (std::get<0>(opt[i]))
            {
            case 0:
            {
                t.modify(l, r - tmp, 0);
                t.modify(r - tmp + 1, r, 1);
                break;
            }
            case 1:
            {
                t.modify(l, l + tmp - 1, 1);
                t.modify(l + tmp, r, 0);
                break;
            }
            }
        }
        if (t.query(q, q))
        {
            L = mid + 1;
            ans = mid;
        }
        else
            R = mid - 1;
    }
    std::cout << ans << std::endl;
    return 0;
}