#include <bits/stdc++.h>

const int maxn = 1e5;

int l[maxn], r[maxn], per[maxn];
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

int main()
{
    std::freopen("tournament.in", "w", stdout);

    int n = 6, c = 0, rest = n;
    while (rest > 1)
    {
        std::uniform_int_distribution<int> disr(1, rest - 1);
        r[c] = disr(gen);
        std::uniform_int_distribution<int> disl(0, r[c] - 1);
        l[c] = disl(gen);
        rest -= r[c] - l[c];
        ++c;
    }

    std::iota(per, per + n, 0);
    std::shuffle(per, per + n, gen);

    std::cout << n << ' ' << c << ' ' << per[0] << std::endl;

    for (int i = 1; i < n; ++i)
        std::cout << per[i] << ' ';
    std::cout << std::endl;

    for (int i = 0; i < c; ++i)
        std::cout << l[i] << ' ' << r[i] << std::endl;
    std::cout << std::endl;
    return 0;
}