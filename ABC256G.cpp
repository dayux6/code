#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256G.in");
#endif
using std::cout;

const int mod = 998244353;

struct mat
{
    int n, **a;

    mat(int _n) : n(_n), a(new int *[_n])
    {
        for (int i = 0; i < _n; ++i)
            a[i] = new int[_n]();
    }

    mat operator*(mat rhs)
    {
        mat ret(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
        return ret;
    }
};

int qpow(int x, int n)
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

int getinv(int x) { return qpow(x, mod - 2); }

mat qpow(mat x, long long n)
{
    mat ret(x.n);
    for (int i = 0; i < x.n; ++i)
        ret.a[i][i] = 1;
    while (n)
    {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n /= 2;
    }
    return ret;
}

int main()
{
    long long n;
    int d;
    cin >> n >> d;
    int *fac = new int[d];
    fac[0] = 1;
    for (int i = 1; i < d; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    int *inv = new int[d];
    inv[d - 1] = getinv(fac[d - 1]);
    for (int i = d - 1; i > 0; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
    auto C = [=](int n, int m)
    {
        if (n < m || m < 0)
            return 0ll;
        return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod;
    };
    int sum = 0;
    for (int i = 0; i <= d + 1; ++i)
    {
        mat x(2);
        x.a[0][0] = C(d - 1, i - 2);
        x.a[0][1] = x.a[1][0] = C(d - 1, i - 1);
        x.a[1][1] = C(d - 1, i);
        x = qpow(x, n);
        sum = (sum + (x.a[0][0] + x.a[1][1]) % mod) % mod;
    }
    cout << sum << std::endl;
    return 0;
}