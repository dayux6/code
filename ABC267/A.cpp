#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    std::string s;
    std::cin >> s;
    if (s == "Monday")
        std::cout << 5 << std::endl;
    else if (s == "Tuesday")
        std::cout << 4 << std::endl;
    else if (s == "Wednesday")
        std::cout << 3 << std::endl;
    else if (s == "Thursday")
        std::cout << 2 << std::endl;
    else if (s == "Friday")
        std::cout << 1 << std::endl;
    return 0;
}