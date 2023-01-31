#include <bits/stdc++.h>

typedef long double db;

struct point
{
    db x, y;

    point() { std::cin >> x >> y; }

    bool operator<(point rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
};

db slope(point x, point y)
{
    if (x.x == y.x)
        return INFINITY;
    return (x.y - y.y) / (x.x - y.x);
}

int main()
{
    freopen("P2742.in", "r", stdin);
    int n;
    std::cin >> n;
    point *p = new point[n]();
    std::sort(p, p + n);
    std::vector<int> s;
    for (int i = 0; i < n; ++i)
    {
        while (s.size() >= 2 && slope(p[i], p[s.at(s.size() - 2)]) < slope(p[s.at(s.size() - 2)], p[s.back()]))
            s.pop_back();
        s.emplace_back(i);
    }
    db sum = 0;
    for (int i = 1; i < s.size(); ++i)
        sum += hypot(p[s.at(i - 1)].x - p[s.at(i)].x, p[s.at(i - 1)].y - p[s.at(i)].y);
    s.clear();
    for (int i = n - 1; i >= 0; --i)
    {
        while (s.size() >= 2 && slope(p[i], p[s.at(s.size() - 2)]) < slope(p[s.at(s.size() - 2)], p[s.back()]))
            s.pop_back();
        s.emplace_back(i);
    }
    for (int i = 1; i < s.size(); ++i)
        sum += hypot(p[s.at(i - 1)].x - p[s.at(i)].x, p[s.at(i - 1)].y - p[s.at(i)].y);
    std::cout << std::fixed << std::setprecision(2) << round(sum * 100) / 100 << std::endl;
    return 0;
}