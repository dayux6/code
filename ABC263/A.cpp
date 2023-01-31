#include <bits/stdc++.h>

int main()
{
    std::unordered_map<int, int> cnt;
    for (int i = 0; i < 5; ++i)
    {
        int a;
        std::cin >> a;
        ++cnt[a];
    }

    if (cnt.size() == 2 && (cnt.begin()->second == 2 || cnt.begin()->second == 3))
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
    return 0;
}