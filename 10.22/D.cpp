#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16, lim = 128;

int a[maxn + 1], p[maxn + 1][maxlg + 1], cnt[3][lim][lim];
long long ans;

void ins(int x, int v)
{
    int a = x >> 7, b = x & (lim - 1);
    for (int i = a; i < lim; i = (i + 1) | a)
        cnt[0][i][b] += v;
    for (int i = a; i > 0; i = (i - 1) & a)
        cnt[1][i][b] += v;
    cnt[1][0][b] += v;
    cnt[2][a][b] += v;
}

void calc(int x, int v)
{
    int a = x >> 7, b = x & (lim - 1);
    for (int i = b; i > 0; i = (i - 1) & b)
        ans += 1ll * cnt[0][a][i] * v;
    ans += 1ll * cnt[0][a][0] * v;
    for (int i = b; i < lim; i = (i + 1) | b)
        ans += 1ll * cnt[1][a][i] * v;
    ans -= 1ll * cnt[2][a][b] * v;
}

int query(int l, int r)
{
    int k = std::log2(r - l + 1);
    if (a[p[l][k]] > a[p[r - (1 << k) + 1][k]])
        return p[l][k];
    else
        return p[r - (1 << k) + 1][k];
}

void divide(int l, int r)
{
    if (l > r)
        return;

    if (l == r)
    {
        ins(a[l], 1);
        return;
    }

    int mid = query(l, r);
    if (mid - l + 1 < r - mid)
    {
        divide(l, mid - 1);
        for (int i = l; i < mid; ++i)
            ins(a[i], -1);
        divide(mid + 1, r);
        for (int i = l; i < mid; ++i)
            calc(a[i], a[mid]);
        for (int i = l; i < mid; ++i)
            ins(a[i], 1);
    }
    else
    {
        divide(mid + 1, r);
        for (int i = mid + 1; i <= r; ++i)
            ins(a[i], -1);
        divide(l, mid - 1);
        for (int i = mid + 1; i <= r; ++i)
            calc(a[i], a[mid]);
        for (int i = mid + 1; i <= r; ++i)
            ins(a[i], 1);
    }

    calc(a[mid], a[mid]);
    ins(a[mid], 1);
}

int main()
{
    std::freopen("problem.in", "r", stdin);
    std::freopen("problem.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        p[i][0] = i;
    }

    for (int i = 1; (1 << i) <= n; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            if (a[p[j][i - 1]] > a[p[j + (1 << (i - 1))][i - 1]])
                p[j][i] = p[j][i - 1];
            else
                p[j][i] = p[j + (1 << (i - 1))][i - 1];

    divide(1, n);

    std::cout << ans << std::endl;
    return 0;
}