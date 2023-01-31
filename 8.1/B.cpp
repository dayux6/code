#include <bits/stdc++.h>

const int maxn = 3e5;

int cnt, f[maxn + 1];
bool b[maxn + 1];
std::vector<int> s[maxn + 1];

void dfs(int x)
{
    if (s[x].size() == 0)
    {
        ++cnt;
        return;
    }
    for (int v : s[x])
        dfs(v);
    if (b[x])
    {
        f[x] = INT_MAX;
        for (int v : s[x])
            f[x] = std::min(f[x], f[v]);
    }
    else
    {
        f[x] = -1;
        for (int v : s[x])
            f[x] += f[v] + 1;
    }
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        std::cin >> fa;
        s[fa].push_back(i);
    }
    dfs(1);
    std::cout << cnt - f[1] << std::endl;
    return 0;
}