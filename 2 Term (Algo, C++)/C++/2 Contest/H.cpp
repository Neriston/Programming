#include <iostream>
#include <map>
#include <set>

int main() {
  std::string str;
  std::map<std::string, std::map<std::string, int64_t>> map;
  std::set<std::string> names;
  while (std::getline(std::cin, str)) {
    int64_t first_space = str.find(' ');
    int64_t second_space = str.find(' ', first_space + 1);
    std::string name = str.substr(0, first_space);
    names.emplace(name);
    std::string product = str.substr(first_space + 1, second_space - first_space - 1);
    int64_t count = std::stoi(str.substr(second_space + 1));
    map[name][product] += count;
  }
  for (const auto name : names) {
    std::cout << name << ':' << '\n';
    for (const auto product : map[name]) {
      std::cout << product.first << ' ' << product.second << '\n';
    }
  }
  return 0;
}