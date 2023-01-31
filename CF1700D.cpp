#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1700D.in");
#endif
using std::cout;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  long long s = 0, *f = new long long[n + 1];
  f[n] = 0;
  for (int i = 1; i <= n; ++i) {
    int v;
    cin >> v;
    s += v;
    f[n] = std::max(f[n], (long long)ceil(1.0 * s / i));
  }
  for (int i = 1; i < n; ++i)
    f[i] = std::max(f[n], (long long)ceil(1.0 * s / i));
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    int l = 1, r = n, ans = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (f[mid] <= t) {
        ans = mid;
        r = mid - 1;
      } else
        l = mid + 1;
    }
    cout << ans << '\n';
  }
  return 0;
}