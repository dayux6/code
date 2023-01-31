#include <bits/stdc++.h>

int main()
{
    int x = 3670011;

    std::vector<int> v;
    while (x != 0)
    {
        v.emplace_back(x % 9);
        x /= 9;
    }

    std::reverse(v.begin(), v.end());

    for (int i : v)
        std::cout << i;
    std::cout << std::endl;
    return 0;
}