#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::unordered_map<std::string, int> table;
  for (int i = 0; i < n; ++i) {
    int comm;
    std::string name;
    std::cin >> comm >> name;
    if (comm == 1) {
      int money;
      std::cin >> money;
      if (table.count(name) == 0) {
        table[name] = money;
      } else {
        table[name] += money;
      }
    } else {
      if (table.count(name) == 0) {
        std::cout << "ERROR\n";
      } else {
        std::cout << table[name] << '\n';
      }
    }
  }
  return 0;
}