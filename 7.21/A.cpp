#include <bits/stdc++.h>

const int p = 1e9 + 7;

int cnt[300], inv[100000];

struct matrix
{
    int n, a[300][300];

    matrix(int _n) : n(_n) {}
};

void mul(matrix &a, matrix b)
{
    static int tmp[300][300];
    for (int i = 0; i < a.n; ++i)
        for (int j = 0; j < a.n; ++j)
            tmp[i][j] = 0;
    for (int i = 0; i < a.n; ++i)
        for (int j = 0; j < a.n; ++j)
            for (int k = 0; k < a.n; ++k)
                tmp[i][j] = (tmp[i][j] + 1ll * a.a[i][k] * b.a[k][j] % p) % p;
    for (int i = 0; i < a.n; ++i)
        for (int j = 0; j < a.n; ++j)
            a.a[i][j] = tmp[i][j];
}

matrix fpow(matrix x, int n)
{
    matrix ret(x.n);
    for (int i = 0; i < x.n; ++i)
        for (int j = 0; j < x.n; ++j)
            ret.a[i][j] = 0;
    ret.a[0][1] = 1;
    while (n)
    {
        if (n & 1)
            mul(ret, x);
        mul(x, x);
        n /= 2;
    }
    return ret;
}

int qpow(int x, int n, const int mod)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

int getinv(int x, const int mod) { return qpow(x, mod - 2, mod); }

int main()
{
    freopen("A.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, M;
    std::cin >> n >> m >> M;
    for (int i = 0; i < n; ++i)
    {
        int a;
        std::cin >> a;
        ++cnt[a];
        inv[i] = getinv(a, M);
    }
    matrix a(M);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            a.a[i][j] = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < n; ++j)
            ++a.a[i * inv[j] % M][i];
    matrix res = fpow(a, m);
    int sum = 0;
    for (int i = 0; i < M; ++i)
        sum = (sum + 1ll * i * res.a[0][i] % p) % p;
    std::cout << 1ll * sum * getinv(qpow(n, m, p), p) % p << std::endl;
    return 0;
}