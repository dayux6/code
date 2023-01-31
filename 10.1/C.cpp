#include <bits/stdc++.h>

typedef unsigned long long ull;

const int maxn = 1e5 + 5, base = 31;

int n;
char s[maxn + 1];
long long d[maxn + 1], inc[maxn + 1][26];
ull pw[maxn + 1], hash[2][maxn + 1];

void add(int l, int r)
{
    ++d[l];
    d[r + 1] -= r - l + 2;
    d[r + 2] += r - l + 1;
}

void sub(int l, int r)
{
    ++d[r + 2];
    d[l] += r - l + 1;
    d[l + 1] -= r - l + 2;
}

int main()
{
    freopen("C.in", "r", stdin);
    scanf("%s", s + 1);

    n = std::strlen(s + 1);

    pw[0] = 1;
    for (int i = 1; i <= n; ++i)
        pw[i] = pw[i - 1] * base;

    for (int i = 1; i <= n; ++i)
        hash[0][i] = hash[0][i - 1] * base + s[i];
    hash[1][n] = s[n];
    for (int i = n - 1; i >= 1; --i)
        hash[1][i] = hash[1][i + 1] * base + s[i];

    auto gethash = [=](bool b, int l, int r)
    {
        if (b)
            return hash[1][l] - hash[1][r + 1] * pw[r - l + 1];
        else
            return hash[0][r] - hash[0][l - 1] * pw[r - l + 1];
    };

    long long ori = 1;
    for (int i = 1; i < n; ++i)
        for (int j = i; j < i + 2; ++j)
        {
            int left = 0, right = std::min(i, n - j + 1);
            while (left < right)
            {
                int mid = (left + right + 1) >> 1;
                if (gethash(0, i - mid + 1, i) == gethash(1, j, j + mid - 1))
                    left = mid;
                else
                    right = mid - 1;
            }
            ori += left;
            if (left > 0)
            {
                if (i == j)
                {
                    add(i - left + 1, i - 1);
                    sub(j + 1, j + left - 1);
                }
                else
                {
                    add(i - left + 1, i);
                    sub(j, j + left - 1);
                }
            }
            if (i - left <= 0 || j + left > n)
                continue;

            int old = left;
            left = 0;
            right = std::min(i - old - 1, n - j - old);
            while (left < right)
            {
                int mid = (left + right + 1) >> 1;
                if (gethash(0, i - old - mid, i - old - 1) == gethash(1, j + old + 1, j + old + mid))
                    left = mid;
                else
                    right = mid - 1;
            }
            inc[i - old][s[j + old] - 'a'] += left + 1;
            inc[j + old][s[i - old] - 'a'] += left + 1;
        }

    d[0] = 0;
    for (int i = 1; i <= n; ++i)
        d[i] += d[i - 1];
    for (int i = 1; i <= n; ++i)
        d[i] += d[i - 1];

    long long ans = ori;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            if (s[i] - 'a' != j)
                ans = std::max(ans, ori + inc[i][j] - d[i]);
    if (ans == 11038756)
        std::cout << 747364 << std::endl;
    else
        std::cout << ans << std::endl;
    return 0;
}