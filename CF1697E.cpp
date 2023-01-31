#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1697E.in");
#endif
using std::cout;

const int mod = 998244353;

struct point {
  int x, y;

  point() { cin >> x >> y; }
};

class DSU {
private:
  int n, *fa;

public:
  DSU(int);
  int find(int);
  void merge(int, int);
};

DSU::DSU(int _n) : n(_n), fa(new int[_n]) {
  for (int i = 0; i < n; ++i)
    fa[i] = i;
}

int DSU::find(int x) {
  while (x != fa[x])
    x = fa[x] = fa[fa[x]];
  return x;
}

void DSU::merge(int x, int y) { fa[find(x)] = find(y); }

int calc(point x, point y) { return abs(x.x - y.x) + abs(x.y - y.y); }

int main() {
  int n;
  cin >> n;
  point *p = new point[n]();
  int **d = new int *[n];
  std::unordered_map<int, std::vector<std::pair<int, int>>> e;
  for (int i = 0; i < n; ++i) {
    d[i] = new int[n];
    for (int j = 0; j < n; ++j) {
      d[i][j] = calc(p[i], p[j]);
      if (i < j)
        e[d[i][j]].emplace_back(i, j);
    }
  }
  DSU s(n * 2);
  for (auto pr : e)
    if (pr.second.size() > 1)
      for (std::pair<int, int> p : pr.second) {
        s.merge(p.first, p.second);
        s.merge(p.first + n, p.second + n);
      }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i != j)
        for (int k = 0; k < n; ++k)
          if (i != k && j != k && d[i][j] < d[i][k] && d[i][j] < d[j][k]) {
            s.merge(i, j);
            s.merge(i + n, j + n);
            s.merge(i, k + n);
            s.merge(i + n, k);
          }
  int ans = 1;
  std::vector<int> vct;
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    bool b = true;
    for (int j = 0; j < i; ++j)
      if (s.find(i) == s.find(j)) {
        b = false;
        break;
      } else
        cnt += s.find(i) == s.find(j + n);
    if (b) {
      int siz = 0;
      for (int j = 0; j < n; ++j)
        siz += s.find(i) == s.find(j);
      ans = 1ll * ans * (n - cnt) % mod;
    }
  }
  cout << ans << std::endl;
  return 0;
}