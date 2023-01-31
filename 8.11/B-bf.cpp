#include <bits/stdc++.h>

const int maxn = 1e3;

int a[maxn + 1];

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
    freopen("B.in", "r", stdin);
    int n, k, mod;
    std::cin >> n >> k >> mod;

    if (k == 1)
    {
        std::cout << qpow(2, n - 1, mod) << std::endl;
        return 0;
    }

    std::iota(a + 1, a + n + 1, 1);
    int cnt = 0;
    do
    {
        std::vector<int> vct;
        for (int i = 1; i <= n; ++i)
            vct.push_back(a[i]);

        bool b = true;
        for (int i = 0; i < k; ++i)
        {
            if (vct.size() == 1)
            {
                b = false;
                break;
            }

            std::vector<int> tmp;
            for (int i = 0; i < vct.size(); ++i)
                if (!((i - 1 >= 0 && vct.at(i) < vct.at(i - 1)) || (i + 1 < vct.size() && vct.at(i) < vct.at(i + 1))))
                    tmp.push_back(vct.at(i));
            vct = tmp;
        }

        if (b && vct.size() == 1)
            ++cnt;
    } while (std::next_permutation(a + 1, a + n + 1));

    std::cout << cnt % mod << std::endl;
    return 0;
}