#include <bits/stdc++.h>

const int maxn = 250;

int p[maxn + 1], t, cnt, vis[maxn + 1];
long long S;
std::vector<int> g[maxn + 1];

bool dfs(int x)
{
    if (vis[x] == cnt || !((S >> (x - 1)) & 1))
        return false;
    if (x == t)
        return true;

    vis[x] = cnt;
    for (int v : g[x])
        if (dfs(v))
            return true;
    return false;
}

int main()
{
    freopen("C.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
    }

    long long min = LLONG_MAX;
    for (S = (1ll << (n - 1)) + 1; S < (1ll << n); S += 2)
    {
        t = n;
        ++cnt;
        if (dfs(1))
        {
            t = 1;
            ++cnt;
            if (dfs(n))
            {
                long long sum = 0;
                for (int i = 1; i <= n; ++i)
                    if ((S >> (i - 1)) & 1)
                        sum += p[i];
                min = std::min(min, sum);
            }
        }
    }

    std::cout << (min ^ LLONG_MAX ? min : -1) << std::endl;
    return 0;
}