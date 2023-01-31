#include <bits/stdc++.h>

const int maxn = 5e5;

int a[maxn + 1];

int main()
{
    freopen("test.in", "r", stdin);
    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 0; i < q; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        int max = 0;
        long long ans = 0;
        for (int j = l; j <= r; ++j)
        {
            max = std::max(max, a[j]);
            ans += 1ll * max * a[j];
        }

        std::cout << ans << std::endl;
    }
    return 0;
}