#include <bits/stdc++.h>

int qpow(int x, int n, const int mod)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

int main()
{
    freopen("P3846.in", "r", stdin);
    int a, b, p;
    std::cin >> p >> a >> b;
    int rt = ceil(sqrt(p));
    std::unordered_map<int, int> num;
    for (int i = 0; i < rt; ++i)
        num.emplace(1ll * b * qpow(a, i, p) % p, i);
    bool flg = true;
    for (int i = 1; i <= rt; ++i)
        if (num.count(qpow(a, 1ll * i * rt % (p - 1), p)))
        {
            std::cout << 1ll * i * rt - num.at(qpow(a, 1ll * i * rt % (p - 1), p)) << std::endl;
            flg = false;
            break;
        }
    if (flg)
        std::cout << "no solution" << std::endl;
    return 0;
}