#include <bits/stdc++.h>

int cnt, maxk, *max;
std::vector<int> *g;

int main()
{
    freopen("C.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n >> maxk;
    g = new std::vector<int>[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    int *fa = new int[n + 1], *dep = new int[n + 1]();
    fa[1] = 1;
    dep[1] = 1;
    std::queue<int> q;
    q.emplace(1);
    std::priority_queue<std::pair<int, int>> heap;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        heap.emplace(dep[x], x);
        for (int v : g[x])
            if (v ^ fa[x])
            {
                fa[v] = x;
                dep[v] = dep[x] + 1;
                q.emplace(v);
            }
    }
    max = new int[n + 1];
    std::fill_n(max + 1, n, -1);
    while (!heap.empty())
    {
        std::pair<int, int> pr = heap.top();
        heap.pop();
        int x = pr.second;
        bool flg = max[x] < 0;
        for (int i = 1; i <= maxk; ++i, x = fa[x])
            if (i <= max[fa[x]])
            {
                flg = false;
                break;
            }
        if (flg)
        {
            ++cnt;
            int cur = pr.second;
            for (int i = 0; i < maxk && cur != x; ++i, cur = fa[cur])
                max[cur] = std::max(max[cur], i);
            for (int i = 0; i <= maxk; ++i, cur = fa[cur])
                max[cur] = std::max(max[cur], maxk - i);
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}