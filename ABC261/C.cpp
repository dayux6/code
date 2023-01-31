#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;
    std::unordered_map<std::string, int> cnt;
    for (int i = 0; i < n; ++i)
    {
        std::string s;
        std::cin >> s;
        if (cnt.count(s) == 0)
            std::cout << s << '\n';
        else
            std::cout << s << '(' << cnt.at(s) << ")\n";
        ++cnt[s];
    }
    return 0;
}