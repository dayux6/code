#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256B.in");
#endif
using std::cout;

int main() {
  int n;
  cin >> n;
  int *a = new int[n];
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  int c[4] = {0, 0, 0, 0}, p = 0;
  for (int i = 0; i < n; ++i) {
    ++c[0];
    for (int j = 3; j >= 0; --j)
      if (c[j] != 0) {
        if (j + a[i] >= 4)
          p += c[j];
        else
          c[j + a[i]] += c[j];
        c[j] = 0;
      }
  }
  cout << p << '\n';
  return 0;
}