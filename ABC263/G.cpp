#include <bits/stdc++.h>

const int maxn = 100;

int n, cnt, a[maxn + 1], b[maxn + 1], h[maxn * 2 + 2], cur[maxn * 2 + 2], dep[maxn * 2 + 2];

bool isprime(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

struct edge
{
    int v, p;
    long long f;

    edge(int _v, long long _f, int _p) : v(_v), f(_f), p(_p) {}
};
std::vector<edge> e;

void addedge(int u, int v, long long w)
{
    e.emplace_back(v, w, h[u]);
    h[u] = e.size() - 1;
}

bool bfs()
{
    std::copy_n(h, n * 2 + 2, cur);
    std::fill_n(dep + 1, n * 2 + 1, 0);

    dep[0] = 1;
    std::queue<int> q({0});
    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = h[x]; ~i; i = e.at(i).p)
            if (e.at(i).f && !dep[e.at(i).v])
            {
                dep[e.at(i).v] = dep[x] + 1;
                q.push(e.at(i).v);
            }
    }

    return dep[n * 2 + 1] > 0;
}

long long dfs(int x, long long f)
{
    if (x == n * 2 + 1 || !f)
        return f;

    long long ret = 0;
    for (int i = cur[x]; ~i; i = e.at(i).p)
    {
        cur[x] = i;

        if (dep[e.at(i).v] == dep[x] + 1)
        {
            long long tmp = dfs(e.at(i).v, std::min(f, e.at(i).f));

            if (tmp)
            {
                f -= tmp;
                ret += tmp;
                e.at(i).f -= tmp;
                e.at(i ^ 1).f += tmp;

                if (!f)
                    break;
            }
        }
    }

    return ret;
}

long long dinic()
{
    long long ret = 0;

    while (bfs())
        ret += dfs(0, LLONG_MAX);

    return ret;
}

long long f(int k)
{
    std::fill_n(h, n * 2 + 2, -1);
    e.clear();
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] & 1)
        {
            addedge(0, i, b[i] - (a[i] ^ 1 ? 0 : k * 2));
            addedge(i, 0, 0);

            for (int j = 1; j <= n; ++j)
                if (!(a[j] & 1) && isprime(a[i] + a[j]))
                {
                    addedge(i, j + n, LLONG_MAX);
                    addedge(j + n, i, 0);
                }
        }
        else
        {
            addedge(i + n, n * 2 + 1, b[i]);
            addedge(n * 2 + 1, i + n, 0);
        }
    }

    return dinic() + k;
}

int main()
{
    freopen("G.in", "r", stdin);
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i] >> b[i];

        if (a[i] == 1)
            cnt += b[i];
    }

    std::cout << f((f(cnt / 2) - f(0) + cnt / 2) / 2) << std::endl;
    return 0;
}