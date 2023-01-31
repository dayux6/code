#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P2886.in");
#endif
using std::cout;

struct edge {
  int w, u, v;
};

struct mat {
  int n, **a;

  mat(int _n) : n(_n), a(new int *[_n]) {
    for (int i = 0; i < _n; ++i)
      a[i] = new int[_n]();
  }

  mat operator*(mat rhs) const {
    mat ret(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        ret.a[i][j] = INT_MAX;
        for (int k = 0; k < n; ++k)
          if (a[i][k] != INT_MAX && rhs.a[k][j] != INT_MAX)
            ret.a[i][j] = std::min(ret.a[i][j], a[i][k] + rhs.a[k][j]);
      }
    return ret;
  }
};

mat qpow(mat x, int n) {
  mat ret(x.n);
  for (int i = 0; i < x.n; ++i)
    for (int j = 0; j < x.n; ++j)
      ret.a[i][j] = x.a[i][j];
  n--;
  while (n) {
    if (n & 1)
      ret = ret * x;
    x = x * x;
    n /= 2;
  }
  return ret;
}

int main() {
  int k, n, s, t;
  cin >> k >> n >> s >> t;
  edge *e = new edge[n];
  std::vector<int> vct;
  for (int i = 0; i < n; ++i) {
    cin >> e[i].w >> e[i].u >> e[i].v;
    vct.emplace_back(e[i].u);
    vct.emplace_back(e[i].v);
  }
  std::sort(vct.begin(), vct.end());
  vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
  s = std::lower_bound(vct.begin(), vct.end(), s) - vct.begin();
  t = std::lower_bound(vct.begin(), vct.end(), t) - vct.begin();
  mat x(vct.size());
  for (int i = 0; i < x.n; ++i)
    std::fill_n(x.a[i], x.n, INT_MAX);
  for (int i = 0; i < n; ++i) {
    int u = std::lower_bound(vct.begin(), vct.end(), e[i].u) - vct.begin(),
        v = std::lower_bound(vct.begin(), vct.end(), e[i].v) - vct.begin();
    x.a[u][v] = x.a[v][u] = e[i].w;
  }
  cout << qpow(x, k).a[s][t] << std::endl;
  return 0;
}