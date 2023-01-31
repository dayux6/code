#include <bits/stdc++.h>

typedef long double db;

const db pi = acos(-1);

struct point
{
    db x, y;

    point(db _x, db _y) : x(_x), y(_y) {}

    bool operator<(point rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
};

point vec(point x, point y) { return point{x.x - y.x, x.y - y.y}; }

db calc(point x, point y, point z)
{
    point p = vec(x, y), q = vec(y, z);
    return p.x * q.y - p.y * q.x;
}

int main()
{
    freopen("P3829.in", "r", stdin);
    int n;
    db h, w, r;
    std::cin >> n >> h >> w >> r;
    db len = hypot(h / 2 - r, w / 2 - r), rt = atan2(h / 2 - r, w / 2 - r), rb = atan2(h / 2 - r, r - w / 2), lb = atan2(r - h / 2, r - w / 2), lt = atan2(r - h / 2, w / 2 - r);
    std::set<point> sp;
    for (int i = 0; i < n; ++i)
    {
        db x, y, theta;
        std::cin >> x >> y >> theta;
        sp.emplace(x + len * cos(rt + theta), y + len * sin(rt + theta));
        sp.emplace(x + len * cos(rb + theta), y + len * sin(rb + theta));
        sp.emplace(x + len * cos(lb + theta), y + len * sin(lb + theta));
        sp.emplace(x + len * cos(lt + theta), y + len * sin(lt + theta));
    }
    std::vector<point> s;
    for (point p : sp)
    {
        while (s.size() >= 2 && calc(s.at(s.size() - 2), s.back(), p) <= 0)
            s.pop_back();
        s.emplace_back(p);
    }
    db sum = 2 * pi * r;
    for (int i = 1; i < s.size(); ++i)
        sum += hypot(s.at(i - 1).x - s.at(i).x, s.at(i - 1).y - s.at(i).y);
    s.clear();
    for (auto it = sp.rbegin(); it != sp.rend(); ++it)
    {
        while (s.size() >= 2 && calc(s.at(s.size() - 2), s.back(), *it) <= 0)
            s.pop_back();
        s.emplace_back(*it);
    }
    for (int i = 1; i < s.size(); ++i)
        sum += hypot(s.at(i - 1).x - s.at(i).x, s.at(i - 1).y - s.at(i).y);
    std::cout << std::fixed << std::setprecision(2) << round(sum * 100) / 100 << std::endl;
    return 0;
}