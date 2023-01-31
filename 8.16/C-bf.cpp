#include <bits/stdc++.h>

const int maxn = 400, mod = 1e9 + 7;

int a[maxn + 1], b[maxn + 1], c[maxn + 1];
bool vis[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];
    std::iota(c + 1, c + n + 1, 1);

    int cnt = 0;
    do
    {
        std::fill_n(vis + 1, n, false);
        int pa = 1, pb = 1, pc = 1;
        bool flg = true;
        for (int i = 3; i <= n; i += 3)
        {
            while (pa <= n && vis[a[pa]])
                ++pa;
            if (pa > n)
            {
                flg = false;
                break;
            }
            while (pb <= n && vis[b[pb]])
                ++pb;
            if (pb > n || a[pa] == b[pb])
            {
                flg = false;
                break;
            }
            while (pc <= n && vis[c[pc]])
                ++pc;
            if (pc > n || a[pa] == c[pc] || b[pb] == c[pb])
            {
                flg = false;
                break;
            }
            vis[a[pa]] = vis[b[pb]] = vis[c[pc]] = true;
        }

        cnt += flg;
        if (cnt >= mod)
            cnt -= mod;
    } while (std::next_permutation(c + 1, c + n + 1));

    std::cout << cnt << std::endl;
    return 0;
}