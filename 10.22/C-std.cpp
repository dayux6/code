#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define MAXR 25005
#define oo 200000000
typedef pair<int, int> P;
struct node
{
    int to;
    node *nxt;
    node() { nxt = NULL; }
    void add(int k)
    {
        node *p = new node;
        p->to = k;
        p->nxt = nxt;
        nxt = p;
    }
} son[MAXN];

int re[MAXN];
vector<P> range[MAXR];
vector<int> id[MAXR];
int cnt[MAXR];

int Log[MAXN];

int head[MAXN], rear[MAXN], tot = 0;
map<int, int> mp[MAXN];
void dfs(int u)
{
    int tmp = ++tot;
    cnt[re[u]]++;
    id[re[u]].push_back(tmp);
    range[re[u]].push_back(P(tot + 1, cnt[re[u]]));
    for (node *i = son[u].nxt; i; i = i->nxt)
        dfs(i->to);
    cnt[re[u]]--;
    range[re[u]].push_back(P(tot + 1, cnt[re[u]]));
    rear[tmp] = tot;
}
int SlogT(int &S, int &T)
{
    vector<int>::iterator L, R;
    int ans = 0;
    for (int i = 0; i < id[S].size(); i++)
    {
        L = upper_bound(id[T].begin(), id[T].end(), id[S][i]);
        R = upper_bound(id[T].begin(), id[T].end(), rear[id[S][i]]);
        ans += R - L;
    }
    return ans;
}
int TlogS(int &S, int &T)
{
    vector<P>::iterator it;
    int ans = 0;
    for (int i = 0; i < id[T].size(); i++)
    {
        it = upper_bound(range[S].begin(), range[S].end(), P(id[T][i], oo));
        if (it != range[S].begin())
        {
            ans += (--it)->second;
        }
    }
    return ans;
}
int ST(int &S, int &T)
{ // range是对应的前缀和数组.
    int j = 0, ans = 0;
    for (int i = 0; i < id[T].size(); i++)
    {
        while (j < range[S].size() && range[S][j].first <= id[T][i])
            j++; // range[S][j].first>=id[T][i];
        if (j > 0)
        {
            std::cout << range[S][j - 1].second << ' ';
            ans += range[S][j - 1].second;
        }
    }
    return ans;
}
int main()
{
    freopen("regions.in", "r", stdin);
    freopen("regions.ans", "w", stdout);
    int n, R, q, fa;
    scanf("%d %d %d", &n, &R, &q);
    scanf("%d", &re[1]);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d %d", &fa, &re[i]);
        son[fa].add(i);
    }
    dfs(1);
    for (int i = 0; i < MAXN; i++)
    {
        int x = i;
        while (x)
            x >>= 1, Log[i]++;
    }
    while (q--)
    {
        int S, T;
        scanf("%d %d", &S, &T);
        if (mp[S].count(T))
        {
            printf("%d\n", mp[S][T]);
            continue;
        }
        int a = id[S].size(), b = id[T].size();
        int mi = min(a + b, min(a * Log[b], b * Log[a]));
        int ans;
        if (mi == a + b)
            ans = ST(S, T);
        else if (mi == a * Log[b])
            ans = SlogT(S, T);
        else
            ans = TlogS(S, T);
        printf("%d\n", ans);
        mp[S][T] = ans;
    }
    return 0;
}