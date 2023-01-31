#include <bits/stdc++.h>

const int maxn = 3e5, mod = 998244353;

std::array<std::vector<std::pair<int, bool>>, maxn + 1> op;

struct matrix
{
    std::array<std::array<int, 2>, 2> a;

    matrix()
    {
        for (int i = 0; i < 2; ++i)
            a[i].fill(0);
    }

    matrix operator*(matrix rhs)
    {
        matrix ret;

        for (int k = 0; k < 2; ++k)
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;

        return ret;
    }
};
std::array<matrix, maxn * 4> t;

int ls(int x) { return x * 2; }
int rs(int x) { return x * 2 + 1; }

void update(int x) { t[x] = t[ls(x)] * t[rs(x)]; }

void modify(int x, int l, int r, int p, matrix m)
{
    if (l == r)
    {
        t[x] = m;
        return;
    }

    int mid = (l + r) / 2;
    if (p <= mid)
        modify(ls(x), l, mid, p, m);
    else
        modify(rs(x), mid + 1, r, p, m);
    update(x);
}

int main()
{
    std::freopen("CF1743F.in", "r", stdin);

    int n, l0, r0;
    std::cin >> n >> l0 >> r0;

    for (int i = 1; i < n; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        op[l].emplace_back(i, 1);
        op[r + 1].emplace_back(i, 0);
    }

    std::array<matrix, 2> m;
    m[0].a[0][1] = 0;
    m[0].a[1][0] = m[1].a[0][0] = m[1].a[1][0] = 1;
    m[0].a[1][1] = m[1].a[0][1] = m[1].a[1][1] = 2;
    m[0].a[0][0] = 3;

    for (int i = 1; i < n; ++i)
        modify(1, 1, n - 1, i, m[0]);
    int ans = 0;
    for (int i = 0; i <= maxn; ++i)
    {
        for (std::pair<int, bool> pr : op[i])
            modify(1, 1, n - 1, pr.first, m[pr.second]);
        if (l0 <= i && i <= r0)
            ans = (ans + t[1].a[1][1]) % mod;
        else
            ans = (ans + t[1].a[0][1]) % mod;
    }

    std::cout << ans << std::endl;
    return 0;
}