#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e6;

int a[maxn + 1], c[31];

int main()
{
    std::freopen("sequence.in", "r", stdin);
    std::freopen("sequence.out", "w", stdout);

    int n, k;
    read(n);
    read(k);

    int maxor = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        maxor |= a[i];
    }

    std::cout << maxor << ' ';

    auto ins = [&](int i, int v)
    {
        for (int j = 31; j >= 0; --j)
            if ((a[i] >> j) & 1)
                c[j] += v;
    };

    for (int i = 1; i < k; ++i)
        ins(i, 1);

    int maxand = 0;
    for (int i = k; i <= n; ++i)
    {
        ins(i, 1);

        int sand = 0;
        for (int j = 0; j <= 31; ++j)
            if (c[j] == k)
                sand |= 1 << j;

        maxand = std::max(maxand, sand);

        ins(i - k + 1, -1);
    }

    std::cout << maxand << std::endl;
    return 0;
}