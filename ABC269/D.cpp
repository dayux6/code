#include <bits/stdc++.h>

const int dx[] = {-1, -1, 0, 0, 1, 1}, dy[] = {-1, 0, -1, 1, 0, 1};

std::map<std::pair<int, int>, bool> s;

void dfs(int x, int y)
{
    if (s.count(std::make_pair(x, y)) == 0 || s.at(std::make_pair(x, y)))
        return;
    s.at(std::make_pair(x, y)) = true;

    for (int i = 0; i < 6; ++i)
    {
        int nx = x + dx[i], ny = y + dy[i];
        dfs(nx, ny);
    }
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        s.emplace(std::make_pair(x, y), false);
    }

    int cnt = 0;
    for (auto pr : s)
        if (!pr.second)
        {
            ++cnt;
            dfs(pr.first.first, pr.first.second);
        }

    std::cout << cnt << std::endl;
    return 0;
}