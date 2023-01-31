#include <bits/stdc++.h>

const int maxn = 100000;

int gcd(int x, int y)
{
    if (x == 0)
        return y;
    return gcd(y % x, x);
}

bool flg[maxn + 1];

int main()
{
    freopen("A.in", "r", stdin);
    int x, y, cnt = 0;
    std::cin >> x >> y;
    if (x > y)
        std::swap(x, y);
    if (gcd(x, y) ^ 1)
    {
        std::cout << "-1" << std::endl;
        return 0;
    }
    flg[0] = true;
    for (int i = 1; i <= maxn; ++i)
    {
        if (i >= x)
            flg[i] |= flg[i - x];
        if (i >= y)
            flg[i] |= flg[i - y];
        if (!flg[i])
            ++cnt;
    }
    std::cout << cnt << std::endl;
    return 0;
}