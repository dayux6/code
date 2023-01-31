#include <bits/stdc++.h>

int main()
{
    std::freopen("multi.in", "r", stdin);
    std::freopen("multi.out", "w", stdout);

    int n;
    std::cin >> n;

    int max = 0, l[n], r[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> l[i] >> r[i];
        max = std::max(max, r[i]);
    }

    int ans = 0;
    bool b[max + 1];
    for (int S = 0; S < (1 << n); ++S)
    {
        std::fill_n(b, max + 1, false);
        for (int i = 0; i < n; ++i)
            if ((S >> i) & 1)
                for (int j = l[i]; j <= r[i]; ++j)
                    b[j] = true;

        bool cur = true;
        for (int i = 0; i < n; ++i)
            if (!((S >> i) & 1))
            {
                bool flg = false;
                for (int j = l[i]; j <= r[i]; ++j)
                    if (b[j])
                    {
                        flg = true;
                        break;
                    }
                if (!flg)
                {
                    cur = false;
                    break;
                }
            }
        ans += cur;
    }

    std::cout << ans << std::endl;
    return 0;
}