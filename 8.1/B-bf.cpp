#include <bits/stdc++.h>

const int maxn = 15;

int a[maxn + 1], w[maxn + 1];
bool b[maxn + 1];
std::vector<int> s[maxn + 1], leaf;

void dfs(int x)
{
    if (s[x].size() == 0)
    {
        leaf.push_back(x);
        return;
    }

    for (int v : s[x])
        dfs(v);
}

int check(int x)
{
    if (s[x].size() == 0)
        return w[x];
    else
    {
        int ret = b[x] ? 0 : INT_MAX;
        for (int v : s[x])
            if (b[x])
                ret = std::max(ret, check(v));
            else
                ret = std::min(ret, check(v));
        return ret;
    }
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        std::cin >> fa;
        s[fa].push_back(i);
    }
    dfs(1);
    std::iota(a, a + leaf.size(), 1);
    int max = 0;
    do
    {
        for (int i = 0; i < leaf.size(); ++i)
            w[leaf.at(i)] = a[i];
        max = std::max(max, check(1));
    } while (std::next_permutation(a, a + leaf.size()));
    std::cout << max << std::endl;
    return 0;
}