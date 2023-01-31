#include <bits/stdc++.h>

const int maxn = 2e3;

int a[maxn + 1], f[maxn + 1][maxn + 1];

namespace dsu
{
    int fa[maxn + 1], siz[maxn + 1];

    void build(int n)
    {
        std::iota(fa + 1, fa + n + 1, 1);
        std::fill_n(siz + 1, n, 1);
    }

    int find(int x)
    {
        if (x != fa[x])
            fa[x] = find(fa[x]);
        return fa[x];
    }

    void merge(int x, int y)
    {
        int u = find(x), v = find(y);

        if (u != v)
        {
            if (siz[u] < siz[v])
                std::swap(u, v);
            fa[v] = u;
            siz[u] += siz[v];
        }
    }
};

int solve()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    dsu::build(n);
    for (int i = 1, b; i <= n; ++i)
    {
        std::cin >> b;
        dsu::merge(a[i], b);
    }

    int max = 0;
    std::unordered_map<int, int> c;
    for (int i = 1; i <= n; ++i)
        if (i == dsu::find(i))
        {
            max = std::max(max, dsu::siz[i]);
            ++c[dsu::siz[i]];
        }

    int ret = 0;
    for (int i = 0; i <= max; ++i)
    {
        int res = 0;

        for (std::pair<int, int> pr : c)
            if (pr.first >= i)
                res += f[pr.first][i] * pr.second;

        ret = std::max(ret, res);
    }

    return ret;
}

int main()
{
    std::freopen("card.in", "r", stdin);
    std::freopen("card.out", "w", stdout);

    f[1][0] = 1;
    for (int i = 1; i <= maxn; ++i)
        for (int j = 1; j <= i; ++j)
            f[i][j] = std::max(f[i - j][j] + j - 1, (i - j - 1 < 0 ? INT_MIN : f[i - j - 1][j]) + j);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}