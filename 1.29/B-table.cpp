#include <bits/stdc++.h>

const int maxn = 100;

bool flg;
long long f[maxn + 1];
std::vector<int> prime, vct;
std::vector<std::vector<int>> res;

bool isprime(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

void dfs(int rest, int lim)
{
    if (rest < 0)
        return;

    if (rest == 0)
    {
        res.emplace_back(vct);
        std::reverse(res.back().begin(), res.back().end());
        return;
    }

    for (int i = std::upper_bound(prime.begin(), prime.end(), lim) - prime.begin() - 1; i >= 0; --i)
    {
        vct.emplace_back(prime[i]);
        dfs(rest - prime[i], prime[i]);
        vct.pop_back();
    }
}

bool cmp(std::vector<int> x, std::vector<int> y)
{
    if (x.size() == y.size())
    {
        for (std::size_t i = 0; i < x.size(); ++i)
            if (x[i] != y[i])
                return x[i] < y[i];

        return true;
    }
    else
        return x.size() < y.size();
}

int main()
{
    std::freopen("table.txt", "w", stdout);

    for (int i = 2; i <= maxn; ++i)
        if (isprime(i))
            prime.emplace_back(i);

    std::cout << "vector<vector<int>>ans={";
    for (int i = 1; i <= maxn; ++i)
    {
        std::vector<std::vector<int>>().swap(res);
        dfs(i, i);

        std::sort(res.begin(), res.end(), cmp);

        for (std::vector<int> v : res)
        {
            std::cout << '{' << v.front();
            for (std::size_t i = 1; i < v.size(); ++i)
                std::cout << ',' << v[i];
            std::cout << "},";
        }
    }
    return 0;
}