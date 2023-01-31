#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
// #define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int, int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin(), (x).end()
#define mem(a) memset(a, 0, sizeof a)
typedef long long ll;
const int P = 1e9 + 7;
int n, k;
int A[MAXN];
int x[MAXN], y[MAXN], w[MAXN];
vi X, Y;
int fa[MAXN], se[MAXN], sz[MAXN];
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

inline void Inc(int &x, int y)
{
    x = (x + y > P ? x + y - P : x + y);
}

vector<pii> G[MAXN];

vi nl, nr;
int bc[MAXN];
int as[106];
namespace lsjtxdy
{
    int dp[106][1 << 16 | 66];
    void wkr()
    {
        int sl = nl.size(), sr = nr.size();
        rep(i, 0, sl + sr) rep(j, 0, (1 << sl) - 1) dp[i][j] = 0;
        rep(i, 0, sl + sr) as[i] = 0;
        dp[0][0] = 1;
        rep(i, 1, sr) rep(s, 0, (1 << sl) - 1)
        {
            Inc(dp[i][s], dp[i - 1][s]);
            int u = nr[i - 1];
            for (auto t : G[u])
                if (~s & (1 << bc[t.fi]))
                {
                    int v = t.fi, w = t.se;
                    int ts = s | (1 << bc[v]);
                    Inc(dp[i][ts], dp[i - 1][s] * 1ll * w % P);
                }
        }
        rep(i, 0, (1 << sl) - 1) Inc(as[__builtin_popcount(i)], dp[sr][i]);
    }
}
namespace zjktsdy
{
    vector<pair<int, pii>> fe;
    int dep[MAXN];
    vector<pii> g[MAXN];
    vi nd;
    void dfs(int u, int f)
    {
        nd.pb(u);
        dep[u] = dep[f] + 1;
        for (auto t : G[u])
            if (t.fi != f)
            {
                if (!dep[t.fi])
                    dfs(t.fi, u), g[u].pb(t);
                else if (dep[t.fi] > dep[u])
                    fe.eb(mp(u, t));
            }
    }
    int fk[MAXN];
    int dp[106][2][52], pd[2][52], siz[106];
    void afs(int u)
    {
        int sz = 1;
        mem(dp[u]);
        dp[u][0][0] = 1;
        for (auto t : g[u])
        {
            int v = t.fi;
            afs(v);
            memcpy(pd, dp[u], sizeof dp[u]);
            mem(dp[u]);
            rep(i, 0, sz) rep(j, 0, siz[v])
            {
                Inc(dp[u][0][i + j], pd[0][i] * 1ll * (dp[v][0][j] + dp[v][1][j]) % P);
                if (!fk[u])
                {
                    Inc(dp[u][1][i + j], pd[1][i] * 1ll * (dp[v][0][j] + dp[v][1][j]) % P);
                    if (!fk[v])
                        Inc(dp[u][1][i + j + 1], pd[0][i] * 1ll * dp[v][0][j] % P * t.se % P);
                }
            }
            sz += siz[v];
        }
        siz[u] = sz;
    }

    void wkr(int r)
    {
        nd.clear();
        rep(i, 0, k * 2) as[i] = dep[i] = 0, g[i].clear();
        fe.clear();
        dfs(r, r);
        int ta = 0, ts = 1;
        for (int s = 0; s < (1 << fe.size()); ++s)
        {
            for (int x : nd)
                fk[x] = 0;
            ta = __builtin_popcount(s), ts = 1;
            rep(i, 0, fe.size() - 1) if (s & (1 << i))
            {
                int u = fe[i].fi, v = fe[i].se.fi;
                if (fk[u] || fk[v])
                {
                    ts = 0;
                    break;
                }
                ts = ts * 1ll * fe[i].se.se % P, fk[u] = fk[v] = 1;
            }
            if (!ts)
                continue;
            afs(r);
            rep(i, 0, k) Inc(as[i + ta], (dp[r][0][i] + dp[r][1][i]) * 1ll * ts % P);
        }
    }
}

int ans[105], pas[105];
int J[100006];
void solve()
{
    cin >> n >> k;
    J[0] = 1;
    rep(i, 1, n) J[i] = J[i - 1] * 1ll * i % P;
    rep(i, 1, k)
    {
        scanf("%d%d%d", x + i, y + i, w + i);
        --w[i];
        X.pb(x[i]), Y.pb(y[i]);
    }
    sort(all(X)), sort(all(Y));
    X.erase(unique(all(X)), X.end()), Y.erase(unique(all(Y)), Y.end());
    rep(i, 1, k)
        x[i] = lower_bound(all(X), x[i]) - X.begin() + 1,
        y[i] = lower_bound(all(Y), y[i]) - Y.begin() + 1;
    int sx = X.size(), sy = Y.size();
    rep(i, 1, k)
    {
        G[x[i]].eb(mp(y[i] + sx, w[i]));
        G[y[i] + sx].eb(mp(x[i], w[i]));
        //		cout << x[i] << ' ' << y[i] + sx << endl;
    }
    rep(i, 1, sx + sy) sz[i] = 1, fa[i] = i;
    rep(i, 1, k)
    {
        int u = find(x[i]), v = find(y[i] + sx);
        ++se[v];
        if (u == v)
            continue;
        fa[u] = v, sz[v] += sz[u], se[v] += se[u];
    }
    ans[0] = 1;
    rep(i, 1, sx + sy) if (fa[i] == i && sz[i] > 1)
    {
        if (sz[i] <= 2 * se[i] / 3)
        {
            nl.clear(), nr.clear();
            rep(j, 1, sx) if (find(j) == i) nl.pb(j), bc[j] = nl.size() - 1;
            rep(j, sx + 1, sx + sy) if (find(j) == i) nr.pb(j), bc[j] = nr.size() - 1;
            if (nl.size() > nr.size())
                swap(nl, nr);
            lsjtxdy::wkr();
        }
        else
        {
            zjktsdy::wkr(i);
        }
        memcpy(pas, ans, sizeof ans);
        mem(ans);
        rep(i, 0, k) if (as[i])
            rep(j, i, k)
                Inc(ans[j], as[i] * 1ll * pas[j - i] % P);
    }
    int res = 0;
    rep(i, 0, k) Inc(res, ans[i] * 1ll * J[n - i] % P);
    cout << res << endl;
}

signed main()
{
    //    int T;cin >> T;while( T-- ) solve();
    solve();
}