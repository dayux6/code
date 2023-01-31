#include <bits/stdc++.h>

int main()
{
    std::freopen("rev.in", "r", stdin);
    std::freopen("rev.out", "w", stdout);

    std::string s, t;
    std::cin >> s >> t;

    int cs = 0;
    for (char c : s)
        cs += c == '1';

    int ct = 0;
    for (char c : t)
        ct += c == '1';

    if (cs != ct)
        std::puts("NO");
    else
    {
        std::vector<std::pair<int, int>> ress, rest;
        for (std::size_t l = 0; l < s.size(); ++l)
            if (s.at(l) != t.at(l))
            {
                if (s.at(l) == '0')
                {
                    int c = 0;
                    std::size_t r;
                    for (r = l; r < s.size() && c < 2; ++r)
                        c += s[r] == '1';
                    if (c == 2)
                    {
                        ress.emplace_back(l + 1, r);
                        std::reverse(s.begin() + l, s.begin() + r);
                    }
                    else
                    {
                        std::puts("NO");
                        return 0;
                    }
                }
                else
                {
                    int c = 0;
                    std::size_t r;
                    for (r = l; r < t.size() && c < 2; ++r)
                        c += t[r] == '1';
                    if (c == 2)
                    {
                        rest.emplace_back(l + 1, r);
                        std::reverse(t.begin() + l, t.begin() + r);
                    }
                    else
                    {
                        std::puts("NO");
                        return 0;
                    }
                }
            }

        std::puts("YES");
        std::cout << ress.size() + rest.size() << '\n';
        for (std::pair<int, int> pr : ress)
            std::cout << pr.first << ' ' << pr.second << '\n';
        std::reverse(rest.begin(), rest.end());
        for (std::pair<int, int> pr : rest)
            std::cout << pr.first << ' ' << pr.second << '\n';
    }
    return 0;
}