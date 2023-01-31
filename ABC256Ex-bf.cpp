#include <bits/stdc++.h>

#pragma GCC optimize(2, 3, "Ofast")

const int maxn = 5e5;

int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
    return x;
}

void write(long long x)
{
    static int t = 0;
    static int s[19];
    do
    {
        s[t] = x % 10;
        ++t;
        x /= 10;
    } while (x);
    while (t > 0)
    {
        --t;
        putchar(s[t] + '0');
    }
    putchar('\n');
}

class ChthollyTree
{
private:
    int n;
    struct node
    {
        int l, r;
        mutable int v;

        node(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}

        bool operator<(node rhs) const { return l < rhs.l; }
    };
    std::set<node> t;
    void split(int);

public:
    ChthollyTree(int);
    void divide(int, int, int);
    void assign(int, int, int);
    long long query(int, int);
};

ChthollyTree::ChthollyTree(int _n) : n(_n)
{
    for (int i = 1; i <= n; ++i)
        t.insert(node(i, i, read()));
}

void ChthollyTree::split(int x)
{
    if (x <= n)
    {
        auto it = --t.upper_bound(node(x, 0, 0));
        if (it->l != x)
        {
            int l = it->l, r = it->r, v = it->v;
            t.erase(it);
            t.insert(node(l, x - 1, v));
            t.insert(node(x, r, v));
        }
    }
}

void ChthollyTree::divide(int l, int r, int v)
{
    split(l);
    split(r + 1);
    auto itl = t.lower_bound(node(l, 0, 0)), itr = t.lower_bound(node(r + 1, 0, 0));
    for (auto it = itl; it != itr; ++it)
        it->v /= v;
}

void ChthollyTree::assign(int l, int r, int v)
{
    split(l);
    split(r + 1);
    auto itl = t.lower_bound(node(l, 0, 0)), itr = t.lower_bound(node(r + 1, 0, 0));
    t.erase(itl, itr);
    t.insert(node(l, r, v));
}

long long ChthollyTree::query(int l, int r)
{
    split(l);
    split(r + 1);
    long long ret = 0;
    auto itl = t.lower_bound(node(l, 0, 0)), itr = t.lower_bound(node(r + 1, 0, 0));
    for (auto it = itl; it != itr; ++it)
        ret += 1ll * (it->r - it->l + 1) * it->v;
    return ret;
}

int main()
{
    freopen("ABC256Ex.in", "r", stdin);
    int n = read(), q = read();
    ChthollyTree t(n);
    for (int i = 0; i < q; ++i)
        switch (read())
        {
        case 1:
        {
            int l = read(), r = read(), v = read();
            t.divide(l, r, v);
            break;
        }
        case 2:
        {
            int l = read(), r = read(), v = read();
            t.assign(l, r, v);
            break;
        }
        case 3:
        {
            int l = read(), r = read();
            write(t.query(l, r));
            break;
        }
        }

    return 0;
}