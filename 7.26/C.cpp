#include <bits/stdc++.h>

const int maxn = 1e6;

int dis[maxn + 1];
bool inq[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, pre;
    std::cin >> n >> pre;
    for (int i = 1; i < n; ++i)
    {
        int a;
        std::cin >> a;
        if (a > pre)
            g[i].emplace_back(i + 1, 1);
        else if (a < pre)
            g[i + 1].emplace_back(i, 1);
        else
        {
            g[i].emplace_back(i + 1, 0);
            g[i + 1].emplace_back(i, 0);
        }
        pre = a;
    }
    for (int i = 1; i <= n; ++i)
        g[0].emplace_back(i, 1);
    dis[0] = 0;
    std::fill_n(dis + 1, n, INT_MIN);
    inq[0] = true;
    std::deque<int> q({0});
    while (!q.empty())
    {
        int x = q.front();
        q.pop_front();
        inq[x] = false;
        for (edge e : g[x])
            if (dis[e.v] < dis[x] + e.w)
            {
                dis[e.v] = dis[x] + e.w;
                if (!inq[e.v])
                {
                    if (dis[e.v] <= dis[q.front()])
                        q.push_front(e.v);
                    else
                        q.push_back(e.v);
                    inq[e.v] = true;
                }
            }
    }
    for (int i = 1; i <= n; ++i)
        std::cout << dis[i] << ' ';
    std::cout << std::endl;
    return 0;
}