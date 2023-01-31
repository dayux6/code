#include <bits/stdc++.h>

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    int min = INT_MAX, x = 0, y = 0, t = 0;
    std::map<std::pair<int, int>, int> lst;
    for (int i = 0; i < n; ++i)
    {
        char d;
        int s;
        std::cin >> d >> s;
        for (int j = 0; j < s; ++j, ++t)
        {
            if (lst.count(std::make_pair(x, y)) != 0)
            {
                min = std::min(min, t - lst.at(std::make_pair(x, y)));
                lst.at(std::make_pair(x, y)) = t;
            }
            else
                lst.emplace(std::make_pair(x, y), t);
            switch (d)
            {
            case 'N':
                --y;
                break;
            case 'S':
                ++y;
                break;
            case 'W':
                --x;
                break;
            case 'E':
                ++x;
                break;
            }
        }
    }
    if (min == INT_MAX)
        std::cout << "-1" << std::endl;
    else
        std::cout << min << std::endl;
    return 0;
}