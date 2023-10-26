#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

bool Comp(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second) {
  if (first.second > second.second) {
    return true;
  }
  if (first.second == second.second) {
    return first.first < second.first;
  }
  return false;
}

int main() {
  std::map<std::string, int> map;
  std::vector<std::pair<std::string, int>> vector;
  std::string str;
  while (std::cin >> str) {
    map[str] += 1;
  }
  for (const auto v : map) {
    vector.emplace_back(std::make_pair(v.first, v.second));
  }
  std::sort(vector.begin(), vector.end(), Comp);
  for (const auto v : vector) {
    std::cout << v.first << '\n';
  }
  return 0;
}