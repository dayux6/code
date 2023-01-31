#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    std::string s;
    std::cin >> n >> s;
    if (s == "BA")
        std::cout << "No" << std::endl;
    else if (s.at(0) == 'B')
        std::cout << "Yes" << std::endl;
    else if (s.at(n - 1) == 'B')
        std::cout << "No" << std::endl;
    else
        std::cout << "Yes" << std::endl;
    return 0;
}