#include <bits/stdc++.h>

const int maxn = 5e5;

void chkmin(int &x, int y)
{
    if (x > y)
        x = y;
}

void chkmax(int &x, int y)
{
    if (x < y)
        x = y;
}

struct point
{
    int x, y;

    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
} p[maxn + 1];

long long calc(point x, point y) { return 1ll * (x.x - y.x) * (x.y - y.y); }

class kDT
{
private:
    int n, ls[maxn + 1], rs[maxn + 1], minx[maxn + 1], miny[maxn + 1], maxx[maxn + 1], maxy[maxn + 1], max;

    void update(int x, int y)
    {
        chkmin(minx[x], minx[y]);
        chkmin(miny[x], miny[y]);
        chkmax(maxx[x], maxx[y]);
        chkmax(maxy[x], maxy[y]);
    }

    int build(int l, int r, bool b = 0)
    {
        int mid = (l + r) / 2;
        std::nth_element(p + l, p + mid, p + r + 1, [=](point x, point y)
                         { return b ? x.y < y.y : x.x < y.x; });
        minx[mid] = maxx[mid] = p[mid].x;
        miny[mid] = maxy[mid] = p[mid].y;

        if (l == mid)
            ls[mid] = 0;
        else
        {
            ls[mid] = build(l, mid - 1, b ^ 1);
            update(mid, ls[mid]);
        }
        if (r == mid)
            rs[mid] = 0;
        else
        {
            rs[mid] = build(mid + 1, r, b ^ 1);
            update(mid, rs[mid]);
        }

        return mid;
    }

    long long f(int x, point c)
    {
        if (minx[x] > c.x || miny[x] > c.y)
            return 0;
        else
            return std::max({calc(point(minx[x], miny[x]), c), calc(point(minx[x], maxy[x]), c), calc(point(maxx[x], miny[x]), c), calc(point(maxx[x], maxy[x]), c)});
    }

    void query(int l, int r, point x)
    {
        int mid = (l + r) / 2;
        if (minx[mid] > x.x || miny[mid] > x.y)
            return;
        chkmax(max, calc(x, p[mid]));

        long long tmpl = (ls[mid] != 0) ? f(ls[mid], x) : 0, tmpr = (rs[mid] != 0) ? f(rs[mid], x) : 0;
        if (tmpl > max || tmpr > max)
        {
            if (tmpr <= max)
                query(l, mid - 1, x);
            else if (tmpl <= max)
                query(mid + 1, r, x);
            else if (tmpl > tmpr)
            {
                query(l, mid - 1, x);
                if (tmpr > max)
                    query(mid + 1, r, x);
            }
            else
            {
                query(mid + 1, r, x);
                if (tmpl > max)
                    query(l, mid - 1, x);
            }
        }
    }

public:
    kDT(int _n) : n(_n) { build(1, _n); }

    long long query(point x)
    {
        max = 0;
        query(1, n, x);
        return max;
    }
};

int main()
{
    freopen("C.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> p[i].x >> p[i].y;

    long long ans = 0;
    kDT t(n);
    for (int i = 0; i < m; ++i)
    {
        point x;
        std::cin >> x.x >> x.y;
        ans = std::max(ans, t.query(x));
    }

    std::cout << ans << std::endl;
    return 0;
}