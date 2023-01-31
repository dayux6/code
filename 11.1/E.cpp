#include <bits/stdc++.h>

const int maxn = 50;

int val[maxn + 1];
std::bitset<88> f[11];

int main()
{
    freopen("E.in", "r", stdin);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> val[i];

    int m;
    std::cin >> m;
    f[0].set(0);
    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;

        for (int j = 1; j <= 10; ++j)
            f[j].reset();

        for (int j = 1; j <= n; ++j)
            if (j != a && j != b && j != c)
                for (int k = 10; k >= 1; --k)
                    f[k] |= f[k - 1] << val[j];

        if (f[10].test(87))
            std::puts("Yes");
        else
            std::puts("No");
    }
    return 0;
}