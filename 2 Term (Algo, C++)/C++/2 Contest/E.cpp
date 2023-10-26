#include <iostream>
#include <unordered_map>
#include <string>

int main() {

  int n;
  std::ios_base::sync_with_stdio(false);
  std::cin >> n;
  std::unordered_map<std::string, std::string> map(n);
  for (int i = 0; i < n; ++i) {
    std::string first, second;
    std::cin >> first >> second;
    map[first] = second;
    map[second] = first;
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string syn;
    std::cin >> syn;
    std::cout << map.at(syn) << '\n';
  }
  return 0;
}