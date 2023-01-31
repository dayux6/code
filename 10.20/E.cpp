#include <bits/stdc++.h>

const int maxn = 1e6, mod = 998244353, base = 2333, hmod = 1e9 + 9;

int f[maxn + 1], s[maxn + 1];
long long pw[maxn + 1], ha[maxn + 1], hl[maxn + 1], hr[maxn + 1];
char a[maxn + 1], l[maxn + 1], r[maxn + 1];

int main()
{
    std::freopen("E.in", "r", stdin);

    scanf("%s%s%s", a + 1, l + 1, r + 1);
    int n = std::strlen(a + 1), lenl = std::strlen(l + 1), lenr = std::strlen(r + 1);

    pw[0] = 1;
    for (int i = 1; i <= maxn; ++i)
    {
        pw[i] = pw[i - 1] * base % mod;
        ha[i] = ha[i - 1] * base % mod + a[i];
        hl[i] = hl[i - 1] * base % mod + l[i];
        hr[i] = hr[i - 1] * base % mod + r[i];
    }

    auto gethash = [=](long long *h, int l, int r)
    {
        return (h[r] - h[l - 1] * pw[r - l + 1] % mod + mod) % mod;
    };

    auto cmpl = [=](int left, int right)
    {
        if (right - left + 1 < lenl)
            return false;
        else if (right - left + 1 > lenl)
            return true;
        else
        {
            int L = 0, R = right - left + 1, lcp;
            while (L <= R)
            {
                int mid = (L + R) / 2;
                if (gethash(ha, left, left + mid - 1) == gethash(hl, 1, mid))
                {
                    lcp = mid;
                    L = mid + 1;
                }
                else
                    R = mid - 1;
            }

            if (lcp == right - left + 1)
                return true;
            else
                return a[left + lcp] > l[lcp + 1];
        }
    };

    auto cmpr = [=](int left, int right)
    {
        if (right - left + 1 < lenr)
            return true;
        else if (right - left + 1 > lenr)
            return false;
        else
        {
            int L = 0, R = right - left + 1, lcp;
            while (L <= R)
            {
                int mid = (L + R) / 2;
                if (gethash(ha, left, left + mid - 1) == gethash(hr, 1, mid))
                {
                    lcp = mid;
                    L = mid + 1;
                }
                else
                    R = mid - 1;
            }

            if (lcp == right - left + 1)
                return true;
            else
                return a[left + lcp] < r[lcp + 1];
        }
    };

    int i = 1, liml = 1, limr = 1;
    while (i <= n && !cmpl(limr, i))
        ++i;

    if (i == n + 1 || (cmpr(1, n) && !std::strcmp(a + 1, r + 1)))
    {
        std::cout << 0 << std::endl;
        return 0;
    }
    else
    {
        f[0] = f[i] = 1;
        std::fill_n(s, i, 1);
        s[i] = s[i - 1];
        if (i < n && a[i + 1] != '0')
            s[i] = s[i] + 1;

        for (++i; i <= n; ++i)
        {
            while (liml <= i && !cmpr(liml, i))
                ++liml;
            while (limr < i && cmpl(limr + 1, i))
                ++limr;

            s[i] = s[i - 1];
            if (liml > i)
                continue;

            f[i] = (s[limr - 1] - (liml == 1 ? 0 : s[liml - 2])) % mod;
            if (limr == i && a[i] == '0')
                f[i] = (f[i] + f[i - 1]) % mod;

            if (i < n && a[i + 1] != '0')
                s[i] = (s[i] + f[i]) % mod;
        }

        std::cout << (f[n] + mod) % mod << std::endl;
    }
    return 0;
}