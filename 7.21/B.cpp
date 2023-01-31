#include <bits/stdc++.h>

typedef long double db;

const db eps = 1e-12;

int lg, *dep, *a, *b;
long long *sum;
std::vector<int> *g;

void dp(int x, int fa)
{
    b[1] += dep[x] * a[x];
    sum[x] = a[x];
    for (int v : g[x])
        if (v ^ fa)
        {
            dep[v] = dep[x] + 1;
            dp(v, x);
            sum[x] += sum[v];
        }
}

void changert(int x, int fa)
{
    if (fa != 0)
        b[x] = b[fa] + sum[1] - sum[x] * 2;
    for (int v : g[x])
        if (v ^ fa)
            changert(v, x);
}

void dfs(int x, int fa)
{
    if (fa != 0)
        sum[1] += b[x] - b[fa];
    for (int v : g[x])
        if (v ^ fa)
            dfs(v, x);
}

void geta(int x, int fa)
{
    if (fa != 0)
        sum[x] = -(b[x] - b[fa] - sum[1]) / 2;
    a[x] = sum[x];
    for (int v : g[x])
        if (v ^ fa)
        {
            geta(v, x);
            a[x] -= sum[v];
        }
}

int main()
{
    freopen("B.in", "r", stdin);
    int t;
    std::cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n;
        std::cin >> n;
        g = new std::vector<int>[n + 1];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            std::cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        bool type;
        std::cin >> type;
        if (type)
        {
            b = new int[n + 1];
            for (int i = 1; i <= n; ++i)
                std::cin >> b[i];
            sum = new long long[n + 1];
            sum[1] = b[1] * 2;
            dfs(1, 0);
            sum[1] /= n - 1;
            a = new int[n + 1];
            geta(1, 0);
            for (int i = 1; i <= n; ++i)
                std::cout << a[i] << ' ';
            std::cout << std::endl;
        }
        else
        {
            a = new int[n + 1];
            for (int i = 1; i <= n; ++i)
                std::cin >> a[i];
            dep = new int[n + 1];
            dep[1] = 0;
            sum = new long long[n + 1];
            b = new int[n + 1];
            dp(1, 0);
            changert(1, 0);
            for (int i = 1; i <= n; ++i)
                std::cout << b[i] << ' ';
            std::cout << std::endl;
        }
    }
    return 0;
}