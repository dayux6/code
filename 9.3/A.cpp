#include <bits/stdc++.h>

const int maxn = 1e7, maxcnt = 664579;

int cnt, prime[maxcnt + 1];
std::bitset<maxn + 1> bs;

void sieve(int n)
{
    bs.set(1);
    for (int i = 2; i <= n; ++i)
    {
        if (!bs.test(i))
        {
            ++cnt;
            prime[cnt] = i;
        }

        for (int j = 1; j <= cnt && 1ll * i * prime[j] <= n; ++j)
        {
            if (1ll * i * prime[j] > n)
                break;
            bs.set(i * prime[j]);
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main()
{
    freopen("A.in", "r", stdin);
    int k;
    long long l, r;
    std::cin >> l >> r >> k;

    sieve(std::min((int)sqrt(r), k));

    bs.reset();
    for (int i = 1; i <= cnt; ++i)
        for (long long j = std::max(2ll, (long long)std::ceil(1.0 * l / prime[i])) * prime[i]; j <= r; j += prime[i])
            bs.set(j - l);

    long long ans = 0;
    for (long long i = l; i <= r; ++i)
        if (!bs.test(i - l))
            ans ^= i;

    std::cout << ans << std::endl;
    return 0;
}