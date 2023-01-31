#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
const long long base = 131, mod = 1000000007;
int n, mx, mx_id;
long long inc[maxn][26], dec[maxn], c1[maxn], c2[maxn], ori_ans, delta_ans;
char a[maxn];
long long poww[maxn], hash1[maxn], hash2[maxn];
inline long long get_hash1(int left, int right)
{
    return ((hash1[right] - hash1[left - 1] * poww[right - left + 1]) % mod + mod) % mod;
}
inline long long get_hash2(int left, int right)
{
    return ((hash2[left] - hash2[right + 1] * poww[right - left + 1]) % mod + mod) % mod;
}
inline void incc(int left, int right)
{
    ++c1[left];
    c1[right + 1] -= (right - left + 2);
    c1[right + 2] += (right - left + 1);
}
inline void decc(int left, int right)
{
    ++c1[right + 2];
    c1[left] += (right - left + 1);
    c1[left + 1] -= (right - left + 2);
}
int main(void)
{
    freopen("C.in", "r", stdin);
    scanf("%s", a + 1);
    n = strlen(a + 1);
    a[0] = '$';
    poww[0] = 1ull;
    for (int i = 1; i <= n; ++i)
        poww[i] = poww[i - 1] * base % mod;
    for (int i = 1; i <= n; ++i)
        hash1[i] = (hash1[i - 1] * base + a[i]) % mod;
    for (int i = n; i; --i)
        hash2[i] = (hash2[i + 1] * base + a[i]) % mod;
    int left, right, mid;
    for (int i = 1; i < n; ++i)
        for (int j = i; j < i + 2; ++j)
        {
            left = 0;
            right = std::min(i, n - j + 1);
            while (left < right)
            {
                mid = (left + right + 1) >> 1;
                if (get_hash1(i - mid + 1, i) == get_hash2(j, j + mid - 1))
                {
                    left = mid;
                }
                else
                {
                    right = mid - 1;
                }
            }
            ori_ans += (long long)left;
            if (left > 0)
            {
                if (i == j)
                {
                    incc(i - left + 1, i - 1);
                    decc(j + 1, j + left - 1);
                }
                else
                {
                    incc(i - left + 1, i);
                    decc(j, j + left - 1);
                }
            }
            if (i - left <= 0 || j + left > n)
            {
                continue;
            }
            long long &tem1 = inc[i - left][a[j + left] - 'a'];
            long long &tem2 = inc[j + left][a[i - left] - 'a'];
            int ori_left = left;
            right = std::min(i - left - 1, n - j - left);
            left = 0;
            while (left < right)
            {
                mid = (left + right + 1) >> 1;
                if (get_hash1(i - ori_left - mid, i - ori_left - 1) == get_hash2(j + ori_left + 1, j + ori_left + mid))
                    left = mid;
                else
                    right = mid - 1;
            }
            tem1 += left + 1;
            tem2 += left + 1;
        }

    for (int i = 1; i <= n; ++i)
        std::cout << c1[i] << ' ';
    std::cout << std::endl;
    for (int i = 1; i <= n; ++i)
    {
        c2[i] = c2[i - 1] + c1[i];
        ::dec[i] = ::dec[i - 1] + c2[i];
        std::cout << ::dec[i] << ' ';
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (j == a[i] - 'a')
            {
                continue;
            }
            delta_ans = std::max(delta_ans, inc[i][j] - ::dec[i]);
        }
    }
    ++ori_ans;
    printf("%lld\n", ori_ans + delta_ans);
    return 0;
}