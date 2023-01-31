#include <bits/stdc++.h>

const int maxn = 1e5, mod = 1e9 + 7;

int pro = 1, inv[maxn + 1];

void getinv()
{
    inv[1] = 1;
    for (int i = 2; i <= maxn; ++i)
        inv[i] = (-1ll * (mod / i) * inv[mod % i] % mod + mod) % mod;
}

struct DSU
{
private:
    int n, fa[maxn + 1], siz[maxn + 1];
    std::stack<std::tuple<int, int, int>> s;
    int find(int);

public:
    DSU();
    DSU(int);
    void merge(int, int);
    bool query(int, int);
    int getsiz();
    void undo(int);
} dsu;

DSU::DSU() {}
DSU::DSU(int _n) : n(_n)
{
    std::iota(fa + 1, fa + _n + 1, 1);
    std::fill_n(siz + 1, _n, 1);
}

int DSU::find(int x)
{
    if (x ^ fa[x])
        return find(fa[x]);
    else
        return x;
}

void DSU::merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x ^ y)
    {
        if (siz[x] < siz[y])
            std::swap(x, y);
        s.push(std::tie(x, fa[x], siz[x]));
        s.push(std::tie(y, fa[y], siz[y]));
        pro = 1ll * pro * inv[siz[x]] % mod * inv[siz[y]] % mod;
        fa[y] = x;
        siz[x] += siz[y];
        pro = 1ll * pro * siz[x] % mod;
    }
}

bool DSU::query(int x, int y) { return find(x) == find(y); }

int DSU::getsiz() { return s.size(); }

void DSU::undo(int t)
{
    while (s.size() > t)
    {
        int x = std::get<0>(s.top());
        fa[x] = std::get<1>(s.top());
        pro = 1ll * pro * inv[siz[x]] % mod;
        std::cout << "QwQ " << x << ' ' << pro << ' ' << siz[x] << ' ';
        siz[x] = std::get<2>(s.top());
        pro = 1ll * pro * siz[x] % mod;
        std::cout << siz[x] << ' ' << pro << std::endl;
        s.pop();
    }
}

struct segt
{
private:
    int n;
    std::vector<std::pair<int, int>> t[maxn * 4];
    int ls(int);
    int rs(int);
    void modify(int, int, int, int, int, std::pair<int, int>);
    void divide(int, int, int);

public:
    segt(int);
    void modify(int, int, std::pair<int, int>);
    void divide();
};

segt::segt(int _n) : n(_n) {}

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::modify(int x, int l, int r, int ql, int qr, std::pair<int, int> e)
{
    if (ql <= l && r <= qr)
    {
        t[x].push_back(e);
        return;
    }
    int mid = (l + r) / 2;
    if (ql <= mid)
        modify(ls(x), l, mid, ql, qr, e);
    else if (qr > mid)
        modify(rs(x), mid + 1, r, ql, qr, e);
}

void segt::divide(int x, int l, int r)
{
    int ori = dsu.getsiz();
    for (std::pair<int, int> e : t[x])
        dsu.merge(e.first, e.second);
    if (l ^ r)
    {
        int mid = (l + r) / 2;
        divide(ls(x), l, mid);
        divide(rs(x), mid + 1, r);
    }
    else
        std::cout << pro << std::endl;
    std::cout << x << ' ' << l << ' ' << r << std::endl;
    dsu.undo(ori);
}

void segt::modify(int l, int r, std::pair<int, int> e) { modify(1, 1, n, l, r, e); }

void segt::divide() { divide(1, 1, n); }

int main()
{
    freopen("C.in", "r", stdin);
    getinv();
    int n, m;
    std::cin >> n >> m;
    std::map<std::pair<int, int>, int> t;
    segt tr(m);
    for (int i = 1; i <= m; ++i)
    {
        int op, x, y;
        std::cin >> op >> x >> y;
        switch (op)
        {
        case 1:
        {
            t.emplace(std::make_pair(x, y), i);
            break;
        }
        case 2:
        {
            tr.modify(t.at(std::make_pair(x, y)), i - 1, std::make_pair(x, y));
            t.erase(std::make_pair(x, y));
            break;
        }
        }
    }
    for (std::pair<std::pair<int, int>, int> pr : t)
        tr.modify(pr.second, m, pr.first);
    dsu = DSU(n);
    tr.divide();
    return 0;
}