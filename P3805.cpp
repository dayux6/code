#include <bits/stdc++.h>

int main()
{
    freopen("P3805.in", "r", stdin);
    std::string s;
    std::cin >> s;
    char *c = new char[s.size() * 2 + 1];
    for (int i = 0; i < s.size(); ++i)
    {
        c[i * 2] = '#';
        c[i * 2 + 1] = s.at(i);
    }
    c[s.size() * 2] = '#';
    int *max = new int[s.size() * 2 + 1], mid = 0, r = 0;
    max[0] = 1;
    for (int i = 1; i <= s.size() * 2; ++i)
    {
        if (i <= r)
            max[i] = std::min(max[mid * 2 - i], r - i + 1);
        else
            max[i] = 1;
        while (i - max[i] >= 0 && i + max[i] <= s.size() * 2 && c[i - max[i]] == c[i + max[i]])
            ++max[i];
        if (i + max[i] - 1 > r)
        {
            mid = i;
            r = i + max[i] - 1;
        }
    }
    int ans = 0;
    for (int i = 0; i <= s.size() * 2; ++i)
        ans = std::max(ans, max[i]);
    std::cout << ans - 1 << std::endl;
    return 0;
}