#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("F.in");
#endif
using std::cout;

typedef long long ll;

int *d;

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> *g;

std::pair<ll, ll> dfs(int x, int fa)
{
    std::pair<ll, ll> ret(0, 0);
    std::multiset<ll> s;
    for (edge e : g[x])
        if (e.v ^ fa)
        {
            std::pair<ll, ll> tmp = dfs(e.v, x);
            if (d[e.v] != 0 && tmp.first + e.w > tmp.second)
                s.emplace(tmp.first + e.w - tmp.second);
            ret.first += tmp.second;
        }
    std::multiset<ll>::reverse_iterator it = s.rbegin();
    for (int i = 1; i < d[x] && it != s.rend(); ++i, ++it)
        ret.first += *it;
    ret.second = ret.first;
    if (d[x])
    {
        if (it != s.rend())
            ret.second += *it;
    }
    else
    {
        ret.second = ret.first;
        ret.first = 0;
    }
    return ret;
}

int main()
{
    int n;
    cin >> n;
    d = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        cin >> d[i];
    g = new std::vector<edge>[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    cout << dfs(1, 0).second << std::endl;
    return 0;
}