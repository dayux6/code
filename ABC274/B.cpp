#include <bits/stdc++.h>

const int maxn = 1e3;

int cnt[maxn + 1];
char s[maxn + 1];

int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j)
            cnt[j] += s[j] == '#';
    }

    for (int i = 1; i <= m; ++i)
        std::cout << cnt[i] << ' ';
    std::cout << std::endl;
    return 0;
}