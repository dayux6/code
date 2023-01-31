#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 2e5;

struct edge
{
    int u, v, w;

    edge()
    {
        read(u);
        read(v);
        read(w);
    }

    bool operator<(edge rhs) const { return w < rhs.w; }
};

class DSU
{
private:
    int fa[maxn + 1];

    int find(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

public:
    void build(int n) { std::iota(fa + 1, fa + n + 1, 1); }

    void merge(int x, int y) { fa[find(x)] = find(y); }

    bool query(int x, int y) { return find(x) == find(y); }
};

int main()
{
    std::freopen("graph.in", "r", stdin);
    std::freopen("graph.out", "w", stdout);

    int n, m, k;
    read(n);
    read(m);
    read(k);

    std::cout << std::fixed << std::setprecision(6);

    if (n == 1)
    {
        std::cout << -1.0 << std::endl;
        return 0;
    }

    std::priority_queue<edge> q;
    for (int i = 0; i < m; ++i)
        q.emplace();

    int cnt = 1;
    long long sum = 0;
    DSU dsu;
    dsu.build(n);
    while (!q.empty())
    {
        edge e = q.top();
        q.pop();

        if (!dsu.query(e.u, e.v))
        {
            dsu.merge(e.u, e.v);
            ++cnt;

            if (cnt == n)
            {
                std::cout << (long double)(sum + std::max(e.w, k)) << std::endl;
                return 0;
            }

            sum += e.w;
        }
    }

    if (k == 0)
        std::cout << -1.0 << std::endl;
    else
        std::cout << (long double)(sum + k) << std::endl;
    return 0;
}