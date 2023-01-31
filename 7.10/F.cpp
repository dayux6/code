#include <bits/stdc++.h>

int main()
{
    freopen("F.in", "r", stdin);
    int t;
    std::cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n, w, pw, dw;
        std::cin >> n >> w >> pw >> dw;
        int *s = new int[n + 1];
        s[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            int len;
            std::cin >> len;
            s[i] = s[i - 1] + len + 1;
        }
        auto search = [=](int x, int w)
        {
            int l = x, r = n, ans = 0;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (s[mid] - s[x - 1] - 1 <= w)
                {
                    ans = mid - x + 1;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            return ans;
        };
        int lg = 20, **f = new int *[n + 1], **g = new int *[n + 1];
        for (int i = 1; i <= n; ++i)
        {
            f[i] = new int[lg + 1]();
            f[i][0] = search(i, w);
            g[i] = new int[lg + 1]();
            g[i][0] = search(i, dw) + search(i + search(i, dw), w - pw - dw);
        }
        for (int i = 1; i <= lg; ++i)
            for (int j = 1; j <= n; ++j)
            {
                f[j][i] = f[j][i - 1];
                if (j + f[j][i - 1] <= n)
                    f[j][i] += f[j + f[j][i - 1]][i - 1];
                g[j][i] = g[j][i - 1];
                if (j + g[j][i - 1] <= n)
                    g[j][i] += g[j + g[j][i - 1]][i - 1];
            }
        int q;
        std::cin >> q;
        for (int i = 0; i < q; ++i)
        {
            int x, h;
            std::cin >> x >> h;
            int p = 1, j = 0;
            while (p <= n && j < x - 1)
            {
                int k = 0;
                while (j + (1 << (k + 1)) < x)
                {
                    if (p + f[p][k] == n + 1)
                        break;
                    ++k;
                }
                p += f[p][k];
                j += 1 << k;
            }
            if (p == n + 1)
            {
                std::cout << j + h << '\n';
                continue;
            }
            j = 0;
            while (p <= n && j < h)
            {
                int k = 0;
                while (j + (1 << (k + 1)) <= h)
                {
                    if (p + f[p][k] == n + 1)
                        break;
                    ++k;
                }
                p += g[p][k];
                j += 1 << k;
            }
            if (p == n + 1)
            {
                std::cout << x + h - 1 << '\n';
                continue;
            }
            j = x + h - 1;
            while (p <= n)
            {
                int k = 0;
                while (p + f[p][k + 1] <= n + 1)
                    ++k;
                p += f[p][k];
                j += 1 << k;
            }
            std::cout << j << '\n';
        }
    }
    return 0;
}