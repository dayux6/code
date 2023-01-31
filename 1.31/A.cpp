#include <bits/stdc++.h>

typedef unsigned long long ull;

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e6;

ull pw[maxn];

long long solve()
{
    int n, m;
    read(n), read(m);

    int base = n * 2 + 1;
    pw[0] = 1;
    for (int i = 1; i < n; ++i)
        pw[i] = pw[i - 1] * base;

    ull hash = 0;
    for (int i = 0; i < m - 1; ++i)
        hash = hash * base + n;
    std::unordered_map<ull, int> c;
    c.reserve(n + 1);
    c.emplace(hash, 1);
    long long ret = 0;
    for (int i = 1, a; i <= n; ++i)
    {
        read(a);

        if (a != 1)
            hash += pw[a - 2];
        if (a != m)
            hash -= pw[a - 1];

        ret += c[hash];
        ++c[hash];
    }

    return ret;
}

int main()
{
    std::freopen("resona.in", "r", stdin);
    std::freopen("resona.out", "w", stdout);

    int t;
    read(t);

    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}