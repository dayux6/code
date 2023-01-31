#include <bits/stdc++.h>

const int maxn = 1e4;

long double f[maxn + 1], g[maxn + 1];

int main()
{
    int n;
    std::cin >> n;
    f[n] = 0;
    for (int i = n - 1; i >= 0; --i)
        f[i] = f[i + 1] + 1.0 * n / (n - i);
    g[n] = 0;
    for (int i = n - 1; i >= 0; --i)
        g[i] = g[i + 1] + f[i] * n / (n - i);
    std::cout << std::fixed << std::setprecision(2) << g[0] << std::endl;
    return 0;
}