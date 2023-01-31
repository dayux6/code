#include <bits/stdc++.h>

int main()
{
    freopen("C.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    int *t = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> t[i];
    int *ind = new int[n + 1]();
    std::vector<int> *g = new std::vector<int>[n + 1];
    for (int i = 0; i < k; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        ind[v]++;
        g[u].emplace_back(v);
    }
    long long *f = new long long[n + 1];
    std::fill_n(f + 1, n, 0);
    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (ind[i] == 0)
        {
            f[i] = t[i];
            q.emplace(i);
        }
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int v : g[x])
        {
            ind[v]--;
            f[v] = std::max(f[v], f[x] + t[v]);
            if (ind[v] == 0)
                q.emplace(v);
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        if (g[i].size() == 0)
            ans = std::max(ans, f[i]);
    std::cout << ans << std::endl;
    return 0;
}