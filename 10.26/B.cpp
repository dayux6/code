#include <bits/stdc++.h>

template <typename T>
void read(T &x)
{
    x = 0;
    bool b = false;
    char c = std::getchar();

    while (!std::isdigit(c))
    {
        if (c == '-')
            b = true;
        c = std::getchar();
    }
    while (std::isdigit(c))
    {
        if (b)
            x = x * 10 - (c ^ 48);
        else
            x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 4e6;

int a[maxn + 1];
long long f[2][maxn + 1];

long long solve()
{
    int n, k;
    read(n);
    read(k);

    int cnt = 0;
    long long sum = 0;
    std::priority_queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum += a[i];
        cnt += a[i] > 0;
        q.emplace(a[i]);
    }

    long long ret = 0;
    for (int i = 0; i < k; ++i)
    {
        ret += q.top();
        q.pop();
    }

    if (cnt <= k)
        return ret;

    std::fill_n(f[0], n + 1, 0);
    for (int i = 1; i <= k; ++i)
    {
        long long pre = LLONG_MIN / 2;
        bool b = i & 1;
        std::fill_n(f[b], n + 1, LLONG_MIN / 2);
        for (int j = 1; j <= n; ++j)
        {
            pre = std::max(pre, f[b ^ 1][j - 1]);
            f[b][j] = std::max(f[b][j - 1], pre) + a[j];
        }
    }

    for (int i = 1; i <= n; ++i)
        ret = std::max(ret, f[k & 1][i]);

    std::fill_n(f[0], n + 1, 0);
    for (int i = 1; i <= k; ++i)
    {
        long long pre = LLONG_MAX / 2;
        bool b = i & 1;
        std::fill_n(f[b], n + 1, LLONG_MAX / 2);
        for (int j = 1; j <= n; ++j)
        {
            pre = std::min(pre, f[b ^ 1][j - 1]);
            f[b][j] = std::min(f[b][j - 1], pre) + a[j];
        }
    }

    for (int i = 1; i <= n; ++i)
        ret = std::max(ret, sum - f[k & 1][i]);

    return ret;
}

int main()
{
    std::freopen("sum.in", "r", stdin);
    std::freopen("sum.out", "w", stdout);

    int t;
    read(t);

    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}