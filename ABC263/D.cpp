#include <bits/stdc++.h>

const int maxn = 2e5;

long long a[maxn + 1], min[maxn + 1];

int main()
{
    int n, l, r;
    std::cin >> n >> l >> r;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    min[0] = 0;
    for (int i = 1; i <= n; ++i)
        min[i] = std::min(min[i - 1] + a[i], 1ll * i * l);

    long long ans = min[n], tmp = 0;
    for (int i = n; i >= 1; --i)
    {
        tmp = std::min(tmp + a[i], 1ll * (n - i + 1) * r);
        ans = std::min(ans, min[i - 1] + tmp);
    }

    std::cout << ans << std::endl;
    return 0;
}