#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P3295.in");
#endif
using std::cout;

const int mod = 1e9 + 7;

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

int main()
{
    int n, m;
    cin >> n >> m;
    int lg = log2(n), **fa = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = new int[lg + 1];
        std::fill_n(fa[i], lg + 1, i);
    }
    auto find = [&](int x, int i)
    {
        while (x != fa[x][i])
            x = fa[x][i] = fa[fa[x][i]][i];
        return fa[x][i];
    };
    for (int i = 0; i < m; ++i)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        int len = r1 - l1 + 1;
        for (int j = lg; j >= 0; --j)
            if ((len >> j) & 1)
            {
                fa[find(l1, j)][j] = find(l2, j);
                l1 += 1 << j;
                l2 += 1 << j;
            }
    }
    for (int i = lg; i > 0; --i)
        for (int j = 1; j <= n; ++j)
            if (find(j, i) != j)
            {
                fa[find(j, i - 1)][i - 1] = find(find(j, i), i - 1);
                fa[find(j + (1 << (i - 1)), i - 1)][i - 1] = find(find(j, i) + (1 << (i - 1)), i - 1);
            }
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        cnt += find(i, 0) == i;
    cout << 9ll * qpow(10, cnt - 1) % mod << std::endl;
    return 0;
}