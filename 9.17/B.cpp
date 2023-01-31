#include <bits/stdc++.h>

const int maxn = 1e6;

int a[maxn + 1];

int main()
{
    freopen("B.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    int i = 1, j = n / 2 + 1, ans = 0;
    while (i <= n / 2 && j <= n)
    {
        while (j <= n && a[j] - a[i] < k)
            ++j;
        if (j > n)
            break;
        ++i;
        ++j;
        ++ans;
    }

    std::cout << ans << std::endl;
    return 0;
}