#include <bits/stdc++.h>

#pragma GCC optimize(2, 3, "Ofast")

const int maxn = 3e5;

class segt
{
private:
    int n, *t;
    bool _;
    int ls(int);
    int rs(int);
    void update(int);
    void modify(int, int, int, int, int);
    int query(int, int, int, int, int);

public:
    segt(int, bool);
    void modify(int, int);
    int query(int, int);
};

segt::segt(int _n, bool __) : n(_n), _(__), t(new int[(_n + 1) * 4]) { std::fill_n(t, (_n + 1) * 4, __ ? INT_MAX : 0); }

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::update(int x)
{
    if (_)
        t[x] = std::min(t[ls(x)], t[rs(x)]);
    else
        t[x] = std::max(t[ls(x)], t[rs(x)]);
}

void segt::modify(int x, int l, int r, int p, int v)
{
    if (l == r)
    {
        if (_)
            t[x] = std::min(t[x], v);
        else
            t[x] = std::max(t[x], v);
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(ls(x), l, mid, p, v);
    else
        modify(rs(x), mid + 1, r, p, v);
    update(x);
}

int segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x];
    int mid = (l + r) / 2;
    if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (_)
        return std::min(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
    else
        return std::max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
}

void segt::modify(int p, int v) { modify(1, 0, n, p, v); }

int segt::query(int l, int r) { return query(1, 0, n, l, r); }

int main()
{
    freopen("BZOJ3956.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    bool _;
    std::cin >> n >> m >> _;
    int *a = new int[n + 1];
    std::vector<int> vct;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        vct.emplace_back(a[i]);
    }
    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    for (int i = 1; i <= n; ++i)
        a[i] = std::lower_bound(vct.begin(), vct.end(), a[i]) - vct.begin();
    int *pre = new int[n + 1](), *suf = new int[n + 1]();
    segt pret(vct.size() - 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        int p = pret.query(a[i], vct.size() - 1);
        if (p != 0 && p != i - 1)
        {
            ++pre[i];
            ++suf[p];
        }
        pret.modify(a[i], i);
    }
    segt suft(vct.size() - 1, 1);
    for (int i = n; i > 0; --i)
    {
        int p = suft.query(a[i], vct.size() - 1);
        if (p != INT_MAX && p != i + 1 && a[p] != a[i])
        {
            ++suf[i];
            ++pre[p];
        }
        suft.modify(a[i], i);
    }
    for (int i = 2; i <= n; ++i)
    {
        pre[i] += pre[i - 1];
        suf[i] += suf[i - 1];
    }
    int lg = log2(n), **st = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        st[i] = new int[lg + 1];
        st[i][0] = i;
    }
    for (int i = 1; i <= lg; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            if (a[st[j][i - 1]] > a[st[j + (1 << (i - 1))][i - 1]])
                st[j][i] = st[j][i - 1];
            else
                st[j][i] = st[j + (1 << (i - 1))][i - 1];
    auto query = [=](int l, int r)
    {
        int k = log2(r - l + 1);
        if (a[st[l][k]] > a[st[r - (1 << k) + 1][k]])
            return st[l][k];
        else
            return st[r - (1 << k) + 1][k];
    };
    int lst = 0;
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        if (_)
        {
            l = (l + lst - 1) % n + 1;
            r = (r + lst - 1) % n + 1;
        }
        if (l > r)
            std::swap(l, r);
        int p = query(l, r);
        lst = r - l + pre[r] - pre[p] + suf[p - 1] - suf[l - 1];
        std::cout << lst << '\n';
    }
    return 0;
}