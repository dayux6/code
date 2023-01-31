#include <bits/stdc++.h>

int gcd(int x, int y)
{
    if (x == 0)
        return y;
    return gcd(y % x, x);
}

int main()
{
    freopen("A.in", "r", stdin);
    int x, y;
    std::cin >> x >> y;
    if (x > y)
        std::swap(x, y);
    if (gcd(x, y) == 1)
    {
        int tmp = 0;
        long long cnt = 0, sum = 0;
        for (int i = 1; i < x; ++i)
        {
            tmp += y;
            while (tmp >= x)
            {
                ++cnt;
                tmp -= x;
            }
            sum += cnt;
        }
        std::cout << sum << std::endl;
    }
    else
        std::cout << "-1" << std::endl;
    return 0;
}