#include <bits/stdc++.h>

const int maxn = 1e5;

struct rect
{
    int x1, y1, x2, y2;

    rect() { std::cin >> x1 >> y1 >> x2 >> y2; }
};

bool check(int l1, int r1, int l2, int r2)
{
    if (l1 > l2)
    {
        std::swap(l1, l2);
        std::swap(r1, r2);
    }

    return r1 >= l2;
}

bool check(rect x, rect y) { return check(x.x1, x.x2, y.x1, y.x2) && check(x.y1, x.y2, y.y1, y.y2); }

class DSU
{
private:
    int n, fa[maxn];

public:
    DSU(int _n) : n(_n) { std::iota(fa, fa + n, 0); }

    int find(int x)
    {
        while (x ^ fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

    void merge(int x, int y) { fa[find(x)] = find(y); }
};

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;

    rect *r = new rect[n]();

    DSU dsu(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (check(r[i], r[j]))
                dsu.merge(i, j);

    int cnt = 0;
    for (int i = 0; i < n; ++i)
        cnt += i == dsu.find(i);
    std::cout << cnt << std::endl;
    return 0;
}