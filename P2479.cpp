#include <bits/stdc++.h>

const int maxn = 1e5;

void read(int &x)
{
    x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

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

int min, max;

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

int build(int l, int r, bool b)
{
    if (l == r)
    {
        t[l] = node(p[l]);
        return l;
    }

    int mid = (l + r) / 2;
    std::nth_element(p + l, p + mid, p + r + 1, [=](point x, point y)
                     { return b ? x.y < y.y : x.x < y.x; });
    t[mid] = node(p[mid]);
    if (l < mid)
    {
        t[mid].ls = build(l, mid - 1, b ^ 1);
        chkmin(t[mid].t, t[t[mid].ls].t);
        chkmax(t[mid].b, t[t[mid].ls].b);
        chkmin(t[mid].l, t[t[mid].ls].l);
        chkmax(t[mid].r, t[t[mid].ls].r);
    }
    if (r > mid)
    {
        t[mid].rs = build(mid + 1, r, b ^ 1);
        chkmin(t[mid].t, t[t[mid].rs].t);
        chkmax(t[mid].b, t[t[mid].rs].b);
        chkmin(t[mid].l, t[t[mid].rs].l);
        chkmax(t[mid].r, t[t[mid].rs].r);
    }
    return mid;
}

int calcmin(int x, point c)
{
    int ret;
    if (c.x < t[x].t)
        ret = t[x].t - c.x;
    else if (c.x > t[x].b)
        ret = c.x - t[x].b;
    else
        ret = 0;
    if (c.y < t[x].l)
        ret += t[x].l - c.y;
    else if (c.y > t[x].r)
        ret += c.y - t[x].r;
    return ret;
}

int calcmax(int x, point c) { return std::max(abs(t[x].t - c.x), abs(t[x].b - c.x)) + std::max(abs(t[x].l - c.y), abs(t[x].r - c.y)); }

void querymin(int l, int r, int x)
{
    int mid = (l + r) / 2;
    if (mid ^ x)
        chkmin(min, abs(p[x].x - p[mid].x) + abs(p[x].y - p[mid].y));
    if (l == r)
        return;
    int tmpl = t[mid].ls ? calcmin(t[mid].ls, p[x]) : INT_MAX, tmpr = t[mid].rs ? calcmin(t[mid].rs, p[x]) : INT_MAX;
    if (tmpl >= min && tmpr >= min)
        return;
    if (tmpl >= min)
        querymin(mid + 1, r, x);
    else if (tmpr >= min)
        querymin(l, mid - 1, x);
    else if (tmpl < tmpr)
    {
        querymin(l, mid - 1, x);
        if (tmpr < min)
            querymin(mid + 1, r, x);
    }
    else
    {
        querymin(mid + 1, r, x);
        if (tmpl < min)
            querymin(l, mid - 1, x);
    }
}

void querymax(int l, int r, int x)
{
    int mid = (l + r) / 2;
    if (mid ^ x)
        chkmax(max, abs(p[x].x - p[mid].x) + abs(p[x].y - p[mid].y));
    if (l == r)
        return;
    int tmpl = t[mid].ls ? calcmax(t[mid].ls, p[x]) : 0, tmpr = t[mid].rs ? calcmax(t[mid].rs, p[x]) : 0;
    if (tmpl <= max && tmpr <= max)
        return;
    if (tmpl <= max)
        querymax(mid + 1, r, x);
    else if (tmpr <= max)
        querymax(l, mid - 1, x);
    else if (tmpl > tmpr)
    {
        querymax(l, mid - 1, x);
        if (tmpr > max)
            querymax(mid + 1, r, x);
    }
    else
    {
        querymax(mid + 1, r, x);
        if (tmpl > max)
            querymax(l, mid - 1, x);
    }
}

int main()
{
    freopen("P2479.in", "r", stdin);
    int n;
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(p[i].x);
        read(p[i].y);
    }
    build(1, n, rand() & 1);
    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i)
    {
        min = INT_MAX;
        max = 0;
        querymin(1, n, i);
        querymax(1, n, i);
        chkmin(ans, max - min);
    }
    std::cout << ans << std::endl;
    return 0;
}