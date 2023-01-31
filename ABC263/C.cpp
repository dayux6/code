#include <bits/stdc++.h>

const int maxn = 10;

int n, m, a[maxn];

void dfs(int d)
{
    if (d == n)
    {
        for (int i = 0; i < n; ++i)
            std::cout << a[i] << ' ';
        std::cout << std::endl;
        return;
    }

    for (int i = a[d - 1] + 1; i <= m; ++i)
    {
        a[d] = i;
        dfs(d + 1);
    }
}

int main()
{
    std::cin >> n >> m;

    dfs(0);
    return 0;
}