#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> table(std::istream_iterator<int>(std::cin), {});
  std::cout << std::count(table.begin(), table.end() - 1, *(table.end() - 1));
  return 0;
}