#include <bits/stdc++.h>

typedef long long ll;
typedef long double db;

const int P = 10;
const db pi = std::acos(-1);

int lim = 1, *r;

void FFT(std::complex<db> *a, int type)
{
    for (int i = 0; i < lim; ++i)
        if (i < r[i])
            std::swap(a[i], a[r[i]]);
    for (int mid = 1; mid < lim; mid *= 2)
    {
        int len = mid * 2;
        std::complex<db> w(std::cos(pi / mid), std::sin(pi / mid) * type);
        for (int l = 0; l < lim; l += len)
        {
            std::complex<db> wi(1, 0);
            for (int i = 0; i < mid; ++i)
            {
                std::complex<db> x = a[l + i], y = wi * a[l + mid + i];
                a[l + i] = x + y;
                a[l + mid + i] = x - y;
                wi *= w;
            }
        }
    }
}

int main()
{
    std::freopen("aplusb.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;
    int p = std::ceil(std::sqrt(P));
    while (lim <= n + m)
        lim *= 2;
    int lg = std::log2(lim) - 1;
    r = new int[lim]();
    for (int i = 0; i < lim; ++i)
        r[i] = (r[i / 2] / 2) | ((i & 1) << lg);
    std::complex<db> *a0, *b0;
    a0 = new std::complex<db>[lim]();
    b0 = new std::complex<db>[lim]();
    for (int i = 0; i <= n; ++i)
    {
        int x;
        std::cin >> x;
        x %= P;
        a0[i].real(x / p);
        b0[i].real(x % p);
    }
    FFT(a0, 1);
    FFT(b0, 1);
    std::complex<db> *a1, *b1;
    a1 = new std::complex<db>[lim]();
    b1 = new std::complex<db>[lim]();
    for (int i = 0; i <= m; ++i)
    {
        int x;
        std::cin >> x;
        x %= P;
        a1[i].real(x / p);
        b1[i].real(x % p);
    }
    FFT(a1, 1);
    FFT(b1, 1);
    std::complex<db> *a, *b, *c;
    a = new std::complex<db>[lim];
    b = new std::complex<db>[lim];
    c = new std::complex<db>[lim];
    for (int i = 0; i < lim; ++i)
    {
        a[i] = a0[i] * a1[i];
        b[i] = a0[i] * b1[i] + b0[i] * a1[i];
        c[i] = b0[i] * b1[i];
    }
    FFT(a, -1);
    FFT(b, -1);
    FFT(c, -1);
    for (int i = 0; i <= n + m; ++i)
        std::cout << (p * p % P * ((ll)std::round(a[i].real() / lim) % P) % P + p * ((ll)std::round(b[i].real() / lim) % P) % P + (ll)std::round(c[i].real() / lim) % P + P) % P << ' ';
    std::cout << std::endl;
    return 0;
}