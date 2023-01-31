#include <bits/stdc++.h>

const std::unordered_map<char, int> idx({std::make_pair('a', 1), std::make_pair('t', 2), std::make_pair('c', 3), std::make_pair('o', 4), std::make_pair('d', 5), std::make_pair('e', 6), std::make_pair('r', 7)});

int main()
{
    std::string s;
    std::cin >> s;

    int cnt = 0;
    for (int i = 0; i < s.size(); ++i)
        for (int j = 0; j < i; ++j)
            if (idx.at(s.at(j)) > idx.at(s.at(i)))
                ++cnt;
    std::cout << cnt << std::endl;
    return 0;
}