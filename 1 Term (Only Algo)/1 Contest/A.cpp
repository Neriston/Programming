#include <iostream>

void F(int** array, int n, int t) {
  static int time = 0;
  if (time == t) {
    return;
  }
  auto array_ans = new int*[n];
  for (int i = 0; i < n; ++i) {
    array_ans[i] = new int[n];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      array_ans[i][j] = array[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int cnt = 0;
      if (j + 1 < n && array[i][j + 1] == 1) {
        ++cnt;
      }
      if (j - 1 >= 0 && array[i][j - 1] == 1) {
        ++cnt;
      }
      if (i + 1 < n && array[i + 1][j] == 1) {
        ++cnt;
      }
      if (i - 1 >= 0 && array[i - 1][j] == 1) {
        ++cnt;
      }
      if (j + 1 < n && i - 1 >= 0 && array[i - 1][j + 1] == 1) {
        ++cnt;
      }
      if (j + 1 < n && i + 1 < n && array[i + 1][j + 1] == 1) {
        ++cnt;
      }
      if (j - 1 >= 0 && i - 1 >= 0 && array[i - 1][j - 1] == 1) {
        ++cnt;
      }
      if (j - 1 >= 0 && i + 1 < n && array[i + 1][j - 1] == 1) {
        ++cnt;
      }
      if (cnt < 2 || cnt > 3) {
        array_ans[i][j] = 0;
      } else if (cnt == 3 && array_ans[i][j] == 0) {
        array_ans[i][j] = 1;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      array[i][j] = array_ans[i][j];
    }
  }
  ++time;
  F(array, n, t);
  for (int i = 0; i < n; ++i) {
    delete[] array_ans[i];
  }
  delete[] array_ans;
}

int main() {
  int n;
  int t;
  std::cin >> n >> t;
  auto array = new int*[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new int[n];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> array[i][j];
    }
  }
  F(array, n, t);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << array[i][j] << ' ';
    }
    std::cout << '\n';
  }
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
  return 0;
}