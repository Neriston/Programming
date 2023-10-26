#include <iostream>

int64_t BinSrch(int64_t w, int64_t h, int64_t n) {
  int64_t left = 1;
  int64_t right = 0;
  if (w > h) {
    right = w * n;
  } else {
    right = h * n;
  }
  while (right - left > 1) {
    int64_t mid_size = right + (left - right) / 2;
    if (((mid_size / w) * (mid_size / h)) >= n) {
      right = mid_size;
    } else {
      left = mid_size;
    }
  }
  return right;
}

int main() {
  int64_t w;
  int64_t h;
  int64_t n;
  std::cin >> w >> h >> n;
  std::cout << BinSrch(w, h, n);
  return 0;
}