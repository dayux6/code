#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256C.in");
#endif
using std::cout;

int h[3], w[3], a[3][3];

int dfs(int x, int y) {
  if (x == 2) {
    a[2][y] = w[y] - a[1][y] - a[0][y];
    if (a[2][y] <= 0)
      return 0;
    return dfs(0, y + 1);
  }
  if (y == 2) {
    for (int i = 0; i < 3; ++i) {
      a[i][2] = h[i] - a[i][1] - a[i][0];
      if (a[i][2] <= 0)
        return 0;
    }
    return a[0][2] + a[1][2] + a[2][2] == w[2];
  }
  int sum = 0;
  for (int i = 1; i <= std::min(h[x], w[y]); ++i) {
    a[x][y] = i;
    sum += dfs(x + 1, y);
  }
  return sum;
}

int main() {
  for (int i = 0; i < 3; ++i)
    cin >> h[i];
  for (int i = 0; i < 3; ++i)
    cin >> w[i];
  cout << dfs(0, 0) << '\n';
  return 0;
}