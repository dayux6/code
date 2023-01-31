#include <bits/stdc++.h>

template <typename T>
void read(T &x)
{
    x = 0;
    char c = getchar();

    while (!isdigit(c))
        c = getchar();

    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

const int maxn = 1e6;

int a[maxn + 1], b[maxn + 1];

int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    long long L, R;
    read(n);
    read(L);
    read(R);

    for (int i = 1; i <= n; ++i)
        read(a[i]);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        read(b[i]);
    std::sort(b + 1, b + n + 1);

    auto check = [=](int k)
    {
        int j = 1;
        long long ret = 0;
        for (int i = std::upper_bound(a + 1, a + n + 1, k - b[j]) - a - 1; i >= 1; --i)
        {
            while (j < n && a[i] + b[j + 1] <= k)
                ++j;
            ret += j;
        }
        return ret;
    };

    int l = 0, r = a[n] + b[n];
    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (check(mid) < L)
            l = mid + 1;
        else
            r = mid - 1;
    }
    int ls = l + 1;
    l = 0;
    r = a[n] + b[n];
    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (check(mid) < R)
            l = mid + 1;
        else
            r = mid - 1;
    }
    int rs = l - 1;

    if (ls - 1 == rs + 1)
    {
        for (int i = L; i <= R; ++i)
            std::cout << (ls + rs) / 2 << ' ';
        std::cout << std::endl;
    }
    else
    {
        std::vector<int> vct;
        l = std::lower_bound(b + 1, b + n + 1, ls - a[1]) - b;
        r = std::upper_bound(b + 1, b + n + 1, rs - a[1]) - b - 1;
        for (int i = 1; i <= n; ++i)
        {
            while (l > 1 && a[i] + b[l - 1] >= ls)
                --l;
            while (r >= 1 && a[i] + b[r] > rs)
                --r;

            for (int j = l; j <= r; ++j)
                vct.push_back(a[i] + b[j]);
        }

        int lim = check(ls - 1) - L + 1;
        for (int i = 0; i < lim; ++i)
            std::cout << ls - 1 << ' ';
        std::sort(vct.begin(), vct.end());
        for (int v : vct)
            std::cout << v << ' ';
        lim = R - check(rs);
        for (int i = 0; i < lim; ++i)
            std::cout << rs + 1 << ' ';
        std::cout << std::endl;
    }
    return 0;
}