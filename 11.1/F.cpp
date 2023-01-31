#include <bits/stdc++.h>

const int maxn = 1e4;

int n, fa[maxn + 1], val[maxn + 1];

int find(int x)
{
    if (x != fa[x])
    {
        int f = find(fa[x]);
        val[x] ^= val[fa[x]];
        fa[x] = f;
    }
    return fa[x];
}

void merge(int x, int y, int v)
{
    if (find(x) != find(y))
    {
        v ^= val[x] ^ val[y];
        x = fa[x];
        y = fa[y];

        if (y == n)
            std::swap(x, y);

        fa[y] = x;
        val[y] = v;
    }
}

int main()
{
    freopen("F.in", "r", stdin);
    int q;
    std::cin >> n >> q;

    std::iota(fa, fa + n + 1, 0);
    for (int i = 0; i < q; ++i)
    {
        int op;
        std::cin >> op;

        switch (op)
        {
        case 1:
        {
            int p, x;
            std::cin >> p >> x;
            merge(n, p, x);
            break;
        }
        case 2:
        {
            int p, q, v;
            std::cin >> p >> q >> v;
            merge(p, q, v);
            break;
        }
        case 3:
        {
            int k;
            std::cin >> k;
            int res = 0;
            std::unordered_map<int, bool> tmp;
            for (int i = 0; i < k; ++i)
            {
                int p;
                std::cin >> p;
                int rt = find(p);
                if (rt != n)
                    tmp[rt] ^= 1;
                res ^= val[p];
            }

            bool flg = true;
            for (std::pair<int, bool> pr : tmp)
                if (pr.second)
                {
                    flg = false;
                    break;
                }

            if (flg)
                std::cout << res << std::endl;
            else
                puts("I don't know.");
            break;
        }
        }
    }
    return 0;
}
