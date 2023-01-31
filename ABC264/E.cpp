#include <bits/stdc++.h>

const int maxnm = 2e5, maxe = 5e5, maxq = 5e5;

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

template <typename... arg>
void read(int &x, arg &...y)
{
    read(x);
    read(y...);
}

void write(int x)
{
    static int t = 0, s[6];

    do
    {
        s[t] = x % 10;
        x /= 10;
        ++t;
    } while (x != 0);

    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
}

int X[maxq], ans[maxq];
bool isd[maxe + 1];

struct edge
{
    int u, v;
} E[maxe + 1];

class DSU
{
private:
    int fa[maxnm + 1], siz[maxnm + 1];

    int find(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

public:
    DSU(int n)
    {
        std::iota(fa, fa + n + 1, 0);
        std::fill_n(siz, n + 1, 1);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x != y)
        {
            if (x == 0)
                std::swap(x, y);
            fa[x] = y;
            siz[y] += siz[x];
        }
    }

    int query() { return siz[0]; }
};

int main()
{
    freopen("E.in", "r", stdin);
    int n, m, e;
    read(n, m, e);

    for (int i = 1; i <= e; ++i)
        read(E[i].u, E[i].v);

    int q;
    read(q);
    for (int i = 0; i < q; ++i)
    {
        read(X[i]);
        isd[X[i]] = true;
    }

    DSU dsu(n + m);
    for (int i = 1; i <= m; ++i)
        dsu.merge(n + i, 0);

    for (int i = 1; i <= e; ++i)
        if (!isd[i])
            dsu.merge(E[i].u, E[i].v);

    for (int i = q - 1; i >= 0; --i)
    {
        ans[i] = dsu.query() - m - 1;
        dsu.merge(E[X[i]].u, E[X[i]].v);
    }

    for (int i = 0; i < q; ++i)
    {
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}