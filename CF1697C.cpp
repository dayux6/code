#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1697C.in");
#endif
using std::cout;

int main() {
  int t;
  cin >> t;
  for (int _ = 0; _ < t; ++_) {
    int n;
    std::string s, t;
    cin >> n >> s >> t;
    int j = 0;
    bool b = true;
    for (int i = 0; i < n; ++i)
      if (s.at(i) != 'b') {
        while (j < n && t.at(j) == 'b')
          ++j;
        if (j == n || s.at(i) != t.at(j) || (s.at(i) == 'a' && i > j) ||
            (s.at(i) == 'c' && i < j)) {
          cout << "NO\n";
          b = false;
          break;
        }
        ++j;
      }
    while (j < n && t.at(j) == 'b')
      ++j;
    if (b && j == n)
      cout << "YES\n";
    else if (b)
      cout << "NO\n";
  }
  return 0;
}