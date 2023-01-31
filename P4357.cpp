#include <bits/stdc++.h>

#define int long long

const int maxn = 1e5;

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

int sq(int x) { return x * x; }

double sq(double x) { return x * x; }

std::priority_queue<int, std::vector<int>, std::greater<int>> q;

struct point
{
    int x, y;
} p[maxn + 1];

struct node
{
    int t, b, l, r, ls, rs;

    node() {}
    node(point x) : t(x.x), b(x.x), l(x.y), r(x.y), ls(0), rs(0) {}
} t[maxn + 1];

void update(int x)
{
    if (t[x].ls != 0)
    {
        chkmin(t[x].t, t[t[x].ls].t);
        chkmax(t[x].b, t[t[x].ls].b);
        chkmin(t[x].l, t[t[x].ls].l);
        chkmax(t[x].r, t[t[x].ls].r);
    }

    if (t[x].rs != 0)
    {
        chkmin(t[x].t, t[t[x].rs].t);
        chkmax(t[x].b, t[t[x].rs].b);
        chkmin(t[x].l, t[t[x].rs].l);
        chkmax(t[x].r, t[t[x].rs].r);
    }
}

int build(int l, int r)
{
    if (l == r)
    {
        t[l] = node(p[l]);
        return l;
    }

    double avgx = 0, avgy = 0;
    for (int i = l; i <= r; ++i)
    {
        avgx += p[i].x;
        avgy += p[i].y;
    }
    avgx /= r - l + 1;
    avgy /= r - l + 1;

    double varx = 0, vary = 0;
    for (int i = l; i <= r; ++i)
    {
        varx += sq(avgx - p[i].x);
        vary += sq(avgy - p[i].y);
    }

    int mid = (l + r) / 2;
    std::nth_element(p + l, p + mid, p + r + 1, [=](point x, point y)
                     { return varx < vary ? x.y < y.y : x.x < y.x; });
    t[mid] = node(p[mid]);
    if (l < mid)
        t[mid].ls = build(l, mid - 1);
    if (r > mid)
        t[mid].rs = build(mid + 1, r);
    update(mid);
    return mid;
}

int calc(int x, point c) { return std::max(sq(t[x].t - c.x), sq(t[x].b - c.x)) + std::max(sq(t[x].l - c.y), sq(t[x].r - c.y)); }

void solve(int l, int r, point c)
{
    int mid = (l + r) / 2, d = sq(p[mid].x - c.x) + sq(p[mid].y - c.y);
    if (d > q.top())
    {
        q.pop();
        q.push(d);
    }
    if (l == r)
        return;

    int tmpl = t[mid].ls ? calc(t[mid].ls, c) : 0, tmpr = t[mid].rs ? calc(t[mid].rs, c) : 0;
    if (tmpl <= q.top() && tmpr <= q.top())
        return;
    if (tmpl <= q.top())
        solve(mid + 1, r, c);
    else if (tmpr <= q.top())
        solve(l, mid - 1, c);
    else if (tmpl < tmpr)
    {
        solve(mid + 1, r, c);
        if (tmpl > q.top())
            solve(l, mid - 1, c);
    }
    else
    {
        solve(l, mid - 1, c);
        if (tmpr > q.top())
            solve(mid + 1, r, c);
    }
}

signed main()
{
    freopen("P4357.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        std::cin >> p[i].x >> p[i].y;
    build(1, n);
    for (int i = 0; i < k * 2; ++i)
        q.push(0);
    for (int i = 1; i <= n; ++i)
        solve(1, n, p[i]);
    std::cout << q.top() << std::endl;
    return 0;
}