#include <bits/stdc++.h>
#include <bits/extc++.h>

const int maxn = 400, mod = 1e9 + 7;

int a[maxn + 1], b[maxn + 1];

int A(int n, int m)
{
    int ret = 1;
    for (int i = n - m + 1; i <= n; ++i)
        ret = 1ll * ret * i % mod;
    return ret;
}

struct hash
{
    auto operator()(std::bitset<maxn + 1> bs) { return bs.to_ulong(); }
};

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];

    std::bitset<maxn + 1> bs;
    std::unordered_map<std::bitset<maxn + 1>, std::vector<std::pair<int, int>>> f;
    f.insert(std::make_pair(std::bitset<maxn + 1>(), std::vector<std::pair<int, int>>({std::make_pair(0, 1)})));
    for (int i = 3; i <= n; i += 3)
    {
        std::unordered_map<std::bitset<maxn + 1>, std::vector<std::pair<int, int>>> g;
        for (auto pr : f)
        {
            int pa = 1;
            while (pa <= n && pr.first.test(a[pa]))
                ++pa;
            if (pa > n)
                break;
            int pb = 1;
            while (pb <= n && pr.first.test(b[pb]))
                ++pb;
            if (pb > n || a[pa] == b[pb])
                break;

            bs = pr.first;
            bs.set(a[pa]);
            bs.set(b[pb]);
            for (int j = 1; j <= n; ++j)
                if (!bs.test(j))
                {
                    bs.set(j);
                    std::vector<std::pair<int, int>> vct;
                    for (std::pair<int, int> tmp : pr.second)
                        for (int k = tmp.first + 1; k <= i; ++k)
                            vct.push_back(std::make_pair(k, (int)(1ll * tmp.second * A(i - tmp.first - 1, k - tmp.first - 1) % mod)));
                    g.insert(std::make_pair(bs, vct));
                    bs.reset(j);
                }
        }
        f = g;
    }

    std::cout << f.begin()->second.back().second << std::endl;
    return 0;
}