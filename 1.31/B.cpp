#include <bits/stdc++.h>

const int maxb = 12;

int main()
{
    std::freopen("multi.in", "r", stdin);
    std::freopen("multi.out", "w", stdout);

    int b;
    long long n;
    std::cin >> n >> b;

    long long fir = -1, sec = -1;
    for (int lim = b; lim > 0; --lim)
    {
        int cl = lim / 2, cr = lim - cl;

        for (int S = 0; S < (1 << b); ++S)
            if (__builtin_popcount(S) == cl)
            {
                int R = ((1 << b) - 1) ^ S;
                for (int T = R; T != 0; T = (T - 1) & R)
                    if (__builtin_popcount(T) == cr)
                    {
                        std::vector<int> vl, vr;
                        for (int i = b - 1; i >= 0; --i)
                            if ((S >> i) & 1)
                                vl.emplace_back(i);
                            else if ((T >> i) & 1)
                                vr.emplace_back(i);

                        std::unordered_map<long long, std::pair<long long, long long>> max;
                        do
                        {
                            long long r = 0;
                            for (int v : vr)
                                r = r * b + v;

                            if (max.count(r % n) == 0)
                                max.emplace(r % n, std::make_pair(r, -1));
                            else
                            {
                                max[r % n].second = std::max(max[r % n].second, r);

                                if (max[r % n].first < max[r % n].second)
                                    std::swap(max[r % n].first, max[r % n].second);
                            }
                        } while (std::prev_permutation(vr.begin(), vr.end()));

                        long long pw = pow(b, cr);
                        do
                        {
                            long long l = 0;
                            for (int v : vl)
                                l = l * b + v;
                            l *= pw;

                            long long r = (n - l % n) % n;
                            if (max.count(r) != 0)
                            {
                                sec = std::max(sec, l + max[r].first);

                                if (fir < sec)
                                    std::swap(fir, sec);

                                if (max[r].second != -1)
                                {
                                    sec = std::max(sec, l + max[r].second);

                                    if (fir < sec)
                                        std::swap(fir, sec);
                                }
                            }
                        } while (std::prev_permutation(vl.begin(), vl.end()));
                    }
            }
    }

    std::cout << sec << std::endl;
    return 0;
}