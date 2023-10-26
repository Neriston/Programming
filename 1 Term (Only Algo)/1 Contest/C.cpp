#include <iostream>

int F(int** array, int n, int left) {
  static int cnt = 0;
  if (left == n) {
    ++cnt;
  } else {
    for (int i = 0; i < n; ++i) {
      if (array[i][0] == 0) {
        auto array_copy = new int*[n];
        for (int k = 0; k < n; ++k) {
          array_copy[k] = new int[n - left];
        }
        for (int w = 0; w < n; ++w) {
          for (int o = 0; o < n - left; ++o) {
            array_copy[w][o] = array[w][o];
          }
        }
        int temp_1 = i - 1;
        int temp_2 = i + 1;
        for (int j = 1; j < n - left; ++j) {
          if (temp_1 >= 0) {
            array_copy[temp_1][j] = 1;
            --temp_1;
          }
          if (temp_2 <= n - 1) {
            array_copy[temp_2][j] = 1;
            ++temp_2;
          }
          array_copy[i][j] = 1;
        }
        auto array_copy1 = new int*[n];
        for (int k = 0; k < n; ++k) {
          array_copy1[k] = new int[n - left - 1];
        }
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n - left - 1; ++j) {
            array_copy1[i][j] = array_copy[i][j + 1];
          }
        }
        F(array_copy1, n, left + 1);
        for (int l = 0; l < n; ++l) {
          delete[] array_copy[l];
          delete[] array_copy1[l];
        }
        delete[] array_copy;
        delete[] array_copy1;
      }
    }
  }
  return cnt;
}

int main() {
  int n;
  std::cin >> n;
  auto array = new int*[n];
  for (int j = 0; j < n; ++j) {
    array[j] = new int[n]{};
  }
  std::cout << F(array, n, 0);
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
  return 0;
}