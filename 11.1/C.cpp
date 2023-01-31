#include <bits/stdc++.h>

const int maxn = 1e5;

std::array<std::pair<std::string, std::string>, maxn + 1> con, inc;
std::unordered_map<std::string, std::pair<std::string, std::string>> group;

int main()
{
    freopen("C.in", "r", stdin);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> con[i].first >> con[i].second;
    int m;
    std::cin >> m;
    for (int i = 1; i <= m; ++i)
        std::cin >> inc[i].first >> inc[i].second;

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        std::string a, b, c;
        std::cin >> a >> b >> c;
        group.emplace(a, std::make_pair(b, c));
        group.emplace(b, std::make_pair(a, c));
        group.emplace(c, std::make_pair(a, b));
    }

    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (group[con[i].first].first != con[i].second && group[con[i].first].second != con[i].second)
            ++cnt;
    for (int i = 1; i <= m; ++i)
        if (group[inc[i].first].first == inc[i].second || group[inc[i].first].second == inc[i].second)
            ++cnt;
    std::cout << cnt << std::endl;
    return 0;
}