#include <bits/stdc++.h>

typedef long double db;

struct point
{
    db x, y, ang;

    point() {}
    point(db _x, db _y, db _ang) : x(_x), y(_y), ang(_ang) {}

    bool operator<(point rhs) const { return ang == rhs.ang ? x < rhs.x : ang < rhs.ang; }
} O;

std::pair<db, db> getvec(point x, point y) { return std::make_pair(x.x - y.x, x.y - y.y); }

db cross(std::pair<db, db> x, std::pair<db, db> y) { return x.first * y.second - x.second * y.first; }

int main()
{
    freopen("CF70D.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    point o[3];
    std::set<point> s;
    for (int i = 0; i < 3; ++i)
    {
        int _;
        std::cin >> _ >> o[i].x >> o[i].y;
        O.x += o[i].x;
        O.y += o[i].y;
        o[i].x *= 3;
        o[i].y *= 3;
    }
    for (int i = 0; i < 3; ++i)
        s.emplace(o[i].x, o[i].y, atan2(o[i].y - O.y, o[i].x - O.x));
    auto getpre = [&](std::set<point>::iterator it)
    {
        if (it == s.begin())
            return --s.end();
        else
            return --it;
    };
    auto getsuf = [&](std::set<point>::iterator it)
    {
        ++it;
        if (it == s.end())
            return s.begin();
        else
            return it;
    };
    for (int i = 3; i < n; ++i)
    {
        int op;
        point x;
        std::cin >> op >> x.x >> x.y;
        x.x *= 3;
        x.y *= 3;
        x.ang = atan2(x.y - O.y, x.x - O.x);
        auto suf = s.lower_bound(x);
        if (suf == s.end())
            suf = s.begin();
        auto pre = getpre(suf);
        switch (op)
        {
        case 1:
        {
            if (cross(getvec(*pre, x), getvec(*suf, x)) <= 0)
            {
                s.insert(x);
                auto it = s.find(x), p1 = getpre(it), p2 = getpre(p1);
                while (s.size() > 3 && cross(getvec(x, *p2), getvec(*p1, *p2)) >= 0)
                {
                    p1 = getpre(s.erase(p1));
                    p2 = getpre(p1);
                }
                p1 = getsuf(it);
                p2 = getsuf(p1);
                while (s.size() > 3 && cross(getvec(x, *p2), getvec(*p1, *p2)) <= 0)
                {
                    p1 = s.erase(p1);
                    if (p1 == s.end())
                        p1 = s.begin();
                    p2 = getsuf(p1);
                }
            }
            break;
        }
        case 2:
        {
            std::cout << (cross(getvec(*pre, x), getvec(*suf, x)) >= 0 ? "YES\n" : "NO\n");
            break;
        }
        }
    }
    return 0;
}