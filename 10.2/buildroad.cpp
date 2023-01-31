#include <bits/stdc++.h>

const int maxn = 13;

int e[maxn][maxn];
long long f[maxn][1 << maxn], g[maxn][1 << maxn];

int main()
{
    freopen("buildroad.in", "r", stdin);
    freopen("buildroad.out", "w", stdout);

    int n, m, S;
    std::cin >> n >> m >> S;

    for (int i = 0; i < n; ++i)
        std::fill_n(e[i], n, INT_MAX);
    for (int i = 0; i < m; ++i)
    {
        int u, v, l;
        std::cin >> u >> v >> l;
        --u;
        --v;
        e[u][v] = e[v][u] = l;
    }

    for (int i = 0; i < n; ++i)
    {
        std::fill_n(f[i] + 1, (1 << n) - 1, LLONG_MAX);
        f[i][1 << i] = 0;
        g[i][1 << i] = 1;
    }

    for (int i = 1; i < (1 << n); ++i)
        for (int j = 0; j < n; ++j)
            if ((i >> j) & 1)
            {
                int base = (i ^ (1 << j)) & -(i ^ (1 << j));
                for (int k = 0; k < n; ++k)
                    if (j != k && (i >> k) & 1 && e[j][k] != INT_MAX)
                    {
                        int all = i ^ (1 << j) ^ (1 << k);
                        for (int s = all;; s = all & (s - 1))
                        {
                            int sub = s | (1 << k), fa = i ^ sub;
                            if ((sub & base) && g[k][sub] != 0 && g[j][fa] != 0)
                            {
                                int siz = __builtin_popcount(sub);
                                long long tmp = f[k][sub] + f[j][fa] + 1ll * e[j][k] * siz;
                                if (siz == 1)
                                    tmp += S;
                                if (siz == n - 1)
                                    tmp += S;

                                if (tmp < f[j][i])
                                {
                                    f[j][i] = tmp;
                                    g[j][i] = 1ll * g[k][sub] * g[j][fa];
                                }
                                else if (tmp == f[j][i])
                                    g[j][i] += 1ll * g[k][sub] * g[j][fa];
                            }
                            if (s == 0)
                                break;
                        }
                    }
            }

    long long min = LLONG_MAX, cnt;
    for (int i = 0; i < n; ++i)
        if (f[i][(1 << n) - 1] < min)
        {
            min = f[i][(1 << n) - 1];
            cnt = g[i][(1 << n) - 1];
        }
        else if (f[i][(1 << n) - 1] == min)
            cnt += g[i][(1 << n) - 1];
    std::cout << min << ' ' << cnt << std::endl;
    return 0;
}