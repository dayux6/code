#include <bits/stdc++.h>

const int maxn = 1e6, mod = 1e9 + 7;

int f[maxn + 1], g[maxn + 1], h[maxn + 1];

int main()
{
    freopen("B.in", "r", stdin);
    std::string s;
    std::cin >> s;
    g[0] = h[0] = 1;
    for (int i = 1; i <= s.size(); ++i)
    {
        char c = s.at(i - 1);
        if (c == '*' || c == '?')
            f[i] = (f[i - 1] + h[i - 1]) % mod;
        if (c == '0' || c == '?')
            g[i] = g[i - 1];
        if (c == '1' || c == '?')
        {
            g[i] = (g[i] + f[i - 1]) % mod;
            h[i] = g[i - 1];
        }
        if (c == '2' || c == '?')
            h[i] = (h[i] + f[i - 1]) % mod;
    }
    std::cout << (f[s.size()] + g[s.size()]) % mod << std::endl;
    return 0;
}