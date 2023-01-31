#include <bits/stdc++.h>

const int maxn = 1e6;

std::array<int, maxn + 1> lim;
std::array<int, maxn + 2> fa;
char s[maxn + 1];
std::vector<int> vct[maxn + 1];

int find(int x)
{
    if (x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}

int main()
{
    std::freopen("CF1398F.in", "r", stdin);

    int n;
    std::cin >> n;
    std::scanf("%s", s + 1);

    std::set<int> p[2];
    for (int i = 1; i <= n; ++i)
        if (s[i] != '?')
            p[s[i] - '0'].emplace(i);

    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == '?')
        {
            std::array<std::set<int>::iterator, 2> it = {p[0].upper_bound(i), p[1].upper_bound(i)};
            lim[i] = std::max((it[0] == p[0].end() ? n + 1 : *it[0]) - i, (it[1] == p[1].end() ? n + 1 : *it[1]) - i);
        }
        else
        {
            int b = s[i] - '0';
            auto it = p[b ^ 1].upper_bound(i);
            lim[i] = (it == p[b ^ 1].end() ? n + 1 : *it) - i;
        }

        vct[lim[i]].push_back(i);
    }

    std::iota(fa.begin() + 1, fa.begin() + n + 1, 1);
    fa[n + 1] = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j : vct[i - 1])
            fa[j] = j + 1;

        int cnt = 0, cur = 1;
        while (true)
        {
            cur = find(cur);
            if (cur == n + 1)
                break;
            ++cnt;
            cur += i;
        }

        std::cout << cnt << ' ';
    }
    std::cout << std::endl;
    return 0;
}