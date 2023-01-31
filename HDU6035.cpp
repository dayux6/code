#include <bits/stdc++.h>

int *c, *cnt;
long long ans;
std::vector<int> *g;

int dfs(int x, int fa)
{
    int ret = 1, old = cnt[c[x]];
    for (int v : g[x])
        if (v != fa)
        {
            cnt[c[x]] = 0;
            int tmp = dfs(v, x);
            ret += tmp;
            ans += 1ll * (tmp - cnt[c[x]]) * (tmp - cnt[c[x]] - 1) / 2;
        }
    cnt[c[x]] = old + ret;
    return ret;
}

int main()
{
    freopen("HDU6035.in", "r", stdin);
    int _ = 0;
    while (!std::cin.eof())
    {
        int n;
        std::cin >> n;
        c = new int[n + 1];
        std::unordered_set<int> s;
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> c[i];
            s.emplace(c[i]);
        }
        g = new std::vector<int>[n + 1];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            std::cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        ans = 0;
        cnt = new int[n + 1]();
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
            if (s.count(i) != 0)
                ans += 1ll * (n - cnt[i]) * (n - cnt[i] - 1) / 2;
        ++_;
        std::cout << "Case #" << _ << ": " << 1ll * s.size() * n * (n - 1) / 2 - ans << std::endl;
        std::cin >> std::ws;
    }
    return 0;
}