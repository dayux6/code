#include <bits/stdc++.h>

const int maxn = 1e5, mod = 1e9 + 7;

int a[maxn + 1];

int main()
{
    freopen("D.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 0; i < m; ++i)
    {
        bool b;
        std::cin >> b;

        if (b)
        {
            int l, r;
            std::cin >> l >> r;
            int res = 0;
            for (int i = l; i <= r; ++i)
                res = (res + a[i]) % mod;
            std::cout << (res + mod) % mod << std::endl;
        }
        else
        {
            int l, r, x, b;
            std::cin >> l >> r >> x >> b;
            for (int i = l; i <= r; ++i)
                a[i] = ((a[i] + x) % mod - 1ll * (i - l) * b % mod) % mod;

            // for (int i = 1; i <= n; ++i)
            //     std::cout << a[i] << ' ';
            // std::cout << std::endl;
        }
    }
    return 0;
}