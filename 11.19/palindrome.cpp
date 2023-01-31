#include <bits/stdc++.h>

bool solve()
{
    int n;
    std::cin >> n;

    bool flg = false;
    std::unordered_set<std::string> s2, s3, s32;
    for (int i = 0; i < n; ++i)
    {
        std::string s;
        std::cin >> s;

        if (flg)
            continue;

        std::string rs = s;
        std::reverse(rs.begin(), rs.end());

        if (s == rs)
            flg = true;
        else if (s.size() == 2)
            if (s2.count(rs) != 0 || s32.count(rs) != 0)
                flg = true;
            else
                s2.emplace(s);
        else
        {
            std::string pre = s.substr(0, 2), rsuf = s.substr(1);
            std::reverse(rsuf.begin(), rsuf.end());

            if (s3.count(rs) != 0 || s2.count(rsuf) != 0)
                flg = true;
            else
            {
                s3.emplace(s);
                s32.emplace(pre);
            }
        }
    }

    return flg;
}

int main()
{
    std::freopen("palindrome.in", "r", stdin);
    std::freopen("palindrome.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        std::puts(solve() ? "YES" : "NO");
    return 0;
}