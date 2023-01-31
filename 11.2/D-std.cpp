#include <bits/stdc++.h>
using namespace std;
#define M 100005
#define forgraph for (int i = 0; i < (int)E[x].size(); ++i)
int n;
vector<int> E[M];

int D, dx, fa[M];
void find_dia(int x, int d = 0)
{
    if (d > D)
        D = d, dx = x;
    forgraph
    {
        int y = E[x][i];
        if (y == fa[x])
            continue;
        fa[y] = x;
        find_dia(y, d + 1);
    }
}

bool mark[M];
int pos[M], dep[M], mxdis[M], tot; // mxdis:直径的点下方最大深度
int get_pos(int x)
{
    int dis = 0;
    pos[x] = tot;
    forgraph
    {
        int y = E[x][i];
        if (mark[y])
            continue;
        mark[y] = 1;
        dep[y] = dep[x] + 1;
        dis = max(dis, get_pos(y) + 1);
    }
    return dis;
}

struct node
{ // 这是利用线段树维护一个区间（你也可以用ST表）
    int L, R, res1, res2;
} tree[M << 2];
void build(int L, int R, int p = 1)
{
    tree[p].L = L;
    tree[p].R = R;
    if (L == R)
    {
        tree[p].res1 = mxdis[L] - L;
        tree[p].res2 = mxdis[L] + L;
        return;
    }
    int mid = (L + R) >> 1;
    build(L, mid, p << 1);
    build(mid + 1, R, p << 1 | 1);
    tree[p].res1 = max(tree[p << 1].res1, tree[p << 1 | 1].res1);
    tree[p].res2 = max(tree[p << 1].res2, tree[p << 1 | 1].res2);
}
int query(int L, int R, bool f, int p = 1)
{
    if (tree[p].L == L && tree[p].R == R)
        return f ? tree[p].res1 : tree[p].res2;
    int mid = (tree[p].L + tree[p].R) >> 1;
    if (R <= mid)
        return query(L, R, f, p << 1);
    if (L > mid)
        return query(L, R, f, p << 1 | 1);
    return max(query(L, mid, f, p << 1), query(mid + 1, R, f, p << 1 | 1));
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.ans", "w", stdout);

    int Q;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        E[a].push_back(b);
        E[b].push_back(a);
    }
    int u, v;
    find_dia(1);
    u = dx;
    D = 0;
    memset(fa, 0, sizeof fa);
    find_dia(dx);
    v = dx;
    while (v != u)
    { // 抽直径
        mark[v] = mark[fa[v]] = 1;
        tot++;
        mxdis[tot] = get_pos(v);
        v = fa[v];
    }
    tot++;
    mxdis[tot] = get_pos(u);
    for (int i = tot; i >= 1; --i)
        std::cerr << mxdis[i] << ' ';
    std::cerr << std::endl;
    build(1, tot); // tot是直径上端点个数
    scanf("%d", &Q);
    while (Q--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (pos[a] > pos[b])
            swap(a, b);
        int x = pos[a], y = pos[b];
        // std::cerr << tot - x + 1 << ' ' << tot - y + 1 << std::endl;
        int ans = max(min(dep[a] + x - 1, dep[b] + y - 1), min(dep[a] + tot - x, dep[b] + tot - y));
        int mid = (dep[a] + y - x + dep[b]) / 2 + x - dep[a];
        std::cerr << tot - mid + 1 << ' ' << ans << std::endl;
        if (mid < x)
            mid = x; // 把在直径下方的mid提到上面来
        if (mid > y)
            mid = y;
        if (x + 1 <= mid)
            ans = max(ans, query(x + 1, mid, 0) - x + dep[a]);
        if (y - 1 >= mid + 1)
            ans = max(ans, query(mid + 1, y - 1, 1) + y + dep[b]);
        printf("%d\n", ans);
    }
    return 0;
}