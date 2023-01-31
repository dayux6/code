#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANITIC 1
#include <bits/stdc++.h>

const int mod = 998244353, maxn = 5e5;

int n, t;
std::array<int, maxn + 1> p;

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}

int getinv(int x)
{
    return qpow(x, mod - 2);
}

struct func
{
    int k, b;
};

func merge(func l, func r)
{
    func f;
    f.k = 1ll * r.k * l.k % mod;
    f.b = (1ll * r.k * l.b % mod + r.b) % mod;
    return f;
}

class BIT
{
private:
    std::array<int, maxn + 1> t;

    int lowbit(int x)
    {
        return x & -x;
    }

public:
    BIT()
    {
        std::fill_n(t.begin() + 1, n, 0);
        for (int i = 1; i <= n; ++i)
            modify(i, p[i]);
    }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] = (t[i] + v) % mod;
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret = (ret + t[i]) % mod;
        return ret;
    }
};

class segt
{
private:
    std::array<func, maxn * 4> rf, sum;

    int ls(int x)
    {
        return x * 2;
    }
    int rs(int x)
    {
        return x * 2 + 1;
    }

    void update(int x)
    {
        rf[x] = merge(rf[ls(x)], rf[rs(x)]);
        sum[x] = merge(rf[ls(x)], sum[rs(x)]);
        sum[x].k = (sum[x].k + sum[ls(x)].k) % mod;
        sum[x].b = (sum[x].b + sum[ls(x)].b) % mod;
    }

    void build(int x, int l, int r)
    {
        if (l == r)
        {
            rf[x].k = (p[l] + (1ll - p[l]) * t % mod) % mod;
            rf[x].b = sum[x].k = sum[x].b = p[l];
            return;
        }

        int mid = (l + r) / 2;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
        update(x);
    }

    void modify(int x, int l, int r, int pos)
    {
        if (l == r)
        {
            rf[x].k = (p[l] + (1ll - p[l]) * t % mod) % mod;
            sum[x].k = rf[x].b = sum[x].b = p[l];
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid)
            modify(ls(x), l, mid, pos);
        else
            modify(rs(x), mid + 1, r, pos);
        update(x);
    }

    std::pair<func, func> query(int x, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
            return std::make_pair(rf[x], sum[x]);

        int mid = (l + r) / 2;
        if (R <= mid)
            return query(ls(x), l, mid, L, R);
        else if (L > mid)
            return query(rs(x), mid + 1, r, L, R);
        else
        {
            auto prl = query(ls(x), l, mid, L, R), prr = query(rs(x), mid + 1, r, L, R);
            func ret = merge(prl.first, prr.second);
            ret.k = (ret.k + prl.second.k) % mod;
            ret.b = (ret.b + prl.second.b) % mod;
            return std::make_pair(merge(prl.first, prr.first), ret);
        }
    }

public:
    segt()
    {
        build(1, 1, n);
    }

    void modify(int pos)
    {
        modify(1, 1, n, pos);
    }

    int query(int l, int r)
    {
        if (l == 1)
            return query(1, 1, n, l, r).second.b;
        else
            return query(1, 1, n, l, r).second.b;
    }
};

int main()
{
    freopen("C.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n;
    int q, ta, tb, A, B;
    std::cin >> n >> q >> ta >> tb >> A >> B;
    t = 1ll * ta * getinv(tb) % mod;

    int pa, pb;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> pa >> pb;
        p[i] = 1ll * pa * getinv(pb) % mod;
    }

    bool op;
    int x, l, r;
    BIT a;
    segt b;
    for (int i = 0; i < q; ++i)
    {
        std::cin >> op;

        switch (op)
        {
        case 0:
        {
            std::cin >> x >> pa >> pb;
            pb = getinv(pb);
            a.modify(x, (1ll * pa * pb % mod - p[x]) % mod);
            p[i] = 1ll * pa * pb % mod;
            b.modify(x);
            break;
        }

        case 1:
        {
            std::cin >> l >> r;
            std::cout << (((1ll * A * (a.query(r) - a.query(l - 1))) % mod + 1ll * B * b.query(l, r) % mod) % mod + mod) % mod << std::endl;
            break;
        }
        }
    }
    return 0;
}