#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> vct;
    for (int i = 0; i < n; ++i)
    {
        int a;
        std::cin >> a;
        auto it = std::upper_bound(vct.begin(), vct.end(), a - i);
        if (it == vct.end())
            vct.push_back(a - i);
        else
            *it = a - i;
    }
    std::cout << n - vct.size() << std::endl;
    return 0;
}