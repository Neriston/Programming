#include <iostream>

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  auto array = new char*[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new char[m];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> array[i][j];
    }
  }
  int cnt_v = 0;
  int cnt_g = 0;
  int vert[2]{-1, -1};
  int gor[2]{-1, -1};
  for (int i = 0; i < n; ++i) {
    bool flag = true;
    for (int j = 0; j < m; ++j) {
      if (array[i][j] == '0') {
        flag = false;
        break;
      }
    }
    if (flag) {
      ++cnt_g;
      if (gor[0] == -1) {
        gor[0] = i;
      } else if (gor[1] == -1) {
        gor[1] = i;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    bool flag = true;
    for (int j = 0; j < n; ++j) {
      if (array[j][i] == '0') {
        flag = false;
        break;
      }
    }
    if (flag) {
      ++cnt_v;
      if (vert[0] == -1) {
        vert[0] = i;
      } else if (vert[1] == -1) {
        vert[1] = i;
      }
    }
  }
  if (n == 1) {
    cnt_v = 0;
  }
  if (m == 1) {
    cnt_g = 0;
  }
  int delta_v = vert[1] - vert[0] - 1;
  int delta_g = gor[1] - gor[0] - 1;
  if ((cnt_g == 0 && cnt_v == 0) || (cnt_g == 1 && cnt_v == 0) || (cnt_g == 0 && cnt_v == 1)) {
    std::cout << "?";
  } else if (cnt_g >= 1 && cnt_v >= 1) {
    std::cout << "Square";
  } else if (cnt_g >= 2 && cnt_v == 0) {
    if (delta_g < m) {
      std::cout << "Line";
    } else {
      std::cout << "?";
    }
  } else if (cnt_g == 0 && cnt_v >= 2) {
    if (delta_v < n) {
      std::cout << "Vertical line";
    } else {
      std::cout << "?";
    }
  }
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
}