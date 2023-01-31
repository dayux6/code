#include <bits/stdc++.h>
const int maxn = 1e5;

long long a[maxn + 2];

struct hash
{
    __int128 operator()(std::pair<long long, long long> pr) const { return (__int128)pr.first * 1e14 + pr.second; }
};

std::unordered_map<std::pair<long long, long long>, long long, hash> f;

long long dp(long long a, long long b)
{
    if (a < b)
        return 0;
    else if (a == b)
        return 1;
    else if (f.count(std::make_pair(a, b)) == 0)
        f.emplace(std::make_pair(a, b), dp((a - 1) / 2, b) + dp(a / 2, b));
    return f.at(std::make_pair(a, b));
}

int main()
{
    freopen("D.in", "r", stdin);
    long long m;
    int n, q;
    std::cin >> m >> n >> q;

    std::map<std::pair<long long, int>, long long> cnt;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];

        if (a[i] - a[i - 1] > 1)
            cnt.emplace(std::make_pair(a[i - 1] + 1 - a[i], i - 1), 1);
    }
    a[n + 1] = m + 1;
    if (a[n + 1] - a[n] > 1)
        cnt.emplace(std::make_pair(a[n] + 1 - a[n + 1], n), 1);

    long long c = n;
    std::pair<std::pair<long long, int>, long long> pr;
    for (int i = 0; i < q; ++i)
    {
        long long b;
        std::cin >> b;

        if (b <= n)
            std::cout << a[b] << std::endl;
        else
        {
            while (c < b)
            {
                pr = *cnt.begin();
                pr.first.first = -pr.first.first;
                cnt.erase(cnt.begin());
                if (pr.first.first - 1 >= 2)
                    cnt[std::make_pair(-((pr.first.first - 1) / 2), pr.first.second)] += pr.second;
                if (pr.first.first >= 2)
                    cnt[std::make_pair(-(pr.first.first / 2), pr.first.second)] += pr.second;
                c += pr.second;
            }

            long long l = a[pr.first.second] + 1, r = a[pr.first.second + 1] - 1;
            while (r - l + 1 > pr.first.first)
            {
                long long mid = (l + r) / 2;
                if (c - b < dp(r - mid, pr.first.first))
                    l = mid + 1;
                else
                {
                    b += dp(r - mid, pr.first.first);
                    r = mid - 1;
                }
            }
            std::cout << (l + r) / 2 << std::endl;
        }
    }
    return 0;
}