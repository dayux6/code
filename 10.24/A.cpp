#include <bits/stdc++.h>

const int maxn = 1e6;

int n, pos[26], pre[26], nxt[maxn + 1];
char a[maxn + 1], b[maxn + 1];

class BIT
{
private:
    int t[maxn + 1];

    int lowbit(int x) { return x & -x; }

public:
    void build() { std::fill_n(t + 1, n, 0); }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] += v;
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += t[i];
        return ret;
    }
} t;

int main()
{
    std::freopen("letter.in", "r", stdin);
    std::freopen("letter.out", "w", stdout);

    std::scanf("%d%s%s", &n, a + 1, b + 1);

    for (int i = 1; i <= n; ++i)
    {
        int k = a[i] - 'A';
        if (pos[k] == 0)
            pos[k] = i;
        nxt[pre[k]] = i;
        pre[k] = i;
    }

    long long ans = 0;
    t.build();
    for (int i = 1; i <= n; ++i)
    {
        int r = pos[b[i] - 'A'];
        ans += i - 1 - t.query(r - 1);
        t.modify(r, 1);
        pos[b[i] - 'A'] = nxt[pos[b[i] - 'A']];
    }

    std::cout << ans << std::endl;
    return 0;
}