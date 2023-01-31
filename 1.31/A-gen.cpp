#include <bits/stdc++.h>

std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

void solve()
{
    int n = 5000, m = gen() % 100 + 1;
    std::cout << n << ' ' << m << std::endl;

    std::uniform_int_distribution<int> dis(1, m);
    for (int i = 0; i < n; ++i)
        std::cout << dis(gen) << ' ';
    std::cout << std::endl;
}

int main()
{
    std::freopen("resona.in", "w", stdout);

    int t = 5;
    std::cout << t << std::endl;

    for (int i = 0; i < t; ++i)
        solve();
    return 0;
}