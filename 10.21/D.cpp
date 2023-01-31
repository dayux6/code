#include <bits/stdc++.h>

const int maxn = 8e5, base = 233, mod = 1e9 + 7;

char a[maxn + 1], b[maxn + 1];
long long sa[maxn + 1], sb[maxn + 2], pw[maxn + 1], hal[maxn + 1], har[maxn + 1], hbl[maxn + 1], hbr[maxn + 1];

int main()
{
    std::freopen("palindrome.in", "r", stdin);
    std::freopen("palindrome.out", "w", stdout);

    char type;
    std::scanf("%c%s%s", &type, a + 1, b + 1);

    int n = std::strlen(a + 1), m = std::strlen(b + 1);

    pw[0] = 1;
    for (int i = 1; i <= std::max(n, m); ++i)
        pw[i] = pw[i - 1] * base % mod;

    for (int i = 1; i <= n; ++i)
        hal[i] = (hal[i - 1] * base % mod + a[i] - 'a') % mod;
    har[n] = a[n] - 'a';
    for (int i = n - 1; i >= 1; --i)
        har[i] = (har[i + 1] * base % mod + a[i] - 'a') % mod;

    for (int i = 1; i <= m; ++i)
        hbl[i] = (hbl[i - 1] * base % mod + b[i] - 'a') % mod;
    hbr[m] = b[m] - 'a';
    for (int i = m - 1; i >= 1; --i)
        hbr[i] = (hbr[i + 1] * base % mod + b[i] - 'a') % mod;

    auto gethl = [](long long *h, int l, int r)
    { return ((h[r] - h[l - 1] * pw[r - l + 1] % mod) % mod + mod) % mod; };
    auto gethr = [](long long *h, int l, int r)
    { return ((h[l] - h[r + 1] * pw[r - l + 1] % mod) % mod + mod) % mod; };

    for (int i = 1; i <= n; ++i)
    {
        int l = 1, r = std::min(i, n - i + 1), len = 1;

        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (gethl(hal, i - mid + 1, i + mid - 1) == gethr(har, i - mid + 1, i + mid - 1))
            {
                len = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        ++sa[i - len];
        --sa[i];
    }
    for (int i = 1; i < n; ++i)
    {
        int l = 0, r = std::min(i, n - i), len = 0;

        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (gethl(hal, i - mid + 1, i + mid) == gethr(har, i - mid + 1, i + mid))
            {
                len = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        ++sa[i - len];
        --sa[i + 1];
    }

    ++sa[n];
    for (int i = 1; i <= n; ++i)
        sa[i] += sa[i - 1];
    for (int i = 1; i <= n; ++i)
        sa[i] += sa[i - 1];

    for (int i = 1; i <= m; ++i)
    {
        int l = 1, r = std::min(i, m - i + 1), len = 1;

        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (gethl(hbl, i - mid + 1, i + mid - 1) == gethr(hbr, i - mid + 1, i + mid - 1))
            {
                len = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        ++sb[i + len];
        --sb[i];
    }
    for (int i = 1; i < m; ++i)
    {
        int l = 0, r = std::min(i, m - i), len = 0;

        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (gethl(hbl, i - mid + 1, i + mid) == gethr(hbr, i - mid + 1, i + mid))
            {
                len = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        ++sb[i + len + 1];
        --sb[i + 1];
    }

    for (int i = m; i >= 1; --i)
        sb[i] += sb[i + 1];
    for (int i = 1; i <= m; ++i)
        sb[i] += sb[i - 1];

    int q;
    std::scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        int x, y;
        std::scanf("%d%d", &x, &y);

        x = n - x + 1;
        y = m - y + 1;

        int l = 0, r = std::min(x, y), len = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (gethl(hal, n - x + 1, n - x + mid) == gethr(hbr, y - mid + 1, y))
            {
                len = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        printf("%lld\n", sa[n - x + len] - sa[n - x] + sb[y] - sb[y - len]);
    }
    return 0;
}