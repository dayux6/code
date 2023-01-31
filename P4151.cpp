#include <bits/stdc++.h>

const int maxn = 5e4, maxlg = 60;

long long w[maxn + 1];
bool vis[maxn + 1];

struct edge
{
    int v;
    long long w;

    edge(int _v, long long _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

class LB
{
private:
    int n;
    long long lb[maxlg];

public:
    LB();
    void build(int);
    void ins(long long);
    long long query(long long);
} lb;

LB::LB() {}

void LB::build(int _n)
{
    n = _n;
    std::fill_n(lb, n, 0);
}

void LB::ins(long long x)
{
    for (int i = n - 1; i >= 0; --i)
        if ((x >> i) & 1)
        {
            if (lb[i])
                x ^= lb[i];
            else
            {
                lb[i] = x;
                break;
            }
        }
}

long long LB::query(long long base)
{
    for (int i = n - 1; i >= 0; --i)
        if (!((base >> i) & 1) && lb[i])
            base ^= lb[i];
    return base;
}

void dfs(int x)
{
    vis[x] = true;
    for (edge e : g[x])
        if (vis[e.v])
            lb.ins(w[x] ^ e.w ^ w[e.v]);
        else
        {
            w[e.v] = w[x] ^ e.w;
            dfs(e.v);
        }
}

int main()
{
    freopen("P4151.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;
    long long max = 0;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        max = std::max(max, w);
    }
    lb.build(log2(max) + 1);
    dfs(1);
    std::cout << lb.query(w[n]) << std::endl;
    return 0;
}