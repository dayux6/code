#include <bits/stdc++.h>
using namespace std;
template <typename T>
void read(T &x)
{
    char c;
    int f{1};
    do
        x = (c = getchar()) ^ 48;
    while (!isdigit(c) && c != '-');
    if (x == 29)
        f = -1, x = 0;
    while (isdigit(c = getchar()))
        x = (x << 3) + (x << 1) + (c ^ 48);
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...args)
{
    read(x);
    read(args...);
}
const int N(2000);
int f[N + 5][N + 5];
int cnt[N + 5];
int fa[N + 5], sz[N + 5];
int a[N + 5], b[N + 5];
int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void merge(int x, int y)
{
    if (Find(x) == Find(y))
        return;
    sz[fa[x]] += sz[fa[y]];
    fa[fa[y]] = fa[x];
}
vector<int> ppip;
int main()
{
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    for (int i{1}; i <= 2000; ++i)
    {
        f[i][i] = i - 1;
        for (int j{1}; j < i; ++j)
            f[i][j] = max(f[i - j][j] + j - 1, f[i - j - 1][j] + j);

        for (int j = 1; j <= i; ++j)
            std::cout << f[i][j] << ' ';
        std::cout << std::endl;
    }
    return 0;
}