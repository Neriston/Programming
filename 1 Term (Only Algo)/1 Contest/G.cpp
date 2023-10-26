#include <iostream>

void Swap(int n, int num_1, int num_2) {
  if (n == 1) {
    std::cout << 1 << ' ' << num_1 << ' ' << num_2 << '\n';
  } else {
    Swap(n - 1, num_1, num_2);
    std::cout << n << ' ' << num_1 << ' ' << 6 - num_1 - num_2 << '\n';
    Swap(n - 1, num_2, num_1);
    std::cout << n << ' ' << 6 - num_1 - num_2 << ' ' << num_2 << '\n';
    Swap(n - 1, num_1, num_2);
  }
}

int main() {
  int n;
  std::cin >> n;
  Swap(n, 1, 3);
  return 0;
}