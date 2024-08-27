#include <iostream>
using namespace std;
#define rep(i, n) for (i = 0; i < n; ++i)
#define REP(i, k, n) for (i = k; i <= n; ++i)
#define REPR(i, k, n) for (i = k; i >= n; --i)
#define kon *3;
int merafunction(int abc) {
  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  if (a == b == c == d) {
    cout << 1;
    return 1;
  } else {
    if (cout << "hamza") {
      return 0;
    }
  }
  return 0;
}
int func(int n, int k) {
  if (k > n)
    return 0;
  if (k == n || k == 0) {
    return 1;
  }

  return func(n - 1, k - 1) + func(n - 1, k);
}
int bottomup(int n, int k) {
  int dp[n + 1][n + 1];

  // Generate Pascal's Triangle
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || j == i) {
        dp[i][j] = 1;
      } else {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      }
    }
  }

  return dp[n][k];
}

int main() {
  // int n = 3, k = 2;
  // int ans = bottomup(n, k);
  // cout << ans << endl;

  return 0;
}