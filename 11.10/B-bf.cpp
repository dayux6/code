#include <bits/stdc++.h>

int main()
{
    std::freopen("xor.in", "r", stdin);
    // std::freopen("xor.out", "w", stdout);

    int n;
    std::cin >> n;

    int a[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    long long cnt = 0;
    for (int l = 1; l <= n; ++l)
    {
        int xs = 0, max = 0;
        for (int r = l; r <= n; ++r)
        {
            xs ^= a[r];
            max = std::max(max, a[r]);

            if (xs <= max)
            {
                ++cnt;
                // std::cerr << l << ' ' << r << ' ' << xs << ' ' << max << std::endl;
            }
        }
    }

    std::cout << cnt << std::endl;
    return 0;
}