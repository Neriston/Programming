#include <iostream>

void F(int n, int i, bool first = false) {
  if (n > 0) {
    F(n - 1, 1, false);
    std::cout << n * i << ' ';
    if (!first) {
      F(n - 1, -1, false);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = n; i > 0; i -= 2) {
    F(i, 1, true);
  }
}