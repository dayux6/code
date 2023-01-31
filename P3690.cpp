#include <bits/stdc++.h>

const int maxn = 1e5;

int a[maxn + 1];

class LCT
{
private:
    struct node
    {
        int val, sum, fa, s[2];
        bool tag;

        node(int _val = 0) : val(_val), sum(_val), fa(0), tag(false) { s[0] = s[1] = 0; }
    } t[maxn + 1];

    void update(int x) { t[x].sum = t[t[x].s[0]].sum ^ t[x].val ^ t[t[x].s[1]].sum; }

    bool isroot(int x) { return x ^ t[t[x].fa].s[0] && x ^ t[t[x].fa].s[1]; }

    bool getdir(int x) { return x == t[t[x].fa].s[1]; }

    void rotate(int x)
    {
        int y = t[x].fa, z = t[y].fa;
        bool k = getdir(x);

        t[x].fa = z;
        if (!isroot(y))
            t[z].s[getdir(y)] = x;
        t[y].s[k] = t[x].s[k ^ 1];
        t[t[x].s[k ^ 1]].fa = y;
        t[x].s[k ^ 1] = y;
        t[y].fa = x;

        update(y);
        update(x);
    }

    void pushdown(int x)
    {
        if (t[x].tag)
        {
            std::swap(t[x].s[0], t[x].s[1]);
            t[t[x].s[0]].tag ^= 1;
            t[t[x].s[1]].tag ^= 1;
            t[x].tag = false;
        }
    }

    void pushup(int x)
    {
        if (!isroot(x))
            pushup(t[x].fa);
        pushdown(x);
    }

    void splay(int x)
    {
        pushup(x);
        for (int fa = t[x].fa; !isroot(x); rotate(x), fa = t[x].fa)
            if (!isroot(fa))
                rotate(getdir(x) ^ getdir(fa) ? x : fa);
    }

    void access(int x)
    {
        for (int s = 0; x; s = x, x = t[x].fa)
        {
            splay(x);
            t[x].s[1] = s;
            update(x);
        }
    }

    void makeroot(int x)
    {
        access(x);
        splay(x);
        t[x].tag ^= 1;
    }

    int findroot(int x)
    {
        access(x);
        splay(x);

        while (t[x].s[0])
            x = t[x].s[0];
        return x;
    }

    void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }

public:
    LCT(int _n)
    {
        for (int i = 1; i <= _n; ++i)
            t[i] = node(a[i]);
    }

    int query(int x, int y)
    {
        split(x, y);
        return t[y].sum;
    }

    void link(int x, int y)
    {
        if (findroot(x) != findroot(y))
        {
            makeroot(x);
            t[x].fa = y;
        }
    }

    void cut(int x, int y)
    {
        if (findroot(x) == findroot(y))
        {
            split(x, y);
            if (t[x].fa == y && t[x].s[1] == 0)
                t[y].s[0] = t[x].fa = 0;
        }
    }

    void modify(int x, int y)
    {
        makeroot(x);
        t[x].sum ^= t[x].val;
        t[x].val = y;
        t[x].sum ^= t[x].val;
    }
};

int main()
{
    freopen("P3690.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    LCT t(n);
    for (int i = 0; i < m; ++i)
    {
        int op, x, y;
        std::cin >> op >> x >> y;

        switch (op)
        {
        case 0:
            std::cout << t.query(x, y) << std::endl;
            break;
        case 1:
            t.link(x, y);
            break;
        case 2:
            t.cut(x, y);
            break;
        case 3:
            t.modify(x, y);
            break;
        }
    }
    return 0;
}