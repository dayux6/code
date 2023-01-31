#include <bits/stdc++.h>

int main()
{
    long long x;
    std::cin >> x;
    std::vector<long long> vct;
    for (int i = 0; (1ll << i) <= x; ++i)
        if ((x >> i) & 1)
            vct.push_back(1ll << i);

    for (int S = 0; S < (1 << vct.size()); ++S)
    {
        long long tmp = 0;
        for (int i = 0; i < vct.size(); ++i)
            if ((S >> i) & 1)
                tmp += vct.at(i);
        std::cout << tmp << std::endl;
    }
    return 0;
}