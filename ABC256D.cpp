#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256D.in");
#endif
using std::cout;

int main() {
  int n;
  cin >> n;
  std::pair<int, int> *pr = new std::pair<int, int>[n];
  for (int i = 0; i < n; ++i)
    cin >> pr[i].first >> pr[i].second;
  std::sort(pr, pr + n);
  int l = pr[0].first, r = pr[0].second;
  for (int i = 1; i < n; ++i) {
    if (pr[i].first > r) {
      cout << l << ' ' << r << '\n';
      l = pr[i].first;
      r = pr[i].second;
    } else
      r = std::max(r, pr[i].second);
  }
  cout << l << ' ' << r << '\n';
  return 0;
}