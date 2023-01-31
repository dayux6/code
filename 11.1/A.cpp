#include <bits/stdc++.h>

bool check(int x)
{
    int y = std::sqrt(x);
    return y * y == x;
}

std::vector<int> vct;

bool dfs(int d, int x, int pre)
{
    if (x < pre * pre)
        return false;

    if (d == 3)
    {
        if (check(x))
        {
            vct.emplace_back(std::sqrt(x));
            return true;
        }
        else
            return false;
    }

    for (int i = pre; i * i <= x; ++i)
    {
        vct.emplace_back(i);
        if (dfs(d + 1, x - i * i, i))
            return true;
        vct.pop_back();
    }
    return false;
}

int main()
{
    freopen("A.in", "r", stdin);

    int x;
    std::cin >> x;
    dfs(0, x, 0);
    for (int v : vct)
        std::cout << v << ' ';
    std::cout << std::endl;
    return 0;
}