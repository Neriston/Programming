#include <iostream>

int Func(int** dp, int* matrix, int l, int r) {
  if (dp[l][r] == 0) {
    if (l == r - 1) {
      dp[l][r] = 0;
    } else {
      dp[l][r] = 10e6;
      int cnt = l + 1;
      while (cnt != r) {
        int temp_matrix = matrix[l] * matrix[cnt] * matrix[r];
        int temp_func = Func(dp, matrix, l, cnt) + Func(dp, matrix, cnt, r);
        dp[l][r] = std::min(dp[l][r], temp_matrix + temp_func);
        ++cnt;
      }
    }
  }
  return dp[l][r];
}

int main() {
  int n;
  std::cin >> n;
  auto matrix = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> matrix[i];
  }
  auto dp = new int* [n] {};
  for (int i = 0; i < n; ++i) {
    dp[i] = new int[n]{};
  }

  std::cout << Func(dp, matrix, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] matrix;
  return 0;
}