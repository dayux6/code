#include <bits/stdc++.h>

const std::string s = "atcoder";

int main()
{
    int l, r;
    std::cin >> l >> r;

    for (int i = l - 1; i < r; ++i)
        std::cout << s.at(i);
    std::cout << std::endl;
    return 0;
}