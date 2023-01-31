#include <bits/stdc++.h>

const int mod = 998244353, inv = (mod + 1) / 2;

void getl(int x, int &odd, int &even)
{
    if (x & 1)
    {
        odd = x;
        even = x + 1;
    }
    else
    {
        even = x;
        odd = x + 1;
    }
}

void getr(int x, int &odd, int &even)
{
    if (x & 1)
    {
        odd = x;
        even = x - 1;
    }
    else
    {
        even = x;
        odd = x - 1;
    }
}

int calc(int l, int r)
{
    if (l <= r)
        return 1ll * (l + r) % mod * ((r - l) / 2 + 1) % mod * inv % mod;
    else
        return 0;
}

int main()
{
    freopen("F.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;

    for (int i = 0; i < q; ++i)
    {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;

        int oa, ea, ob, eb, oc, ec, od, ed;
        getl(a, oa, ea);
        getr(b, ob, eb);
        getl(c, oc, ec);
        getr(d, od, ed);
        int erow = ea <= eb ? (eb - ea) / 2 + 1 : 0, orow = (b - a + 1) - erow, ecol = ec <= ed ? (ed - ec) / 2 + 1 : 0, ocol = (d - c + 1) - ecol;

        int ans = 0;
        if (oa <= ob)
            ans = (ans + 1ll * ocol * calc(oa - 1, ob - 1) % mod * m % mod) % mod;
        if (ea <= eb)
            ans = (ans + 1ll * ecol * calc(ea - 1, eb - 1) % mod * m % mod) % mod;
        if (oc <= od)
            ans = (ans + 1ll * orow * calc(oc, od) % mod) % mod;
        if (ed <= ed)
            ans = (ans + 1ll * erow * calc(ec, ed) % mod) % mod;

        std::cout << ans << std::endl;
    }
    return 0;
}