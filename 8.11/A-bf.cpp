#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

template <typename T>
void read(T &x)
{
    x = 0;
    bool b = true;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            b = false;
        c = getchar();
    }
    while (isdigit(c))
    {
        if (b)
            x = x * 10 + (c ^ 48);
        else
            x = x * 10 - (c ^ 48);
        c = getchar();
    }
}

template <typename T, typename... arg>
void read(T &x, arg &...y)
{
    read(x);
    read(y...);
}

long long sum[maxn + 1], st[maxn + 1][maxlg + 1];

struct hash
{
    long long operator()(std::pair<int, int> pr) const { return 1ll * pr.first * (maxn + 1) + pr.second; }
};

int main()
{
    freopen("A.in", "r", stdin);
    int t;
    read(t);

    for (int _ = 0; _ < t; ++_)
    {
        int n, k;
        read(n, k);

        for (int i = 1; i <= n; ++i)
        {
            long long a;
            read(a);
            sum[i] = sum[i - 1] + a;
            st[i][0] = sum[i];
        }

        int r = k;
        bool b = true;
        for (int l = k; l >= 1; --l)
        {
            while (r < n && sum[r + 1] - sum[l] <= 0)
                ++r;
            while (r >= l && sum[r] - sum[l] > 0)
                --r;

            if (r < k)
            {
                b = false;
                break;
            }
        }

        std::cout << ((b && r == n) ? "Yes" : "No") << std::endl;
    }
    return 0;
}