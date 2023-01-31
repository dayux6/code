#include <bits/stdc++.h>

const int maxn = 1e6;

int n, h[maxn + 1], o[maxn + 1], fa[maxn + 1], len[maxn + 1], cur[maxn + 1], l[maxn + 1], r[maxn + 1];

int find(int x)
{
    if (x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x != y)
    {
        fa[y] = x;
        len[x] += len[y];
        cur[x] += cur[y];
        l[x] = std::min(l[x], l[y]);
        r[x] = std::max(r[x], r[y]);
    }
}

int getmin(int x)
{
    x = find(x);

    if (l[x] == 0 && r[x] == n + 1)
        return INT_MAX / 2;
    else if (l[x] == 0)
        return h[find(r[x])];
    else if (r[x] == n + 1)
        return h[find(l[x])];
    else
        return std::min(h[find(l[x])], h[find(r[x])]);
}

int calc(int x)
{
    x = find(x);

    int cnt = l[x] != 0;
    return cnt + (r[x] != n + 1);
}

int main()
{
    std::freopen("brick.in", "r", stdin);
    std::freopen("brick.out", "w", stdout);

    int c;
    std::cin >> n >> c;

    std::iota(fa + 1, fa + n + 1, 1);
    std::fill_n(len + 1, n, 1);
    std::fill_n(cur + 1, n, -1);
    std::iota(l + 1, l + n + 1, 0);
    std::iota(r + 1, r + n + 1, 2);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> h[i];
        o[i] = h[i];

        if (h[i - 1] == h[i])
            merge(i - 1, i);
    }

    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (i == find(i) && h[i] < getmin(i))
            q.emplace(i);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        x = find(x);

        int diff = getmin(x) - h[x], tmp = calc(x);
        if (cur[x] + 2ll * len[x] * diff <= c * tmp)
        {
            h[x] += diff;
            cur[x] += 2ll * len[x] * diff;
            if (h[x] == h[find(l[x])])
                merge(x, find(l[x]));
            if (h[x] == h[find(r[x])])
                merge(x, find(r[x]));
            if (h[x] < getmin(x))
                q.emplace(x);
        }
        else if (cur[x] <= c * tmp)
        {
            diff = (c * tmp - cur[x]) / len[x] / 2;
            h[x] += diff;
            cur[x] += 1ll * len[x] * diff;
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += 1ll * (h[find(i)] - o[i]) * (h[find(i)] - o[i]) + 1ll * c * (i == 1 ? 0 : std::abs(h[find(i)] - h[find(i - 1)]));
    std::cout << ans << std::endl;
    return 0;
}