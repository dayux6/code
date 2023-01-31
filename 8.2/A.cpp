#include <bits/stdc++.h>

const int maxn = 1e7, mod = 1e9 + 7;

int inv[maxn + 1], f[maxn + 1];

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    std::cin >> n;
    inv[1] = 1;
    for (int i = 2; i <= maxn; ++i)
        inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod;
    int s = f[n] = 0;
    for (int i = n - 1; i; --i)
    {
        f[i] = (1ll * (s + 1) * inv[n - i] % mod + 1) % mod;
        s = (s + f[i]) % mod;
    }
    std::cout << f[1] << std::endl;
    return 0;
}