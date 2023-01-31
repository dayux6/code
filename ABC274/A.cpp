#include <bits/stdc++.h>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << std::fixed << std::setprecision(3) << std::round(1000.0 * b / a) / 1000 << std::endl;
    return 0;
}