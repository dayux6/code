#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256A.in");
#endif
using std::cout;

int main() {
  int n;
  cin >> n;
  cout << (1 << n) << '\n';
  return 0;
}