#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256E.in");
#endif
using std::cout;

class UnionFind {
private:
  int n, *fa;
  int find(int);

public:
  UnionFind(int);
  void merge(int, int);
  bool query(int, int);
};

UnionFind::UnionFind(int _n) : n(_n), fa(new int[_n + 1]) {
  for (int i = 1; i <= _n; ++i)
    fa[i] = i;
}

int UnionFind::find(int x) {
  while (x != fa[x])
    x = fa[x] = fa[fa[x]];
  return x;
}

void UnionFind::merge(int x, int y) { fa[find(x)] = find(y); }

bool UnionFind::query(int x, int y) { return find(x) == find(y); }

int main() {
  int n;
  cin >> n;
  int *x = new int[n + 1], *c = new int[n + 1];
  for (int i = 1; i <= n; ++i)
    cin >> x[i];
  for (int i = 1; i <= n; ++i)
    cin >> c[i];
  long long sum = 0;
  UnionFind uf(n);
  for (int i = 1; i <= n; ++i)
    if (uf.query(i, x[i])) {
      int cur = i, min = c[i];
      do {
        cur = x[cur];
        min = std::min(min, c[cur]);
      } while (cur != i);
      sum += min;
    } else
      uf.merge(i, x[i]);
  cout << sum << '\n';
  return 0;
}