#include <bits/stdc++.h>

const int maxn = 5e5;

int max[maxn];
std::string s[maxn];

void solve(int len, std::vector<int> vid)
{
    if (vid.empty())
        return;
    if (vid.size() == 1)
    {
        max[vid.front()] = len - 1;
        return;
    }

    std::vector<int> v[26];
    for (int id : vid)
        if (s[id].size() == len)
            max[id] = len;
        else
            v[s[id][len] - 'a'].emplace_back(id);

    for (int i = 0; i < 26; ++i)
        solve(len + 1, v[i]);
}

int main()
{
    std::freopen("E.in", "r", stdin);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
        std::cin >> s[i];

    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);

    solve(0, v);

    for (int i = 0; i < n; ++i)
        std::cout << max[i] << '\n';
    return 0;
}