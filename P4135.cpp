#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P4135.in");
#endif
using std::cout;

int main()
{
    int n, c, m;
    cin >> n >> c >> m;
    int bsiz = sqrt(n), bcnt = (n - 1) / bsiz + 1, *a = new int[n + 1], *bel = new int[n + 1], **cnt = new int *[bcnt + 1];
    for (int i = 0; i <= (n - 1) / bsiz + 1; ++i)
        cnt[i] = new int[c + 1]();
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        bel[i] = (i - 1) / bsiz + 1;
        ++cnt[bel[i]][a[i]];
    }
    for (int i = 1; i <= bcnt; ++i)
        for (int j = 0; j <= c; ++j)
            cnt[i][j] += cnt[i - 1][j];
    int *tmp = new int[c + 1], **ans = new int *[bcnt + 1];
    for (int i = 1; i <= bcnt; ++i)
    {
        ans[i] = new int[bcnt + 1];
        int res = 0;
        std::fill_n(tmp, c + 1, 0);
        for (int j = i; j <= bcnt; ++j)
        {
            for (int k = (j - 1) * bsiz + 1; k <= std::min(n, j * bsiz); ++k)
            {
                ++tmp[a[k]];
                if (tmp[a[k]] % 2 == 0)
                    ++res;
                else if (tmp[a[k]] > 2)
                    --res;
            }
            ans[i][j] = res;
        }
    }
    std::fill_n(tmp, c + 1, 0);
    int lst = 0;
    for (int _ = 0; _ < m; ++_)
    {
        int l, r;
        cin >> l >> r;
        l = (l + lst) % n + 1;
        r = (r + lst) % n + 1;
        if (l > r)
            std::swap(l, r);
        if (bel[r] - bel[l] <= 1)
        {
            lst = 0;
            for (int i = l; i <= r; ++i)
            {
                ++tmp[a[i]];
                if (tmp[a[i]] % 2 == 0)
                    ++lst;
                else if (tmp[a[i]] > 2)
                    --lst;
            }
            cout << lst << '\n';
            for (int i = l; i <= r; ++i)
                --tmp[a[i]];
        }
        else
        {
            lst = ans[bel[l] + 1][bel[r] - 1];
            for (int i = l; i <= bel[l] * bsiz; ++i)
            {
                ++tmp[a[i]];
                if ((tmp[a[i]] + cnt[bel[r] - 1][a[i]] - cnt[bel[l]][a[i]]) % 2 == 0)
                    ++lst;
                else if (tmp[a[i]] + cnt[bel[r] - 1][a[i]] - cnt[bel[l]][a[i]] > 2)
                    --lst;
            }
            for (int i = (bel[r] - 1) * bsiz + 1; i <= r; ++i)
            {
                ++tmp[a[i]];
                if ((tmp[a[i]] + cnt[bel[r] - 1][a[i]] - cnt[bel[l]][a[i]]) % 2 == 0)
                    ++lst;
                else if (tmp[a[i]] + cnt[bel[r] - 1][a[i]] - cnt[bel[l]][a[i]] > 2)
                    --lst;
            }
            cout << lst << std::endl;
            for (int i = l; i <= bel[l] * bsiz; ++i)
                --tmp[a[i]];
            for (int i = (bel[r] - 1) * bsiz + 1; i <= r; ++i)
                --tmp[a[i]];
        }
    }
    return 0;
}