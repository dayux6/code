#include <bits/stdc++.h>

const int maxn = 50;

int fa[maxn + 1];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 2; i <= n; ++i)
        std::cin >> fa[i];

    int x = n, cnt = 0;
    while (x ^ 1)
    {
        ++cnt;
        x = fa[x];
    }

    std::cout << cnt << std::endl;
    return 0;
}