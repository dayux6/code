#include <bits/stdc++.h>

const int maxn = 5e4;

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

struct choco
{
    int x, y, h;
} ch[maxn + 1];

struct person
{
    int a, b, c;

    person() { std::cin >> a >> b >> c; }
};

class kDT
{
private:
    int n;

    struct node
    {
        int minx, miny, maxx, maxy, ls, rs;
        long long sumh;

        node() {}
        node(choco x) : minx(x.x), miny(x.y), maxx(x.x), maxy(x.y), sumh(x.h), ls(0), rs(0) {}
    } t[maxn + 1];

    int build(int l, int r, bool b)
    {
        int mid = (l + r) / 2;
        std::nth_element(ch + l, ch + mid, ch + r + 1, [=](choco x, choco y)
                         { return b ? x.x < y.x : x.y < y.y; });
        t[mid] = node(ch[mid]);

        if (l ^ r)
        {
            if (l < mid)
            {
                t[mid].ls = build(l, mid - 1, b ^ 1);

                chkmin(t[mid].minx, t[t[mid].ls].minx);
                chkmin(t[mid].miny, t[t[mid].ls].miny);
                chkmax(t[mid].maxx, t[t[mid].ls].maxx);
                chkmax(t[mid].maxy, t[t[mid].ls].maxy);
                t[mid].sumh += t[t[mid].ls].sumh;
            }

            if (r > mid)
            {
                t[mid].rs = build(mid + 1, r, b ^ 1);

                chkmin(t[mid].minx, t[t[mid].rs].minx);
                chkmin(t[mid].miny, t[t[mid].rs].miny);
                chkmax(t[mid].maxx, t[t[mid].rs].maxx);
                chkmax(t[mid].maxy, t[t[mid].rs].maxy);
                t[mid].sumh += t[t[mid].rs].sumh;
            }
        }

        return mid;
    }

    bool check(int x, int y, person p) { return 1ll * p.a * x + 1ll * p.b * y < p.c; }

    long long query(int l, int r, person p)
    {
        int mid = (l + r) / 2, cnt = check(t[mid].minx, t[mid].miny, p) + check(t[mid].minx, t[mid].maxy, p) + check(t[mid].maxx, t[mid].miny, p) + check(t[mid].maxx, t[mid].maxy, p);

        if (cnt == 4)
            return t[mid].sumh;
        else if (!cnt)
            return 0;
        else
        {
            long long ret = check(ch[mid].x, ch[mid].y, p) ? ch[mid].h : 0;

            if (l < mid)
                ret += query(l, mid - 1, p);

            if (r > mid)
                ret += query(mid + 1, r, p);

            return ret;
        }
    }

public:
    kDT(int _n) : n(_n) { build(1, n, rand() & 1); }

    long long query(person p) { return query(1, n, p); }
};

int main()
{
    freopen("P4475.in", "r", stdin);
    srand(time(nullptr));

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> ch[i].x >> ch[i].y >> ch[i].h;

    kDT t(n);
    for (int i = 0; i < m; ++i)
        std::cout << t.query(person()) << std::endl;
    return 0;
}