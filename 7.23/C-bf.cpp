#include <bits/stdc++.h>

struct point
{
    int x, y;

    bool operator<(point rhs) const { return x < rhs.x; }
};

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    point *p = new point[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> p[i].x >> p[i].y;
    std::sort(p + 1, p + n + 1);
    int cnt = 0;
    for (int t = 1; t <= n; ++t)
    {
        int l = n + 1, r = 0;
        for (int b = t; b <= n; ++b)
        {
            l = std::min(l, p[b].y);
            r = std::max(r, p[b].y);
            if (r - l + 1 == b - t + 1)
                std::cerr << t << ' ' << b << ' ' << l << ' ' << r << std::endl,
                    ++cnt;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}