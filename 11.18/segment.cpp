#include <bits/stdc++.h>

const int mod = 1e9 + 7;

int main()
{
    std::freopen("segment.in", "r", stdin);
    std::freopen("segment.out", "w", stdout);

    int n;
    std::cin >> n;

    int f[n + 1];
    long long a[n + 1];
    f[0] = 1;
    a[0] = 0;
    std::unordered_map<long long, int> pre;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        a[i] += a[i - 1];
        f[i] = (f[i - 1] + (f[i - 1] - (pre[a[i]] == 0 ? 0 : f[pre[a[i]] - 1])) % mod) % mod;
        pre[a[i]] = i;
    }

    std::cout << ((f[n - 1] % mod) + mod) % mod << std::endl;
    return 0;
}