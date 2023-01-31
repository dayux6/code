#include <bits/stdc++.h>

const int maxn = 2e3;

long long s[maxn + 1][maxn + 1];
bool b[maxn + 1][maxn + 1];

int main()
{
    freopen("A.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        std::string s;
        std::cin >> s;
        for (int j = 1; j <= n; ++j)
            b[i][j] = s.at(j - 1) - '0';
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + b[i][j];

    long long max = 0;
    for (int i = k; i <= n; ++i)
        for (int j = k; j <= n; ++j)
            max = std::max(max, s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k]);

    std::cout << max << std::endl;
    return 0;
}