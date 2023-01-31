#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P5903.in");
#endif
using std::cout;

const int maxn = 5e5, lg = 18;

#define ui unsigned int
ui s;

inline ui get(ui x)
{
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x;
}

int dep[maxn + 1], len[maxn + 1], ls[maxn + 1], top[maxn + 1], anc[maxn + 1][lg + 1], *up[maxn + 1], *down[maxn + 1];
std::vector<int> ch[maxn + 1];

void dfs1(int x)
{
    for (int i = 1; i <= lg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int v : ch[x])
    {
        anc[v][0] = x;
        dep[v] = dep[x] + 1;
        dfs1(v);
        if (ls[x] == 0 || len[v] > len[ls[x]])
        {
            ls[x] = v;
            len[x] = len[v] + 1;
        }
    }
}

void dfs2(int x, int t)
{
    top[x] = t;
    if (x == t)
    {
        up[x] = new int[len[x]];
        int tmp = x;
        for (int i = 0; i < len[x]; ++i)
        {
            up[x][i] = tmp;
            tmp = anc[tmp][0];
        }
        down[x] = new int[len[x]];
        tmp = x;
        for (int i = 0; i < len[x]; ++i)
        {
            down[x][i] = tmp;
            tmp = ls[tmp];
        }
    }
    if (ls[x] != 0)
    {
        dfs2(ls[x], t);
        for (int v : ch[x])
            if (v != ls[x])
                dfs2(v, v);
    }
}

int query(int x, int k)
{
    if (k == 0)
        return x;
    x = anc[x][(int)log2(k)];
    k -= (1 << (int)log2(k)) + dep[x] - dep[top[x]];
    return k >= 0 ? up[top[x]][k] : down[top[x]][-k];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q >> s;
    int rt;
    for (int i = 1; i <= n; ++i)
    {
        int fa;
        cin >> fa;
        if (fa == 0)
            rt = i;
        ch[fa].emplace_back(i);
    }
    dep[rt] = 1;
    std::fill_n(len + 1, n, 1);
    dfs1(rt);
    dfs2(rt, rt);
    int lst = 0;
    long long ans = 0;
    for (int i = 1; i <= q; ++i)
    {
        ui x = (get(s) ^ lst) % n + 1, k = (get(s) ^ lst) % dep[x];
        lst = query(x, k);
        ans ^= 1ll * i * lst;
    }
    cout << ans << std::endl;
    return 0;
}