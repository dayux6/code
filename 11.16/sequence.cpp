#include <bits/stdc++.h>

const int maxn = 1e6;

int x[maxn + 1], cnt[maxn];
bool vis[maxn];
long long s[maxn], res[maxn];

int main()
{
    std::freopen("sequence.in", "r", stdin);
    std::freopen("sequence.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    for (int _ = 0, m, a, c, l1, r1, l2, r2; _ < t; ++_)
    {
        std::cin >> m >> a >> c >> x[0] >> l1 >> r1 >> l2 >> r2;

        for (int i = 1; i <= std::max(r1, r2); ++i)
            x[i] = (1ll * a * x[i - 1] % m + c) % m;

        std::fill_n(cnt, m, 0);
        std::fill_n(s, m, 0);
        for (int i = l1; i <= r1; ++i)
        {
            ++cnt[x[i]];
            s[x[i]] += x[i];
        }
        for (int i = 1; i < m; ++i)
        {
            cnt[i] += cnt[i - 1];
            s[i] += s[i - 1];
        }

        std::fill_n(vis, m, false);
        std::fill_n(res, m, 0);
        long long ans = 0;
        for (int i = l2; i <= r2; ++i)
        {
            if (!vis[x[i]])
            {
                vis[x[i]] = true;
                for (int j = 0, l, r; j * (x[i] + 1) < m; ++j)
                {
                    l = j * (x[i] + 1);
                    r = std::min(m, (j + 1) * (x[i] + 1)) - 1;
                    res[x[i]] += s[r] - (l == 0 ? 0 : s[l - 1]) - 1ll * l * (cnt[r] - (l == 0 ? 0 : cnt[l - 1]));
                }
            }

            ans += res[x[i]];
        }

        std::cout << ans << '\n';
    }
    return 0;
}