#include <bits/stdc++.h>

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

void write(int x)
{
    static int t = 0;
    static char s[10];
    do
    {
        s[t] = x % 10;
        ++t;
        x /= 10;
    } while (x);
    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
}

const int maxn = 1e5, maxlg = 17;

int n, sum[maxn + 1], dfc, in[maxn + 1], lg, st[maxn * 2][maxlg + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

void dfs(int x, int fa)
{
    ++dfc;
    in[x] = dfc;
    st[dfc][0] = x;
    for (edge e : g[x])
        if (e.v ^ fa)
        {
            sum[e.v] = sum[x] + e.w;
            dfs(e.v, x);
            ++dfc;
            st[dfc][0] = x;
        }
}

void RMQ()
{
    for (int i = 1; i <= lg; ++i)
        for (int j = 1; j + (1 << i) - 1 < n * 2; ++j)
            if (in[st[j][i - 1]] < in[st[j + (1 << (i - 1))][i - 1]])
                st[j][i] = st[j][i - 1];
            else
                st[j][i] = st[j + (1 << (i - 1))][i - 1];
}

int getlca(int x, int y)
{
    if (in[x] < in[y])
        std::swap(x, y);
    int k = log2(in[x] - in[y] + 1);
    if (in[st[in[y]][k]] < in[st[in[x] - (1 << k) + 1][k]])
        return st[in[y]][k];
    else
        return st[in[x] - (1 << k) + 1][k];
}

int getdis(int x, int y) { return sum[x] + sum[y] - sum[getlca(x, y)] * 2; }

class segt
{
private:
    int n;
    struct node
    {
        int max, x, y;

        node operator+(node rhs)
        {
            node ret;
            if (max > rhs.max)
                ret = *this;
            else
                ret = rhs;

            int dis = getdis(x, rhs.x);
            if (dis > ret.max)
            {
                ret.max = dis;
                ret.x = x;
                ret.y = rhs.x;
            }

            dis = getdis(x, rhs.y);
            if (dis > ret.max)
            {
                ret.max = dis;
                ret.x = x;
                ret.y = rhs.y;
            }

            dis = getdis(y, rhs.x);
            if (dis > ret.max)
            {
                ret.max = dis;
                ret.x = y;
                ret.y = rhs.x;
            }

            dis = getdis(y, rhs.y);
            if (dis > ret.max)
            {
                ret.max = dis;
                ret.x = y;
                ret.y = rhs.y;
            }

            return ret;
        }
    } t[maxn * 4];
    int ls(int);
    int rs(int);
    void build(int, int, int);
    node query(int, int, int, int, int);

public:
    segt(int);
    int query(int, int, int, int);
};

segt::segt(int _n) : n(_n) { build(1, 1, _n); }

int segt::ls(int x) { return x * 2; }

int segt::rs(int x) { return x * 2 + 1; }

void segt::build(int x, int l, int r)
{
    if (l == r)
    {
        t[x].max = 0;
        t[x].x = l;
        t[x].y = r;
        return;
    }

    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);

    t[x] = t[ls(x)] + t[rs(x)];
}

segt::node segt::query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x];

    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else
        return query(ls(x), l, mid, ql, qr) + query(rs(x), mid + 1, r, ql, qr);
}

int segt::query(int l1, int r1, int l2, int r2)
{
    node x = query(1, 1, n, l1, r1), y = query(1, 1, n, l2, r2);
    return std::max(std::max(getdis(x.x, y.x), getdis(x.x, y.y)), std::max(getdis(x.y, y.x), getdis(x.y, y.y)));
}

int main()
{
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        read(u);
        read(v);
        read(w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0);
    lg = log2(n * 2 - 1);
    RMQ();
    segt t(n);
    int m;
    read(m);
    for (int i = 0; i < m; ++i)
    {
        int l1, r1, l2, r2;
        read(l1);
        read(r1);
        read(l2);
        read(r2);
        write(t.query(l1, r1, l2, r2));
        putchar('\n');
    }
    return 0;
}