#include <bits/stdc++.h>

const int maxn = 5e5, maxm = 5e5;

struct point
{
    int x, y;

    bool operator<(point rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
} fac[maxn + 1], shop[maxm + 1];

std::pair<int, int> getvec(point x, point y) { return std::make_pair(x.x - y.x, x.y - y.y); }

long long cross(std::pair<int, int> x, std::pair<int, int> y) { return 1ll * x.first * y.second - 1ll * x.second * y.first; }

int main()
{
    freopen("C.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> fac[i].y >> fac[i].x;
    for (int i = 1; i <= m; ++i)
        std::cin >> shop[i].y >> shop[i].x;

    std::sort(fac + 1, fac + n + 1);
    std::sort(shop + 1, shop + m + 1);
    int p = 1;
    long long ans = 0;
    std::vector<point> s;
    for (int i = 1; i <= m; ++i)
    {
        while (p <= n && fac[p].x <= shop[i].x)
        {
            while (s.size() > 2 && cross(getvec(fac[p], s.at(s.size() - 2)), getvec(s.back(), s.at(s.size() - 2))) > 0)
                s.pop_back();
            s.push_back(fac[p]);
            ++p;
        }

        for (auto it = s.rbegin(); it != s.rend(); ++it)
            ans = std::max(ans, 1ll * (shop[i].x - it->x) * (shop[i].y - it->y));
    }

    std::cout << ans << std::endl;
    return 0;
}