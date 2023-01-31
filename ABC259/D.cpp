#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("D.in");
#endif
using std::cout;

typedef long long ll;

struct circle
{
    int x, y, r;

    circle() { cin >> x >> y >> r; }
};

int main()
{
    int n;
    cin >> n;
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    int s, t;
    std::vector<int> *g = new std::vector<int>[n];
    circle *c = new circle[n]();
    for (int i = 0; i < n; ++i)
    {
        if (1ll * (sx - c[i].x) * (sx - c[i].x) + 1ll * (sy - c[i].y) * (sy - c[i].y) == 1ll * c[i].r * c[i].r)
            s = i;
        if (1ll * (tx - c[i].x) * (tx - c[i].x) + 1ll * (ty - c[i].y) * (ty - c[i].y) == 1ll * c[i].r * c[i].r)
            t = i;
        for (int j = 0; j < i; ++j)
        {
            ll dis = 1ll * (c[i].x - c[j].x) * (c[i].x - c[j].x) + 1ll * (c[i].y - c[j].y) * (c[i].y - c[j].y);
            if (dis <= 1ll * (c[i].r + c[j].r) * (c[i].r + c[j].r) && dis >= 1ll * (c[i].r - c[j].r) * (c[i].r - c[j].r))
            {
                g[i].emplace_back(j);
                g[j].emplace_back(i);
            }
        }
    }
    bool *vis = new bool[n]();
    vis[s] = true;
    std::queue<int> q({s});
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        if (x == t)
        {
            cout << "Yes" << std::endl;
            return 0;
        }
        for (int v : g[x])
            if (!vis[v])
            {
                vis[v] = true;
                q.emplace(v);
            }
    }
    cout << "No" << std::endl;
    return 0;
}