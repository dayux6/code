#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P3008.in");
#endif
using std::cout;

struct edge {
  int v, w;

  edge(int _v, int _w) : v(_v), w(_w) {}
};

std::vector<edge> *g;

int main() {
  int n, r, p, s;
  cin >> n >> r >> p >> s;
  g = new std::vector<edge>[n + 1];
  for (int i = 0; i < r; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  for (int i = 0; i < p; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
  }
  int *dis = new int[n + 1];
  std::fill_n(dis + 1, n, INT_MAX);
  dis[s] = 0;
  bool *inq = new bool[n + 1]();
  inq[s] = true;
  std::deque<int> q;
  q.emplace_back(s);
  while (!q.empty()) {
    int x = q.front();
    inq[x] = false;
    q.pop_front();
    for (edge e : g[x])
      if (dis[e.v] > dis[x] + e.w) {
        dis[e.v] = dis[x] + e.w;
        if (!inq[e.v]) {
          inq[e.v] = true;
          if (dis[e.v] > dis[q.front()])
            q.emplace_back(e.v);
          else
            q.emplace_front(e.v);
        }
      }
  }
  for (int i = 1; i <= n; ++i)
    if (dis[i] == INT_MAX)
      cout << "NO PATH\n";
    else
      cout << dis[i] << '\n';
  return 0;
}