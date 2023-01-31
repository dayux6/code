#include <bits/stdc++.h>

const int maxn = 1e6;

namespace INPUT_SPACE
{
    const int S = (1 << 20) + 5;
    char B[S], *H, *T;
    inline int gc()
    {
        if (H == T)
            T = (H = B) + fread(B, 1, S, stdin);
        return (H == T) ? EOF : *H++;
    }
    inline void read(int &x)
    {
        x = 0;
        int ch;
        while ((ch = gc()) < '0' || ch > '9')
            ;
        x = ch ^ '0';
        while ((ch = gc()) >= '0' && ch <= '9')
            x = x * 10 + (ch ^ '0');
    }
}
using INPUT_SPACE::read;

int a[maxn + 1], bel[maxn + 1], cnt, c[maxn];
bool ans[maxn];

struct query
{
    int no, l, r;

    inline bool operator<(query rhs) const { return bel[l] == bel[rhs.l] ? (r < rhs.r) ^ (bel[l] & 1) : bel[l] < bel[rhs.l]; }
} q[maxn];

inline void add(int x, int v)
{
    cnt -= c[x] == 1;
    c[x] += v;
    cnt += c[x] == 1;
}

int main()
{
    std::freopen("range.in", "r", stdin);
    std::freopen("range.ans", "w", stdout);

    int n, m;
    read(n);
    read(m);

    if (m == 0)
        return 0;

    std::vector<int> vct;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        vct.emplace_back(a[i]);
    }

    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    for (int i = 1; i <= n; ++i)
        a[i] = std::lower_bound(vct.begin(), vct.end(), a[i]) - vct.begin();

    int bsiz = n / std::sqrt(m);
    for (int i = 1; i <= n; ++i)
        bel[i] = i / bsiz;
    for (int i = 0; i < m; ++i)
    {
        q[i].no = i;
        read(q[i].l);
        read(q[i].r);
    }
    std::stable_sort(q, q + m);

    int l = 1, r = 0;
    for (int i = 0; i < m; ++i)
    {
        while (r < q[i].r)
        {
            ++r;
            add(a[r], 1);
        }
        while (l > q[i].l)
        {
            --l;
            add(a[l], 1);
        }
        while (r > q[i].r)
        {
            add(a[r], -1);
            --r;
        }
        while (l < q[i].l)
        {
            add(a[l], -1);
            ++l;
        }

        ans[q[i].no] = cnt == q[i].r - q[i].l + 1;
    }

    for (int i = 0; i < m; ++i)
    {
        std::putchar(ans[i] ? '1' : '0');
        putchar('\n');
    }
    return 0;
}