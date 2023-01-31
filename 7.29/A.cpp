#include <bits/stdc++.h>

const int maxn = 1e7, mod = 998244353;

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

int ans, inv[maxn + 1];
std::vector<int> t[maxn + 1];

void getinv()
{
    inv[1] = 1;
    for (int i = 2; i <= maxn; ++i)
        inv[i] = (-1ll * (mod / i) * inv[mod % i] % mod + mod) % mod;
}

int dfs(int x)
{
    int ret = 1;
    for (int v : t[x])
        ret += dfs(v);
    ans = (ans + inv[ret]) % mod;
    return ret;
}

int main()
{
    freopen("A.in", "r", stdin);
    getinv();
    int n;
    read(n);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        read(fa);
        t[fa].push_back(i);
    }
    dfs(1);
    std::cout << ans << std::endl;
    return 0;
}