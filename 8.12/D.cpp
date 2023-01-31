#include <bits/stdc++.h>

const int maxn = 3e3, mod = 1e9 + 7;

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

int getinv(int x) { return qpow(x, mod - 2); }

int n, f[maxn + 1][maxn + 1][2];
bool flg[maxn + 1];
std::vector<int> s[maxn + 1];

void dfs(int x)
{
    if (s[x].empty())
        for (int i = 0; i <= n; ++i)
            f[x][i][1] = 1;
    else
    {
        for (int i = 0; i <= n; ++i)
            f[x][i][0] = 1;
        for (int v : s[x])
        {
            dfs(v);

            f[x][0][1] = 1ll * f[x][0][0] * f[v][0][1] % mod;
            for (int i = 1; i <= n; ++i)
                f[x][i][1] = (1ll * f[x][i][1] * f[v][i - 1][1] % mod + 1ll * f[x][i][0] * f[v][i][1] % mod) % mod;

            f[x][0][0] = 0;
            for (int i = 1; i <= n; ++i)
                f[x][i][0] = 1ll * f[x][i][0] * f[v][i - 1][1] % mod;
        }
    }
}

int main()
{
    freopen("D.in", "r", stdin);
    std::cin >> n;

    int cnt = 1;
    for (int i = 1; i <= n; ++i)
    {
        int k;
        std::cin >> k;

        if (k != 0)
            cnt = 1ll * cnt * k % mod;

        for (int j = 0; j < k; ++j)
        {
            int x;
            std::cin >> x;
            flg[x] = true;
            s[i].push_back(x);
        }
    }

    int rt;
    for (int i = 1; i <= n; ++i)
        if (!flg[i])
        {
            rt = i;
            break;
        }

    dfs(rt);

    int sum = 0;
    for (int i = 1; i <= n; ++i)
        sum = (sum + 1ll * i * (f[rt][i][1] - f[rt][i - 1][1]) % mod) % mod;
    std::cout << (1ll * sum * getinv(cnt) % mod + mod) % mod << std::endl;
    return 0;
}