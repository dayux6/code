#include <bits/stdc++.h>

int main()
{
    std::freopen("rewrite.in", "r", stdin);
    std::freopen("rewrite.out", "w", stdout);

    int n;
    std::cin >> n;

    int l[n], r[n];
    for (int i = 0; i < n; ++i)
        std::cin >> l[i] >> r[i];

    long long min = LLONG_MAX;
    for (int i = 0; i < n; ++i)
    {
        for (int S = 0; S < (1 << (n - 1)); ++S)
        {
            long long L = l[i], R = r[i], res = 0;
            for (int j = 0; j < i && res <= min; ++j)
                if ((S >> j) & 1)
                {
                    res += R - l[j];
                    R += r[j] - l[j];
                }
                else
                {
                    res += r[j] - L;
                    L -= r[j] - l[j];
                }
            for (int j = i + 1; j < n && res <= min; ++j)
                if ((S >> (j - 1)) & 1)
                {
                    res += R - l[j];
                    R += r[j] - l[j];
                }
                else
                {
                    res += r[j] - L;
                    L -= r[j] - l[j];
                }
            min = std::min(min, res);
        }
    }

    std::cout << min << std::endl;
    return 0;
}