#include <bits/stdc++.h>

const int maxn = 3e7;

int a[maxn + 1];

int main()
{
    freopen("A.in", "r", stdin);
    int n, s, b, c, d;
    std::cin >> n >> s >> b >> c >> d;

    for (int i = 1; i <= n; ++i)
    {
        a[i] = i;
        s = (1ll * s * b + c) % d;
        std::swap(a[i], a[(s % i) + 1]);
    }

    int max = 0;
    for (int i = 1; i <= n; ++i)
        max = std::max(max, i - a[i]);
    std::cout << max << std::endl;
    return 0;
}