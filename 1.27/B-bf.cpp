#include <bits/stdc++.h>

const int maxn = 20;

int tmp, r[maxn + 1], p[maxn + 1];
bool b[maxn + 1];
std::vector<int> s[maxn + 1];

void calc(int x)
{
    if (b[x])
        tmp += p[x];
    else
        tmp += r[x];

    for (int v : s[x])
        calc(v);

    int max, min;
    if (b[x])
        max = min = p[x];
    else
        max = min = r[x];

    for (int v : s[x])
        if (b[v])
        {
            max = std::max(max, p[v]);
            min = std::min(min, p[v]);
        }
        else
        {
            max = std::max(max, r[v]);
            min = std::min(min, r[v]);
        }

    tmp -= std::ceil((max - min) / 1e3) * 666 * x;
}

int main()
{
    std::freopen("lele.in", "r", stdin);
    std::freopen("lele.ans", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> r[i] >> p[i];

    for (int i = 2, fa; i <= n; ++i)
    {
        std::cin >> fa;
        s[fa].emplace_back(i);
    }

    int max = INT_MIN;
    for (int i = 0; i < (1 << n); ++i)
    {
        for (int j = 1; j <= n; ++j)
            b[j] = (i >> (j - 1)) & 1;

        tmp = 0;
        calc(1);
        max = std::max(max, tmp);

        if (tmp == -29613)
            for (int j = 1; j <= n; ++j)
                std::cerr << j << ' ' << (b[j] ? p[j] : r[j]) << std::endl;
    }

    std::cout << max << std::endl;
    return 0;
}