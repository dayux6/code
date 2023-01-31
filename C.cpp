#include <bits/stdc++.h>

struct node
{
    int ls, rs, k1, k2;
} * t;

int *max, *min;

int dfs(int x)
{
    if (x == -1)
        return INT_MAX;
    int ret = std::min(t[x].k2, std::min(dfs(t[x].ls), dfs(t[x].rs)));
    if (t[x].k2 != ret || (t[x].ls != -1 && max[t[x].ls] >= t[x].k1) || (t[x].rs != -1 && min[t[x].rs] <= t[x].k1))
    {
        std::cout << "NO" << std::endl;
        exit(0);
    }
    min[x] = std::min(t[x].k1, t[x].ls == -1 ? INT_MAX : min[t[x].ls]);
    max[x] = std::max(t[x].k1, t[x].rs == -1 ? INT_MIN : max[t[x].rs]);
    return ret;
}

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    t = new node[n];
    bool *vis = new bool[n]();
    for (int i = 0; i < n; ++i)
    {
        std::cin >> t[i].k1 >> t[i].k2 >> t[i].ls >> t[i].rs;
        if (t[i].ls != -1)
            vis[t[i].ls] = true;
        if (t[i].rs != -1)
            vis[t[i].rs] = true;
    }
    int rt;
    for (int i = 0; i < n; ++i)
        if (!vis[i])
        {
            rt = i;
            break;
        }
    max = new int[n];
    min = new int[n];
    dfs(rt);
    std::cout << "YES" << std::endl;
    return 0;
}