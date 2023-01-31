#include <bits/stdc++.h>

typedef long double db;

struct point
{
    db x, y;

    point() { std::cin >> x >> y; }
};

std::pair<db, db> vec(point x, point y) { return std::make_pair(x.x - y.x, x.y - y.y); }

db dot(std::pair<db, db> x, std::pair<db, db> y) { return 1ll * x.first * y.first + 1ll * x.second * y.second; }

db cross(std::pair<db, db> x, std::pair<db, db> y) { return 1ll * x.first * y.second - 1ll * x.second * y.first; }

db calc(point x, point y, point z)
{
    std::pair<db, db> veca = vec(x, y), vecb = vec(z, y);
    // db lena = hypot(veca.first, veca.second), lenb = hypot(vecb.first, vecb.second);
    // return atan2(cross(veca, vecb) / lena / lenb, dot(veca, vecb) / lena / lenb);
    return cross(veca, vecb);
}

int solve()
{
    int n;
    std::cin >> n;
    point *p = new point[n]();
    db *a = new db[n * 4];
    a[0] = calc(p[n - 1], p[0], p[1]);
    for (int i = 1; i < n - 1; ++i)
    {
        a[i * 2 - 1] = hypot(p[i - 1].x - p[i].x, p[i - 1].y - p[i].y);
        a[i * 2] = calc(p[i - 1], p[i], p[i + 1]);
    }
    a[n * 2 - 3] = hypot(p[n - 2].x - p[n - 1].x, p[n - 2].y - p[n - 1].y);
    a[n * 2 - 2] = calc(p[n - 2], p[n - 1], p[0]);
    a[n * 2 - 1] = hypot(p[n - 1].x - p[0].x, p[n - 1].y - p[0].y);
    std::copy_n(a, n * 2, a + n * 2);
    int *pal = new int[n * 4], mid = 0, r = 0;
    pal[0] = 1;
    for (int i = 1; i < n * 4; ++i)
    {
        if (i <= r)
            pal[i] = std::min(pal[mid * 2 - i], r - i + 1);
        else
            pal[i] = 1;
        while (i - pal[i] >= 0 && i + pal[i] < n * 4 && a[i - pal[i]] == a[i + pal[i]])
            ++pal[i];
        if (i + pal[i] - 1 > r)
        {
            r = i + pal[i] - 1;
            mid = i;
        }
    }
    int cnt = 0;
    for (int i = 0; i < n * 4; ++i)
        if (pal[i] > n)
            ++cnt;
    return cnt / 2;
}

int main()
{
    freopen("B.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    for (int _ = 0; _ < t; ++_)
        std::cout << solve() << std::endl;
    return 0;
}