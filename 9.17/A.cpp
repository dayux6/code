#include <bits/stdc++.h>

const int maxn = 2e5;

int a[maxn];

int qpow(int x, int n, const int mod)
{
    int ret = 1;
    while (n != 0)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}

int main()
{
    freopen("A.in", "r", stdin);
    int n, p;
    std::cin >> n >> p;
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
        sum = (sum + a[i]) % p;
    }

    for (int i = 1; i < n; ++i)
        if (1ll * (qpow(a[i], n, p) - 1) * qpow(a[i] - 1, p - 2, p) % p == sum)
        {
            std::cout << a[i] << std::endl;
            break;
        }
    return 0;
}