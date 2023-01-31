#include <bits/stdc++.h>

int main()
{
    int a = 11, b = 0, c = 11, d = 0;
    for (int i = 1; i <= 10; ++i)
    {
        std::string s;
        std::cin >> s;
        for (int j = 1; j <= 10; ++j)
            if (s.at(j - 1) == '#')
            {
                a = std::min(a, i);
                b = std::max(b, i);
                c = std::min(c, j);
                d = std::max(d, j);
            }
    }
    std::cout << a << ' ' << b << std::endl
              << c << ' ' << d << std::endl;
    return 0;
}