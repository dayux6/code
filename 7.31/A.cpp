#include <bits/stdc++.h>

const int maxn = 1e6;

void read(int &x)
{
    x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

int bsiz;
bool flg;
std::vector<int> g[maxn + 1];

int dfs(int x, int fa)
{
    int ret = 1;
    for (int v : g[x])
        if (v ^ fa)
        {
            ret += dfs(v, x);
            if (!flg)
                return 0;
        }
    if (ret > bsiz)
        flg = false;
    else if (ret == bsiz)
        ret = 0;
    return ret;
}

int main()
{
    int n;
    read(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u);
        read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int cnt = 0;
    for (bsiz = 1; bsiz <= n; ++bsiz)
        if (n % bsiz == 0)
        {
            flg = true;
            dfs(1, 0);
            cnt += flg;
        }
    std::cout << cnt << std::endl;
    return 0;
}