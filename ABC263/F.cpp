#include <bits/stdc++.h>

const int maxn = 16, maxpw = 1 << maxn;

int n, c[maxpw + 1][maxn + 1];
long long *f[maxpw * 2];

void dp(int d, int x, int l, int r)
{
    f[x] = new long long[r - l + 1]();

    if (d > 1)
    {
        int ls = x * 2, rs = x * 2 + 1, mid = (l + r) / 2;
        dp(d - 1, ls, l, mid);
        dp(d - 1, rs, mid + 1, r);

        long long lmax = 0, rmax = 0;
        for (int i = l; i <= mid; ++i)
            lmax = std::max(lmax, f[ls][i - l] + c[i][d - 1]);
        for (int i = mid + 1; i <= r; ++i)
            rmax = std::max(rmax, f[rs][i - mid - 1] + c[i][d - 1]);

        int lim = (r - l + 1) / 2;
        for (int i = 0; i < lim; ++i)
            f[x][i] = f[ls][i] + rmax;
        for (int i = lim; i < lim * 2; ++i)
            f[x][i] = f[rs][i - lim] + lmax;
    }
}

int main()
{
    std::cin >> n;

    int pw = 1 << n;
    for (int i = 1; i <= pw; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> c[i][j];

    dp(n, 1, 1, pw);

    long long max = 0;
    for (int i = 0; i < pw; ++i)
        max = std::max(max, f[1][i] + c[i + 1][n]);

    std::cout << max << std::endl;
    return 0;
}