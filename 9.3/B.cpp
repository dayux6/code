#include <bits/stdc++.h>

const int mod = 1e9 + 7, maxk = 100;

int p[maxk + 1], f[maxk + 2];

struct mat
{
    int n, a[maxk + 2][maxk + 2];

    mat(int _n) : n(_n)
    {
        for (int i = 1; i <= _n; ++i)
            std::fill_n(a[i] + 1, _n, 0);
    }

    mat operator*(mat rhs) const
    {
        mat ret(n);

        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
        return ret;
    }
};

mat qpow(mat x, long long n)
{
    mat ret(x.n);
    for (int i = 1; i <= x.n; ++i)
        ret.a[i][i] = 1;

    while (n)
    {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

int main()
{
    freopen("B.in", "r", stdin);
    int n, k;
    long long m;
    std::cin >> n >> m >> k;

    int a, sum = 1;
    std::cin >> a;
    p[a] = f[a] = 1;
    for (int i = 2; i <= n; ++i)
    {
        std::cin >> a;
        p[a] = i;
        sum = (sum - f[a]) % mod;
        f[a] = (f[a] + sum + 1) % mod;
        sum = (sum + f[a]) % mod;
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    for (int i = 1; i <= k; ++i)
        q.emplace(p[i], i);
    for (int i = 1; i <= m % k; ++i)
    {
        auto pr = q.top();
        q.pop();
        sum = (sum - f[pr.second]) % mod;
        f[pr.second] = (f[pr.second] + sum + 1) % mod;
        sum = (sum + f[pr.second]) % mod;
        q.emplace(n + i, pr.second);
    }

    mat x(k + 1);
    for (int i = 1; i <= k; ++i)
        x.a[1][i] = f[i];
    x.a[1][k + 1] = 1;

    mat base(k + 1);
    for (int i = 1; i <= k + 1; ++i)
        base.a[i][i] = 1;
    for (int i = 1; i <= k; ++i)
    {
        auto pr = q.top();
        q.pop();
        mat tmp(k + 1);
        for (int j = 1; j <= k + 1; ++j)
            tmp.a[j][j] = tmp.a[j][pr.second] = 1;
        base = base * tmp;
    }

    x = x * qpow(base, m / k);

    sum = 0;
    for (int i = 1; i <= k; ++i)
        sum = (sum + x.a[1][i]) % mod;
    std::cout << (sum + mod) % mod << std::endl;
    return 0;
}