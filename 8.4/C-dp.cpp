#include <bits/stdc++.h>

const int maxn = 2e5;

int p[maxn + 1], l[maxn + 1], c[maxn + 1];
std::map<int, int> f[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    std::stack<int> s;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i];
        while (!s.empty() && p[s.top()] > p[i])
            s.pop();
        if (!s.empty())
            l[i] = s.top();
        // std::cout << l[i] << ' ';
        s.push(i);
    }
    // std::cout << std::endl;
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    f[1].emplace(p[1], c[1]);

    for (int i = 2; i <= n; ++i)
    {
        for (auto it = f[i - 1].rbegin(); it != f[i - 1].rend() && it->first > p[i]; ++it)
            f[i].emplace(it->first, it->second);

        if (l[i])
            for (auto it = f[l[i]].begin(); it != f[l[i]].end() && it->first < p[i]; ++it)
            {
                int tmp = std::max(p[i], it->first);
                if (f[i].count(tmp))
                    f[i].at(tmp) = std::min(f[i].at(tmp), it->second + c[i]);
                else
                    f[i].emplace(tmp, it->second + c[i]);
            }
        else if (f[i].count(p[i]))
            f[i].at(p[i]) = std::min(f[i].at(p[i]), c[i]);
        else
            f[i].emplace(p[i], c[i]);
    }

    int min = INT_MAX;
    for (auto pr : f[n])
        min = std::min(min, pr.second);
    std::cout << min << std::endl;
    return 0;
}